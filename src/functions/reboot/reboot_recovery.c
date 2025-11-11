/**
* reboot_recovery.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// Callback functions for each button
// start reboot_recovery adb-function
static void start_recovery_adb(GtkWidget *widget, gpointer stack) 
{
    LOGD("start_recovery_adb");
    
    // prevention of crashes
    if (!is_android_device_connected_adb()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(widget, error_message);
        return;
    }
    
    auto_free char *device_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot recovery", device_command);
    show_spinner_dialog(GTK_WIDGET(widget), _("Rebooting Recovery"), _("Please wait..."), command);
    LOGD("end start_recovery_adb");
}

// start reboot_recovery fastboot
static void start_recovery_fastboot(GtkWidget *widget, gpointer stack) 
{
    LOGD("start_recovery_fastboot");
        
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(widget, error_message);
        return;
    }
    
    auto_free char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot recovery", device_command);
    show_spinner_dialog(GTK_WIDGET(widget), _("Rebooting Recovery"), _("Please wait..."), command);
    LOGD("end start_recovery_fastboot");
}

// function to set up button labels based on the language
void set_button_labels_reboot_recovery(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Restart ADB"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Restarting Fastboot"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Back"), sizeof(labels[2]));
} 


/* main function - reboot_recovery */
void reboot_recovery(GtkWidget *widget, gpointer stack) 
{
    LOGD("reboot_recovery");
    
    char labels[3][30];  // labels for the button 
    set_button_labels_reboot_recovery(labels);  // for both languages
    
    GtkWidget *reboot_recovery = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(reboot_recovery, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(reboot_recovery, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button(labels[0], G_CALLBACK(start_recovery_adb), stack);
    GtkWidget *btn2 = create_button(labels[1], G_CALLBACK(start_recovery_fastboot), stack);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[2], G_CALLBACK(reboot_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(reboot_recovery), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(reboot_recovery), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "reboot_recovery")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), reboot_recovery, "reboot_recovery");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "reboot_recovery");
    
    LOGD("end reboot_recovery");
}
