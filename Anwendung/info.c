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
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              info						 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

// check if device are connected
int is_android_device_connected() 
{
    char *info_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s devices | grep -w 'device'", info_command);
    
    char *output = execute_command(command);
    free(info_command);  // clean memory

    if (output == NULL || strlen(output) == 0) 
    {
        return 0;  // no device
    }
    return 1;  // device
}

// create function to show info windows
void get_android_info(char *android_version, char *kernel_version, char *device_name, char *project_treble, char *active_slot, char *get_root, char *get_soc, char *get_distro, char *get_version, char *get_desktop, char *get_language, char *get_session_type) 
{
    if (!is_android_device_connected()) 
    {
        g_print("Log: No Android device connected.\n");
        return;
    }

    char *info_command = adb_command();

    // android version
    snprintf(android_version, 2048, "%s", execute_command(g_strdup_printf("%s shell getprop ro.build.version.release", info_command)));
    
    // android kernel version
    snprintf(kernel_version, 2048, "%s", execute_command(g_strdup_printf("%s shell uname -r", info_command)));

    // device name
    snprintf(device_name, 2048, "%s", execute_command(g_strdup_printf("%s shell getprop ro.product.model", info_command)));

    // project treble support
    snprintf(project_treble, 2048, "%s", execute_command(g_strdup_printf("%s shell getprop ro.treble.enabled", info_command)));

    // get active slot
    snprintf(active_slot, 2048, "%s", execute_command(g_strdup_printf("%s shell getprop ro.boot.slot_suffix", info_command)));
    
    // check for root
    snprintf(get_root, 2048, "%s", execute_command(g_strdup_printf("%s shell su -c id", info_command)));
    
    // soc info
    snprintf(get_soc, 2048, "%s", execute_command(g_strdup_printf("%s shell cat /proc/cpuinfo", info_command)));

    free(info_command);  // clean memory

    // get other infos 
    snprintf(get_distro, 2048, "%s", execute_command("grep '^NAME=' /etc/os-release | cut -d'=' -f2 | tr -d '\"'"));
    snprintf(get_version, 2048, "%s", execute_command("grep '^VERSION=' /etc/os-release | cut -d'=' -f2 | cut -d' ' -f1 | tr -d '\"'"));
    snprintf(get_desktop, 2048, "%s", execute_command("echo $XDG_CURRENT_DESKTOP"));
    snprintf(get_language, 2048, "%s", execute_command("echo $LANG | cut -d'_' -f1"));
    snprintf(get_session_type, 2048, "%s", execute_command("echo $XDG_SESSION_TYPE"));
}

