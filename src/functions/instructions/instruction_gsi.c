/**
* instruction_gsi.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

/* main function */
void instruction_gsi(GtkWidget *widget, gpointer stack) 
{	
	LOGD("instruction_gsi");
	
	// char for the next page button
	const char *next_page_char = _("Next");
	const char *back_page_char = _("Back");
	const char *exit_page_char = _("Exit");

	/* page 1 */
    GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    GtkWidget *button_gsi1 = gtk_button_new_with_label(_("Notes"));
    // label 1
    GtkWidget *label_gsi1_1 = gtk_label_new(_("GSI (Generic System Image) is an Android system image that requires support for Project Treble (see further information)."));
    gtk_label_set_wrap(GTK_LABEL(label_gsi1_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_gsi1_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_gsi1_2 = gtk_label_new(_("GSI enable Android devices without custom ROMs support manual flashing of newer Android versions."));
    gtk_label_set_wrap(GTK_LABEL(label_gsi1_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_gsi1_2), PANGO_WRAP_WORD_CHAR);	
    // new button
    GtkWidget *button_gsi_1 = create_button_icon_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_gsi_2 = create_button_icon_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_gsi1);
    gtk_box_append(GTK_BOX(page1), label_gsi1_1);
    gtk_box_append(GTK_BOX(page1), label_gsi1_2);
    gtk_box_append(GTK_BOX(page1), button_gsi_1);
    gtk_box_append(GTK_BOX(page1), button_gsi_2);
    
    // position left of the labels
    gtk_widget_set_halign(label_gsi1_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_gsi1_2, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_gsi1_1, 15);
    gtk_widget_set_margin_start(label_gsi1_2, 15);

    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_gsi_1")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page1, "inst_gsi_1");
	}
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "inst_gsi_1");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_gsi_1), "stack", stack);
	g_signal_connect(button_gsi_1, "clicked", G_CALLBACK(switch_page), "inst_gsi_2");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_gsi_2), "stack", stack);
	g_signal_connect(button_gsi_2, "clicked", G_CALLBACK(switch_page), "instruction_flash");
	
	/* page 2 */
    GtkWidget *page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_gsi2 = gtk_button_new_with_label(_("GSI Flashing"));
    // label 1
    GtkWidget *label_gsi2_1 = gtk_label_new(_("1. Check if your device is compatible with Project Treble. \n2. Download a corresponding GSI. \n3. Prepare the images for the Flash."));
    gtk_label_set_wrap(GTK_LABEL(label_gsi2_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_gsi2_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_gsi2_2 = gtk_label_new(_("4. Boot your device in Fastboot. \n5. Open the bootloader. Some devices do not support the Fastboot method."));
    gtk_label_set_wrap(GTK_LABEL(label_gsi2_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_gsi2_2), PANGO_WRAP_WORD_CHAR);	
    // label 3
    GtkWidget *label_gsi2_3 = gtk_label_new(_("The alternatives 'dirty flash'(1) and 'clean flash'(2) are available as flash methods."));
    gtk_label_set_wrap(GTK_LABEL(label_gsi2_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_gsi2_3), PANGO_WRAP_WORD_CHAR);	
	
    // new button
    GtkWidget *button_gsi_3 = create_button_icon_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_gsi_4 = create_button_icon_no_callback("pan-start-symbolic", back_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_gsi2);
    gtk_box_append(GTK_BOX(page2), label_gsi2_1);
    gtk_box_append(GTK_BOX(page2), label_gsi2_2);
    gtk_box_append(GTK_BOX(page2), label_gsi2_3);
    gtk_box_append(GTK_BOX(page2), button_gsi_3);
    gtk_box_append(GTK_BOX(page2), button_gsi_4);
	
	// position left of the labels
    gtk_widget_set_halign(label_gsi2_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_gsi2_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_gsi2_3, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_gsi2_1, 15);
    gtk_widget_set_margin_start(label_gsi2_2, 15);
    gtk_widget_set_margin_start(label_gsi2_3, 15);
	
	// add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_gsi_2")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page2, "inst_gsi_2");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_gsi_3), "stack", stack);
	g_signal_connect(button_gsi_3, "clicked", G_CALLBACK(switch_page), "inst_gsi_3");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_gsi_4), "stack", stack);
	g_signal_connect(button_gsi_4, "clicked", G_CALLBACK(switch_page), "inst_gsi_1");
	
	/* page 3 */
    GtkWidget *page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_gsi3 = gtk_button_new_with_label(_("Clean Flash"));
    GtkWidget *label_gsi3_1 = gtk_label_new(_("1. Delete all user data. \n2. Flash the system image \n3. If necessary, flash a vbmeta.img. \n4. Restart your device."));
    gtk_label_set_wrap(GTK_LABEL(label_gsi3_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_gsi3_1), PANGO_WRAP_WORD_CHAR);	
    
    // new button
    GtkWidget *button_gsi_5 = create_button_icon_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_gsi_6 = create_button_icon_no_callback("pan-start-symbolic", back_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page3), button_gsi3);
    gtk_box_append(GTK_BOX(page3), label_gsi3_1);
    gtk_box_append(GTK_BOX(page3), button_gsi_5);
    gtk_box_append(GTK_BOX(page3), button_gsi_6);
	
	// position left of the labels
    gtk_widget_set_halign(label_gsi3_1, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_gsi3_1, 15);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_gsi_3")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page3, "inst_gsi_3");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_gsi_5), "stack", stack);
	g_signal_connect(button_gsi_5, "clicked", G_CALLBACK(switch_page), "inst_gsi_4");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_gsi_6), "stack", stack);
	g_signal_connect(button_gsi_6, "clicked", G_CALLBACK(switch_page), "inst_gsi_2");
	
	/* page 4 */
    GtkWidget *page4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_gsi4 = gtk_button_new_with_label(_("Dirty Flash"));
    // label 1
    GtkWidget *label_gsi4_1 = gtk_label_new(_("After a 'dirty flash', the user data is retained, but not every GSI starts afterwards."));
    gtk_label_set_wrap(GTK_LABEL(label_gsi4_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_gsi4_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_gsi4_2 = gtk_label_new(_("1. Flash the system image. \n2. Restart your device."));
    gtk_label_set_wrap(GTK_LABEL(label_gsi4_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_gsi4_2), PANGO_WRAP_WORD_CHAR);	
    
    // new button
    GtkWidget *button_gsi_7 = create_button_icon_no_callback("pan-start-symbolic", back_page_char);
    GtkWidget *button_gsi_8 = create_button_icon_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page4), button_gsi4);
    gtk_box_append(GTK_BOX(page4), label_gsi4_1);
    gtk_box_append(GTK_BOX(page4), label_gsi4_2); 
    gtk_box_append(GTK_BOX(page4), button_gsi_7); 
    gtk_box_append(GTK_BOX(page4), button_gsi_8);   
	
	
	// position left of the labels
    gtk_widget_set_halign(label_gsi4_1, GTK_ALIGN_START);
    gtk_widget_set_halign(label_gsi4_2, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_gsi4_1, 15);
    gtk_widget_set_margin_start(label_gsi4_2, 15);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_gsi_4")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page4, "inst_gsi_4");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_gsi_7), "stack", stack);
	g_signal_connect(button_gsi_7, "clicked", G_CALLBACK(switch_page), "inst_gsi_3");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_gsi_8), "stack", stack);
	g_signal_connect(button_gsi_8, "clicked", G_CALLBACK(switch_page), "instruction_flash");
	
	LOGD("end instruction_gsi");
}	
