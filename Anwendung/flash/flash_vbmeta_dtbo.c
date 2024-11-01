/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - flash_vbmeta_dtbo		 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"
#include "flash_function_header.h"

// Button handler functions
// function to flash vbmeta.img on only-a-devices
void vbmeta_on_a(GtkWidget *widget, GtkWindow *window)
{
    g_print("Log: vbmeta_on_a\n");
    char image_path[3072];
    set_main_dir_with_wsl(image_path, sizeof(image_path), "vbmeta.img");

    char function_command[3072];
    char *device_command = fastboot_command();
    snprintf(function_command, sizeof(function_command), "%s flash --disable-verity --disable-verification vbmeta %s && exit", device_command, image_path);
    g_print("Log: Run: %s", function_command);
    open_terminal_by_desktop(function_command);
    free(device_command);
    g_print("Log: end vbmeta_on_a\n");
}

// function to flash vbmeta.img (a/b-devices)
void vbmeta_on_ab(GtkWidget *widget, GtkWindow *window)
{
    g_print("Log: vbmeta_on_ab\n");
    char image_path[3072];
    set_main_dir_with_wsl(image_path, sizeof(image_path), "vbmeta.img");

    char function_command[3072];
    char *device_command = fastboot_command();
    snprintf(function_command, sizeof(function_command), "%s flash --disable-verity --disable-verification vbmeta_a %s && fastboot flash --disable-verity --disable-verification vbmeta_b %s && exit", device_command, image_path, image_path);
    g_print("Log: Run: %s", function_command);
    open_terminal_by_desktop(function_command);
    free(device_command);
    g_print("Log: end vbmeta_on_ab\n");
}

// function to flash dtbo.img (only-a-devices)
void dtbo_on_a(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "dtbo", NULL, "dtbo.img");
}

// function to flash dtbo.img (a/b-devices)
void dtbo_on_ab(GtkWidget *widget, GtkWindow *window)
{
    flash_image(widget, window, "dtbo_a", "dtbo_b", "dtbo.img");
}

// function to flash vbmeta.img (heimdall)
void vbmeta_img_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "VBMETA", "vbmeta.img");
}

// function to flash dtbo.img (heimdall)
void dtbo_heimdall(GtkWidget *widget, GtkWindow *window)
{
    flash_heimdall(widget, window, "DTBO", "dtbo.img");
}

// main function
void flash_vbmeta_dtbo(int argc, char *argv[])
{
	g_print("Log: flash_vbmeta_dtbo\n");
	GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[6][30] = {"vbmeta (only-a)", "vbmeta (a/b)", "vbmeta (heimdall)", 
                                 "dtbo (only-a)", "dtbo (a/b)", "dtbo (heimdall)"};

    gtk_init(&argc, &argv);
    apply_theme();

     // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Flash:");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
    // create the grid and centre it
    grid = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    // add the grid to the window
    gtk_container_add(GTK_CONTAINER(window), grid);

    // add and centre all button
    for (int i = 0; i < 6; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);

        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(vbmeta_on_a), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(vbmeta_on_ab), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(vbmeta_img_heimdall), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(dtbo_on_a), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(dtbo_on_ab), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(dtbo_heimdall), NULL);
                break;
        }
    }
    
    // clean the storage
    g_object_unref(provider);
    
    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
    g_print("Log: end flash_vbmeta_dtbo\n");
}
