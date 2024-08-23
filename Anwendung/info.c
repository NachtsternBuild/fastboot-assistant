/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
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
#include "program_functions.h"

// function to check if an android device is connected
int is_android_device_connected() 
{
    char *output = execute_command("adb devices | grep -w 'device'");
    if (output == NULL || strlen(output) == 0) 
    {
        return 0; // No device connected
    }
    return 1; // Device connected
}

// function to get android-device and desktop info
void get_android_info(char *android_version, char *kernel_version, char *device_name, char *project_treble, char *active_slot, char *get_root, char *get_soc, char *get_distro, char *get_version, char *get_desktop, char *get_language, char *get_session_type) 
{
    if (!is_android_device_connected()) 
    {
        g_print("Kein Android-Gerät verbunden.\n");
        return;
    }

    // get android-version
    strcpy(android_version, execute_command("adb shell getprop ro.build.version.release"));
    
    // get kernel-info
    strcpy(kernel_version, execute_command("adb shell uname -r"));
    
    // get devicename
    strcpy(device_name, execute_command("adb shell getprop ro.product.model"));

    // get project-treble support info
    strcpy(project_treble, execute_command("adb shell getprop ro.treble.enabled"));

    // get activ-slot
    strcpy(active_slot, execute_command("adb shell getprop ro.boot.slot_suffix"));
    
    // get superuser
    strcpy(get_root, execute_command("adb shell su -c id"));
        
    // get SoC
    strcpy(get_soc, execute_command("adb shell cat /proc/cpuinfo"));
    
    // get distribution
    strcpy(get_distro, execute_command("grep '^NAME=' /etc/os-release | cut -d'=' -f2 | tr -d ''"));
    
    // get version
    strcpy(get_version, execute_command("grep '^VERSION=' /etc/os-release | cut -d'=' -f2 | cut -d' ' -f1 | tr -d ''"));
    
    // get desktop
    strcpy(get_desktop, execute_command("echo $XDG_CURRENT_DESKTOP"));
    
    // get language
    strcpy(get_language, execute_command("echo $LANG | cut -d'_' -f1"));
    
    // get session type
    strcpy(get_session_type, execute_command("echo $XDG_SESSION_TYPE"));
}

// create function to show info windows
void info(int argc, char *argv[]) 
{
    gtk_init(&argc, &argv);

    // strings for system-info
    char android_version[128] = "Unbekannt";
    char kernel_version[128] = "Unbekannt";
    char device_name[128] = "Unbekannt";
    char project_treble[128] = "Unbekannt";
    char active_slot[128] = "Unbekannt";
    char get_root[255] = "Unbekannt";
    char get_soc[128] = "Unbekannt";
    char get_distro[128] = "Unbekannt";
    char get_version[128] = "Unbekannt";
    char get_desktop[128] = "Unbekannt";
    char get_language[128] = "Unbekannt";
    char get_session_type[128] = "Unbekannt";

    if (!is_android_device_connected()) 
    {
        // create windows
        GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), "Info");
        gtk_widget_set_size_request(window, 400, 200);
        // connect the 'destroy'-function
    	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        GtkWidget *label = gtk_label_new("Kein Android-Gerät verbunden. \nWarte auf Android-Gerät. \nSchließen sie, bitte, das Fenster!");
        gtk_container_add(GTK_CONTAINER(window), label);
        // show everything
        gtk_widget_show_all(window);
        // start gtk mainloop
        gtk_main();
        return;
    }
	
	// get all infos
    get_android_info(android_version, kernel_version, device_name, project_treble, active_slot, get_root, get_soc, get_distro, get_version, get_desktop, get_language, get_session_type);

    // create gtk-main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Info");
    gtk_widget_set_size_request(window, 700, 600);

    // connect the 'destroy'-function
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // frame at the box
    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(window), frame);

    // create vbox
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(frame), vbox);
    
    // show-text
    GtkWidget *info1_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info1_label), g_strdup_printf("<b><u> Android-Info: </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), info1_label);

    // android-label
    GtkWidget *android_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(android_label), g_strdup_printf("<b>Android-Version:</b> %s", android_version));
    gtk_container_add(GTK_CONTAINER(vbox), android_label);
    
    // kernel-label
    GtkWidget *kernel_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(kernel_label), g_strdup_printf("<b>Kernel-Version:</b> %s", kernel_version));
    gtk_container_add(GTK_CONTAINER(vbox), kernel_label);
    
    // devicename-label 
    GtkWidget *devicename_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(devicename_label), g_strdup_printf("<b>Gerätname:</b> %s", device_name));
    gtk_container_add(GTK_CONTAINER(vbox), devicename_label);

    // project-treble-support-label
    GtkWidget *treble_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(treble_label), g_strdup_printf("<b>Project Treble:</b> %s", project_treble));
    gtk_container_add(GTK_CONTAINER(vbox), treble_label);

    // activ-slot-label
    GtkWidget *slot_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(slot_label), g_strdup_printf("<b>Aktiver Slot:</b> %s", active_slot));
    gtk_container_add(GTK_CONTAINER(vbox), slot_label);
    
    // check for superuser
    GtkWidget *get_root_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(get_root_label), g_strdup_printf("<b>Root-Rechte verfügbar:</b> %s", get_root));
    gtk_container_add(GTK_CONTAINER(vbox), get_root_label);
    
    // SoC-label
    GtkWidget *soc_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(soc_label), g_strdup_printf("<b>System-on-Chip:</b> %s", get_soc));
    gtk_container_add(GTK_CONTAINER(vbox), soc_label);

    // show-text
    GtkWidget *info2_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(info2_label), g_strdup_printf("<b><u> Computer-Info: </u></b>"));
    gtk_container_add(GTK_CONTAINER(vbox), info2_label);
    
    // Distro-label
    GtkWidget *distro_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(distro_label), g_strdup_printf("<b>Distribuation:</b> %s", get_distro));
    gtk_container_add(GTK_CONTAINER(vbox), distro_label);
    
    // Version-label
    GtkWidget *version_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(version_label), g_strdup_printf("<b>Version:</b> %s", get_version));
    gtk_container_add(GTK_CONTAINER(vbox), version_label);
    
    // Desktop-label
    GtkWidget *desktop_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(desktop_label), g_strdup_printf("<b>Desktop:</b> %s", get_desktop));
    gtk_container_add(GTK_CONTAINER(vbox), desktop_label);
    
    // Language-label
    GtkWidget *language_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(language_label), g_strdup_printf("<b>Sprache:</b> %s", get_language));
    gtk_container_add(GTK_CONTAINER(vbox), language_label);
    
    // Session-type-label
    GtkWidget *session_type_label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(session_type_label), g_strdup_printf("<b>Session Typ:</b> %s", get_session_type));
    gtk_container_add(GTK_CONTAINER(vbox), session_type_label);

    // show all elements
    gtk_widget_show_all(window);

    // GTK-mainloop start
    gtk_main();
}
