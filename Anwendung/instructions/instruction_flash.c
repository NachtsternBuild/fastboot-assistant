/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_flash		 *
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
#include "instruction_header.h"

#define MAX_BUFFER_SIZE 256

extern void instruction_root();
extern void instruction_vendor();
extern void instruction_gsi();
extern void instruction_custom_rom();
extern void instruction_recovery();
extern void instruction_others();

// button 1 - inst. for root
static void inst_root(GtkWidget *widget, gpointer data)
{
    instruction_root();
}

// button 2 - inst. for vendor
static void inst_vendor(GtkWidget *widget, gpointer data)
{
	instruction_vendor();
}

// button 3 - inst. for GSI
static void inst_gsi(GtkWidget *widget, gpointer data)
{
    instruction_gsi();
}

// button 4 - inst. for custom ROMs
static void inst_custom_rom(GtkWidget *widget, gpointer data)
{
	instruction_custom_rom();
}

// button 5 - inst. for recovery
static void inst_recovery(GtkWidget *widget, gpointer data)
{
	instruction_recovery();
}

// button 6 - inst. for other images
static void inst_others(GtkWidget *widget, gpointer data)
{
	instruction_others();
}

/* start main programm */
void instruction_flash(int argc, char *argv[])
{
	GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    char button_labels[6][30] = {"Rooten", "Vendor (VNDK)", "Generic System Image (GSI)", 
    							 "Custom ROMs", "Recovery", "Anderes"};

    gtk_init(&argc, &argv);
    apply_theme();
    
     // create the window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Anleitungen - Flash");
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
                g_signal_connect(button, "clicked", G_CALLBACK(inst_root), NULL);
                break;
            case 1:
                g_signal_connect(button, "clicked", G_CALLBACK(inst_vendor), NULL);
                break;
            case 2:
                g_signal_connect(button, "clicked", G_CALLBACK(inst_gsi), NULL);
                break;
            case 3:
                g_signal_connect(button, "clicked", G_CALLBACK(inst_custom_rom), NULL);
                break;
            case 4:
                g_signal_connect(button, "clicked", G_CALLBACK(inst_recovery), NULL);
                break;
            case 5:
                g_signal_connect(button, "clicked", G_CALLBACK(inst_others), NULL);
                break;          
        }
    }
	// cleaning the provider
    g_object_unref(provider);

    // show window
    gtk_widget_show_all(window);

    // run main-gtk-loop
    gtk_main();
}
   
