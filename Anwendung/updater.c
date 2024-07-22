/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *			funkelnde Datenkristalle		 *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - updater				 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// get the new version from github
void get_latest_release_url(const char *repo, char *url_buffer) 
{
    char command[512];
    snprintf(command, sizeof(command),
             "curl -s https://api.github.com/repos/%s/releases/latest | grep 'browser_download_url' | head -n 1 | cut -d '\"' -f 4",
             repo);
    FILE *fp = popen(command, "r");
    if (fp == NULL) 
    {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    
    if (fgets(url_buffer, 256, fp) == NULL) 
    {
        perror("fgets");
        exit(EXIT_FAILURE);
    }
    
    url_buffer[strcspn(url_buffer, "\n")] = '\0';  // remove line breaks
    pclose(fp);
}

// download the file
int download_file(const char *url, const char *outfilename) 
{
    char command[512];
    snprintf(command, sizeof(command), "curl -L %s -o %s", url, outfilename);
    return system(command);
}

// main function
void updater(void) 
{
    const char *repo = "NachtsternBuild/fastboot-assitant"; 
    char download_url[256];
    get_latest_release_url(repo, download_url);  // run get url
    if (strlen(download_url) > 0) 
    {
        printf("Neueste Version URL: %s\n", download_url);
        const char *output_directory = getenv("HOME"); // set home as main dir
		char output_file[512];
		snprintf(output_file, sizeof(output_file), "%s/Downloads/fastboot-assistant.deb", output_directory);

        // download the .deb-file
        // const char *output_file = "fastboot-assistant.deb";
        if (download_file(download_url, output_file) == 0) 
        {
            printf("Paket heruntergeladen: %s\n", output_file);
           
            char function_command[255];
            // install the .deb-file
            open_terminal_by_desktop("sudo apt install ~/fastboot-assistant.deb && exit");
            printf("Fertig!\n");
        } 
        else 
        {
            printf("Fehler beim Herunterladen des Pakets\n");
        }
    } 
    else 
    {
        printf("Fehler beim Abrufen der neuesten Version\n");
    }

    return 0;
}

