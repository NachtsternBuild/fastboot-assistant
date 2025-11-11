/**
* lock_unlock_bootloader.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

char bootloader_lock_command[2048];

// button 1 - unlock bootloader new
static void bootloader_new(GtkWidget *widget, gpointer stack)
{
    LOGD("bootloader_new");
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    auto_free char *device_command = fastboot_command();
    snprintf(bootloader_lock_command, sizeof(bootloader_lock_command), "%s flashing unlock", device_command);
    LOGD("Run: %s", bootloader_lock_command);
    show_spinner_dialog(GTK_WIDGET(widget), _("Unlocking Bootloader"), _("Please wait..."), bootloader_lock_command);
    LOGD("end bootloader_new");
}

// button 2 - unlock bootloader old
static void bootloader_old(GtkWidget *widget, gpointer stack)
{
    LOGD("bootloader_old");
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    auto_free char *device_command = fastboot_command();
    snprintf(bootloader_lock_command, sizeof(bootloader_lock_command), "%s oem unlock", device_command);
    LOGD("Run: %s", bootloader_lock_command);
    show_spinner_dialog(GTK_WIDGET(widget), _("Unlocking Bootloader"), _("Please wait..."), bootloader_lock_command);
    LOGD("end bootloader_old");
}

// button 3 - lock bootloader
static void bootloader_lock(GtkWidget *widget, gpointer stack)
{
    LOGD("bootloader_lock");
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    auto_free char *device_command = fastboot_command();
    snprintf(bootloader_lock_command, sizeof(bootloader_lock_command), "%s flashing lock", device_command);
    LOGD("Run: %s", bootloader_lock_command);
    show_spinner_dialog(GTK_WIDGET(widget), _("Locking Bootloader"), _("Please wait..."), bootloader_lock_command);
    LOGD("end bootloader_lock");
}

// function to set up button labels based on the language
void set_button_labels_bootloader(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Unlock (new)"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Unlock (old)"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Lock"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Back"), sizeof(labels[3]));
}

/* main programm - lock_unlock_bootloader*/
void lock_unlock_bootloader(GtkWidget *widget, gpointer stack)
{
	LOGD("lock_unlock_bootloader");
    
    char labels[4][30];  // labels for the button 
    set_button_labels_bootloader(labels);  // for both languages
    
    GtkWidget *lock_unlock_bootloader = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(lock_unlock_bootloader, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(lock_unlock_bootloader, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button_icon_position("changes-allow-symbolic", labels[0], G_CALLBACK(bootloader_new), stack, GTK_ALIGN_CENTER); 
    GtkWidget *btn2 = create_button_icon_position("changes-allow-symbolic", labels[1], G_CALLBACK(bootloader_old), stack, GTK_ALIGN_CENTER); 
    GtkWidget *btn3 = create_button_icon_position("changes-prevent-symbolic", labels[2], G_CALLBACK(bootloader_lock), stack, GTK_ALIGN_CENTER); 
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[3], G_CALLBACK(preflash_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(lock_unlock_bootloader), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(lock_unlock_bootloader), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "lock_unlock_bootloader")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), lock_unlock_bootloader, "lock_unlock_bootloader");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "lock_unlock_bootloader");
        
    LOGD("end lock_unlock_bootloader");
}