/* the main function from info */
void info(int argc, char *argv[], GtkWindow *parent_window) 
{  
	LOG_INFO("info");
	gtk_init();
	main_loop = g_main_loop_new(NULL, FALSE);
	apply_theme();

    apply_language();

    // Define labels based on the selected language
    const char *android_info_title = strcmp(language, "de") == 0 ? "Android-Info:" : "Android Info:";
    const char *android_version_label = strcmp(language, "de") == 0 ? "Android-Version: " : "Android Version: ";
    const char *kernel_version_label = strcmp(language, "de") == 0 ? "Kernel-Version: " : "Kernel Version: ";
    const char *device_name_label = strcmp(language, "de") == 0 ? "Gerätename: " : "Device Name: ";
    const char *project_treble_label = strcmp(language, "de") == 0 ? "Project Treble: " : "Project Treble: ";
    const char *active_slot_label = strcmp(language, "de") == 0 ? "Aktiver Slot: " : "Active Slot: ";
    const char *root_access_label = strcmp(language, "de") == 0 ? "Root-Rechte verfügbar: " : "Root Access: ";
    const char *soc_label = strcmp(language, "de") == 0 ? "System-on-Chip: " : "<b>System-on-Chip: ";
    const char *computer_info_title = strcmp(language, "de") == 0 ? "Computer-Info:" : "Computer Info:";
    const char *distro_label = strcmp(language, "de") == 0 ? "Distribution: " : "Distribution: ";
    const char *version_label = strcmp(language, "de") == 0 ? "Version: " : "Version: ";
    const char *desktop_label = strcmp(language, "de") == 0 ? "Desktop: " : "Desktop: ";
    const char *language_label = strcmp(language, "de") == 0 ? "Sprache: " : "Language: ";
    const char *session_type_label = strcmp(language, "de") == 0 ? "Session Typ: " : "Session Type: ";
    
     if (!is_android_device_connected()) 
    {      
        char error_message[1024];
        snprintf(error_message, sizeof(error_message), "No device!");
        show_error_message(GTK_WIDGET(parent_window), error_message);
        return;
    }
	
	// safe memory for the infos
	// declare them as char
    char android_version[2048] = {0};
    char kernel_version[2048] = {0};
    char device_name[2048] = {0};
    char project_treble[2048] = {0};
    char active_slot[2048] = {0};
    char get_root[2048] = {0};
    char get_soc[2048] = {0};
    char get_distro[2048] = {0};
    char get_version[2048] = {0};
    char get_desktop[2048] = {0};
    char get_language[2048] = {0};
    char get_session_type[2048] = {0};
    
    // Get all infos
    get_android_info(android_version, kernel_version, device_name, project_treble, active_slot, get_root, get_soc, get_distro, get_version, get_desktop, get_language, get_session_type);


    // create a window
    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Info");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);
    add_css_provider(GTK_WIDGET(window), provider); // Apply CSS

    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_window_set_child(GTK_WINDOW(window), scrolled_window);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), box);

    // labels and add them to the window
    GtkWidget *info1_label = gtk_button_new_with_label(android_info_title);
    gtk_box_append(GTK_BOX(box), info1_label);
	
	// android-version	
    GtkWidget *android_label = gtk_label_new(g_strdup_printf("%s%s", android_version_label, android_version));
    gtk_box_append(GTK_BOX(box), android_label);
	
	// kernel-version
    GtkWidget *kernel_label = gtk_label_new(g_strdup_printf("%s%s", kernel_version_label, kernel_version));
    gtk_box_append(GTK_BOX(box), kernel_label);
	
	// device-name 
    GtkWidget *device_label = gtk_label_new(g_strdup_printf("%s%s", device_name_label, device_name));
    gtk_box_append(GTK_BOX(box), device_label);
	
	// project treble support
    GtkWidget *treble_label = gtk_label_new(g_strdup_printf("%s%s", project_treble_label, project_treble));
    gtk_box_append(GTK_BOX(box), treble_label);
	
	// get the active slot
    GtkWidget *slot_label = gtk_label_new(g_strdup_printf("%s%s", active_slot_label, active_slot));
    gtk_box_append(GTK_BOX(box), slot_label);
	
	// get info for root
    GtkWidget *root_label = gtk_label_new(g_strdup_printf("%s%s", root_access_label, get_root));
    gtk_box_append(GTK_BOX(box), root_label);
	
	// get the SoC info
    GtkWidget *soc_info_label = gtk_label_new(g_strdup_printf("%s%s", soc_label, get_soc));
    gtk_box_append(GTK_BOX(box), soc_info_label);

    GtkWidget *info2_label = gtk_button_new_with_label(computer_info_title);
    gtk_box_append(GTK_BOX(box), info2_label);
	
	// get the distro
    GtkWidget *distro_info_label = gtk_label_new(g_strdup_printf("%s%s", distro_label, get_distro));
    gtk_box_append(GTK_BOX(box), distro_info_label);
	
	// get the distro version
    GtkWidget *version_info_label = gtk_label_new(g_strdup_printf("%s%s", version_label, get_version));
    gtk_box_append(GTK_BOX(box), version_info_label);
	
	// get desktop
    GtkWidget *desktop_info_label = gtk_label_new(g_strdup_printf("%s%s", desktop_label, get_desktop));
    gtk_box_append(GTK_BOX(box), desktop_info_label);
	
	// get the language
    GtkWidget *language_info_label = gtk_label_new(g_strdup_printf("%s%s", language_label, get_language));
    gtk_box_append(GTK_BOX(box), language_info_label);
	
	// get the session type of the desktop
    GtkWidget *session_type_info_label = gtk_label_new(g_strdup_printf("%s%s", session_type_label, get_session_type));
    gtk_box_append(GTK_BOX(box), session_type_info_label);

    // show all widgets
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
    
    // free the provider
    if (provider != NULL) 
    {
    	g_object_unref(provider);
    	provider = NULL;
	}

	if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
    LOG_INFO("end info");
}
