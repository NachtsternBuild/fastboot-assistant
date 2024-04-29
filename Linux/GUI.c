/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *			Sprudelnde PC-Kühlung			 *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - GUI					 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include "function_header.h"
#include "program_functions.h"
#include "flash_function_header.h"

#define MAX_BUFFER_SIZE 256

// include all functions
extern void adb_check();
extern void make_dir();
extern void change_dir();
extern void boot_recovery();
extern void boot_fastboot();
extern void reboot_fastboot();
extern void lock_unlock_bootloader();
extern void erase_data();
extern void rename_function();
extern void flash_GUI();
extern void flash_recovery();
extern void update_function();
extern void remove_old();
extern void info();
extern void about(); 

// button 1 - check for adb/fastboot
static void on_button1_clicked(GtkWidget *widget, gpointer data)
{
    adb_check();
}

// button 2 - mkdir 'ROM-Install'
static void on_button2_clicked(GtkWidget *widget, gpointer data)
{
	make_dir();
}

// button 3 - cd to 'ROM-Install'
static void on_button3_clicked(GtkWidget *widget, gpointer data)
{
	change_dir();
}

// button 4 - boot to recovery
static void on_button4_clicked(GtkWidget *widget, gpointer data)
{
	boot_recovery();
}

// button 5 - boot to fastboot
static void on_button5_clicked(GtkWidget *widget, gpointer data)
{
	boot_fastboot();
}

// button 6 - reboot from fastboot
static void on_button6_clicked(GtkWidget *widget, gpointer data)
{
	reboot_fastboot();
}

// button 7 - lock/unlock bootloader
static void on_button7_clicked(GtkWidget *widget, gpointer data)
{
	lock_unlock_bootloader();
}

// button 8 - erase userdata
static void on_button8_clicked(GtkWidget *widget, gpointer data)
{
	erase_data();
}

// button 9 - rename images
static void on_button9_clicked(GtkWidget *widget, gpointer data)
{
	rename_function();
}

// button 10 - start flashGUI
static void on_button10_clicked(GtkWidget *widget, gpointer data)
{
	flash_GUI();
}

// button 11 - update engine
static void on_button11_clicked(GtkWidget *widget, gpointer data)
{
	update_function();
}

// button 12 - remove old files 
static void on_button12_clicked(GtkWidget *widget, gpointer data)
{
	remove_old();
}

// button 13 - info
static void on_button13_clicked(GtkWidget *widget, gpointer data)
{
	info();
}

// button 14 - about
static void on_button14_clicked(GtkWidget *widget, gpointer data)
{	
	about(); 
}

/* start main programm */
int main(int argc, char *argv[])
{
	// int gtk
	gtk_init(&argc, &argv);
	
	// make main window
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Projekt 122");
    gtk_container_set_border_width(GTK_CONTAINER(window), 500);
    gtk_widget_set_size_request(window, 800, 750);
	gtk_widget_show(window);
	
	// make button for every function
    GtkWidget *button1 = gtk_button_new_with_label("Verbindung überprüfen (ADB/Fastboot)");
    GtkWidget *button2 = gtk_button_new_with_label("Erstellen Verzeichnis 'ROM-Install'");
    GtkWidget *button3 = gtk_button_new_with_label("Wechseln in das Verzeichnis 'ROM-Install'");
    GtkWidget *button4 = gtk_button_new_with_label("Boot in den Recovery");
    GtkWidget *button5 = gtk_button_new_with_label("Boot in den Fastboot-Modus");
    GtkWidget *button6 = gtk_button_new_with_label("Neustart");
    GtkWidget *button7 = gtk_button_new_with_label("Öffnen/schließen Bootloader");
    GtkWidget *button8 = gtk_button_new_with_label("Löschen Nutzerdaten");
    GtkWidget *button9 = gtk_button_new_with_label("Umbenennen von Image-Dateien");
    GtkWidget *button10 = gtk_button_new_with_label("Flashen von Dateien");
    GtkWidget *button11 = gtk_button_new_with_label("Update Projekt-122"); 
    GtkWidget *button12 = gtk_button_new_with_label("Entfernen alter Dateien");
    GtkWidget *button13 = gtk_button_new_with_label("Info"); 
    GtkWidget *button14 = gtk_button_new_with_label("Über die Anwendung");             
    
    // Link the click callback function with the buttons 
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button1_clicked), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button2_clicked), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(on_button3_clicked), NULL);
    g_signal_connect(button4, "clicked", G_CALLBACK(on_button4_clicked), NULL);
    g_signal_connect(button5, "clicked", G_CALLBACK(on_button5_clicked), NULL);
    g_signal_connect(button6, "clicked", G_CALLBACK(on_button6_clicked), NULL);
    g_signal_connect(button7, "clicked", G_CALLBACK(on_button7_clicked), NULL);
    g_signal_connect(button8, "clicked", G_CALLBACK(on_button8_clicked), NULL);
    g_signal_connect(button9, "clicked", G_CALLBACK(on_button9_clicked), NULL);
    g_signal_connect(button10, "clicked", G_CALLBACK(on_button10_clicked), NULL);
    g_signal_connect(button11, "clicked", G_CALLBACK(on_button11_clicked), NULL);
    g_signal_connect(button12, "clicked", G_CALLBACK(on_button12_clicked), NULL);
    g_signal_connect(button13, "clicked", G_CALLBACK(on_button13_clicked), NULL);
    g_signal_connect(button14, "clicked", G_CALLBACK(on_button14_clicked), NULL);
    
    // Create a layout container (HBox) for the buttons
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    
    // Create a layout container (VBox) for the left and right buttons
    GtkWidget *left_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    GtkWidget *right_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 7);
    
    // Add the first two buttons to the left VBox
    gtk_box_pack_start(GTK_BOX(left_vbox), button1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button5, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button7, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button9, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button11, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_vbox), button13, TRUE, TRUE, 0);

    // Add the other two buttons to the right VBox
    gtk_box_pack_start(GTK_BOX(right_vbox), button2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button4, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button6, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button8, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button10, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button12, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right_vbox), button14, TRUE, TRUE, 0);

    // Add the left and right VBoxes to the main HBox
    gtk_box_pack_start(GTK_BOX(hbox), left_vbox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), right_vbox, TRUE, TRUE, 0);

    // Add the main HBox to the main window
    gtk_container_add(GTK_CONTAINER(window), hbox);

    // show all button
    gtk_widget_show(button1);
    gtk_widget_show(button2);
    gtk_widget_show(button3);
    gtk_widget_show(button4);
    gtk_widget_show(button5);
    gtk_widget_show(button6);
    gtk_widget_show(button7);
    gtk_widget_show(button8);
    gtk_widget_show(button9);
    gtk_widget_show(button10);
    gtk_widget_show(button11);
    gtk_widget_show(button12);
    gtk_widget_show(button13);
    gtk_widget_show(button14);
    gtk_widget_show(left_vbox);
    gtk_widget_show(right_vbox);
    gtk_widget_show(hbox);
	
	// gtk main loop
	gtk_main();
	
	return (0);
}
