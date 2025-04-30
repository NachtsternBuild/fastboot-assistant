/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - instruction_root		 *
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

// function to open the GitHub website from magisk
void magisk(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("magisk");
    const char *magisk_url = "https://github.com/topjohnwu/Magisk";
	open_url(magisk_url);
	LOG_INFO("end magisk");
}

// open the downloads from the magisk apk
void magisk_apk(GtkWidget *widget, gpointer stack)
{
    LOG_INFO("magisk_apk");
    const char *magisk_apk_url = "https://github.com/topjohnwu/Magisk/releases/download/v28.1/Magisk-v28.1.apk";    
	open_url(magisk_apk_url);
	LOG_INFO("end magisk_apk");
}

void instruction_root(GtkWidget *widget, gpointer stack) 
{
	LOG_INFO("instruction_root");
	apply_language();
	
	// char for the next page button
	const char *next_page_char = strcmp(language, "de") == 0 ? "Weiter" : "Next";
	const char *back_page_char = strcmp(language, "de") == 0 ? "Zurück" : "Back";
	const char *exit_page_char = strcmp(language, "de") == 0 ? "Verlassen" : "Exit";
	
	/* page 1 */
    GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    GtkWidget *button_root1 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Hinweise" : "Notes");
    // label 1
    GtkWidget *label_root1_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Beim Rooten von Android-Geräten werden dem Nutzer Superuser-Rechte eingeräumt, die ihm vollen Zugriff auf Android. Damit die Möglichkeit weitreichende Änderungen vorzunehmen." : "When rooting Android devices, the user is granted superuser rights that give them full access to Android. This gives them the possibility to make far-reaching changes.");
    gtk_label_set_wrap(GTK_LABEL(label_root1_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root1_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_root1_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Dies ermöglicht das Entfernen vorinstallierter Anwendungen, das Ändern von Systemeinstellungen und Installieren spezieller Anwendungen, die erweiterte Berechtigungen erfordern." : "This allows you to remove pre-installed applications, change system settings and install special applications that require extended permissions.");
    gtk_label_set_wrap(GTK_LABEL(label_root1_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root1_2), PANGO_WRAP_WORD_CHAR);	
    // label 3
    GtkWidget *label_root1_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Mit den umfangreichen Rechten bestehen auch große Gefahren, da Nutzer und Software große Schäden an der Software verursachen können." : "With the extensive rights, there are also great dangers while users and software can cause great damage to the software.");
    gtk_label_set_wrap(GTK_LABEL(label_root1_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root1_3), PANGO_WRAP_WORD_CHAR);	
    // new button
    GtkWidget *button_root_1 = create_icon_nav_button_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_root_2 = create_icon_nav_button_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_root1);
    gtk_box_append(GTK_BOX(page1), label_root1_1);
    gtk_box_append(GTK_BOX(page1), label_root1_2);
    gtk_box_append(GTK_BOX(page1), label_root1_3);
    gtk_box_append(GTK_BOX(page1), button_root_1);
    gtk_box_append(GTK_BOX(page1), button_root_2);
	
	// position left of the labels
    gtk_widget_set_halign(label_root1_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_root1_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_root1_3, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_root1_1, 15);
    gtk_widget_set_margin_start(label_root1_2, 15);
    gtk_widget_set_margin_start(label_root1_3, 15);

    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_root_1")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page1, "inst_root_1");
	}
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "inst_root_1");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_root_1), "stack", stack);
	g_signal_connect(button_root_1, "clicked", G_CALLBACK(switch_page), "inst_root_2");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_root_2), "stack", stack);
	g_signal_connect(button_root_2, "clicked", G_CALLBACK(switch_page), "instruction_flash");
	
	/* page 2 */
    GtkWidget *page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_root2 = gtk_button_new_with_label("Magisk");
    // label 1
    GtkWidget *label_root2_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Magisk ist ein Paket von Open-Source-Software für die Anpassung von Android. Mit folgenden Bestandteilen:" : "Magisk is a package of open source software for Android customization. With the following components:");
    gtk_label_set_wrap(GTK_LABEL(label_root2_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root2_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_root2_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. MagiskSU: Bereitstellung von Root-Zugriff für Anwendungen. \n2. Magisk Modules: Ändern von schreibgeschützten Partitionen durch Installation von Modulen." : "1. MagiskSU: Provision of root access for applications. \n2. Magisk Modules: Change read-only partitions by installing modules.");
    gtk_label_set_wrap(GTK_LABEL(label_root2_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root2_2), PANGO_WRAP_WORD_CHAR);	
    // label 3
    GtkWidget *label_root2_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "3. MagiskBoot: Das umfassendste Tool zum Entpacken und Neuverpacken von Android-Boot-Images. \n4. Zygisk: Code in allen Prozessen von Android-Anwendungen ausführen." : "3. MagiskBoot: The most comprehensive tool for unpacking and repacking Android boot images. \n4. Zygisk: Execute code in all processes of Android applications.");
    gtk_label_set_wrap(GTK_LABEL(label_root2_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root2_3), PANGO_WRAP_WORD_CHAR);	
    
    // other button
    GtkWidget *button_root3 = gtk_button_new_with_label("Magisk");
    GtkWidget *button_root4 = gtk_button_new_with_label("Magisk-APK");
	
	// new button
    GtkWidget *button_root_3 = create_icon_nav_button_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_root_4 = create_icon_nav_button_no_callback("pan-start-symbolic", back_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_root2);
    gtk_box_append(GTK_BOX(page2), label_root2_1);
    gtk_box_append(GTK_BOX(page2), label_root2_2);
    gtk_box_append(GTK_BOX(page2), label_root2_3);
    gtk_box_append(GTK_BOX(page2), button_root3);
    gtk_box_append(GTK_BOX(page2), button_root4);
    gtk_box_append(GTK_BOX(page2), button_root_3);
    gtk_box_append(GTK_BOX(page2), button_root_4);
	
	// position left of the labels
    gtk_widget_set_halign(label_root2_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_root2_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_root2_3, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_root2_1, 15);
    gtk_widget_set_margin_start(label_root2_2, 15);
    gtk_widget_set_margin_start(label_root2_3, 15);
	
	// add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_root_2")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page2, "inst_root_2");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_root_3), "stack", stack);
	g_signal_connect(button_root_3, "clicked", G_CALLBACK(switch_page), "inst_root_3");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_root_4), "stack", stack);
	g_signal_connect(button_root_4, "clicked", G_CALLBACK(switch_page), "inst_root_1");
	
	/* page 3 */
    GtkWidget *page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_root5 = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Rooten via Magisk" : "Rooting via Magisk");
    // label 1
    GtkWidget *label_root3_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Installieren Sie die Magisk-APK auf Ihrem Gerät. \n2. Starten Sie Magisk auf Ihrem Gerät und wählen Sie Magisk installieren." : "1. Install the Magisk APK on your device. \n2. Start Magisk on your device and select Install Magisk.");
    gtk_label_set_wrap(GTK_LABEL(label_root3_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root3_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_root3_2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "3. Wählen Sie ein Boot-Image für Ihr Gerät und lassen Sie es von Magisk patchen (Meist finden sich die Boot-Images im Internet. Hier ist Vorsicht geboten.)" : "3. Select a boot image for your device and have it patched by Magisk (Usually the boot images can be found on the Internet. Caution is advised here).");
    gtk_label_set_wrap(GTK_LABEL(label_root3_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root3_2), PANGO_WRAP_WORD_CHAR);	
    // label 3
    GtkWidget *label_root3_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "4. Kopieren Sie das von Magisk gepatchte Boot-Image auf Ihren Computer. \n5. Benennen Sie das Image in um 'boot.img' um oder lassen Sie es von der Anwendung vorbereiten." : "4. Copy the boot image patched by Magisk to your computer. \n5. Rename the image to boot.img or let the application prepare it.");
    gtk_label_set_wrap(GTK_LABEL(label_root3_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root3_3), PANGO_WRAP_WORD_CHAR);	
    // label 4
    GtkWidget *label_root3_4 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "6. Starten sie ihr Gerät in Fastboot \n7. Flashen sie das Boot-Image für Ihren Gerätetyp. \n8. Starten Sie Ihr Gerät neu. Nun sollte Magisk Root-Rechte bereitstehen." : "6. Start your device to Fastboot. \n7. Flash the boot image for your device type. \n8. Reboot your device. Now Magisk should provide root privileges.");
    gtk_label_set_wrap(GTK_LABEL(label_root3_4), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root3_4), PANGO_WRAP_WORD_CHAR);	
	
    // new button
    GtkWidget *button_root_5 = create_icon_nav_button_no_callback("pan-start-symbolic", back_page_char);
    GtkWidget *button_root_6 = create_icon_nav_button_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page3), button_root5);
    gtk_box_append(GTK_BOX(page3), label_root3_1);
    gtk_box_append(GTK_BOX(page3), label_root3_2);
    gtk_box_append(GTK_BOX(page3), label_root3_3);
    gtk_box_append(GTK_BOX(page3), label_root3_4);
    gtk_box_append(GTK_BOX(page3), button_root_5);
    gtk_box_append(GTK_BOX(page3), button_root_6);
	
	// position left of the labels
    gtk_widget_set_halign(label_root3_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_root3_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_root3_3, GTK_ALIGN_START);
    gtk_widget_set_halign(label_root3_4, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_root3_1, 15);
    gtk_widget_set_margin_start(label_root3_2, 15);
    gtk_widget_set_margin_start(label_root3_3, 15);
    gtk_widget_set_margin_start(label_root3_4, 15);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_root_3")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page3, "inst_root_3");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_root_5), "stack", stack);
	g_signal_connect(button_root_5, "clicked", G_CALLBACK(switch_page), "inst_root_2");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_root_6), "stack", stack);
	g_signal_connect(button_root_6, "clicked", G_CALLBACK(switch_page), "instruction_flash");
	
	LOG_INFO("end instruction_root");
}
