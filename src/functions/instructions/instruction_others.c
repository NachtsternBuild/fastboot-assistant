/**
* instruction_others.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

/* main function */
void instruction_others(GtkWidget *widget, gpointer stack)
{
	LOGD("instruction_others");
	
	// char for the next page button
	const char *next_page_char = _("Next");
	const char *back_page_char = _("Back");
	const char *exit_page_char = _("Exit");
	
	/* page 1 */
     GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); 
    
    // button and label
    GtkWidget *button_others1 = gtk_button_new_with_label(_("dtbo"));
    GtkWidget *label_others_1 = gtk_label_new(_("This is a partition which is stored in the device tree of the device. This is essential for the communication of the hardware with the boot loader and the kernel."));
	gtk_label_set_wrap(GTK_LABEL(label_others_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_others_1), PANGO_WRAP_WORD_CHAR);	

	// new button
    GtkWidget *button_others_1 = create_button_icon_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_others_2 = create_button_icon_no_callback("application-exit-symbolic", exit_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), button_others1);
    gtk_box_append(GTK_BOX(page1), label_others_1);
    gtk_box_append(GTK_BOX(page1), button_others_1);
    gtk_box_append(GTK_BOX(page1), button_others_2);
    
     // position left of the labels
    gtk_widget_set_halign(label_others_1, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_others_1, 15);

    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_others_1")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page1, "inst_others_1");
	}
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "inst_others_1");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_others_1), "stack", stack);
	g_signal_connect(button_others_1, "clicked", G_CALLBACK(switch_page), "inst_others_2");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_others_2), "stack", stack);
	g_signal_connect(button_others_2, "clicked", G_CALLBACK(switch_page), "instruction_flash");
	
	/* page 2 */
    GtkWidget *page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_others2 = gtk_button_new_with_label(_("Super"));
	GtkWidget *label_others_2 = gtk_label_new(_("This is a partition that includes all other partitions on devices with dynamic partitions."));
	gtk_label_set_wrap(GTK_LABEL(label_others_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_others_2), PANGO_WRAP_WORD_CHAR);	
    
	// new button
    GtkWidget *button_others_3 = create_button_icon_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_others_4 = create_button_icon_no_callback("pan-start-symbolic", back_page_char);
        
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_others2);
    gtk_box_append(GTK_BOX(page2), label_others_2);
    gtk_box_append(GTK_BOX(page2), button_others_3);
    gtk_box_append(GTK_BOX(page2), button_others_4);
    
    // position left of the labels
    gtk_widget_set_halign(label_others_2, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_others_2, 15);
	
	// add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_others_2")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page2, "inst_others_2");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_others_3), "stack", stack);
	g_signal_connect(button_others_3, "clicked", G_CALLBACK(switch_page), "inst_others_3");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_others_4), "stack", stack);
	g_signal_connect(button_others_4, "clicked", G_CALLBACK(switch_page), "inst_others_1");
	
	/* page 3 */
    GtkWidget *page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *button_others3 = gtk_button_new_with_label(_("vbmeta"));
	GtkWidget *label_others_3 = gtk_label_new(_("'vbmeta' ensures that the boot process of Stock-Android runs safely. Some custom ROMs can only be started if a new vbmeta image has been flashed."));
	
	// new button
    GtkWidget *button_others_5 = create_button_icon_no_callback("pan-start-symbolic", back_page_char);
    GtkWidget *button_others_6 = create_button_icon_no_callback("application-exit-symbolic", exit_page_char);
	
	// add everything to the page
    gtk_box_append(GTK_BOX(page3), button_others3);
    gtk_box_append(GTK_BOX(page3), label_others_3);
    gtk_box_append(GTK_BOX(page3), button_others_5);
    gtk_box_append(GTK_BOX(page3), button_others_6);
    
    // position left of the labels
    gtk_widget_set_halign(label_others_3, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(label_others_3, 15);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "inst_others_3")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page3, "inst_others_3");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_others_5), "stack", stack);
	g_signal_connect(button_others_5, "clicked", G_CALLBACK(switch_page), "inst_others_2");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_others_6), "stack", stack);
	g_signal_connect(button_others_6, "clicked", G_CALLBACK(switch_page), "instruction_flash");
	
	LOGD("end instruction_others");
}
