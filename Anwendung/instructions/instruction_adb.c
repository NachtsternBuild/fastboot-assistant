/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_adb		 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

/* main function */
void instruction_adb(int argc, char *argv[]) 
{
	LOG_INFO("instruction_adb");
	// GTK init
    gtk_init();
	main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    
    GtkWidget *window, *notebook;
    GtkWidget *page1, *page2, *page3, *page4;
    GtkWidget *label_adb1_1, *label_adb1_2, *label_adb1_3, *label_adb2_1, *label_adb2_2, *label_adb2_3, *label_adb3_1, *label_adb3_2, *label_adb3_3, *label_adb4_1, *label_adb4_2, *label_adb4_3;
    GtkWidget *button_adb1, *button_adb2, *button_adb3, *button_adb4, *button_adb5, *button_adb6, *button_adb7;
    
    // create the main window
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "ADB/Fastboot");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);

    // create the notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    button_adb1 = gtk_button_new_with_label("ADB/Fastboot");
    label_adb1_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "ADB (Android Debug Bridge) dient als \nKommunikationsschnittstelle zwischen Computer und einem Android-Gerät. \nSie wird zum Debugging und Dateiübertragung verwendet." : "ADB (Android Debug Bridge) serves as a \ncommunication interface between a computer and an Android device. \nIt is used for debugging and file transfer.");
    label_adb1_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Fastboot ist ein Befehlszeilenwerkzeug \nfür den Bootloader von Android-Geräten, mit dem benutzerdefinierte Firmware \nund andere Systemabbilder geflasht werden können." : "Fastboot is a command line tool \nfor the bootloader of Android devices, with which user-defined firmware \nand other system images can be flashed.");
    label_adb1_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Beide Tools sind für Entwickler und fortgeschrittene Nutzer \nvon großem Nutzen, wenn es darum geht, Android-Geräte zu modifizieren \nund zu diagnostizieren." : "Both tools are very useful for developers and \nadvanced users when it comes to modifying and diagnosing Android devices.");
    button_adb2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_adb1);
    gtk_box_append(GTK_BOX(page1), label_adb1_1);
    gtk_box_append(GTK_BOX(page1), label_adb1_2);
    gtk_box_append(GTK_BOX(page1), label_adb1_3);
    gtk_box_append(GTK_BOX(page1), button_adb2);

    // connect everything
    g_signal_connect(button_adb2, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new("ADB/Fastboot"));
    
    // page 2
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_adb3 = gtk_button_new_with_label("Bootloader/Preloader");
    label_adb2_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Der Bootloader ist ein Programm, das beim Starten eines Android-Geräts \ndas Betriebssystem lädt und überprüft, ob die Software sicher und \nautorisiert ist." : "The bootloader is a program that loads the operating system when an Android device \nis started and checks whether the software is secure and \nauthorized.");
    label_adb2_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Durch das Öffnen des Bootloaders wird diese Sicherheitsprüfung umgangen, \num benutzerdefinierte Betriebssysteme oder Software \nauf dem Gerät zu installieren." : "Opening the bootloader bypasses this security check \nto install custom OS or software \non the device.");
    label_adb2_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "\nDadurch lassen sich Custom-ROMs und andere Image-Dateien flashen." : "\nThis allows custom ROMs and other image files to be flashed.");
    button_adb4 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_adb3);
    gtk_box_append(GTK_BOX(page2), label_adb2_1);
    gtk_box_append(GTK_BOX(page2), label_adb2_2);
    gtk_box_append(GTK_BOX(page2), label_adb2_3);
    gtk_box_append(GTK_BOX(page2), button_adb4);
    
    // connect everything
    g_signal_connect(button_adb4, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, gtk_label_new("Bootloader"));
    
    // page 3
    page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_adb5 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Verbinden mit ADB" : "Connect with ADB");
    label_adb3_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Verbinden sie ihr Gerät mit ihrem Computer. \n1.Enwickleroptionen aktivieren.\n1.1. Suchen sie in den Einstellungen nach 'Build-Nummer'." : "Connect your device to your computer. \n1.Enable developer options. \n1.1. Search for 'Build number' in the settings.");
    label_adb3_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1.2. Tippen sie siebenmal auf die 'Build-Nummer'. \n1.3. Suchen sie in den Einstellungen 'Debug'. \n1.4. Aktivieren sie USB-Debbuging. \n1.5. Aktivieren sie in den USB-Einstellungen 'Dateiübertragung'." : "1.2. Tap the 'Build number' seven times. \n1.3. Search for 'Debug' in the settings. \n1.4. Activate USB debugging. \n1.5. Activate 'File transfer' in the USB settings.");
    label_adb3_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "2. Prüfen sie mithilfe des Programms ob Verbindung zur ADB besteht." : "2. Use the program to check whether there is a connection to the ADB.");
    button_adb6 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page3), button_adb5);
    gtk_box_append(GTK_BOX(page3), label_adb3_1);
    gtk_box_append(GTK_BOX(page3), label_adb3_2);
    gtk_box_append(GTK_BOX(page3), label_adb3_3);
    gtk_box_append(GTK_BOX(page3), button_adb6);
    
    // connect everything
    g_signal_connect(button_adb6, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page3, gtk_label_new("ADB"));
    
    // page 4
    page4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_adb7 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Neustart Fastboot" : "Reboot Fastboot");
    label_adb4_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Navigieren sie in der Anwendung durch 'Gerät neustarten' \nzu 'Neustart von ADB'." : "1. Navigate in the application through 'Reboot device' \nto 'Reboot from ADB'.");
    label_adb4_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "2. Warten sie bis sich ihr Gerät im Fastboot-Modus befindet." : "2. Wait until your device is in fastboot mode.");
    label_adb4_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "3. Prüfen sie ob eine Verbindung zum Fastboot-Modus besteht." : "3. Check whether there is a connection to fastboot mode.");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page4), button_adb7);
    gtk_box_append(GTK_BOX(page4), label_adb4_1);
    gtk_box_append(GTK_BOX(page4), label_adb4_2);
    gtk_box_append(GTK_BOX(page4), label_adb4_3);
    
    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page4, gtk_label_new("Fastboot"));
    
     // show all widgets
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
    
    if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
    
    LOG_INFO("end instruction_adb");
}
