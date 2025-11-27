/**
* config-project.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

char success_message[4096];

// Callback functions for each button
// function that start make_dir
static void start_make_dir_function(GtkWidget *widget, gpointer stack) 
{
    const char *message = _("Ready!");
    make_dir();
    show_info_dialog(widget, message);
}

// function start post_update
static void run_post_update(GtkWidget *widget, gpointer stack)
{
	post_update();
}


// function to create a new setup dir
static void new_setup_dir(GtkWidget *widget, gpointer stack)
{
	LOGD("new_setup_dir");
	char old_dir_path[256];
    char old_dir_file[280];
    
    // logic to remove old path_config.txt
    // get config dir
    get_config_dir(old_dir_path, sizeof(old_dir_path));
    
    // remove path_config
    snprintf(old_dir_file, sizeof(old_dir_file), "%s/path_config.txt", old_dir_path);
    // delete file in dir
    remove_file(old_dir_file);
		    
    // transform the callback
    gpointer callback_data = (gpointer)process_selected_setup_folder;
	// start the folder chooser
    show_folder_chooser(widget, callback_data);

	LOGD("end new_setup_dir");
}

// Function to set up button labels based on the language
void set_button_labels_config_project(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Create folder"), sizeof(labels[0]));
	g_strlcpy(labels[1], _("Cleanup"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Configure"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Post Update"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("System Informations"), sizeof(labels[4]));
    g_strlcpy(labels[5], _("Define new directory"), sizeof(labels[6]));
    g_strlcpy(labels[6], _("Updates"), sizeof(labels[7]));
    g_strlcpy(labels[7], _("Back to Home"), sizeof(labels[9]));
}


/* main function - config-projekt_GUI*/
void config_project_GUI(GtkWidget *widget, gpointer stack) 
{
	LOGD("config_project_GUI");
    
    char labels[10][30];  // labels for the button 
    set_button_labels_config_project(labels);  // for both languages
    
    GtkWidget *config_project_GUI = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(config_project_GUI, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(config_project_GUI, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button_icon_position("folder-new-symbolic", labels[0], G_CALLBACK(start_make_dir_function), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("user-trash-full-symbolic", labels[1], G_CALLBACK(remove_old), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_button_icon_position("applications-engineering-symbolic", labels[2], G_CALLBACK(wsl_config), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn4 = create_button_icon_position("system-software-update-symbolic", labels[3], G_CALLBACK(run_post_update), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn5 = create_button_icon_position("start-here-symbolic", labels[4], G_CALLBACK(info_tools), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn6 = create_button_icon_position("folder-open-symbolic", labels[5], G_CALLBACK(new_setup_dir), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn7 = create_button_icon_position("software-update-available-symbolic", labels[6], G_CALLBACK(updater), stack, GTK_ALIGN_CENTER);
	GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[7], G_CALLBACK(show_home_page), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    // line 1
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);
    // line 2 (1)
    gtk_grid_attach(GTK_GRID(grid), btn4, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn5, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn6, 2, 1, 1, 1);
    // line 3 (2)
    //gtk_grid_attach(GTK_GRID(grid), btn7, 0, 2, 1, 1);
    //gtk_grid_attach(GTK_GRID(grid), btn8, 1, 2, 1, 1);
    //gtk_grid_attach(GTK_GRID(grid), btn9, 2, 2, 1, 1);
	
	// get the env of the application
	// enable updater at debug mode
	if (debug_mode)
	{
		gtk_widget_set_visible(GTK_WIDGET(btn7), TRUE);
	}
	// disable updater for snap/flatpak/PPA version
	if (snap_app || flatpak_app || ppa_app) 
	{
	    gtk_widget_set_visible(GTK_WIDGET(btn7), FALSE);
	} 
	// enable updater for local version
	else 
	{
	    gtk_widget_set_visible(GTK_WIDGET(btn7), TRUE);
	}
	
    // pack the grid to the box
    gtk_box_append(GTK_BOX(config_project_GUI), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(config_project_GUI), btn7);
    gtk_box_append(GTK_BOX(config_project_GUI), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "config_project_GUI")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), config_project_GUI, "config_project_GUI");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "config_project_GUI");

    LOGD("end config_project_GUI");
}
