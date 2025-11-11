/**
* reboot_heimdall.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// reboot to download from adb
static void reboot_from_adb_heimdall(GtkWidget *widget, gpointer stack)
{
    LOGD("reboot_from_adb_heimdall");
    
    // prevention of crashes
    if (!is_android_device_connected_adb()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(widget, error_message);
        return;
    }
    
    auto_free char *device_command = adb_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot download", device_command);
    show_spinner_dialog(GTK_WIDGET(widget), _("Rebooting Download"), _("Please wait..."), command);
    LOGD("end reboot_from_adb_heimdall");
}

// heimdall help
static void heimdall_help(GtkWidget *widget, gpointer stack)
{ 
    open_terminal_by_desktop("heimdall help");
}
	
// get pit
static void get_pit(GtkWidget *widget, gpointer stack) 
{
	LOGD("get_pit");
    const char *message = _("Please note that your device is in download mode!");
    show_info_dialog(widget, message);
    
    open_terminal_by_desktop("heimdall print-pit");
    LOGD("end get_pit");
}

// Function to set up button labels based on the language
void set_button_labels_reboot_heim(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Restart in Download"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Help"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Output pit"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Back"), sizeof(labels[3]));
}

/* main function - reboot_heimdall */
void reboot_heimdall(GtkWidget *widget, gpointer stack)
{
	LOGD("reboot_heimdall");
    
    char labels[4][30];  // labels for the button 
    set_button_labels_reboot_heim(labels);  // for both languages
    
    GtkWidget *reboot_heimdall = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(reboot_heimdall, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(reboot_heimdall, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button(labels[0], G_CALLBACK(reboot_from_adb_heimdall), stack);
    GtkWidget *btn2 = create_button(labels[1], G_CALLBACK(heimdall_help), stack);
    GtkWidget *btn3 = create_button(labels[2], G_CALLBACK(get_pit), stack);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[3], G_CALLBACK(reboot_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(reboot_heimdall), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(reboot_heimdall), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "reboot_heimdall")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), reboot_heimdall, "reboot_heimdall");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "reboot_heimdall");
           
    LOGD("end reboot_heimdall");
}
