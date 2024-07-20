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

    printf("Sicherung aller verfügbaren Partitionen nach %s.\n", BACKUP_DIR);

    // Sicherungspfad erstellen
    snprintf(command, sizeof(command), "mkdir -p %s", BACKUP_DIR);
    execute_command(command);

    // Gerät mit adb verbinden
    snprintf(command, sizeof(command), "%s wait-for-device", ADB);
    execute_command(command);

    // Ermitteln der Partitionen
    snprintf(command, sizeof(command), "%s shell %s -c \"ls %s\" > partitions.txt", ADB, SU, BLOCK_PATH);
    execute_command(command);

    FILE *file = fopen("partitions.txt", "r");
    if (!file) 
    {
        perror("Fehler beim Öffnen der partitions.txt");
        return EXIT_FAILURE;
    }

    char partition[128];
    while (fgets(partition, sizeof(partition), file)) 
    {
        // Entfernen des Zeilenumbruchs
        partition[strcspn(partition, "\r\n")] = 0;

        // Überprüfen, ob die Partition Slots hat
        snprintf(command, sizeof(command), "%s shell %s -c \"ls %s%s_a\" >/dev/null 2>&1", ADB, SU, BLOCK_PATH, partition);
        int has_slot_a = system(command);

        if (has_slot_a == 0) 
        { // Partition hat Slots
            for (char slot = 'a'; slot <= 'b'; slot++) 
            {
                snprintf(command, sizeof(command), "%s/%s_%c.img", BACKUP_DIR, partition, slot);
                printf("Sichere %s (Slot %c) nach %s\n", partition, slot, command);

                snprintf(command, sizeof(command), "%s shell %s -c \"%s if=%s%s_%c\" | %s of=%s/%s_%c.img", 
                        ADB, SU, DD, BLOCK_PATH, partition, slot, DD, BACKUP_DIR, partition, slot);
                execute_command(command);
            }
        } 
        
        else 
        { // Partition hat keine Slots
            snprintf(command, sizeof(command), "%s/%s.img", BACKUP_DIR, partition);
            printf("Sichere %s nach %s\n", partition, command);

            snprintf(command, sizeof(command), "%s shell %s -c \"%s if=%s%s\" | %s of=%s/%s.img", 
                    ADB, SU, DD, BLOCK_PATH, partition, DD, BACKUP_DIR, partition);
            execute_command(command);
        }
    }

    fclose(file);
    printf("Sicherung abgeschlossen. Dateien befinden sich in %s\n", BACKUP_DIR);
    return 0;
}