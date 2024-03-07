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
 *              renamefileboot				 *
 *											 *
 *-------------------------------------------*
 */
 
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// set file and rename it
void on_file_set_boot(GtkFileChooser *chooser, gpointer data)
{
    // get filename from userchoice
    gchar *filename = gtk_file_chooser_get_filename(chooser);
    const char *newname = "boot.img";

    if (rename(filename, newname) != 0) 
    {
        perror("Error renaming file");
        exit(EXIT_FAILURE);
    }

    printf("Datei erfolgreich umbenannt.\n");

    g_free(filename);
}

// UI for rename file
void renamefileboot(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_file_chooser_dialog_new("Auswahl des Images", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(window), ".");
    gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(window), gtk_file_filter_new());
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(window), "*.img");
    g_signal_connect(window, "response", G_CALLBACK(gtk_widget_destroy), NULL);
    g_signal_connect(window, "file-set", G_CALLBACK(on_file_set_boot), NULL);

    gtk_widget_show_all(window);

    gtk_main();
}
