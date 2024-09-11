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
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

/* headers that used in the programm */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "program_functions.h"

static void rom_text()
{
	g_print("Auch nix Neues.\n");
}

void instruction_custom_rom(int argc, char *argv[]) 
{
	GtkWidget *window;
    GtkWidget *page_rom1, *page_rom2;
    GtkWidget *label_rom1_1, *label_rom1_2, *label_rom2_1, *label_rom2_2, *label_rom2_3, *label_rom2_4;
    GtkWidget *button_rom1, *button_rom2, *button_rom3;
    
	gtk_init(&argc, &argv);
	apply_theme();
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Custom ROMs");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    
     // Connect close function to 'destroy' signal
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	GtkWidget *notebook = gtk_notebook_new();
    gtk_container_add(GTK_CONTAINER(window), notebook);
    
    if (!GTK_IS_NOTEBOOK(notebook)) 
    {
    	g_warning("Notebook is not initialized properly.");
    	return;
	}
	
	// page 1
    page_rom1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_rom1 = gtk_button_new_with_label("Hinweise");
    label_rom1_1 = gtk_label_new("Custom-ROMs sind modifizierte Versionen des Android, um zusätzliche Funktionen, \nLeistungsverbesserungen oder eine andere Benutzeroberfläche \nzu bieten.");
    label_rom1_2 = gtk_label_new("Sie ersetzen das vorinstallierte Android und enthalten oft neuere Softwareversionen \noder spezielle Anpassungen, die der Hersteller nicht \nanbietet.");
    button_rom2 = gtk_button_new_with_label("Weiter");
    gtk_box_pack_start(GTK_BOX(page_rom1), button_rom1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_rom1), label_rom1_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_rom1), label_rom1_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_rom1), button_rom2, FALSE, FALSE, 0);
    g_signal_connect(button_rom1, "clicked", G_CALLBACK(rom_text), notebook);
    g_signal_connect(button_rom2, "clicked", G_CALLBACK(next_page), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_rom1, gtk_label_new("Hinweise"));
    
    // run css-provider
    add_css_provider(button_rom1, provider);
    add_css_provider(label_rom1_1, provider);
    add_css_provider(label_rom1_2, provider);
    add_css_provider(button_rom2, provider);
    
    // page 2
    page_rom2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    button_rom3 = gtk_button_new_with_label("Custom ROM Flashen");
    label_rom2_1 = gtk_label_new("1. Laden sie ein Custom-ROM für ihr Gerät herunter. \n2. Booten sie ihr Gerät in den Fastboot-Modus. \n3. Öffnen sie den Bootloader.");
    label_rom2_2 = gtk_label_new("4. Flashen sie den Custom-Recovery, das Boot-Image (boot.img/init_boot.img), \nfalls nötig das dtbo.img. \n5. Führen sie einen Neustart in den Recovery aus.");
    label_rom2_3 = gtk_label_new("6. Kopieren sie das Zip des Custom-ROMs auf ihr Gerät. \n7. Tippen sie installieren und flashen sie das Zip.");
    label_rom2_4 = gtk_label_new("8. Optional können sie jetzt Magisk (als Zip) oder Google Dienste \n(nur falls ihr Custom-ROM keine enthält) flashen. \n9. Starten sie ihr Gerät neu.");
    gtk_box_pack_start(GTK_BOX(page_rom2), button_rom3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(page_rom2), label_rom2_1, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_rom2), label_rom2_2, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_rom2), label_rom2_3, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(page_rom2), label_rom2_4, TRUE, TRUE, 0);
    g_signal_connect(button_rom3, "clicked", G_CALLBACK(rom_text), notebook);
    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), page_rom2, gtk_label_new("Flashen"));
    
    // run css-provider
    add_css_provider(button_rom3, provider);
    add_css_provider(label_rom2_1, provider);
    add_css_provider(label_rom2_2, provider);
    add_css_provider(label_rom2_3, provider);
    add_css_provider(label_rom2_4, provider);
    
    // clean the storage
    g_object_unref(provider);
	
	// show all widgets
    gtk_widget_show_all(window);
	
	// run gtk mainloop
    gtk_main();
}
