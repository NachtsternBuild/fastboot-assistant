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
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "program_functions.h"

#define SU "su"
#define DD "dd"
#define BLOCK_PATH "/dev/block/bootdevice/by-name/"

void backup_root() 
{
    char command[512];
    char *homeDir = getenv("HOME");
    char backup_predir[2048];
    char backup_dir[2048];	
    char *adb = adb_command();
	
	// WSL logic
    const char *user = getenv("USER");
    if (user == NULL) 
    {	
        g_print("Fehler: Konnte den Benutzernamen nicht ermitteln.\n");
        exit(1);
    }
	// linux logic
    if (homeDir == NULL) 
    {
        fprintf(stderr, "Fehler: Konnte das Home-Verzeichnis nicht finden.\n");
        exit(1);
    }
    char wsl_setup_base[2048];
    snprintf(wsl_setup_base, sizeof(wsl_setup_base), "/mnt/c/Users/%s", user);
	
	// for linux
    //snprintf(backup_predir, sizeof(backup_predir), "%s", homeDir);
    // for windows
    snprintf(backup_predir, sizeof(backup_predir), "%s", wsl_setup_base);
    // create full path
    snprintf(backup_dir, sizeof(backup_dir), "%s/Downloads/ROM-Install/Backup", backup_predir);
    g_print("Sicherung aller verfügbaren Partitionen nach %s.\n", backup_dir);
	// create backup path
    snprintf(command, sizeof(command), "mkdir -p %s", backup_dir);
    execute_command(command);
	// wait for a device
    snprintf(command, sizeof(command), "%s wait-for-device", adb);
    execute_command(command);
	// write partition list to partition.txt
    snprintf(command, sizeof(command), "%s shell %s -c \"ls %s\" > %s/partitions.txt", adb, SU, BLOCK_PATH, backup_dir);
    execute_command(command);
    
    char file_partition[2048];
    snprintf(file_partition, sizeof(file_partition), "%s/partitions.txt", backup_dir);
    
    FILE *file = fopen(file_partition, "r");
    if (!file) 
    {
        g_print("Fehler beim Öffnen der partitions.txt\n");
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

        if (has_slot_a == 0) // for devices with a/b slots
        {
            for (char slot = 'a'; slot <= 'b'; slot++) 
            {
                snprintf(command, sizeof(command), "%s/%s_%c.img", backup_dir, partition, slot);
                g_print("Sichere %s (Slot %c) nach %s\n", partition, slot, command);

                snprintf(command, sizeof(command), "%s shell %s -c \"%s if=%s%s_%c\" | %s of=%s/%s_%c.img", 
                        adb, SU, DD, BLOCK_PATH, partition, slot, DD, backup_dir, partition, slot);
                execute_command(command);
            }
        } 
        else // for devices without a/b slots
        {
            snprintf(command, sizeof(command), "%s/%s.img", backup_dir, partition);
            g_print("Sichere %s nach %s\n", partition, command);

            snprintf(command, sizeof(command), "%s shell %s -c \"%s if=%s%s\" | %s of=%s/%s.img", 
                    adb, SU, DD, BLOCK_PATH, partition, DD, backup_dir, partition);
            execute_command(command);
        }
    }

    fclose(file);
    g_print("Sicherung abgeschlossen. Dateien befinden sich in %s\n", backup_dir);
}

