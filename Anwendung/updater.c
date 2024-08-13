/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *              funkende Datenkristalle      *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm, um das Installieren von 		 *
 *	Custom-ROMs und GSIs auf Android-Geräte *
 *	zu erleichtern - Updater				 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

// Funktion, um die neueste Release-URL von GitHub abzurufen
void get_latest_release_url(const char *repo, char *url_buffer, size_t buffer_size) 
{
    char command[512];
    snprintf(command, sizeof(command),
             "curl -s https://api.github.com/repos/%s/releases/latest | grep 'browser_download_url' | head -n 1 | cut -d '\"' -f 4",
             repo);
    FILE *fp = popen(command, "r");
    if (fp == NULL) 
    {
        perror("Fehler beim Ausführen des Befehls");
        exit(EXIT_FAILURE);
    }
    
    if (fgets(url_buffer, buffer_size, fp) == NULL) 
    {
        fprintf(stderr, "Fehler beim Abrufen der URL\n");
        pclose(fp);
        exit(EXIT_FAILURE);
    }
    
    url_buffer[strcspn(url_buffer, "\n")] = '\0';  // Entfernen des Zeilenumbruchs
    pclose(fp);
}

// Funktion, um eine Datei herunterzuladen
int download_file(const char *url, const char *outfilename) 
{
    char command[512];
    snprintf(command, sizeof(command), "curl -L %s -o %s", url, outfilename);
    return system(command);
}

// Hauptfunktion
void updater(void) 
{
    int argc = 0;
    char **argv = NULL;

    const char *repo = "NachtsternBuild/fastboot-assistant"; 
    char download_url[256];
    get_latest_release_url(repo, download_url, sizeof(download_url));  // Abrufen der URL

    if (strlen(download_url) > 0) 
    {
        printf("Neueste Version URL: %s\n", download_url);
        gtk_init(&argc, &argv);

        char message[256];
        snprintf(message, sizeof(message), "Neueste Version URL: %s\nNeueste Version wird heruntergeladen.\n", download_url);
        show_message(message);

        const char *output_directory = getenv("HOME");
        if (output_directory == NULL) 
        {
            fprintf(stderr, "Fehler: HOME-Verzeichnis nicht gefunden\n");
            exit(EXIT_FAILURE);
        }

        char output_file[512];
        snprintf(output_file, sizeof(output_file), "%s/Downloads/Projekt-122-l.deb", output_directory);

        const char *download_message = "Paket heruntergeladen.\nWird installiert.\n";
        show_message(download_message);

        // Datei herunterladen
        if (download_file(download_url, output_file) == 0) 
        {
            printf("Paket heruntergeladen: %s\n", output_file);

            char install_command[512];
            snprintf(install_command, sizeof(install_command), "sudo apt-get install -y %s && exit", output_file);
            open_terminal_by_desktop(install_command);
            printf("Fertig!\n");
        } 
        else 
        {
            fprintf(stderr, "Fehler beim Herunterladen des Pakets\n");
        }
        gtk_main();
    } 
    else 
    {
        fprintf(stderr, "Fehler beim Abrufen der neuesten Version\n");
    }
}
