/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              treble_updater				 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include "language_check.h"
#include "program_functions.h"

GtkWidget *start_button;
GtkWidget *boot_checkbox;
GtkWidget *system_checkbox;
GtkWidget *treble_spinner;
GtkWidget *restarting_system;
GtkWidget *root_status_label;
GtkWidget *bootctl_status_label;
GtkWidget *free_space1;
GtkWidget *free_space2;
GtkWidget *boot_image_file_chooser;
GtkWidget *system_image_file_chooser;
GtkWidget *set_active_slot_checkbox;
GtkWidget *treble_spinner_window;
GtkWidget *info_treble;
GtkWidget *info2_treble;


// get the active slot with adb
char *get_inactive_slot() 
{
    FILE *fp;
    char slot_command[2048];
    char buffer[128];
    auto_free char *inactive_slot = malloc(4);
    auto_free char *device_command = adb_command();
    if (!inactive_slot) return NULL; // if malloc won't work
	
	snprintf(slot_command, sizeof(slot_command), "%s shell getprop ro.boot.slot_suffix", device_command);
	
    fp = popen(slot_command, "r");
    if (!fp) 
    {
        LOG_ERROR("Error: Unable to get current slot.\n");
        return NULL;
    }

    if (fgets(buffer, sizeof(buffer), fp) != NULL) 
    {
        if (strstr(buffer, "_a")) 
            strcpy(inactive_slot, "_b");
        else if (strstr(buffer, "_b")) 
            strcpy(inactive_slot, "_a");
        else 
        {
            inactive_slot = NULL;
        }
    }

    pclose(fp);
    return inactive_slot;
}

// function that flash the images in the inactive slot and set a new active slot
void *flash_thread_func(void *arg) 
{      
    char config_file[4096];
    char boot_image[4096];
    char system_image[4096];
    char command_build[4096];
    const char *boot_image_name = "boot.img";
	const char *system_image_name = "system.img";
	
    // get the inactive slot
    char *inactive_slot = get_inactive_slot();
    // get the adb command
    auto_free char *device_command = adb_command();
    // get the config file
    get_config_file_path(config_file, sizeof(config_file));
    // load the path
    const char *image_path = load_path_from_file(config_file);

    if (image_path) 
    {
        LOG_INFO("Loaded path: %s", image_path);
    }
	
	// create the path from the images
	snprintf(boot_image, sizeof(boot_image), "%s/%s", image_path, boot_image_name);
	snprintf(system_image, sizeof(system_image), "%s/%s", image_path, system_image_name);
    
    // wait for a device
    snprintf(command_build, sizeof(command_build), "%s wait-for-device", device_command);
    char *command = execute_command(command_build);
	
	// multiple options for the treble updater
	// flash new boot.img
    if (gtk_check_button_get_active(GTK_CHECK_BUTTON(boot_checkbox)))
	{
    	// push image to the device
    	snprintf(command_build, sizeof(command_build), "%s push %s /data/local/tmp/boot.img", device_command, boot_image);
    	command = execute_command(command_build);
    	
    	// copy the image in the inactive slot
    	// with 'wait' and 'sync' the adb should wait that 'dd' finished
    	snprintf(command_build, sizeof(command_build), "%s shell su -c dd if=/data/local/tmp/boot.img of=/dev/block/by-name/boot%s & PID=$!; wait $PID; sync'", device_command, inactive_slot);
    	command = execute_command(command_build);
    	
    	// remove the image in tmp/
    	snprintf(command_build, sizeof(command_build), "%s shell su -c rm -f /data/local/tmp/boot.img", device_command);
    	command = execute_command(command_build);
	}

	// flash new system.img
	if (gtk_check_button_get_active(GTK_CHECK_BUTTON(system_checkbox))) 
	{
    	// push image to the device
    	snprintf(command_build, sizeof(command_build), "%s push %s /data/local/tmp/system.img", device_command, system_image);
    	command = execute_command(command_build);
    	
    	// copy the image in the inactive slot
    	// with 'wait' and 'sync' the adb should wait that 'dd' finished
    	snprintf(command_build, sizeof(command_build), "%s shell su -c 'dd if=/data/local/tmp/system.img of=/dev/block/by-name/system%s & PID=$!; wait $PID; sync'", device_command, inactive_slot);
		command = execute_command(command_build);

    	// remove the image in tmp/
    	snprintf(command_build, sizeof(command_build), "%s shell su -c rm -f /data/local/tmp/system.img", device_command);
    	command = execute_command(command_build);
	}
	
	// for the security that adb is ready
	snprintf(command_build, sizeof(command_build), "%s wait-for-device", device_command);
	command = execute_command(device_command);
	
	// get the bootctl
	snprintf(command_build, sizeof(command_build), "%s shell su -c bootctl", device_command);
	command = execute_command(command_build);
	
  	// set the active slot with the bootctl
   	snprintf(command_build, sizeof(command_build), "%s shell su -c bootctl set-active-boot-slot %d", device_command, inactive_slot[1] == 'b' ? 0 : 1);
   	command = execute_command(command_build);
    
    // alternative way to set new active slot
    // I won't use this, because using bootctl is better	
   	if (gtk_check_button_get_active(GTK_CHECK_BUTTON(set_active_slot_checkbox)))
   	{
    	snprintf(command_build, sizeof(command_build), "%s shell su -c setprop persist.sys.boot.slot %s", device_command, inactive_slot);
    	command = execute_command(command_build);
	}
	        
    // stop the spinner
    gtk_spinner_stop(GTK_SPINNER(treble_spinner));
    gtk_window_destroy(GTK_WINDOW(treble_spinner_window));
    
    if (image_path != NULL) 
	{
    	g_free((gpointer)image_path); // free this (because g_file_get_contents was used)
    	// I'll try to create a autofree for g_free and this to
	}
    
    return NULL;
}

