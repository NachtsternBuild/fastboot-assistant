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
 *              Headerpart - gtk_message	 *
 *											 *
 *-------------------------------------------*
 */

/* headers */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

// function to display a message dialog
void show_message(const char *message)
{
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                              GTK_DIALOG_MODAL,
                                              GTK_MESSAGE_INFO,
                                              GTK_BUTTONS_OK,
                                              "%s", message);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

