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

#define BACKUP_DIR "/home/USER/Downloads/ROM-Install/Backup"
#define ADB "adb"
#define SU "su"
#define DD "dd"
#define BLOCK_PATH "/dev/block/bootdevice/by-name/"

void backup_root() 
{
    char command[512];
	char *homeDir = getenv("HOME");
	char *backup_predir[2048];
	char *backup_dir[2048];
	// WSL Logik
	const char *user = getenv("USER");
	if (user == NULL) 
	{	
    	g_print("Fehler: Konnte den Benutzernamen nicht ermitteln.\n");
    	exit(1);  // close the program if there are errors
	}
	
	if (homeDir == NULL) 
	{
    	fprintf(stderr, "Fehler: Konnte das Home-Verzeichnis nicht finden.\n");
    	exit(1);  // close the program if there are errors
	}
	char wsl_setup_base[2048];
	snprintf(wsl_setup_base, sizeof(wsl_setup_base), "/mnt/c/Users/%s", user);

	// for linux
	//snprintf(backup_predir, sizeof(backup_predir), "%s", homeDir);
	// for wsl
	snprintf(backup_predir, sizeof(backup_predir), "%s", wsl_setup_base);

	// create full path for the config.txt
	snprintf(backup_dir, sizeof(backup_dir), "%s/Downloads/ROM-Install/Backup", backup_predir);
    g_print("Sicherung aller verfügbaren Partitionen nach %s.\n", backup_dir);

    // create backup path
    snprintf(command, sizeof(command), "mkdir -p %s", backup_dir);
    execute_command(command);

    // connect device with adb
    snprintf(command, sizeof(command), "%s wait-for-device", ADB);
    execute_command(command);

    // get partitions
    snprintf(command, sizeof(command), "%s shell %s -c \"ls %s\" > %s/partitions.txt", ADB, SU, BLOCK_PATH, backup_dir);
    execute_command(command);
    
    char file_partition[2048];
    snprintf(file_partition, sizeof(file_partition), "%s/partitions.txt", backup_dir);
    

    FILE *file = fopen( file_partition , "r");
    if (!file) 
    {
        g_print("Fehler beim Öffnen der partitions.txt");
    }

    char partition[128];
    while (fgets(partition, sizeof(partition), file)) 
    {
        // delete linebreak
        partition[strcspn(partition, "\r\n")] = 0;

        // get slots 
        snprintf(command, sizeof(command), "%s shell %s -c \"ls %s%s_a\" >/dev/null 2>&1", ADB, SU, BLOCK_PATH, partition);
        int has_slot_a = system(command);

        if (has_slot_a == 0) 
        { // devices with a/b slots
            for (char slot = 'a'; slot <= 'b'; slot++) 
            {
                snprintf(command, sizeof(command), "%s/%s_%c.img", backup_dir, partition, slot);
                g_print("Sichere %s (Slot %c) nach %s\n", partition, slot, command);

                snprintf(command, sizeof(command), "%s shell %s -c \"%s if=%s%s_%c\" | %s of=%s/%s_%c.img", 
                        ADB, SU, DD, BLOCK_PATH, partition, slot, DD, backup_dir, partition, slot);
                execute_command(command);
            }
        } 
        
        else 
        { // devices without a/b slots
            snprintf(command, sizeof(command), "%s/%s.img", backup_dir, partition);
            g_print("Sichere %s nach %s\n", partition, command);

            snprintf(command, sizeof(command), "%s shell %s -c \"%s if=%s%s\" | %s of=%s/%s.img", 
                    ADB, SU, DD, BLOCK_PATH, partition, DD, backup_dir, partition);
            execute_command(command);
        }
    }

    fclose(file);
    printf("Sicherung abgeschlossen. Dateien befinden sich in %s\n", backup_dir);
}
