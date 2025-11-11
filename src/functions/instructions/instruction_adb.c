/**
* instruction_adb.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

/* main function */
void instruction_adb(GtkWidget *widget, gpointer stack) 
{
	LOGD("instruction_adb");
	
	// char for the next page button
	const char *next_page_char = _("Next");
	const char *back_page_char = _("Back");
	const char *exit_page_char = _("Exit");
	
	/* page 1 */
    GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    GtkWidget *button_adb1 = gtk_button_new_with_label(_("ADB/Fastboot"));
    // 1. label
    GtkWidget *label_adb1_1 = gtk_label_new(_("ADB (Android Debug Bridge) serves as a communication interface between a computer and an Android device. It is used for debugging and file transfer."));
    gtk_label_set_wrap(GTK_LABEL(label_adb1_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_adb1_1), PANGO_WRAP_WORD_CHAR);	
	// 2. label
    GtkWidget *label_adb1_2 = gtk_label_new(_("Fastboot is a command line tool for the bootloader of Android devices, with which user-defined firmware and other system images can be flashed."));
    gtk_label_set_wrap(GTK_LABEL(label_adb1_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_adb1_2), PANGO_WRAP_WORD_CHAR);	
	// 3. label
    GtkWidget *label_adb1_3 = gtk_label_new(_("Both tools are very useful for developers and advanced users when it comes to modifying and diagnosing Android devices."));
    gtk_label_set_wrap(GTK_LABEL(label_adb1_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_adb1_3), PANGO_WRAP_WORD_CHAR);	
    
    // new button
    GtkWidget *button_adb_1 = create_button_icon_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_adb_2 = create_button_icon_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_adb1);
    gtk_box_append(GTK_BOX(page1), label_adb1_1);
    gtk_box_append(GTK_BOX(page1), label_adb1_2);
    gtk_box_append(GTK_BOX(page1), label_adb1_3);
    gtk_box_append(GTK_BOX(page1), button_adb_1);
    gtk_box_append(GTK_BOX(page1), button_adb_2);
    
    // position left of the labels
    gtk_widget_set_halign(label_adb1_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_adb1_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_adb1_3, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_adb1_1, 15);
    gtk_widget_set_margin_start(label_adb1_2, 15);
    gtk_widget_set_margin_start(label_adb1_3, 15);

    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_adb_1")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page1, "inst_adb_1");
	}
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "inst_adb_1");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_adb_1), "stack", stack);
	g_signal_connect(button_adb_1, "clicked", G_CALLBACK(switch_page), "inst_adb_2");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_adb_2), "stack", stack);
	g_signal_connect(button_adb_2, "clicked", G_CALLBACK(switch_page), "instruction_GUI");
	
	/* page 2 */
    GtkWidget *page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_adb2 = gtk_button_new_with_label(_("Bootloader/Preloader"));
    // 1. label
    GtkWidget *label_adb2_1 = gtk_label_new(_("The bootloader is a program that loads the operating system when an Android device is started and checks whether the software is secure and authorized."));
    gtk_label_set_wrap(GTK_LABEL(label_adb2_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_adb2_1), PANGO_WRAP_WORD_CHAR);	
    // 2. label
    GtkWidget *label_adb2_2 = gtk_label_new(_("Opening the bootloader bypasses this security check to install custom OS or software on the device."));
    gtk_label_set_wrap(GTK_LABEL(label_adb2_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_adb2_2), PANGO_WRAP_WORD_CHAR);	
    // 3. label
    GtkWidget *label_adb2_3 = gtk_label_new(_("This allows custom ROMs and other image files to be flashed."));
    gtk_label_set_wrap(GTK_LABEL(label_adb2_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_adb2_3), PANGO_WRAP_WORD_CHAR);	
    
    // new button
    GtkWidget *button_adb_3 = create_button_icon_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_adb_4 = create_button_icon_no_callback("pan-start-symbolic", back_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_adb2);
    gtk_box_append(GTK_BOX(page2), label_adb2_1);
    gtk_box_append(GTK_BOX(page2), label_adb2_2);
    gtk_box_append(GTK_BOX(page2), label_adb2_3);
    gtk_box_append(GTK_BOX(page2), button_adb_3);
    gtk_box_append(GTK_BOX(page2), button_adb_4);
    
    // position left of the labels
    gtk_widget_set_halign(label_adb2_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_adb2_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_adb2_3, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_adb2_1, 15);
    gtk_widget_set_margin_start(label_adb2_2, 15);
    gtk_widget_set_margin_start(label_adb2_3, 15);
	
	// add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_adb_2")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page2, "inst_adb_2");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_adb_3), "stack", stack);
	g_signal_connect(button_adb_3, "clicked", G_CALLBACK(switch_page), "inst_adb_3");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_adb_4), "stack", stack);
	g_signal_connect(button_adb_4, "clicked", G_CALLBACK(switch_page), "inst_adb_1");
	
	/* page 3 */
    GtkWidget *page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_margin_start(page3, 12);
    
    // button and label
    GtkWidget *button_adb5 = gtk_button_new_with_label(_("Connect with ADB"));
    // 1. label
    GtkWidget *label_adb3_1 = gtk_label_new(_("Connect your device to your computer. \n1.Enable developer options. \n1.1. Search for 'Build number' in the settings."));
    gtk_label_set_wrap(GTK_LABEL(label_adb3_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_adb3_1), PANGO_WRAP_WORD_CHAR);	
    // 2. label
    GtkWidget *label_adb3_2 = gtk_label_new(_("1.2. Tap the 'Build number' seven times. \n1.3. Search for 'Debug' in the settings. \n1.4. Activate USB debugging. \n1.5. Activate 'File transfer' in the USB settings."));
    gtk_label_set_wrap(GTK_LABEL(label_adb3_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_adb3_2), PANGO_WRAP_WORD_CHAR);	
    // 3. label
    GtkWidget *label_adb3_3 = gtk_label_new(_("2. Use the program to check whether there is a connection to the ADB."));
    gtk_label_set_wrap(GTK_LABEL(label_adb3_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_adb3_3), PANGO_WRAP_WORD_CHAR);	
    
    // new button
    GtkWidget *button_adb_5 = create_button_icon_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_adb_6 = create_button_icon_no_callback("pan-start-symbolic", back_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page3), button_adb5);
    gtk_box_append(GTK_BOX(page3), label_adb3_1);
    gtk_box_append(GTK_BOX(page3), label_adb3_2);
    gtk_box_append(GTK_BOX(page3), label_adb3_3);
    gtk_box_append(GTK_BOX(page3), button_adb_5);
    gtk_box_append(GTK_BOX(page3), button_adb_6);
    
    // position left of the labels
    gtk_widget_set_halign(label_adb3_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_adb3_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_adb3_3, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_adb3_1, 15);
    gtk_widget_set_margin_start(label_adb3_2, 15);
    gtk_widget_set_margin_start(label_adb3_3, 15);
    
    
	// add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_adb_3")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page3, "inst_adb_3");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_adb_5), "stack", stack);
	g_signal_connect(button_adb_5, "clicked", G_CALLBACK(switch_page), "inst_adb_4");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_adb_6), "stack", stack);
	g_signal_connect(button_adb_6, "clicked", G_CALLBACK(switch_page), "inst_adb_2");
	
	/* page 4 */
    GtkWidget *page4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_adb7 = gtk_button_new_with_label(_("Reboot Fastboot"));
    // 1. label
    GtkWidget *label_adb4_1 = gtk_label_new(_("1. Navigate in the application through 'Reboot device' to 'Reboot from ADB'."));
    gtk_label_set_wrap(GTK_LABEL(label_adb4_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_adb4_1), PANGO_WRAP_WORD_CHAR);	
    // 2. label
    GtkWidget *label_adb4_2 = gtk_label_new(_("2. Wait until your device is in fastboot mode."));
    gtk_label_set_wrap(GTK_LABEL(label_adb4_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_adb4_2), PANGO_WRAP_WORD_CHAR);	
    // 3. label
    GtkWidget *label_adb4_3 = gtk_label_new(_("3. Check whether there is a connection to fastboot mode."));
    gtk_label_set_wrap(GTK_LABEL(label_adb4_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_adb4_3), PANGO_WRAP_WORD_CHAR);	
    
    // new button
    GtkWidget *button_adb_7 = create_button_icon_no_callback("pan-start-symbolic", back_page_char);
    GtkWidget *button_adb_8 = create_button_icon_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page4), button_adb7);
    gtk_box_append(GTK_BOX(page4), label_adb4_1);
    gtk_box_append(GTK_BOX(page4), label_adb4_2);
    gtk_box_append(GTK_BOX(page4), label_adb4_3);
    gtk_box_append(GTK_BOX(page4), button_adb_7);
    gtk_box_append(GTK_BOX(page4), button_adb_8);
	
	// position left of the labels
    gtk_widget_set_halign(label_adb4_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_adb4_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_adb4_3, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_adb4_1, 15);
    gtk_widget_set_margin_start(label_adb4_2, 15);
    gtk_widget_set_margin_start(label_adb4_3, 15);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_adb_4")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page4, "inst_adb_4");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_adb_7), "stack", stack);
	g_signal_connect(button_adb_7, "clicked", G_CALLBACK(switch_page), "inst_adb_3");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_adb_8), "stack", stack);
	g_signal_connect(button_adb_8, "clicked", G_CALLBACK(switch_page), "instruction_GUI");
    
    LOGD("end instruction_adb");
}
