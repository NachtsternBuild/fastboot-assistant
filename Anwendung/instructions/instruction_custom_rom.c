/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_custom_rom	 *
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
void instruction_custom_rom(GtkWidget *widget, gpointer stack) 
{
	LOG_INFO("instruction_custom_rom");
	
	    // GTK init
    gtk_init();
	main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
    
	GtkWidget *window, *notebook;
    GtkWidget *page1, *page2;
    GtkWidget *label_rom1_1, *label_rom1_2, *label_rom2_1, *label_rom2_2, *label_rom2_3, *label_rom2_4;
    GtkWidget *button_rom1, *button_rom2, *button_rom3;
    
    // create the main window
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Custom ROM");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), main_loop);

    // create the notebook
    notebook = gtk_notebook_new();
    gtk_window_set_child(GTK_WINDOW(window), notebook);

    // page 1
    page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    button_rom1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Hinweise" : "Notes");
    label_rom1_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Custom-ROMs sind modifizierte Versionen des Android, um zusätzliche Funktionen, \nLeistungsverbesserungen oder eine andere Benutzeroberfläche \nzu bieten." : "Custom ROMs are modified versions of Android to offer additional functions, \nperformance improvements or a different user interface.");
    label_rom1_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Sie ersetzen das vorinstallierte Android und enthalten oft neuere Softwareversionen \noder spezielle Anpassungen, die der Hersteller nicht \nanbietet." : "They replace the pre-installed Android and often contain newer software versions \nor special customizations that the manufacturer does not \noffer.");
    button_rom2 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Weiter" : "Next");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_rom1);
    gtk_box_append(GTK_BOX(page1), label_rom1_1);
    gtk_box_append(GTK_BOX(page1), label_rom1_2);
    gtk_box_append(GTK_BOX(page1), button_rom2);

    // connect everything
    g_signal_connect(button_rom2, "clicked", G_CALLBACK(next_page), notebook);

    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page1, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Hinweise" : "Notes"));
    
    // page 2
    page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    button_rom3 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Custom ROM Flashen" : "Custom ROM flashing");
    label_rom2_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Laden sie ein Custom-ROM für ihr Gerät herunter. \n2. Booten sie ihr Gerät in den Fastboot-Modus. \n3. Öffnen sie den Bootloader." : "1. Download a custom ROM for your device. \n2. Boot your device into fastboot mode. \n3. Unlock the bootloader.");
    label_rom2_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "4. Flashen sie den Custom-Recovery, das Boot-Image (boot.img/init_boot.img), \nfalls nötig das dtbo.img. \n5. Führen sie einen Neustart in den Recovery aus." : "4. Flash the custom recovery, the boot image (boot.img/init_boot.img), \nif necessary the dtbo.img. \n5. Perform a reboot in the recovery.");
    label_rom2_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "6. Kopieren sie das Zip des Custom-ROMs auf ihr Gerät. \n7. Tippen sie installieren und flashen sie das Zip." : "6. Copy the zip of the custom ROM to your device. \n7. Tap install and flash the zip.");
    label_rom2_4 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "8. Optional können sie jetzt Magisk (als Zip) oder Google Dienste \n(nur falls ihr Custom-ROM keine enthält) flashen. \n9. Starten sie ihr Gerät neu." : "8. Optionally you can now flash Magisk (as a zip) or Google services \n(only if your custom ROM does not contain any). \n9. Restart your device.");
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_rom3);
    gtk_box_append(GTK_BOX(page2), label_rom2_1);
    gtk_box_append(GTK_BOX(page2), label_rom2_2);
    gtk_box_append(GTK_BOX(page2), label_rom2_3);
    gtk_box_append(GTK_BOX(page2), label_rom2_4);
    
    // add page to the notebook
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page2, gtk_label_new(g_strcmp0(language, "de") == 0 ? "Flashen" : "Flashing"));
    
    // show all widgets
    gtk_window_present(GTK_WINDOW(window)); // gtk_window_present instead of gtk_widget_show

     // run GTK main loop
    g_main_loop_run(main_loop); 
    
    if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
	
    LOG_INFO("end instruction_custom_rom");
}
