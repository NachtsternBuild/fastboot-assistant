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
GtkWidget *free_space1;
GtkWidget *free_space2;
GtkWidget *boot_image_file_chooser;
GtkWidget *system_image_file_chooser;
GtkWidget *set_active_slot_checkbox;
GtkWidget *treble_spinner_window;


// get the active slot with adb
char *get_inactive_slot() 
{
    FILE *fp;
    char buffer[128];
    auto_free char *inactive_slot = malloc(4);
    if (!inactive_slot) return NULL; // if malloc won't work

    fp = popen("adb shell getprop ro.boot.slot_suffix", "r");
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
    char *inactive_slot = get_inactive_slot();
    const char *boot_image_path = "~/Downloads/ROM-Install/boot.img";
    const char *system_image_path = "~/Downloads/ROM-Install/system.img";
    char command_build[512];
    
    char *command = execute_command("adb wait-for-device");
	
	// multiple options for the treble updater
	// flash new boot.img
    if (gtk_check_button_get_active(GTK_CHECK_BUTTON(boot_checkbox)))
	{
    	// push image to the device
    	snprintf(command_build, sizeof(command_build), "adb push %s /data/local/tmp/boot.img", boot_image_path);
    	command = execute_command(command_build);
    	
    	// copy the image in the inactive slot
    	// with 'wait' and 'sync' the adb should wait that 'dd' finished
    	snprintf(command_build, sizeof(command_build), "adb shell su -c dd if=/data/local/tmp/boot.img of=/dev/block/by-name/boot%s & PID=$!; wait $PID; sync'", inactive_slot);
    	command = execute_command(command_build);
    	
    	// remove the image in tmp/
    	snprintf(command_build, sizeof(command_build), "adb shell su -c rm -f /data/local/tmp/boot.img");
    	command = execute_command(command_build);
	}

	// flash new system.img
	if (gtk_check_button_get_active(GTK_CHECK_BUTTON(system_checkbox))) 
	{
    	// push image to the device
    	snprintf(command_build, sizeof(command_build), "adb push %s /data/local/tmp/system.img", system_image_path);
    	command = execute_command(command_build);
    	
    	// copy the image in the inactive slot
    	// with 'wait' and 'sync' the adb should wait that 'dd' finished
    	snprintf(command_build, sizeof(command_build), "adb shell su -c 'dd if=/data/local/tmp/system.img of=/dev/block/by-name/system%s & PID=$!; wait $PID; sync'", inactive_slot);
		command = execute_command(command_build);

    	// remove the image in tmp/
    	snprintf(command_build, sizeof(command_build), "adb shell su -c rm -f /data/local/tmp/system.img");
    	command = execute_command(command_build);
	}
	
	// for the security that 
	command = execute_command("adb wait-for-device");
	
	// get the bootctl
	command = execute_command("adb shell su -c bootctl");
	
  	// set the active slot with the bootctl
   	snprintf(command_build, sizeof(command_build), "adb shell su -c bootctl set-active-boot-slot %d", inactive_slot[1] == 'b' ? 0 : 1);
   	command = execute_command(command_build);
    
    // alternative way to set new active slot
    // I won't use this, because using bootctl is better	
   	if (gtk_check_button_get_active(GTK_CHECK_BUTTON(set_active_slot_checkbox)))
   	{
    	snprintf(command_build, sizeof(command_build), "adb shell su -c setprop persist.sys.boot.slot %s", inactive_slot);
    	command = execute_command(command_build);
	}
	        
    // stop the spinner
    gtk_spinner_stop(GTK_SPINNER(treble_spinner));
    gtk_window_destroy(GTK_WINDOW(treble_spinner_window));
    
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
	char *command = execute_command("adb reboot");
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
    
    // label for some free space
    free_space1 = gtk_label_new("  ");
    gtk_box_append(GTK_BOX(vbox), free_space1);
    
    // root status label
    root_status_label = gtk_label_new("Prüfe Root-Rechte...");
    gtk_box_append(GTK_BOX(vbox), root_status_label);
   
    // label for some free space
    free_space2 = gtk_label_new("  ");
    gtk_box_append(GTK_BOX(vbox), free_space2);
    
    // checkbox for boot.img
    boot_checkbox = gtk_check_button_new_with_label("boot.img");
    gtk_box_append(GTK_BOX(vbox), boot_checkbox);
	
	// checkbox for system.img
    system_checkbox = gtk_check_button_new_with_label("system.img");
    gtk_box_append(GTK_BOX(vbox), system_checkbox);
	
	// use option to set active slot with setprop
    set_active_slot_checkbox = gtk_check_button_new_with_label("Alternative für den Slot Wechsel");
    gtk_box_append(GTK_BOX(vbox), set_active_slot_checkbox);
	
	// Start the flash
    start_button = gtk_button_new_with_label("Start Flash");
    gtk_box_append(GTK_BOX(vbox), start_button);
    g_signal_connect(start_button, "clicked", G_CALLBACK(update_device), NULL);
	
	// restart the system
	restarting_system = gtk_button_new_with_label("Neustart");
	gtk_box_append(GTK_BOX(vbox), restarting_system);
	g_signal_connect(restarting_system, "clicked", G_CALLBACK(restart_system), NULL);
	
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show
	
	// check root access at the start
    check_root_access();
	
    // run GTK main loop
    g_main_loop_run(main_loop);
    
    if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
	LOG_INFO("end treble_updater");
}
