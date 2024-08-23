/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
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

// Function to retrieve the latest release URL from GitHub
void get_latest_release_url(const char *repo, const char *package_type, char *url_buffer, size_t buffer_size) 
{
    char command[512];
    // get the url from the github api
    snprintf(command, sizeof(command),
             "curl -s https://api.github.com/repos/%s/releases/latest | grep 'browser_download_url' | grep '%s' | head -n 1 | cut -d '\"' -f 4",
             repo, package_type);
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
    
    url_buffer[strcspn(url_buffer, "\n")] = '\0';  // remove linebreak
    pclose(fp);
}

// function to download the file
int download_file(const char *url, const char *outfilename) 
{
    char command[512];
    snprintf(command, sizeof(command), "curl -L %s -o %s", url, outfilename);
    return system(command);
}

// function to check the typ of the package
int verify_package_type(const char *filepath, const char *expected_extension) 
{
    const char *ext = strrchr(filepath, '.');
    if (!ext || strcmp(ext, expected_extension) != 0) 
    {
        return 0; // false typ
    }
    return 1; // the right typ
}

// main function
void updater(void) 
{
    int argc = 0;
    char **argv = NULL;
    
    const char *repo = "NachtsternBuild/fastboot-assistant";
    char download_url[256];
    /* please change the package type for the different packages → .rpm or .deb or .zip*/
    const char *package_type = ".deb"; 
	// const char *package_type = ".rpm";
	// const char *package_type =".zip";

    get_latest_release_url(repo, package_type, download_url, sizeof(download_url));  // get url

    if (strlen(download_url) > 0) 
    {
        g_print("Neueste Version URL: %s\n", download_url);
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
        snprintf(output_file, sizeof(output_file), "%s/Downloads/fastboot-assistant%s", output_directory, package_type);

        const char *download_message = "Paket heruntergeladen.\nWird installiert.\n";
        show_message(download_message);

        // download the file
        if (download_file(download_url, output_file) == 0) 
        {
            g_print("Paket heruntergeladen: %s\n", output_file);

            // check the package typ
            if (!verify_package_type(output_file, package_type)) 
            {
                fprintf(stderr, "Fehler: Das heruntergeladene Paket ist kein %s Paket\n", package_type);
                exit(EXIT_FAILURE);
            }

            // install the package
            char install_command[512];
            char remove_command[512];
            char cd_command[512];
            char output_path[512];
            char deb_on_wsl[512];
            char wsl_dir[512];
            char unzip_command[512];
            
            if (strcmp(package_type, ".deb") == 0) 
            {
                g_print("Start install Debian package.\n");
                system("cd ~/Downloads/");
                snprintf(install_command, sizeof(install_command), "sudo dpkg -i %s && exit", output_file);
                snprintf(remove_command, sizeof(remove_command), "rm -f %s", output_file);
            }
             
            else if (strcmp(package_type, ".rpm") == 0) 
            {
                g_print("Start install RPM.\n");
                system("cd ~/Downlaods/");
                snprintf(install_command, sizeof(install_command), "sudo rpm -i %s && exit", output_file);
                snprintf(remove_command, sizeof(remove_command), "rm -f %s", output_file);
            }
                
            else if (strcmp(package_type, ".zip") == 0)
			{
    			g_print("Start install Windows file.\n");
    			get_wsl_directory(wsl_dir, sizeof(wsl_dir));
    			g_print(wsl_dir);
    			snprintf(output_file, sizeof(output_file), "%s/fastboot-assistant.zip", wsl_dir);
    			snprintf(output_path, sizeof(output_path), "%s/ROM-Install", wsl_dir);
    			snprintf(deb_on_wsl, sizeof(deb_on_wsl), "%s/fastboot-assistant.deb", output_path);

    			// Download the file to the Windows Downloads directory
    			if (download_file(download_url, output_file) == 0) 
    			{
        			g_print("Paket heruntergeladen: %s\n", output_file);

        			// Unzip the file in the Windows Downloads directory
        			snprintf(unzip_command, sizeof(unzip_command), "unzip %s -d %s", output_file, output_path);
        			system(unzip_command);
        			
        			// change to to wsl dir and install the new file
        			snprintf(cd_command, sizeof(cd_command), "cd %s", output_path);
        			system(cd_command);
        			snprintf(install_command, sizeof(install_command), "sudo dpkg -i %s && exit", deb_on_wsl);
					
					// remove the other files
					system("rm -f WSL_install.bat");
					system("rm -f Enable_WSL.bat");
					system("rm -f README.md");
        			// Remove the ZIP file after extraction
        			snprintf(remove_command, sizeof(remove_command), "rm -f %s", output_file);
    			}
    			 
    			else 
    			{
        			fprintf(stderr, "Fehler beim Herunterladen des ZIP-Pakets\n");
        			exit(EXIT_FAILURE);
    			}
			}
			g_print(install_command);
			g_print(remove_command);
            open_terminal_by_desktop(install_command);
            system(remove_command);
            g_print("Fertig!\n");
        } 
        else 
        {
            fprintf(stderr, "Fehler beim Herunterladen des Pakets\n");
        }
        gtk_main_quit();
    } 
    else 
    {
        fprintf(stderr, "Fehler beim Abrufen der neuesten Version\n");
    }
    gtk_main();
}

