/**
* backup_root.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

#define SU "su"
#define DD "dd"
#define BLOCK_PATH "/dev/block/bootdevice/by-name/"

AdwDialog *dialog;

gpointer backup_root_thread(gpointer data)
{
    LOGD("backup_root");
    
    char command[2048];
    char backup_dir[1024];
    char backup_predir_file[512];
    auto_free const char *adb = adb_command();
    
	// get path
	get_config_file_path(backup_predir_file, sizeof(backup_predir_file));
    // load the path
    const char *backup_predir = load_path_from_file(backup_predir_file);

    if (backup_predir) 
    {
        LOGD("Loaded path: %s", backup_predir);
    }
    // create full path
    snprintf(backup_dir, sizeof(backup_dir), "%s/Backup", backup_predir);
    LOGD("Backup of all available partitions to %s.", backup_dir);
    
	// create backup path
    snprintf(command, sizeof(command), "mkdir -p %s", backup_dir);
    execute_command(command);
        
    snprintf(command, sizeof(command), "%s wait-for-device", adb);
    execute_command(command);
    
	// write partition list to partition.txt
    snprintf(command, sizeof(command), "%s shell %s -c \"ls %s\" > %s/partitions.txt", adb, SU, BLOCK_PATH, backup_dir);
    execute_command(command);
    
    // file with all partitions
    char file_partition[1050];
    snprintf(file_partition, sizeof(file_partition), "%s/partitions.txt", backup_dir);
    
    // open file
    FILE *file = fopen(file_partition, "r");
    if (!file) 
    {
        LOGE("Error when opening the partitions.txt.");
        exit(1); 
    }

    char partition[128];
    while (fgets(partition, sizeof(partition), file)) 
    {
        // delete linebreak
        partition[strcspn(partition, "\r\n")] = 0;
        
		// get slots 
        snprintf(command, sizeof(command), "%s shell %s -c \"ls %s%s_a\" >/dev/null 2>&1", adb, SU, BLOCK_PATH, partition);
        int has_slot_a = system(command);
		
		// for devices with a/b slots
        if (has_slot_a == 0)
        {
            for (char slot = 'a'; slot <= 'b'; slot++) 
            {
                LOGD("Safe %s (slot %c) to %s", partition, slot, command);
                snprintf(command, sizeof(command), "%s shell %s -c \"%s if=%s%s_%c\" | %s of=%s/%s_%c.img", adb, SU, DD, BLOCK_PATH, partition, slot, DD, backup_dir, partition, slot);
                execute_command(command);
            }
        } 
        
        // for devices without a/b slots
        else 
        {
            LOGD("Safe %s to %s", partition, command);
            snprintf(command, sizeof(command), "%s shell %s -c \"%s if=%s%s\" | %s of=%s/%s.img", adb, SU, DD, BLOCK_PATH, partition, DD, backup_dir, partition);
            execute_command(command);
        }
    }
	
	// close the file
    fclose(file);
    
    LOGD("Backup completed. Files are located in %s.", backup_dir);
    
    if (backup_predir != NULL) 
	{
    	g_free((gpointer)backup_predir); // free the info (because g_file_get_contents was used)
	}
    LOGD("end backup_root");
    
    // close the dialog in the main thread
    g_idle_add((GSourceFunc)adw_dialog_force_close, dialog);
    
    return NULL;
}

void backup_root(GtkWidget *widget, gpointer stack) 
{   
    const char *title = "Backup";
    const char *body = "Run Backup with Root...";
    
    dialog = adw_alert_dialog_new(title, body);
    GtkWidget *content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 12);
    gtk_widget_set_margin_top(content, 16);
    gtk_widget_set_margin_bottom(content, 16);
    gtk_widget_set_margin_start(content, 16);
    gtk_widget_set_margin_end(content, 16);
    gtk_widget_set_halign(content, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(content, GTK_ALIGN_CENTER);

    GtkWidget *spinner = gtk_spinner_new();
    gtk_widget_set_size_request(spinner, 150, 150);
    gtk_spinner_start(GTK_SPINNER(spinner));
    gtk_box_append(GTK_BOX(content), spinner);

    adw_alert_dialog_set_extra_child(ADW_ALERT_DIALOG(dialog), content);
    adw_dialog_present(dialog, widget);
    
    // use new thread to flash the images
    g_thread_new("backup_root_thread", backup_root_thread, dialog);
}



