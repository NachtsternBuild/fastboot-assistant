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
 *              info						 *
 *											 *
 *-------------------------------------------*
 */
 
 /* headers that used in the main programm */
#include <gtk/gtk.h>

void info(int argc, char *argv[]) 
{
    // int gtk
    gtk_init(&argc, &argv);

    // creat main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Info");
    gtk_widget_set_size_request(window, 700, 600);

    // connect close function to 'destroy'-signal
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_window_close), NULL);


    // Creation of a text label with the text to be displayed
    // check the text
    const char *text = "ADB (Android Debug Bridge) ermöglicht die Kommunikation \nzwischen einem Computer und einem Android-Gerät \nfür Debugging und Dateiübertragung. \nFastboot ist ein Befehlszeilenwerkzeug \nfür den Bootloader-Modus von Android-Geräten, \num Systemabbilder zu flashen und \nbenutzerdefinierte Firmware zu installieren. \nBeide sind wichtige Tools für Entwickler \nund fortgeschrittene Nutzer zur Modifikation und Diagnose\n von Android-Geräten über eine USB-Verbindung.\n \nGSI (Generic System Image) ist ein standardisiertes \nAndroid-Systemabbild, das auf verschiedenen Geräten laufen kann. \nCustom-ROMs sind modifizierte \nAndroid-Betriebssystemversionen, die von der \nStandard-Software abweichen und von Entwicklern \nerstellt werden, um zusätzliche Funktionen oder Anpassungen anzubieten. \nBeide ermöglichen Nutzern die Anpassung \nihrer Android-Geräte über Installationen von alternativen \nBetriebssystemversionen.\n \nA/B Partitionsschema verwendet zwei Systempartitionen, \num nahtlose Updates zu ermöglichen, \nindem es zwischen ihnen wechselt. \n Das only-A Partitionsschema \nhat nur eine Systempartition und erfordert einen Neustart für Updates. \nA/B bietet redundante Sicherheit und ermöglicht ein \nkontinuierliches Betriebssystem, während Only-A \neinfachere Verwaltung erfordert.\n \nProject Treble ist eine Android-Initiative von Google, \ndie die Trennung von Betriebssystem- und Hardwarekomponenten ermöglicht. \nDies erleichtert Herstellern \ndie Bereitstellung von Android-Updates, \nindem das Betriebssystem unabhängig \nvon den spezifischen Treibern für den Chipsatz ist.\n";
    GtkWidget *label = gtk_label_new(text);

    // add text label to main window
    gtk_container_add(GTK_CONTAINER(window), label);

    // show all elements
    gtk_widget_show_all(window);

    // gtk main loop
    gtk_main();
}
