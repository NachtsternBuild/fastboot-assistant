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
	apply_language();
	
	// char for the next page button
	const char *next_page_char = strcmp(language, "de") == 0 ? "Weiter" : "Next";
	const char *back_page_char = strcmp(language, "de") == 0 ? "Zurück" : "Back";
	const char *exit_page_char = strcmp(language, "de") == 0 ? "Verlassen" : "Exit";
	
	/* page 1 */
    GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    GtkWidget *button_rom1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Hinweise" : "Notes");
    // label 1
    GtkWidget *label_rom1_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Custom-ROMs sind modifizierte Versionen des Android, um zusätzliche Funktionen, Leistungsverbesserungen oder eine andere Benutzeroberfläche zu bieten." : "Custom ROMs are modified versions of Android to offer additional functions, performance improvements or a different user interface.");
    gtk_label_set_wrap(GTK_LABEL(label_rom1_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_rom1_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_rom1_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Sie ersetzen das vorinstallierte Android und enthalten oft neuere Softwareversionen oder spezielle Anpassungen, die der Hersteller nicht anbietet." : "They replace the pre-installed Android and often contain newer software versions or special customizations that the manufacturer does not offer.");
    gtk_label_set_wrap(GTK_LABEL(label_rom1_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_rom1_2), PANGO_WRAP_WORD_CHAR);	
    
    // new button
    GtkWidget *button_rom2 = create_icon_nav_button_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_rom3 = create_icon_nav_button_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_rom1);
    gtk_box_append(GTK_BOX(page1), label_rom1_1);
    gtk_box_append(GTK_BOX(page1), label_rom1_2);
    gtk_box_append(GTK_BOX(page1), button_rom2);
    gtk_box_append(GTK_BOX(page1), button_rom3);
	
	// position left of the labels
    gtk_widget_set_halign(label_rom1_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_rom1_2, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_rom1_1, 15);
    gtk_widget_set_margin_start(label_rom1_2, 15);

    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_rom_1")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page1, "inst_rom_1");
	}
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "inst_rom_1");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_rom2), "stack", stack);
	g_signal_connect(button_rom2, "clicked", G_CALLBACK(switch_page), "inst_rom_2");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_rom3), "stack", stack);
	g_signal_connect(button_rom3, "clicked", G_CALLBACK(switch_page), "instruction_flash");
	
	/* page 2 */
    GtkWidget *page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_rom4 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Custom ROM Flashen" : "Custom ROM flashing");
    // label 1
    GtkWidget *label_rom2_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Laden sie ein Custom-ROM für ihr Gerät herunter. \n2. Booten sie ihr Gerät in den Fastboot-Modus. \n3. Öffnen sie den Bootloader." : "1. Download a custom ROM for your device. \n2. Boot your device into fastboot mode. \n3. Unlock the bootloader.");
    gtk_label_set_wrap(GTK_LABEL(label_rom2_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_rom2_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_rom2_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "4. Flashen sie den Custom-Recovery, das Boot-Image (boot.img/init_boot.img), \nfalls nötig das dtbo.img. \n5. Führen sie einen Neustart in den Recovery aus." : "4. Flash the custom recovery, the boot image (boot.img/init_boot.img), \nif necessary the dtbo.img. \n5. Perform a reboot in the recovery.");
    gtk_label_set_wrap(GTK_LABEL(label_rom2_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_rom2_2), PANGO_WRAP_WORD_CHAR);	
    // label 3
    GtkWidget *label_rom2_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "6. Kopieren sie das Zip des Custom-ROMs auf ihr Gerät. \n7. Tippen sie installieren und flashen sie das Zip." : "6. Copy the zip of the custom ROM to your device. \n7. Tap install and flash the zip.");
    gtk_label_set_wrap(GTK_LABEL(label_rom2_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_rom2_3), PANGO_WRAP_WORD_CHAR);	
    // label 4
    GtkWidget *label_rom2_4 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "8. Optional können sie jetzt Magisk (als Zip) oder Google Dienste (nur falls ihr Custom-ROM keine enthält) flashen. \n9. Starten sie ihr Gerät neu." : "8. Optionally you can now flash Magisk (as a zip) or Google services (only if your custom ROM does not contain any). \n9. Restart your device.");
    gtk_label_set_wrap(GTK_LABEL(label_rom2_4), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_rom2_4), PANGO_WRAP_WORD_CHAR);	
	
    // new button
    GtkWidget *button_rom5 = create_icon_nav_button_no_callback("pan-start-symbolic", back_page_char);
    GtkWidget *button_rom6 = create_icon_nav_button_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_rom4);
    gtk_box_append(GTK_BOX(page2), label_rom2_1);
    gtk_box_append(GTK_BOX(page2), label_rom2_2);
    gtk_box_append(GTK_BOX(page2), label_rom2_3);
    gtk_box_append(GTK_BOX(page2), label_rom2_4);
    gtk_box_append(GTK_BOX(page2), button_rom5);
    gtk_box_append(GTK_BOX(page2), button_rom6);
    
    // position left of the labels
    gtk_widget_set_halign(label_rom2_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_rom2_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_rom2_3, GTK_ALIGN_START);
    gtk_widget_set_halign(label_rom2_4, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_rom2_1, 15);
    gtk_widget_set_margin_start(label_rom2_2, 15);
    gtk_widget_set_margin_start(label_rom2_3, 15);
    gtk_widget_set_margin_start(label_rom2_4, 15);
	
	// add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_rom_2")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page2, "inst_rom_2");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_rom5), "stack", stack);
	g_signal_connect(button_rom5, "clicked", G_CALLBACK(switch_page), "inst_rom_1");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_rom6), "stack", stack);
	g_signal_connect(button_rom6, "clicked", G_CALLBACK(switch_page), "instruction_flash");
	
}