// function that create the window for the spinner and run all commands in the background
void update_device(GtkWidget *widget, gpointer user_data) 
{
    LOG_INFO("Start the Update via ADB");
    // window for the spinner
    treble_spinner_window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(treble_spinner_window), " ");
    gtk_window_set_default_size(GTK_WINDOW(treble_spinner_window), 200, 200);

    // create a spinner
    treble_spinner = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), treble_spinner);
    gtk_widget_set_size_request(treble_spinner, 150, 150);
    gtk_window_set_child(GTK_WINDOW(treble_spinner_window), vbox);
	
    // start the spinner
    gtk_spinner_start(GTK_SPINNER(treble_spinner));

    // make the window visible using gtk_window_present
    gtk_window_present(GTK_WINDOW(treble_spinner_window));

    // use new thread to flash the images
    pthread_t flash_thread;
    pthread_create(&flash_thread, NULL, flash_thread_func, NULL);
    pthread_detach(flash_thread);
}

// function to reboot use 'adb reboot'
void restart_system(GtkWidget *widget, gpointer user_data)
{
	LOG_INFO("Restart with ADB");
	char command_build[2048];
	auto_free char *device_command = adb_command();
	
	snprintf(command_build, sizeof(command_build), "%s reboot", device_command);
	char *command = execute_command(command_build);
}

/* main function - treble_updater */
void treble_updater(int argc, char *argv[]) 
{
    LOG_INFO("treble_updater");
    gtk_init();
    
    apply_theme();
    apply_language();
    main_loop = g_main_loop_new(NULL, FALSE);
	
	// create a new window for the treble updater
    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Treble Updater");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(window), vbox);
    
    info_treble = gtk_label_new(g_strcmp0(language, "de") == 0 ? "\nDer Treble Updater funktioniert nur mit a/b-Geräten. \nEs müssen Root-Rechte bereitgestellt werden.\n" : "\nThe Treble Updater only works with a/b devices. \nRoot rights must be provided.\n");
    info2_treble = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Der Treble Updater hat die Aufgabe ein neues Boot/System-Image \nin den inaktiven Slot zu flashen und \ndiesen aktiv zusetzen.\n" : "The Treble Updater has the task of flashing \na new boot/system image into the inactive slot \nand making it active.\n");
    
    // label for some free space
    free_space1 = gtk_label_new("  ");
    gtk_box_append(GTK_BOX(vbox), free_space1);
    
    // root status label
    root_status_label = gtk_label_new("Check Root permission...");
    gtk_box_append(GTK_BOX(vbox), root_status_label);
    
    // bootctl status label
    bootctl_status_label = gtk_label_new("Search for bootctl...");
    gtk_box_append(GTK_BOX(vbox), bootctl_status_label);
    
    // label for some free space
    free_space2 = gtk_label_new("  ");
    gtk_box_append(GTK_BOX(vbox), free_space2);
    
    // checkbox for boot.img
    boot_checkbox = gtk_check_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Flashe neues Boot-Image" : "Flash new boot image");
    gtk_box_append(GTK_BOX(vbox), boot_checkbox);
	
	// checkbox for system.img
    system_checkbox = gtk_check_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Flashe neues System-Image" : "Flash new system image");
    gtk_box_append(GTK_BOX(vbox), system_checkbox);
	
	// use option to set active slot with setprop
    set_active_slot_checkbox = gtk_check_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Alternative für Slotwechsel (nicht empfohlen)" : "Alternative for slot change (not recommended)");
    gtk_box_append(GTK_BOX(vbox), set_active_slot_checkbox);
	
	// Start the flash
    start_button = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Starte Flash" : "Start Flash");
    gtk_box_append(GTK_BOX(vbox), start_button);
    g_signal_connect(start_button, "clicked", G_CALLBACK(update_device), NULL);
	
	// restart the system
	restarting_system = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Neustarten" : "Reboot Device");
	gtk_box_append(GTK_BOX(vbox), restarting_system);
	g_signal_connect(restarting_system, "clicked", G_CALLBACK(restart_system), NULL);
	
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show
	
	// check root access at the start
    check_root_access();
    // chech for android bootctl
    get_bootctl();
	
    // run GTK main loop
    g_main_loop_run(main_loop);
    
    if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
	LOG_INFO("end treble_updater");
}
