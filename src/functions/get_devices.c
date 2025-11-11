/**
* get_devices.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

#define MAX_BUFFER_SIZE 256

// callback functions for each button
// check connected adb devices
static void get_adb(GtkWidget *widget, gpointer stack) 
{
    LOGD("get_adb");
    auto_free char *device_command = adb_command();
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, "%s devices", device_command);
    connected_devices(command, _("Desvices (ADB)"));
    LOGD("end get_adb");
}

// check connected fastboot devices
static void get_fastboot(GtkWidget *widget, gpointer stack) 
{
    LOGD("get_fastboot");
    auto_free char *device_command = fastboot_command();
    char command[MAX_BUFFER_SIZE];
    snprintf(command, MAX_BUFFER_SIZE, "%s devices", device_command);
    connected_devices(command, _("Devcies (fastboot)"));
    LOGD("end get_fastboot");
}

// get bootloader status
static void bootloader_status_adb(GtkWidget *widget, gpointer stack)
{
	LOGD("bootloader_status_adb");
	auto_free char *device_command = adb_command();
    char command[MAX_BUFFER_SIZE];
    
    // prevention of crashes
    if (!is_android_device_connected()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }

    snprintf(command, MAX_BUFFER_SIZE, "%s shell getprop ro.boot.flash.locked", device_command);
    connected_devices(command, _("Bootloader Status (ADB)"));
    LOGD("end bootloader_status_adb");
}

// get bootloader status
static void bootloader_status_fastboot(GtkWidget *widget, gpointer stack)
{
	LOGD("bootloader_status_fastboot");
	auto_free char *device_command = fastboot_command();
    char command[MAX_BUFFER_SIZE];
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
	
    snprintf(command, MAX_BUFFER_SIZE, "%s getvar unlocked", device_command);
    connected_devices(command, _("Bootloader Status (fastboot)"));
    LOGD("bootloader_status_fastboot");
}

// function to set up button labels based on the language
void set_button_labels_get_devices(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Devices in ADB"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Devices in Fastboot"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Bootloader status (ADB)"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Bootloader status (fastboot)"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("Back to Home"), sizeof(labels[4]));
}


/* main function - get_devices */
void get_devices(GtkWidget *widget, gpointer stack) 
{ 
    LOGD("get_devices");
    
    char labels[5][30];  // labels for the button 
    set_button_labels_get_devices(labels);  // for both languages
    
    // create box for get_devices
    GtkWidget *get_devices = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(get_devices, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(get_devices, GTK_ALIGN_CENTER);
	
	// create a grid
    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create the button for get_devices
    GtkWidget *btn1 = create_button_icon_position("content-loading-symbolic", labels[0], G_CALLBACK(get_adb), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("preferences-other-symbolic", labels[1], G_CALLBACK(get_fastboot), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_button_icon_position("content-loading-symbolic", labels[2], G_CALLBACK(bootloader_status_adb), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn4 = create_button_icon_position("preferences-other-symbolic", labels[3], G_CALLBACK(bootloader_status_fastboot), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[4], G_CALLBACK(show_home_page), stack, GTK_ALIGN_CENTER);
	
    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn4, 1, 1, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(get_devices), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(get_devices), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "get_devices")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), get_devices, "get_devices");
    }
    
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "get_devices");
	LOGD("end get_devices");
}
