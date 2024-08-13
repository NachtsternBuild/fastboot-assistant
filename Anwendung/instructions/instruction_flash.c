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
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

extern void instruction_root();
extern void instruction_gsi();
extern void instruction_custom_rom();
extern void instruction_recovery();

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

// button 4 - inst. for recovery
static void inst_recovery(GtkWidget *widget, gpointer data)
{
	instruction_recovery();
}

/* start main programm */
void instruction_flash(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122 - Anleitungen Flash");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	// make button for every function with label
    GtkWidget *button_inst_root = gtk_button_new_with_label("Rooten des Gerätes");
    GtkWidget *button_inst_vendor = gtk_button_new_with_label("Vendor");
    GtkWidget *button_inst_gsi = gtk_button_new_with_label("Generic System Image (GSI)");
    GtkWidget *button_inst_custom_rom = gtk_button_new_with_label("Custom ROMs");
    GtkWidget *button_inst_recovery = gtk_button_new_with_label("Recovery");
    
    // Link the click callback function with the buttons 
    g_signal_connect(button_inst_root, "clicked", G_CALLBACK(inst_root), NULL);
    g_signal_connect(button_inst_vendor, "clicked", G_CALLBACK(inst_vendor), NULL);
    g_signal_connect(button_inst_gsi, "clicked", G_CALLBACK(inst_gsi), NULL);
    g_signal_connect(button_inst_custom_rom, "clicked", G_CALLBACK(inst_custom_rom), NULL);
    g_signal_connect(button_inst_recovery, "clicked", G_CALLBACK(inst_recovery), NULL);
    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button_inst_root, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_inst_vendor, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button_inst_recovery, TRUE, TRUE, 0);
    
    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button_inst_gsi, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button_inst_custom_rom, TRUE, TRUE, 0);
    
     // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button_inst_root);
    gtk_widget_show(button_inst_vendor);
    gtk_widget_show(button_inst_recovery);
    gtk_widget_show(button_inst_gsi);
    gtk_widget_show(button_inst_custom_rom);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
}
    
