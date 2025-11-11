/**
* instruction_root.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// function to open the GitHub website from magisk
void magisk(GtkWidget *widget, gpointer stack)
{
    const char *magisk_url = "https://github.com/topjohnwu/Magisk";
	open_url(magisk_url);
}

// open the downloads from the magisk apk
void magisk_apk(GtkWidget *widget, gpointer stack)
{
    const char *magisk_apk_url = "https://github.com/topjohnwu/Magisk/releases/download/v28.1/Magisk-v28.1.apk";    
	open_url(magisk_apk_url);
}

void instruction_root(GtkWidget *widget, gpointer stack) 
{
	LOGD("instruction_root");
	
	// char for the next page button
	const char *next_page_char = _("Next");
	const char *back_page_char = _("Back");
	const char *exit_page_char = _("Exit");
	
	/* page 1 */
    GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // button and label
    GtkWidget *button_root1 = gtk_button_new_with_label(_("Notes"));
    // label 1
    GtkWidget *label_root1_1 = gtk_label_new(_("When rooting Android devices, the user is granted superuser rights that give them full access to Android. This gives them the possibility to make far-reaching changes."));
    gtk_label_set_wrap(GTK_LABEL(label_root1_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root1_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_root1_2 = gtk_label_new(_("This allows you to remove pre-installed applications, change system settings and install special applications that require extended permissions."));
    gtk_label_set_wrap(GTK_LABEL(label_root1_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root1_2), PANGO_WRAP_WORD_CHAR);	
    // label 3
    GtkWidget *label_root1_3 = gtk_label_new(_("With the extensive rights, there are also great dangers while users and software can cause great damage to the software."));
    gtk_label_set_wrap(GTK_LABEL(label_root1_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root1_3), PANGO_WRAP_WORD_CHAR);	
    // new button
    GtkWidget *button_root_1 = create_button_icon_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_root_2 = create_button_icon_no_callback("application-exit-symbolic", exit_page_char);
    
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
    GtkWidget *button_root2 = gtk_button_new_with_label(_("Magisk"));
    // label 1
    GtkWidget *label_root2_1 = gtk_label_new(_("Magisk is a package of open source software for Android customization. With the following components:"));
    gtk_label_set_wrap(GTK_LABEL(label_root2_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root2_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_root2_2 = gtk_label_new(_("1. MagiskSU: Provision of root access for applications. \n2. Magisk Modules: Change read-only partitions by installing modules."));
    gtk_label_set_wrap(GTK_LABEL(label_root2_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root2_2), PANGO_WRAP_WORD_CHAR);	
    // label 3
    GtkWidget *label_root2_3 = gtk_label_new(_("3. MagiskBoot: The most comprehensive tool for unpacking and repacking Android boot images. \n4. Zygisk: Execute code in all processes of Android applications."));
    gtk_label_set_wrap(GTK_LABEL(label_root2_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root2_3), PANGO_WRAP_WORD_CHAR);	
    
    // other button
    GtkWidget *button_root3 = gtk_button_new_with_label(_("Magisk"));
    GtkWidget *button_root4 = gtk_button_new_with_label(_("Magisk-APK"));
	
	// new button
    GtkWidget *button_root_3 = create_button_icon_no_callback("pan-end-symbolic", next_page_char);
    GtkWidget *button_root_4 = create_button_icon_no_callback("pan-start-symbolic", back_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page2), button_root2);
    gtk_box_append(GTK_BOX(page2), label_root2_1);
    gtk_box_append(GTK_BOX(page2), label_root2_2);
    gtk_box_append(GTK_BOX(page2), label_root2_3);
    gtk_box_append(GTK_BOX(page2), button_root3);
    gtk_box_append(GTK_BOX(page2), button_root4);
    gtk_box_append(GTK_BOX(page2), button_root_3);
    gtk_box_append(GTK_BOX(page2), button_root_4);
    
    // connect the button to a callback
    g_signal_connect(button_root3, "clicked", G_CALLBACK(magisk), stack);
    g_signal_connect(button_root4, "clicked", G_CALLBACK(magisk_apk), stack);
	
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
    GtkWidget *button_root5 = gtk_button_new_with_label(_("Rooting via Magisk"));
    // label 1
    GtkWidget *label_root3_1 = gtk_label_new(_("1. Install the Magisk APK on your device. \n2. Start Magisk on your device and select Install Magisk."));
    gtk_label_set_wrap(GTK_LABEL(label_root3_1), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root3_1), PANGO_WRAP_WORD_CHAR);	
    // label 2
    GtkWidget *label_root3_2 = gtk_label_new(_("3. Select a boot image for your device and have it patched by Magisk (Usually the boot images can be found on the Internet. Caution is advised here)."));
    gtk_label_set_wrap(GTK_LABEL(label_root3_2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root3_2), PANGO_WRAP_WORD_CHAR);	
    // label 3
    GtkWidget *label_root3_3 = gtk_label_new(_("4. Copy the boot image patched by Magisk to your computer. \n5. Rename the image to boot.img or let the application prepare it."));
    gtk_label_set_wrap(GTK_LABEL(label_root3_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root3_3), PANGO_WRAP_WORD_CHAR);	
    // label 4
    GtkWidget *label_root3_4 = gtk_label_new(_("6. Start your device to Fastboot. \n7. Flash the boot image for your device type. \n8. Reboot your device. Now Magisk should provide root privileges."));
    gtk_label_set_wrap(GTK_LABEL(label_root3_4), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_root3_4), PANGO_WRAP_WORD_CHAR);	
	
    // new button
    GtkWidget *button_root_5 = create_button_icon_no_callback("pan-start-symbolic", back_page_char);
    GtkWidget *button_root_6 = create_button_icon_no_callback("application-exit-symbolic", exit_page_char);
    
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
	
	LOGD("end instruction_root");
}
