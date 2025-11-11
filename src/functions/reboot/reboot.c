/**
* reboot.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// reboot system
static void reboot_system(GtkWidget *widget, gpointer stack)
{
    LOGD("reboot_system");
        
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(widget, error_message);
        return;
    }
    
    // reboot from fastboot
    auto_free char *device_command = fastboot_command();
    char command[256];
    snprintf(command, sizeof(command), "%s reboot", device_command);
    show_spinner_dialog(GTK_WIDGET(widget), _("Rebooting"), _("Please wait..."), command);
    LOGD("end reboot_system");
}

// boot to an image
static void boot_to_image(const gchar *i_filename) 
{
    LOGD("boot_to_image");
    char boot_image[4096];
    char boot_command[4096];
    get_config_file_path(boot_image, sizeof(boot_image));
    // load the path
    const char *boot_image_path = load_path_from_file(boot_image);

    if (boot_image_path) 
    {
        LOGD("Loaded path: %s", boot_image_path);
    }
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }

    // create fastboot command
    auto_free char *device_command = fastboot_command(); 
    snprintf(boot_command, sizeof(boot_command), "%s boot %s/%s", device_command, boot_image_path, i_filename);
    LOGD("Run: %s \n", boot_command);
    
    show_spinner_dialog(GTK_WIDGET(main_window), _("Rebooting"), _("Please wait..."), boot_command);

    LOGD("end boot_to_image");
}

// function to set up button labels based on the language
void set_button_labels_reboot(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Reboot System"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Reboot Image(.img)"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Back"), sizeof(labels[2]));
} 

/* main function - reboot */
void reboot(GtkWidget *widget, gpointer stack)
{
	LOGD("reboot");
    
    char labels[3][30];  // labels for the button 
    set_button_labels_reboot(labels);  // for both languages
    
    GtkWidget *reboot = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(reboot, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(reboot, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button(labels[0], G_CALLBACK(reboot_system), stack);
    GtkWidget *btn2 = create_button(labels[1], G_CALLBACK(show_file_chooser), (gpointer)boot_to_image);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[2], G_CALLBACK(reboot_GUI), stack, GTK_ALIGN_CENTER);


    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(reboot), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(reboot), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "reboot")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), reboot, "reboot");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "reboot");
        
    LOGD("end reboot");
}
