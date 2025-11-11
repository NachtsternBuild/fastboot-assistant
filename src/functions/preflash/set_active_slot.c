/**
* set_active_slot.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

#define BUFFER_SIZE 2048

char slot_command[2048];

// button 1 - set slot a
static void set_slot_a(GtkWidget *widget, gpointer stack)
{
    LOGD("set_slot_a");
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    auto_free char *device_command = fastboot_command();
	snprintf(slot_command, sizeof(slot_command), "%s set_active a && %s getvar current-slot", device_command, device_command);
	LOGD("Run: %s", slot_command);
    show_spinner_dialog(GTK_WIDGET(widget), _("Setting slot"), _("Please wait..."), slot_command);  
    LOGD("end set_slot_a");
}

// button 2 - set slot b
static void set_slot_b(GtkWidget *widget, gpointer stack)
{
    LOGD("set_slot_b");
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
   
    auto_free char *device_command = fastboot_command();
	snprintf(slot_command, sizeof(slot_command), "%s set_active b && %s getvar current-slot", device_command, device_command);
	LOGD("Run: %s", slot_command);
    show_spinner_dialog(GTK_WIDGET(widget), _("Setting slot"), _("Please wait..."), slot_command);
    LOGD("end set_slot_b");
}

// button 3 - set the slot automatic
static void set_slot_auto(GtkWidget *widget, gpointer stack)
{
	LOGD("set_slot_auto");
	char active_slot[BUFFER_SIZE] = {0};
    char inactive_slot[BUFFER_SIZE] = {0};

    // get active slot
    check_active_slot(active_slot, sizeof(active_slot));
    LOGD("active slot: %s", active_slot);

    // get inactive slot
    if (strcmp(active_slot, "a") == 0) 
    {
        strncpy(inactive_slot, "b", sizeof(inactive_slot) - 1);
        LOGD("inactive slot: %s", inactive_slot);
    } 
    
    else if (strcmp(active_slot, "b") == 0) 
    {
        strncpy(inactive_slot, "a", sizeof(inactive_slot) - 1);
        LOGD("inactive slot: %s", inactive_slot);
    } 
    
    else 
    {
        LOGE("Unknown active slot: %s", active_slot);
        exit(1);
    }
    
    auto_free char *device_command = fastboot_command();
    // create the command
    snprintf(slot_command, sizeof(slot_command), "%s set_active %s && %s getvar current-slot", device_command, inactive_slot, device_command);
    LOGD("Run: %s", slot_command);
       
    // set the new active slot
    show_spinner_dialog(GTK_WIDGET(widget), _("Setting slot"), _("Please wait..."), slot_command);
	LOGD("end set_slot_auto");
}

// function to set up button labels based on the language
void set_button_labels_slot(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Set 'a'"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Set 'b'"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Set slot auto"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Back"), sizeof(labels[3]));
}

/* start main programm */
void set_active_slot(GtkWidget *widget, gpointer stack)
{
    LOGD("set_active_slot");
    
    char labels[4][30];  // labels for the button 
    set_button_labels_slot(labels);  // for both languages
    
    GtkWidget *set_active_slot = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(set_active_slot, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(set_active_slot, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button_icon_position("network-receive-symbolic", labels[0], G_CALLBACK(set_slot_a), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("network-transmit-symbolic", labels[1], G_CALLBACK(set_slot_b), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_button_icon_position("network-transmit-receive-symbolic", labels[2], G_CALLBACK(set_slot_auto), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[3], G_CALLBACK(preflash_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(set_active_slot), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(set_active_slot), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "set_active_slot")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), set_active_slot, "set_active_slot");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "set_active_slot");
        
    LOGD("end set_active_slot");
}
    
