/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - partitions				 *
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
#include "function_header.h"

#define MAX_BUFFER_SIZE 256
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400
// Callback functions for each button
// remove the boot partition
static void remove_boot(GtkWidget *widget, gpointer data) 
{
    const char *message = "Achtung:\nManche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n";
    // show message
    show_message(message);
    
    open_terminal_by_desktop("fastboot delete-logical-partition boot_a && fastboot delete-logical-partition boot_b && exit");
    
    const char *message2 = "Fertig!\n";
    // show message
    show_message(message2);
}

// remove the vendor partition
static void remove_vendor(GtkWidget *widget, gpointer data) 
{
    const char *message = "Achtung:\nManche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n";
    // show message
    show_message(message);
    
    open_terminal_by_desktop("fastboot delete-logical-partition vendor_a && fastboot delete-logical-partition vendor_b && exit");
    
    const char *message2 = "Fertig!\n";
    // show message
    show_message(message2);
}

// remove the system partition
static void remove_system(GtkWidget *widget, gpointer data) 
{
    const char *message = "Achtung:\nManche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n";
    // show message
    show_message(message);
    
    open_terminal_by_desktop("fastboot delete-logical-partition system_a && fastboot delete-logical-partition system_b && exit");
    
    const char *message2 = "Fertig!\n";
    // show message
    show_message(message2);
}

// resize of the boot partition
static void resize_boot(GtkWidget *widget, gpointer data) 
{
    const char *message = "Achtung:\nManche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n";
    // show message
    show_message(message);
    
    open_terminal_by_desktop("fastboot resize-logical-partition boot_a 400000000 && fastboot resize-logical-partition boot_b 400000000 && exit");
    
    const char *message2 = "Fertig!\n";
    // show message
    show_message(message2);
}

// resize of the vendor partition
static void resize_vendor(GtkWidget *widget, gpointer data) 
{
    const char *message = "Achtung:\nManche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n";
    // show message
    show_message(message);
    
    open_terminal_by_desktop("fastboot resize-logical-partition vendor_a 900000000 && fastboot resize-logical-partition vendor_b 900000000 && exit");
    
    const char *message2 = "Fertig!\n";
    // show message
    show_message(message2);
}

// resize of the system partition
static void resize_system(GtkWidget *widget, gpointer data) 
{
    const char *message = "Achtung:\nManche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n";
    // show message
    show_message(message);
    
    open_terminal_by_desktop("fastboot resize-logical-partition system_a 7500000000 && fastboot resize-logical-partition system_b 7500000000 && exit");
    
    const char *message2 = "Fertig!\n";
    // show message
    show_message(message2);
}

// create boot partition
static void create_boot(GtkWidget *widget, gpointer data) 
{
    const char *message = "Achtung:\nManche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n";
    // show message
    show_message(message);
    
    open_terminal_by_desktop("fastboot create-logical-partition boot_a 400000000 && fastboot create-logical-partition boot_b 400000000 && exit");
    
    const char *message2 = "Fertig!\n";
    // show message
    show_message(message2);
}

// create vendor partition
static void create_vendor(GtkWidget *widget, gpointer data) 
{
    const char *message = "Achtung:\nManche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n";
    // show message
    show_message(message);
    
    open_terminal_by_desktop("fastboot create-logical-partition vendor_a 900000000 && fastboot create-logical-partition vendor_b 900000000 && exit");
    
    const char *message2 = "Fertig!\n";
    // show message
    show_message(message2);
}

// create system partition
static void create_system(GtkWidget *widget, gpointer data) 
{
    const char *message = "Achtung:\nManche Chipsätze unterstützen diesen Vorgang nicht in dieser Weise.\n";
    // show message
    show_message(message);
    
    open_terminal_by_desktop("fastboot create-logical-partition system_a 7500000000 && fastboot create-logical-partition system_b 7500000000 && exit");
    
    const char *message2 = "Fertig!\n";
    // show message
    show_message(message2);
}


/* main function of preflash_GUI*/
void partitions(int argc, char *argv[]) 
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[9][30] = {"Lösche Boot", "Lösche Vendor", "Lösche System", 
                                 "Resize Boot", "Resize Vendor", "Resize System",
                                 "Erstelle Boot", "Erstelle Vendor", "Erstelle System"};

    gtk_init(&argc, &argv);
    css_provider(); // load css-provider

     // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Partitionen");
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
    for (int i = 0; i < 9; i++) {
        button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i % 3, i / 3, 1, 1);

        // execute css-provider for all buttons
        add_css_provider(button, provider);

        switch (i) {
            case 0:
                g_signal_connect(button, "clicked", G_CALLBACK(remove_boot), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(remove_vendor), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(remove_system), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(resize_boot), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(resize_vendor), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(resize_system), NULL);
                break;
            case 6:
            	g_signal_connect(button, "clicked", G_CALLBACK(create_boot), NULL);
            	break;
            case 7:
            	g_signal_connect(button, "clicked", G_CALLBACK(create_vendor), NULL);
            	break;
            case 8:
            	g_signal_connect(button, "clicked", G_CALLBACK(create_system), NULL);
            	break;
        }
    }
    
    // clean the storage
    g_object_unref(provider);
    
    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
}
