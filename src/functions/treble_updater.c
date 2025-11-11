/**
* connected_devices.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

GtkWidget *boot_checkbox;
GtkWidget *system_checkbox;
GtkWidget *set_active_slot_checkbox;
GtkWidget *bootctl_status_label;

// function that flash the images in the inactive slot and set a new active slot
void update_device(GtkWidget *widget, gpointer stack) 
{      
    char config_file[4096];
    char boot_image[4096];
    char system_image[4096];
    char command_build[4096];
    const char *boot_image_name = "boot.img";
	const char *system_image_name = "system.img";
	// define list for commands
	GSList *commands = NULL;
	
    // get the inactive slot
    char *inactive_slot = get_inactive_slot();
    // get the adb command
    char *device_command = adb_command();
    // get the config file
    get_config_file_path(config_file, sizeof(config_file));
    // load the path
    const char *image_path = load_path_from_file(config_file);

    if (image_path) 
    {
        LOGD("Loaded path: %s", image_path);
    }
	
	// create the path from the images
	snprintf(boot_image, sizeof(boot_image), "%s/%s", image_path, boot_image_name);
	snprintf(system_image, sizeof(system_image), "%s/%s", image_path, system_image_name);
        
    // wait for a device
    snprintf(command_build, sizeof(command_build), "%s wait-for-device", device_command);
        
    CommandEntry *entry1 = g_new0(CommandEntry, 1);
    entry1->cmd = g_strdup(command_build); 
    entry1->description = g_strdup(_("Getting devices...")); 
    commands = g_slist_append(commands, entry1);
	
	// multiple options for the treble updater
	// flash new boot.img
    if (gtk_check_button_get_active(GTK_CHECK_BUTTON(boot_checkbox)))
	{
    	// push image to the device
    	snprintf(command_build, sizeof(command_build), "%s push %s /data/local/tmp/boot.img", device_command, boot_image);
    	
    	CommandEntry *entry2 = g_new0(CommandEntry, 1);
    	entry2->cmd = g_strdup(command_build); 
    	entry2->description = g_strdup(_("Copy boot.img...")); 
    	commands = g_slist_append(commands, entry2);
    	
    	// copy the image in the inactive slot
    	// with 'wait' and 'sync' the adb should wait that 'dd' finished
    	snprintf(command_build, sizeof(command_build), "%s shell su -c dd if=/data/local/tmp/boot.img of=/dev/block/by-name/boot%s & PID=$!; wait $PID; sync'", device_command, inactive_slot);
    	
    	CommandEntry *entry3 = g_new0(CommandEntry, 1);
    	entry3->cmd = g_strdup(command_build); 
    	entry3->description = g_strdup(_("Installing boot...")); 
    	commands = g_slist_append(commands, entry3);
    	
    	// remove the image in tmp/
    	snprintf(command_build, sizeof(command_build), "%s shell su -c rm -f /data/local/tmp/boot.img", device_command);
    	
    	CommandEntry *entry4 = g_new0(CommandEntry, 1);
    	entry4->cmd = g_strdup(command_build); 
    	entry4->description = g_strdup(_("Cleaning up...")); 
    	commands = g_slist_append(commands, entry4);
	}

	// flash new system.img
	if (gtk_check_button_get_active(GTK_CHECK_BUTTON(system_checkbox))) 
	{
    	// push image to the device
    	snprintf(command_build, sizeof(command_build), "%s push %s /data/local/tmp/system.img", device_command, system_image);
    	
    	CommandEntry *entry5 = g_new0(CommandEntry, 1);
    	entry5->cmd = g_strdup(command_build); 
    	entry5->description = g_strdup(_("Copy system.img...")); 
    	commands = g_slist_append(commands, entry5);
    	
    	
    	// copy the image in the inactive slot
    	// with 'wait' and 'sync' the adb should wait that 'dd' finished
    	snprintf(command_build, sizeof(command_build), "%s shell su -c 'dd if=/data/local/tmp/system.img of=/dev/block/by-name/system%s & PID=$!; wait $PID; sync'", device_command, inactive_slot);
		
		CommandEntry *entry6 = g_new0(CommandEntry, 1);
    	entry6->cmd = g_strdup(command_build); 
    	entry6->description = g_strdup(_("Installing system...")); 
    	commands = g_slist_append(commands, entry6);

    	// remove the image in tmp/
    	snprintf(command_build, sizeof(command_build), "%s shell su -c rm -f /data/local/tmp/system.img", device_command);
    	
    	CommandEntry *entry7 = g_new0(CommandEntry, 1);
    	entry7->cmd = g_strdup(command_build); 
    	entry7->description = g_strdup(_("Cleaning up...")); 
    	commands = g_slist_append(commands, entry7);
	}
	
	// get the bootctl
	snprintf(command_build, sizeof(command_build), "%s shell su -c bootctl", device_command);
	
	CommandEntry *entry8 = g_new0(CommandEntry, 1);
    entry8->cmd = g_strdup(command_build); 
    entry8->description = g_strdup(_("Checking bootctl...")); 
    commands = g_slist_append(commands, entry8);
	
  	// set the active slot with the bootctl
   	snprintf(command_build, sizeof(command_build), "%s shell su -c bootctl set-active-boot-slot %d", device_command, inactive_slot[1] == 'b' ? 0 : 1);
   	
   	CommandEntry *entry9 = g_new0(CommandEntry, 1);
    entry9->cmd = g_strdup(command_build); 
    entry9->description = g_strdup(_("Setting active slot...")); 
    commands = g_slist_append(commands, entry9);
    
    // alternative way to set new active slot
    // I won't use this, because using bootctl is better	
   	if (gtk_check_button_get_active(GTK_CHECK_BUTTON(set_active_slot_checkbox)))
   	{
    	snprintf(command_build, sizeof(command_build), "%s shell su -c setprop persist.sys.boot.slot %s", device_command, inactive_slot);
    	
    	CommandEntry *entry10 = g_new0(CommandEntry, 1);
    	entry10->cmd = g_strdup(command_build); 
    	entry10->description = g_strdup(_("Setting active slot...")); 
    	commands = g_slist_append(commands, entry10);
	}
    
    // show the dialog and run the commands
    show_progress_dialog_multi(main_window, "Treble Updater", "This may take some time...", commands);
    
    if (image_path != NULL) 
	{
    	g_free((gpointer)image_path); // free this (because g_file_get_contents was used)
	}
    free(device_command);
}

// function to reboot use 'adb reboot'
void restart_system(GtkWidget *widget, gpointer stack)
{
	LOGD("Restart with ADB");
	char command_build[2048];
	auto_free char *device_command = adb_command();
	snprintf(command_build, sizeof(command_build), "%s reboot", device_command);
	
	const char *title = _("Treble Updater");
	const char *body = _("Rebooting device...");
    show_progress_dialog(widget, title, body, command_build);
}

/* main function - treble_updater */
void treble_updater(GtkWidget *widget, gpointer stack) 
{
    LOGD("treble_updater");
        
    // create box for the treble updater
    GtkWidget *treble_updater = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(treble_updater, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(treble_updater, GTK_ALIGN_CENTER);
    
    // some free space
    GtkWidget *free_space1 = gtk_label_new(" ");
    
    // some informations
    GtkWidget *info_treble = gtk_label_new(_("The Treble Updater only works with a/b devices. Root rights must be provided."));
	gtk_label_set_wrap(GTK_LABEL(info_treble), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(info_treble), PANGO_WRAP_WORD_CHAR);
    
    
    GtkWidget *info2_treble = gtk_label_new(_("The Treble Updater has the task of flashing a new boot/system image into the inactive slot and making it active."));
	gtk_label_set_wrap(GTK_LABEL(info2_treble), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(info2_treble), PANGO_WRAP_WORD_CHAR);
      
    // root info label
    GtkWidget *root_status_info = gtk_label_new(_("Root permission:"));

    // root status label
    root_status_label = gtk_label_new("Check Root permission...");
    
    // bootctl info label
    GtkWidget *bootctl_status_info = gtk_label_new(_("Bootctl:"));

    // bootctl status label
    bootctl_status_label = gtk_label_new("Search for bootctl...");
	
	/* the button for the action */		
    // checkbox for boot.img
    boot_checkbox = gtk_check_button_new_with_label(_("Flash new boot image"));
	
	// checkbox for system.img
    system_checkbox = gtk_check_button_new_with_label(_("Flash new system image"));
	
	// use option to set active slot with setprop
    set_active_slot_checkbox = gtk_check_button_new_with_label(_("Alternative for slot change (not recommended)"));
	
	// Start the flash
    const char *start_button_char = _("Start Flash");
    GtkWidget *start_button = create_button_icon_position("drive-multidisk-symbolic", start_button_char, G_CALLBACK(update_device), stack, GTK_ALIGN_CENTER);
	
	// restart the system
	const char *restarting_system_char = _("Reboot Device");
	GtkWidget *restarting_system = create_button_icon_position("system-reboot-symbolic", restarting_system_char, G_CALLBACK(restart_system), stack, GTK_ALIGN_CENTER);
	
	// function to show the home page
	const char *back_to_home_char = _("Back to Home");
	GtkWidget *back_to_home = create_button_icon_position("pan-start-symbolic", back_to_home_char, G_CALLBACK(show_home_page), stack, GTK_ALIGN_CENTER);
	  
    
    // add everything to the box
    gtk_box_append(GTK_BOX(treble_updater), free_space1);
    gtk_box_append(GTK_BOX(treble_updater), info_treble);
    gtk_box_append(GTK_BOX(treble_updater), info2_treble); 
    gtk_box_append(GTK_BOX(treble_updater), root_status_info);
    gtk_box_append(GTK_BOX(treble_updater), root_status_label);
    gtk_box_append(GTK_BOX(treble_updater), bootctl_status_info); 
    gtk_box_append(GTK_BOX(treble_updater), bootctl_status_label);
    gtk_box_append(GTK_BOX(treble_updater), boot_checkbox);
    gtk_box_append(GTK_BOX(treble_updater), system_checkbox);
    gtk_box_append(GTK_BOX(treble_updater), set_active_slot_checkbox);
    gtk_box_append(GTK_BOX(treble_updater), start_button);
    gtk_box_append(GTK_BOX(treble_updater), restarting_system);
    gtk_box_append(GTK_BOX(treble_updater), back_to_home);
    
    // set position of the labels
    gtk_widget_set_halign(info_treble, GTK_ALIGN_START);
    gtk_widget_set_halign(info2_treble, GTK_ALIGN_START);
    
    // same start of the labels
    gtk_widget_set_margin_start(info_treble, 15);
    gtk_widget_set_margin_start(info2_treble, 15);
        
    // is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "treble_updater")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), treble_updater, "treble_updater");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "treble_updater");
	
	// check root access at the start
    check_root_access(root_status_label);
    // chech for android bootctl
    get_bootctl(bootctl_status_label);
	
	LOGD("end treble_updater");
}
    
    
