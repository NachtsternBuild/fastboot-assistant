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
	g_print("Log: flash_boot\n");
	GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[6][30] = {"Boot (only-a)", "Boot (a/b)", "Boot (heimdall)", 
                                 "init_boot (only-a)", "init_boot (a/b)", "init_boot (heimdall)"};

    gtk_init(&argc, &argv);
    apply_theme();

     // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Flashen:");
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
                g_signal_connect(button, "clicked", G_CALLBACK(boot_on_a), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(boot_on_ab), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(boot_heimdall), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(init_boot_on_a), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(init_boot_on_ab), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(init_boot_heimdall), NULL);
                break;
        }
    }
    
    // clean the storage
    g_object_unref(provider);
    
    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
    g_print("Log: end flash_boot\n");
}
