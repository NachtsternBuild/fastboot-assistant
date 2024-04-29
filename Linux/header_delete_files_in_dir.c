/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *        Headerpart - delete files in dir	 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void delete_files_in_dir(const char *path) 
{
    DIR *dir;
    struct dirent *entry;
    char fullpath[PATH_MAX];

    // open dir
    dir = opendir(path);
    if (dir == NULL) 
    {
        perror("Fehler beim Öffnen des Verzeichnisses");
        exit(EXIT_FAILURE);
    }

    // read dir
    while ((entry = readdir(dir)) != NULL) {
        // skip '.' and '..'
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // get full path
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        // delet files
        if (remove(fullpath) != 0) {
            perror("Fehler beim Löschen der Datei");
        } else {
            printf("Datei gelöscht: %s\n", fullpath);
        }
    }

    // close dir
    closedir(dir);
}

