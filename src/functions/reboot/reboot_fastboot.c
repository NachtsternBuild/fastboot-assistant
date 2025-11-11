/**
* reboot_fastboot.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// reboot to bootloader from adb
static void reboot_from_adb(GtkWidget *widget, gpointer stack)
{
    LOGD("reboot_from_adb");
    
    // prevention of crashes
    if (!is_android_device_connected_adb()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(widget, error_message);
        return;
    }
    
    auto_free char *device_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s -d reboot bootloader", device_command);

    show_spinner_dialog(GTK_WIDGET(widget), _("Rebooting Bootloader"), _("Please wait..."), command);

    LOGD("end reboot_from_adb");
}

// reboot to bootloader from fastboot
static void reboot_from_fastboot(GtkWidget *widget, gpointer stack)
{
    LOGD("reboot_from_fastboot");
   
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(widget, error_message);
        return;
    }
    
    auto_free char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot bootloader", device_command);

    show_spinner_dialog(GTK_WIDGET(widget), _("Rebooting Bootloader"), _("Please wait..."), command);

    LOGD("end reboot_from_fastboot");
}
	
// start help-function
static void fastboot_help(GtkWidget *widget, gpointer stack) 
{
    LOGD("fastboot_help");
    
    auto_free char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s help", device_command);
    open_terminal_by_desktop(command);
    LOGD("end fastboot_help");
}

// get bootloader variablen-function
static void list_bootloader_var(GtkWidget *widget, gpointer stack) 
{
    LOGD("list_bootloader_var");
   
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(widget, error_message);
        return;
    }
    
    auto_free char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s getvar all", device_command);
    open_terminal_by_desktop(command);
    LOGD("end list_bootloader_var");
}

// Function to set up button labels based on the language
void set_button_labels_reboot_fast(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Restart ADB"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Restarting Fastboot"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Fastboot help"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Bootloader variables"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("Back"), sizeof(labels[4]));
}

/* main function - reboot_fastboot */
void reboot_fastboot(GtkWidget *widget, gpointer stack)
{
	LOGD("reboot_fastboot");
    
    char labels[5][30];  // labels for the button 
    set_button_labels_reboot_fast(labels);  // for both languages
    
    GtkWidget *reboot_fastboot = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(reboot_fastboot, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(reboot_fastboot, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button(labels[0], G_CALLBACK(reboot_from_adb), stack);
    GtkWidget *btn2 = create_button(labels[1], G_CALLBACK(reboot_from_fastboot), stack);
    GtkWidget *btn3 = create_button(labels[2], G_CALLBACK(fastboot_help), stack);
    GtkWidget *btn4 = create_button(labels[3], G_CALLBACK(list_bootloader_var), stack);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[4], G_CALLBACK(reboot_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    // line 1
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    // line 2
    gtk_grid_attach(GTK_GRID(grid), btn3, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn4, 1, 1, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(reboot_fastboot), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(reboot_fastboot), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "reboot_fastboot")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), reboot_fastboot, "reboot_fastboot");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "reboot_fastboot");

    LOGD("end reboot_fastboot");
}
