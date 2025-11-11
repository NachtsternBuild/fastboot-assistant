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

// function that start wsl_config
static void start_wsl_config(GtkWidget *widget, gpointer stack) 
{
    wsl_config();
}

// function start post_update
static void run_post_update(GtkWidget *widget, gpointer stack)
{
	post_update();
}

// function restart the update
static void run_setup(GtkWidget *widget, gpointer stack)
{
	LOGD("run_setup");
	char restart_setup[2048];
	char restart_setup_file_dark[2048];
	char restart_setup_file_path[2048];
	char restart_setup_file_config[2048];
	
	// get config dir
    get_config_dir(restart_setup, sizeof(restart_setup));
    
    // config files
    snprintf(restart_setup_file_dark, sizeof(restart_setup_file_dark), "%s/dark.txt", restart_setup);
    snprintf(restart_setup_file_path, sizeof(restart_setup_file_path), "%s/path_config.txt", restart_setup);
    snprintf(restart_setup_file_config, sizeof(restart_setup_file_config), "%s/config/config.txt", restart_setup);
	
	// delete config files
	remove_file(restart_setup_file_dark);
	remove_file(restart_setup_file_path);
	remove_file(restart_setup_file_config);
	
	// start first setup
	run_first_run_setup(stack);
	LOGD("end run_setup");
}

// function to clean the log
static void clean_log(GtkWidget *widget, gpointer stack)
{
	LOGD("clean_log");
	char log_dir_settings[4096];
    char log_file_settings_path[4096];
    char log_file_settings[4096];
        
    // get config dir
    get_config_dir(log_dir_settings, sizeof(log_dir_settings));
    
    // log file with path
    snprintf(log_file_settings_path, sizeof(log_file_settings_path), "%s/log", log_dir_settings);
    snprintf(log_file_settings, sizeof(log_file_settings), "%s/log/log.txt", log_dir_settings);
    // delete files in dir
    LOGD("Remove: %s", log_file_settings_path);
    delete_files_in_dir(log_file_settings_path);
    
    // create log_dir
    // only if it not exsists
    if (access(log_file_settings_path, F_OK) == -1) 
    {
        create_directory(log_file_settings_path);
    }
    // open log file or create it
    int log_fd = open(log_file_settings, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_fd == -1) 
    {
        LOGE("Error when opening the log file.");
        exit(1);
    }
    close(log_fd);
    
    snprintf(success_message, sizeof(success_message), _("Completed"));
    show_info_dialog(widget, success_message);
    
    LOGD("end clean_log");
}

// function to create a new setup dir
static void new_setup_dir(GtkWidget *widget, gpointer stack)
{
	LOGD("new_setup_dir");
	char old_dir_path[4096];
    char old_dir_file[4096];
    
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
void set_button_labels_config_projekt(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Create folder"), sizeof(labels[0]));
	g_strlcpy(labels[1], _("Clean up"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Configure"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Updates"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("System Informations"), sizeof(labels[4]));
    g_strlcpy(labels[5], _("Clean log"), sizeof(labels[5]));
    g_strlcpy(labels[6], _("Define new directory"), sizeof(labels[6]));
    g_strlcpy(labels[7], _("Post update"), sizeof(labels[7]));
    g_strlcpy(labels[8], _("Restart Setup"), sizeof(labels[8]));
    g_strlcpy(labels[9], _("Back to Home"), sizeof(labels[9]));
}


/* main function - config-projekt_GUI*/
void config_projekt_GUI(GtkWidget *widget, gpointer stack) 
{
	LOGD("config_projekt_GUI");
    
    char labels[10][30];  // labels for the button 
    set_button_labels_config_projekt(labels);  // for both languages
    
    GtkWidget *config_projekt_GUI = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(config_projekt_GUI, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(config_projekt_GUI, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button_icon_position("folder-new-symbolic", labels[0], G_CALLBACK(start_make_dir_function), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("user-trash-full-symbolic", labels[1], G_CALLBACK(remove_old), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_button_icon_position("applications-engineering-symbolic", labels[2], G_CALLBACK(start_wsl_config), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn4 = create_button_icon_position("software-update-available-symbolic", labels[3], G_CALLBACK(updater), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn5 = create_button_icon_position("start-here-symbolic", labels[4], G_CALLBACK(info_tools), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn6 = create_button_icon_position("folder-documents-symbolic", labels[5], G_CALLBACK(clean_log), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn7 = create_button_icon_position("folder-open-symbolic", labels[6], G_CALLBACK(new_setup_dir), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn8 = create_button_icon_position("system-software-update-symbolic", labels[7], G_CALLBACK(run_post_update), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn9 = create_button_icon_position("start-here-symbolic", labels[8], G_CALLBACK(run_setup), stack, GTK_ALIGN_CENTER);
	GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[9], G_CALLBACK(show_home_page), stack, GTK_ALIGN_CENTER);

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
    gtk_grid_attach(GTK_GRID(grid), btn7, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn8, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn9, 2, 2, 1, 1);

    // pack the grid to the box
    gtk_box_append(GTK_BOX(config_projekt_GUI), grid);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(config_projekt_GUI), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "config_projekt_GUI")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), config_projekt_GUI, "config_projekt_GUI");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "config_projekt_GUI");

    LOGD("end config_projekt_GUI");
}
