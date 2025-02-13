/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von 		 *
 *  Custom-ROM und GSIs auf Android-Geräte 	 *
 *  zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz	 	 *
 *-------------------------------------------*
 *									 		 *
 *              info_tools				 	 *
 *									 		 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

// function to get the package 
void get_package_status(const char *command, char *output, size_t size, gboolean *is_installed) 
{
    FILE *fp = popen(command, "r");
    if (fp == NULL) 
    {
        snprintf(output, size, "Error: Unable to fetch version");
        *is_installed = FALSE;
        return;
    }

    if (fgets(output, size, fp) != NULL) 
    {
        strtok(output, "\n"); // remove linbreak
        *is_installed = TRUE;
    } 
    
    else 
    {
        snprintf(output, size, "Not Installed");
        *is_installed = FALSE;
    }

    pclose(fp);
}

/* main function - info_tools */
void info_tools(int argc, char *argv[], GtkWindow *parent_window) 
{  
    LOG_INFO("info_tools");
    gtk_init();
    main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    
    char versions[12][2048] = {0};
    char informations[15][2048] = {0};
    gboolean is_installed[12] = {FALSE};

    // define labels 
    const char *version_info_title = strcmp(language, "de") == 0 ? "System- und Paket-Informationen" : "System and Package Informations";
    const char *system_infos = strcmp(language, "de") == 0 ? "System-Informationen:" : "System and Package Informations:";
    const char *version_package = strcmp(language, "de") == 0 ? "Paket-Informationen:" : "Package Informations:";
	
	// commands for system informations
    const char *commands_system[] = {
        "grep '^NAME=' /etc/os-release | cut -d'=' -f2 | tr -d '\"'",
        "grep '^VERSION=' /etc/os-release | cut -d'=' -f2 | cut -d' ' -f1 | tr -d '\"'",
        "uname -r",
        "lscpu | grep \"Modellname:\"",
        "lspci | grep -E \"VGA|3D|Display\" | awk -F: '{print $3}' | sed 's/^ *//'",
        "echo $XDG_CURRENT_DESKTOP",
        "echo $LANG | cut -d'_' -f1",
        "echo $XDG_SESSION_TYPE",
    };
    
	// labels for system informations
    const char *labels_system[] = {
        strcmp(language, "de") == 0 ? "Distribution: " : "Distribution: ",
        strcmp(language, "de") == 0 ? "Version: " : "Version: ",
        strcmp(language, "de") == 0 ? "Kernel-Version: " : "Kernel-Version: ",
        strcmp(language, "de") == 0 ? "Prozessor: " : "Processor: ",
        strcmp(language, "de") == 0 ? "Grafikkarte: " : "Graphics card: ",
        strcmp(language, "de") == 0 ? "Desktop: " : "Desktop: ",
        strcmp(language, "de") == 0 ? "Sprache: " : "Language: ",
        strcmp(language, "de") == 0 ? "Session: " : "Session: ",
    };

    // commands for the packages
    const char *commands_packages[] = {
        "which adb",
        "which fastboot",
        "which xz",
        "which unzip",
        "which zip",
        "which wget",
        "which curl",
        "which pkexec",
        "which heimdall",
        "which gtk4-demo",
        "which ls",
        "which ldd",
    };
	
	// lables for the packages
    const char *labels_packages[] = {
        strcmp(language, "de") == 0 ? "ADB: " : "ADB: ",
        strcmp(language, "de") == 0 ? "Fastboot: " : "Fastboot: ",
        strcmp(language, "de") == 0 ? "XZ-Utils: " : "XZ Utils: ",
        strcmp(language, "de") == 0 ? "Unzip: " : "Unzip: ",
        strcmp(language, "de") == 0 ? "Zip: " : "Zip: ",
        strcmp(language, "de") == 0 ? "Wget: " : "Wget: ",
        strcmp(language, "de") == 0 ? "Curl: " : "Curl: ",
        strcmp(language, "de") == 0 ? "Pkexec: " : "Pkexec: ",
        strcmp(language, "de") == 0 ? "Heimdall: " : "Heimdall: ",
        strcmp(language, "de") == 0 ? "GTK+: " : "GTK+: ",
        strcmp(language, "de") == 0 ? "Coreutils: " : "Coreutils: ",
        strcmp(language, "de") == 0 ? "Libc6: " : "Libc6: ",
    };
    
    // function to get the infos
    for (int i = 0; i < 8; i++) 
    {
        get_package_status(commands_system[i], informations[i], sizeof(informations[i]), &is_installed[i]);
    }
    
    // function to get the installed packages
    for (int i = 0; i < 12; i++) 
    {
        get_package_status(commands_packages[i], versions[i], sizeof(versions[i]), &is_installed[i]);
    }

    // create a window
    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), version_info_title);
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);

    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_window_set_child(GTK_WINDOW(window), scrolled_window);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), box);
	
	// system informations
	GtkWidget *system_info_title_label = gtk_button_new_with_label(system_infos);
    gtk_box_append(GTK_BOX(box), system_info_title_label);
    
    GtkWidget *assistant_version_label = gtk_button_new_with_label("Fastboot-Assistant: v.0.7.1");
    gtk_box_append(GTK_BOX(box), assistant_version_label);

    // add system info labels to the window
    for (int i = 0; i < 8; i++) 
    {
        GtkWidget *label = gtk_label_new(g_strdup_printf("%s%s", labels_system[i], informations[i]));
        gtk_box_append(GTK_BOX(box), label);
    }
	
	// packages versions
    GtkWidget *version_title_label = gtk_button_new_with_label(version_package);
    gtk_box_append(GTK_BOX(box), version_title_label);
    
    // add version info labels to the window
    // packageinforamtions with labels
    for (int i = 0; i < 12; i++) 
    {
        const char *checkmark = is_installed[i] ? "✅ " : "❌ ";
        GtkWidget *label = gtk_label_new(g_strdup_printf("%s%s%s", checkmark, labels_packages[i], versions[i]));
        gtk_box_append(GTK_BOX(box), label);
    }
	
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

    LOG_INFO("end info_tools");
}

