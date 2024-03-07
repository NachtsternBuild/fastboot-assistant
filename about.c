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
 *              about						 *
 *											 *
 *-------------------------------------------*
 */
 
#include <gtk/gtk.h>

void about(int argc, char *argv[]) 
{
    // int gtk
    gtk_init(&argc, &argv);

    // creat main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Über das Programm");
    gtk_widget_set_size_request(window, 500, 400);

    // connect close function to 'destroy'-signal
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_close), NULL);


    // Creation of a text label with the text to be displayed 
    // all six tab, name seven, version seven, description one
    const char *text = "							Projekt 122\n \n						Apache License, Version 2.0\n \n	Programm um das installieren von Custom-ROM und GSIs \nauf Android-Geräte zu erleichtern.\n \n						(C) Copyright 2023 Elias Mörz\n \n							Version 0.3.\n \n						'Funkelnde Datenkristalle'\n \n						Architektur: unbestimmt\n \n						https://github.com/NachtsternBuild/Projekt-122/\n";
    GtkWidget *label = gtk_label_new(text);

    // add text label to main window
    gtk_container_add(GTK_CONTAINER(window), label);

    // show all elements
    gtk_widget_show_all(window);

    // gtk main loop
    gtk_main();

}
