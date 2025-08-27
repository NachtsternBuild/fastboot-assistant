/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *       Apache License, Version 2.0         *
 *-------------------------------------------*
 *                                           *
 *  Programm, um das Installieren von        *
 *  Custom-ROMs und GSIs auf Android-Geräte  *
 *  zu erleichtern - updater_devmode         *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz        *
 *-------------------------------------------*
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

// install tools for the build from the fastboot-assistant 
void prepare_build(GtkWidget *widget, gpointer user_data)
{
	install_with_pkexec("apt install gcc libgtk-4-dev adb fastboot desktop-file-utils make dpkg-dev debhelper ccache -y");
	execute_command("ccache -M 5G");
	command_with_spinner("git clone https://github.com/NachtsternBuild/fastboot-assistant.git");
}

// start the build skript in a new terminal
void build_from_source(GtkWidget *widget, gpointer user_data)
{
	char command[2048];
	const char* home_dir = getenv("HOME");
	snprintf(command, sizeof(command), "cd %s/fastboot-assistant/Anwendung", home_dir);
	execute_command(command);
	open_terminal_by_desktop("bash Build/build-fastboot-assistant.sh");
}	

/* main function - devmode_updater */
void updater_devmode(void)
{
    LOG_INFO("devmode_updater");

    gtk_init();
    main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
	   
    const char *confirmation = _("Updater (Dev)");
    GtkWidget *confirmation_window = gtk_window_new();  
    gtk_window_set_title(GTK_WINDOW(confirmation_window), confirmation);

    gtk_window_set_default_size(GTK_WINDOW(confirmation_window), 500, 500);
    g_signal_connect(confirmation_window, "destroy", G_CALLBACK(on_window_destroy), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(confirmation_window), vbox);

    GtkWidget *message_label = gtk_label_new(_("\n\nBuild the Fastboot Assistant from source?\n\n"));
    gtk_box_append(GTK_BOX(vbox), message_label);
    
    GtkWidget *prepare_build_button = gtk_button_new_with_label(_("Prepare Build"));
    gtk_box_append(GTK_BOX(vbox), prepare_build_button);
    
    g_signal_connect(prepare_build_button, "clicked", G_CALLBACK(prepare_build), confirmation_window);
        
    GtkWidget *confirm_button = gtk_button_new_with_label(_("Build Project"));
    gtk_box_append(GTK_BOX(vbox), confirm_button);

    g_signal_connect(confirm_button, "clicked", G_CALLBACK(build_from_source), confirmation_window);
			
    GtkWidget *cancel_button = gtk_button_new_with_label(_("Build later"));
    gtk_box_append(GTK_BOX(vbox), cancel_button);
    g_signal_connect(cancel_button, "clicked", G_CALLBACK(close_window_mainloop), confirmation_window);

    // show all widgets
    gtk_window_present(GTK_WINDOW(confirmation_window)); // gtk_window_present instead of gtk_widget_show 
    
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
	
    LOG_INFO("end devmode_updater");
}
