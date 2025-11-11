/**
* flash_list_images.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// prepare commands and descriptions
GSList *commands = NULL;

void process_file(const char *filepath) 
{   
    char command[1024];
    auto_free char *device_command = fastboot_command();
    
    if (strstr(filepath, "gz.img")) 
    {
        snprintf(command, sizeof(command), "%s flash gz_a %s && %s flash gz_b %s", device_command, filepath, device_command, filepath);
        
        CommandEntry *entry1 = g_new0(CommandEntry, 1);
    	entry1->cmd = g_strdup(command); 
    	entry1->description = g_strdup(_("Flashing gz.img...")); 
    	commands = g_slist_append(commands, entry1);
    } 
    
    else if (strstr(filepath, "lk.img")) 
    {
        snprintf(command, sizeof(command), "%s flash lk_a %s && %s flash lk_b %s", device_command, filepath, device_command, filepath);
        
        CommandEntry *entry2 = g_new0(CommandEntry, 1);
    	entry2->cmd = g_strdup(command); 
    	entry2->description = g_strdup(_("Flashing lk.img...")); 
    	commands = g_slist_append(commands, entry2);
    } 
    
    else if (strstr(filepath, "logo.img")) 
    {        
        snprintf(command, sizeof(command), "%s flash logo %s", device_command, filepath);
        
        CommandEntry *entry3 = g_new0(CommandEntry, 1);
    	entry3->cmd = g_strdup(command); 
    	entry3->description = g_strdup(_("Flashing logo.img...")); 
    	commands = g_slist_append(commands, entry3);
    } 
    
    else if (strstr(filepath, "md1img.img")) 
    {        
        snprintf(command, sizeof(command), "%s flash md1img_a %s && %s flash md1img_b %s", device_command, filepath, device_command, filepath);
        
        CommandEntry *entry4 = g_new0(CommandEntry, 1);
    	entry4->cmd = g_strdup(command); 
    	entry4->description = g_strdup(_("Flashing md1img.img...")); 
    	commands = g_slist_append(commands, entry4);
    } 
    
    else if (strstr(filepath, "metadata.img")) 
    {
        snprintf(command, sizeof(command), "%s flash metadata %s", device_command, filepath);
        
        CommandEntry *entry5 = g_new0(CommandEntry, 1);
    	entry5->cmd = g_strdup(command); 
    	entry5->description = g_strdup(_("Flashing metadata.img...")); 
    	commands = g_slist_append(commands, entry5);
    }
    
    else if (strstr(filepath, "protect.img")) 
    {       
        snprintf(command, sizeof(command), "%s flash protect_a %s && %s flash protect_b %s", device_command, filepath, device_command, filepath);
        
        CommandEntry *entry6 = g_new0(CommandEntry, 1);
    	entry6->cmd = g_strdup(command); 
    	entry6->description = g_strdup(_("Flashing protect.img...")); 
    	commands = g_slist_append(commands, entry6);
    } 
    
    else if (strstr(filepath, "scp.img")) 
    {        
        snprintf(command, sizeof(command), "%s flash scp_a %s && %s flash scp_b %s", device_command, filepath, device_command, filepath);
        
        CommandEntry *entry7 = g_new0(CommandEntry, 1);
    	entry7->cmd = g_strdup(command); 
    	entry7->description = g_strdup(_("Flashing scp.img...")); 
    	commands = g_slist_append(commands, entry7);
    } 
    
    else if (strstr(filepath, "spmfw.img")) 
    {       
        snprintf(command, sizeof(command), "%s flash spmfw_a %s && %s flash spmfw_b %s", device_command, filepath, device_command, filepath);
        
        CommandEntry *entry8 = g_new0(CommandEntry, 1);
    	entry8->cmd = g_strdup(command); 
    	entry8->description = g_strdup(_("Flashing spmfw.img...")); 
    	commands = g_slist_append(commands, entry8);
    } 
    
    else if (strstr(filepath, "sspm.img")) 
    {        
        snprintf(command, sizeof(command), "%s flash sspm_a %s && %s flash sspm_b %s", device_command, filepath, device_command, filepath);
        
        CommandEntry *entry9 = g_new0(CommandEntry, 1);
    	entry9->cmd = g_strdup(command); 
    	entry9->description = g_strdup(_("Flashing sspm.img...")); 
    	commands = g_slist_append(commands, entry9);
    } 
    
    else if (strstr(filepath, "tee.img")) 
    {        
        snprintf(command, sizeof(command), "%s flash tee_a %s && %s flash tee_b %s", device_command, filepath, device_command, filepath);
        
        CommandEntry *entry10 = g_new0(CommandEntry, 1);
    	entry10->cmd = g_strdup(command); 
    	entry10->description = g_strdup(_("Flashing tee.img...")); 
    	commands = g_slist_append(commands, entry10);
    } 
       
    else 
    {
        LOGW("Unknown file: %s, will be skipped.", filepath);
    }
}

void flash_images_in_directory(const char *directory) 
{
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(directory)) != NULL) 
    {
        while ((ent = readdir(dir)) != NULL) 
        {
            if (ent->d_type == DT_REG) 
            {
                char filepath[512];
                snprintf(filepath, sizeof(filepath), "%s/%s", directory, ent->d_name);
                process_file(filepath);
            }
        }
        closedir(dir);
        // show the dialog and run the commands
    	show_progress_dialog_multi(GTK_WIDGET(main_window), _("Fastboot Flashing"), _("This may take some time..."), commands);
    } 
    
    else 
    {
        LOGE("Could not open directory '%s'.", directory);
    }
}

void flash_list_images(GtkWidget *widget, gpointer *stack) 
{
    LOGD("flash_other");
	
    char directory[2048];

	// snprintf(other_dir, sizeof(other_dir), "%s", wsl_setup_base);
	char config_file_images[2048];
    get_config_file_path(config_file_images, sizeof(config_file_images));
    // load the path
    const char *other_dir = load_path_from_file(config_file_images);

    if (other_dir) 
    {
        LOGD("Loaded path: %s", other_dir);
    }
    // create the path
    snprintf(directory, sizeof(directory), "%s/Images", other_dir);
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    flash_images_in_directory(directory);
    
    if (other_dir != NULL) 
	{
    	g_free((gpointer)other_dir); // free the info (because g_file_get_contents was used)
	}
	
    LOGD("end flash_other");
}
