/**
* flash_system.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

#define BUFFER_SIZE 2048

// button handler functions
void system_to_inactiv(GtkWidget *widget, gpointer stack)
{
	LOGD("system_to_inactiv");
		
	char active_slot[BUFFER_SIZE] = {0};
    char inactive_slot[BUFFER_SIZE] = {0};
	
	// prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    // get active slot
    check_active_slot(active_slot, sizeof(active_slot));
    LOGD("active slot: %s", active_slot);

    // get inactive slot
    if (strcmp(active_slot, "a") == 0) 
    {
        strncpy(inactive_slot, "b", sizeof(inactive_slot) - 1);
    } 
    
    else if (strcmp(active_slot, "b") == 0) 
    {
        strncpy(inactive_slot, "a", sizeof(inactive_slot) - 1);
    } 
    
    else 
    {
        LOGE("Unknown active slot: %s", active_slot);
        exit(1);
    }
        
    char config_file[4096];
    char erase_command[BUFFER_SIZE];
	char function_command[4096];
	char image_info[BUFFER_SIZE];
    auto_free char *device_command = fastboot_command();
    
    // get the path of the image
    //set_main_dir_with_wsl(image_path, sizeof(image_path), "system.img");
    get_config_file_path(config_file, sizeof(config_file));
    // load the path
    const char *image_path = load_path_from_file(config_file);
    const char *image_name = "system.img";

    if (image_path) 
    {
        LOGD("Loaded path: %s", image_path);
    }
	
	// create the image path
	snprintf(image_info, sizeof(image_info), "%s/%s", image_path, image_name);
    
    // create command for erase inactive system
    snprintf(erase_command, sizeof(erase_command), "%s erase system_%s", device_command, inactive_slot);
        
    // create command to flash system.img and add erase command
    snprintf(function_command, sizeof(function_command), "%s && %s flash system_%s %s && %s set_active %s", erase_command, device_command, inactive_slot, image_info, device_command, inactive_slot);
	
	// check if the image not exists
    if (access(image_info, F_OK) == -1)
    {      
        const char *error_message = _("Image file not found.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        LOGE("%s", error_message);
        return;
    }
	        
    const char *title = _("Fastboot Running");
    const char *body = _("Flashing...");
    show_progress_dialog(widget, title, body, function_command);
		
	if (image_path != NULL) 
	{
    	g_free((gpointer)image_path); // free the info (because g_file_get_contents was used)
	}
	
	LOGD("end system_to_inactiv");
}

// function to flash system.img
void system_to_activ(GtkWidget *widget, gpointer stack)
{
    LOGD("system_to_activ");
    char function_command[3072];
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    auto_free char *device_command = fastboot_command();
    snprintf(function_command, sizeof(function_command), "%s erase system", device_command);
    LOGD("Run: %s", function_command);
    const char *title = _("Fastboot Running");
    const char *body = _("Erasing old files...");
    show_spinner_dialog(widget, title, body, function_command);
    
    flash_image(widget, "system", NULL, "system.img", NULL);
    LOGD("end system_to_activ");
}

// flash system.img (heimdall)
void system_to_activ_heimdall(GtkWidget *widget, gpointer stack)
{
    LOGD("system_to_activ_heimdall");
    flash_heimdall(widget, "SYSTEM", "system.img");
    LOGD("end system_to_activ_heimdall");
}

// function to set up button labels based on the language
void set_button_labels_flash_system(char labels[][30]) 
{
    g_strlcpy(labels[0], _("System"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("System (heimdall)"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("System (inactive)"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Back"), sizeof(labels[3]));
}

/* main function - flash_system */
void flash_system(GtkWidget *widget, gpointer stack)
{
	LOGD("flash_system");
    
    char labels[4][30];  // labels for the button 
    set_button_labels_flash_system(labels);  // for both languages
    
    GtkWidget *flash_system = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(flash_system, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(flash_system, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button(labels[0], G_CALLBACK(system_to_activ), stack);
    GtkWidget *btn2 = create_button(labels[1], G_CALLBACK(system_to_activ_heimdall), stack);
    GtkWidget *btn3 = create_button(labels[2], G_CALLBACK(system_to_inactiv), stack);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[3], G_CALLBACK(flash_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(flash_system), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(flash_system), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "flash_system")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), flash_system, "flash_system");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "flash_system");
    
    LOGD("end flash_system");
}
