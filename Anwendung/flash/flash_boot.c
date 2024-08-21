/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_boot				 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "flash_function_header.h"

// Button-Handler-Funktionen
// function to flash boot.img on only-a-devices
void boot_on_a(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "boot", NULL, "boot.img");
}

// function to flash boot.img (a/b-devices)
void boot_on_ab(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "boot_a", "boot_b", "boot.img");
}

// function to flash init_boot.img (only-a-devices)
void init_boot_on_a(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "init_boot", NULL, "init_boot.img");
}

// function to flash init_boot.img (a/b-devices)
void init_boot_on_ab(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "init_boot_a", "init_boot_b", "init_boot.img");
}

// function to flash boot.img (heimdall)
void boot_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "BOOT", "boot.img");
}

// function to flash init_boot.img (heimdall)
void init_boot_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "INIT_BOOT", "init_boot.img");
}

// main function
void flash_boot(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    
    // create a windows
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Flash Boot");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // create button
    GtkWidget *button_boot_on_a = gtk_button_new_with_label("Flash Boot (only-a-devices)");
    GtkWidget *button_boot_on_ab = gtk_button_new_with_label("Flash Boot (a/b-devices)");
    GtkWidget *button_init_boot_on_a = gtk_button_new_with_label("Flash init_boot (only-a-devices)");
    GtkWidget *button_init_boot_on_ab = gtk_button_new_with_label("Flash init_boot (a/b-devices)");
    GtkWidget *button_boot_heimdall = gtk_button_new_with_label("Flash boot (heimdall)");
    GtkWidget *button_init_boot_heimdall= gtk_button_new_with_label("Flash init_boot (heimdall)");
    
    // Verknüpfung der Click-Callback-Funktion mit den Buttons
	g_signal_connect(button_boot_on_a, "clicked", G_CALLBACK(boot_on_a), (gpointer) window);
	g_signal_connect(button_boot_on_ab, "clicked", G_CALLBACK(boot_on_ab), (gpointer) window);
	g_signal_connect(button_init_boot_on_a, "clicked", G_CALLBACK(init_boot_on_a), (gpointer) window);
	g_signal_connect(button_init_boot_on_ab, "clicked", G_CALLBACK(init_boot_on_ab), (gpointer) window);
	g_signal_connect(button_boot_heimdall, "clicked", G_CALLBACK(boot_heimdall), (gpointer) window);
	g_signal_connect(button_init_boot_heimdall, "clicked", G_CALLBACK(init_boot_heimdall), (gpointer) window);

    
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    gtk_box_pack_start(GTK_BOX(left_vbox), button_boot_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_boot_on_ab, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_boot_heimdall, TRUE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(right_vbox), button_init_boot_on_a, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_init_boot_on_ab, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_init_boot_heimdall, TRUE, TRUE, 0);
    
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), hbox);
    
    gtk_widget_show_all(window);
    
    gtk_main();
}

