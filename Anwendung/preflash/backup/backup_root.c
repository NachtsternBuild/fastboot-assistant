/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - backup_function		 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "language_check.h"
#include "program_functions.h"

#define SU "su"
#define DD "dd"
#define BLOCK_PATH "/dev/block/bootdevice/by-name/"

void backup_root() 
{
    LOG_INFO("backup_root");

    apply_theme();
    apply_language();
    
    char command[4096];
    char backup_dir[4096];
    char backup_predir_file[4096];
    auto_free const char *adb = adb_command();
    
	// get path
	get_config_file_path(backup_predir_file, sizeof(backup_predir_file));
    // load the path
    const char *backup_predir = load_path_from_file(backup_predir_file);

    if (backup_predir) 
    {
        LOG_INFO("Loaded path: %s", backup_predir);
    }
    // create full path
    snprintf(backup_dir, sizeof(backup_dir), "%s/Backup", backup_predir);
    LOG_INFO("Backup of all available partitions to %s.", backup_dir);
    
	// create backup path
    snprintf(command, sizeof(command), "mkdir -p %s", backup_dir);
    execute_command(command);
    
	// wait for a device
    snprintf(command, sizeof(command), "%s wait-for-device", adb);
    if (!is_android_device_connected_adb()) 
    {      
        const char *message = strcmp(language, "de") == 0 ? "Kein Gerät erkannt. Prüfen sie ob ihr Gerät verbunden ist." : "No device recognized. Check whether your device is connected.";
        show_message(message);
        LOG_INFO("No device recognized.");
    }
    
    snprintf(command, sizeof(command), "%s wait-for-device", adb);
    execute_command(command);
    
	// write partition list to partition.txt
    snprintf(command, sizeof(command), "%s shell %s -c \"ls %s\" > %s/partitions.txt", adb, SU, BLOCK_PATH, backup_dir);
    execute_command(command);
    
    // file with all partitions
    char file_partition[2048];
    snprintf(file_partition, sizeof(file_partition), "%s/partitions.txt", backup_dir);
    
    // open file
    FILE *file = fopen(file_partition, "r");
    if (!file) 
    {
        LOG_ERROR("Error when opening the partitions.txt.");
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
                snprintf(command, sizeof(command), "%s/%s_%c.img", backup_dir, partition, slot);
                LOG_INFO("Safe %s (slot %c) to %s", partition, slot, command);

                snprintf(command, sizeof(command), "%s shell %s -c \"%s if=%s%s_%c\" | %s of=%s/%s_%c.img", 
                        adb, SU, DD, BLOCK_PATH, partition, slot, DD, backup_dir, partition, slot);
                execute_command(command);
            }
        } 
        
        // for devices without a/b slots
        else 
        {
            snprintf(command, sizeof(command), "%s/%s.img", backup_dir, partition);
            LOG_INFO("Safe %s to %s", partition, command);

            snprintf(command, sizeof(command), "%s shell %s -c \"%s if=%s%s\" | %s of=%s/%s.img", 
                    adb, SU, DD, BLOCK_PATH, partition, DD, backup_dir, partition);
            execute_command(command);
        }
    }
	
	// close the file
    fclose(file);
    
    const char *message1 = strcmp(language, "de") == 0 ? "Backup beendet." : "Backup completed.";
    show_message(message1);
    LOG_INFO("Backup completed. Files are located in %s.", backup_dir);
    
    if (backup_predir != NULL) 
	{
    	g_free((gpointer)backup_predir); // free the info (because g_file_get_contents was used)
	}
    LOG_INFO("end backup_root");
}

