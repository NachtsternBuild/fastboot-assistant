/**
* backup_noroot.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

#define MAX_BUFFER_SIZE 3072

char install_command_backup[2048];

// function that Install dependencies with root rights 
static void install_depends(GtkWidget *widget, gpointer stack) 
{
    // for wsl
    if (directory_exists("/mnt/c/Users")) 
    {
        // use the cmd.exe to start a new cmd with wsl.exe
		snprintf(install_command_backup, sizeof(install_command_backup), "apt-get install p7zip-full secure-delete whiptail curl dos2unix pv bc zenity '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev -y");
    }  
    // for linux
    else 
    {
    	snprintf(install_command_backup, sizeof(install_command_backup), "apt install p7zip-full adb curl whiptail pv bc secure-delete zenity -y");
    }
        
    LOGD("Run: %s", install_command_backup);

    // run command with pkexec
    command_pkexec_spinner(widget, install_command_backup, _("Install Depends"), _("Please wait..."));
}

// download the backup
static void download_backup(GtkWidget *widget, gpointer stack) 
{
	char path_file[4096];
    char main_path_build[4096];
    char wget_command[16384];
    // load path
    get_config_file_path(path_file, sizeof(path_file));
    // load the path
    const char *path_file_load = load_path_from_file(path_file);

    if (path_file_load) 
    {
        LOGD("Loaded path: %s", path_file_load);
    }
    snprintf(main_path_build, sizeof(main_path_build), "%s/Backup/Noroot/Open_Android_Backup_v1.2.0_Bundle", path_file_load);
    snprintf(wget_command, sizeof(wget_command), "wget -O %s https://github.com/mrrfv/open-android-backup/releases/download/v1.2.0/Open_Android_Backup_v1.2.0_Bundle.zip && unzip %s.zip -d %s", main_path_build, main_path_build, main_path_build);
	
    LOGD("Run: %s", wget_command);
    show_spinner_dialog(GTK_WIDGET(widget), _("Downloading Backup Tool"), _("Please wait..."), wget_command);
    
    if (path_file_load != NULL) 
	{
    	g_free((gpointer)path_file_load); // free the info (because g_file_get_contents was used)
	}
}

// start backup
static void open_backup(GtkWidget *widget, gpointer stack) 
{
    char bash_command[4096];
    char run_open_backup[4096];
    // load path
    get_config_file_path(run_open_backup, sizeof(run_open_backup));
    // load the path
    const char *run_open_backup_bash = load_path_from_file(run_open_backup);

    if (run_open_backup_bash) 
    {
        LOGD("Loaded path: %s", run_open_backup_bash);
    }
    // build command
    snprintf(bash_command, sizeof(bash_command), "bash %s/Backup/Noroot/Open_Android_Backup_v1.2.0_Bundle/backup.sh", run_open_backup_bash);
    open_terminal_by_desktop(bash_command);
    
    if (run_open_backup_bash != NULL) 
	{
    	g_free((gpointer)run_open_backup_bash); // free the info (because g_file_get_contents was used)
	}
}

static void show_backup_help(GtkWidget *widget, gpointer stack)
{
	const char *title = _("Backup No Root in Sandbox");
	const char *message = _("Due to the Snap/Flatpak sandbox, it is not possible to execute commands as root on the host. Run the following command on your host: \napt install p7zip-full adb curl whiptail pv bc secure-delete zenity");
	show_dialog_title(widget, title, message);
}

// Function to set up button labels based on the language
void set_button_labels_backup_noroot(char labels[][30]) 
{
    g_strlcpy(labels[0], _("Prepare"), sizeof(labels[0]));
    g_strlcpy(labels[1], _("Download"), sizeof(labels[1]));
    g_strlcpy(labels[2], _("Start"), sizeof(labels[2]));
    g_strlcpy(labels[3], _("Information"), sizeof(labels[3]));
    g_strlcpy(labels[4], _("Back"), sizeof(labels[4]));
} 

/* main function - backup_noroot */
void backup_noroot(GtkWidget *widget, gpointer stack) 
{
    LOGD("backup_noroot");
    
    char labels[5][30];  // labels for the button 
    set_button_labels_backup_noroot(labels);  // for both languages
    
    GtkWidget *backup_noroot = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_halign(backup_noroot, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(backup_noroot, GTK_ALIGN_CENTER);

    GtkWidget *grid = gtk_grid_new();
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	
	// create button
    GtkWidget *btn1 = create_button_icon_position("applications-engineering-symbolic", labels[0], G_CALLBACK(install_depends), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("folder-download-symbolic", labels[1], G_CALLBACK(download_backup), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_button_icon_position("utilities-terminal-symbolic", labels[2], G_CALLBACK(open_backup), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_h = create_button_icon_position("dialog-information-symbolic", labels[3], G_CALLBACK(show_backup_help), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn_back = create_button_icon_position("pan-start-symbolic", labels[4], G_CALLBACK(preflash_GUI), stack, GTK_ALIGN_CENTER);

    // add the button to the grid
    gtk_grid_attach(GTK_GRID(grid), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn3, 2, 0, 1, 1);
	
	// get the env of the application
	// enable backup functions at debug mode
	if (debug_mode)
	{
		gtk_widget_set_visible(GTK_WIDGET(btn1), TRUE);
		gtk_widget_set_visible(GTK_WIDGET(btn2), TRUE);
		gtk_widget_set_visible(GTK_WIDGET(btn3), TRUE);
		gtk_widget_set_visible(GTK_WIDGET(btn_h), FALSE);
	}
	// disable backup functions for snap/flatpak version
	if (snap_app || flatpak_app) 
	{
	    gtk_widget_set_visible(GTK_WIDGET(btn1), FALSE);
	    gtk_widget_set_visible(GTK_WIDGET(btn2), TRUE);
	    gtk_widget_set_visible(GTK_WIDGET(btn3), FALSE);
	    gtk_widget_set_visible(GTK_WIDGET(btn_h), TRUE);
	} 
	// enable functions for local version
	else 
	{
	    gtk_widget_set_visible(GTK_WIDGET(btn1), TRUE);
	    gtk_widget_set_visible(GTK_WIDGET(btn2), TRUE);
	    gtk_widget_set_visible(GTK_WIDGET(btn3), TRUE);
	    gtk_widget_set_visible(GTK_WIDGET(btn_h), FALSE);
	}
	
    // pack the grid to the box
    gtk_box_append(GTK_BOX(backup_noroot), grid);
    // add info button
    gtk_box_append(GTK_BOX(backup_noroot), btn_h);
    // add the back button under the grid
    gtk_box_append(GTK_BOX(backup_noroot), btn_back); 

	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "backup_noroot")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), backup_noroot, "backup_noroot");
    }
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "backup_noroot");
    
    LOGD("end backup_noroot");
}

