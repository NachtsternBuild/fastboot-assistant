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
 *              instruction_info			 *
 *											 *
 *-------------------------------------------*
 */
 
 /* headers that used in the main programm */
#include <gtk/gtk.h>

void instruction_info(int argc, char *argv[]) 
{
    // int gtk
    gtk_init(&argc, &argv);

    // creat main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Anleitung Info");
    gtk_widget_set_size_request(window, 700, 600);

    // connect close function to 'destroy'-signal
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_close), NULL);


    // Creation of a text label with the text to be displayed
    // check the text
    const char *text = "\nA/B Partitionsschema verwendet zwei Systempartitionen, \num nahtlose Updates zu ermöglichen, \nindem es zwischen ihnen wechselt. \n Das only-A Partitionsschema \nhat nur eine Systempartition und erfordert einen Neustart für Updates. \nA/B bietet redundante Sicherheit und ermöglicht ein \nkontinuierliches Betriebssystem, während Only-A \neinfachere Verwaltung erfordert.\n \nProject Treble ist eine Android-Initiative von Google, \ndie die Trennung von Betriebssystem- und Hardwarekomponenten ermöglicht. \nDies erleichtert Herstellern \ndie Bereitstellung von Android-Updates, \nindem das Betriebssystem unabhängig \nvon den spezifischen Treibern für den Chipsatz ist.\n \nSystem-as-root ist ein Mechanismus in Android, \nbei dem das System-Image als Root-Dateisystem gemountet wird. \nDurch wird die Trennung von System- und Vendor-Partitionen \nverbessert und die Sicherheit erhöht. \nDies erleichtert das Aktualisieren des Systems \nund die Verwaltung von Berechtigungen, \nda systemkritische Dateien \nund Konfigurationen besser geschützt und isoliert werden.\n \nEin System on a Chip (SoC) ist ein integrierter Schaltkreis, \nder alle wesentlichen Komponenten eines Computersystems, \neinschließlich CPU, GPU, Speicher und Ein-/Ausgabeschnittstellen, \nauf einem einzigen Chip vereint. \nSoCs werden häufig verwendet, \num Platz und Energie zu sparen.\n";
    GtkWidget *label = gtk_label_new(text);

    // add text label to main window
    gtk_container_add(GTK_CONTAINER(window), label);

    // show all elements
    gtk_widget_show_all(window);

    // gtk main loop
    gtk_main();
}
