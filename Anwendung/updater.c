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
 *      (C) Copyright 2024 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "program_functions.h"

char output_file[2048];
char deb_on_wsl[2048];
char install_command[2048];

static void install_wsl(GtkButton *button, GtkEntry *password_entry) 
{
    snprintf(install_command, sizeof(install_command), "dpkg -i %s && rm -f %s", deb_on_wsl, deb_on_wsl);
    g_print("Installiere: %s", install_command);
    install_with_root(button, password_entry, install_command);
}

static void install_rpm(GtkButton *button, GtkEntry *password_entry) 
{
    snprintf(install_command, sizeof(install_command), "rpm -u %s && rm -f %s", output_file, output_file);
    g_print("Installiere: %s", install_command);
    install_with_root(button, password_entry, install_command);
}

static void install_deb(GtkButton *button, GtkEntry *password_entry) 
{
    snprintf(install_command, sizeof(install_command), "dpkg -i %s && rm -f %s", output_file, output_file);
    g_print("Installiere: %s", install_command);
    install_with_root(button, password_entry, install_command);
}

// Function to retrieve the latest release URL from GitHub
void get_latest_release_url(const char *repo, const char *package_type, char *url_buffer, size_t buffer_size) 
{
    char command[2048];
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
    char command[2048];
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
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *password_entry;
    GtkWidget *install_deb_button, *install_rpm_button, *install_wsl_button;

    gtk_init(&argc, &argv);
    apply_theme();
    
    const char *repo = "NachtsternBuild/fastboot-assistant";
    char download_url[2048];
    /* please change the package type for the different packages → .rpm or .deb or .zip*/
    const char *package_type = ".deb"; 
	// const char *package_type = ".rpm";
	// const char *package_type =".zip";

    get_latest_release_url(repo, package_type, download_url, sizeof(download_url));  // get url

    if (strlen(download_url) > 0) 
    {
        g_print("Neueste Version URL: %s\n", download_url);

        char message[2048];
        snprintf(message, sizeof(message), "Neueste Version URL: %s\nNeueste Version wird heruntergeladen.\n", download_url);
        show_message(message);

        const char *output_directory = getenv("HOME");
        if (output_directory == NULL) 
        {
            fprintf(stderr, "Fehler: HOME-Verzeichnis nicht gefunden\n");
            exit(EXIT_FAILURE);
        }
        
		const char *user = getenv("USER");
		if (user == NULL) 
		{	
    		g_print("Fehler: Konnte den Benutzernamen nicht ermitteln.\n");
    		exit(1);  // close the program if there are errors
		}

		char wsl_setup_base[2048];
		snprintf(wsl_setup_base, sizeof(wsl_setup_base), "/mnt/c/Users/%s", user);
		
		// for linux
        snprintf(output_file, sizeof(output_file), "%s/Downloads/fastboot-assistant%s", output_directory, package_type);
        
        // for wsl
		// snprintf(output_file, sizeof(output_file), "%s/Downloads/fastboot-assistant%s", wsl_setup_base, package_type);

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
            char install_command[2048];
            char remove_command[2048];
            char cd_command[2048];
            char output_path[2048];
            char wsl_dir[2048];
            char unzip_command[2048];
            
            if (strcmp(package_type, ".deb") == 0) 
            {
                g_print("Start install Debian package.\n");
                system("cd ~/Downloads/");
                // create window
    			window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    			gtk_window_set_title(GTK_WINDOW(window), "Aktualisieren");
    			gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
    			g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    			vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    			gtk_container_add(GTK_CONTAINER(window), vbox);

    			// password input 
    			password_entry = gtk_entry_new();
    			gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);  // hide the password
    			gtk_box_pack_start(GTK_BOX(vbox), password_entry, TRUE, TRUE, 0);

    			// install button
    			install_deb_button = gtk_button_new_with_label("Installieren");
    			g_signal_connect(install_deb_button, "clicked", G_CALLBACK(install_deb), password_entry);
   	 			gtk_box_pack_start(GTK_BOX(vbox), install_deb_button, TRUE, TRUE, 0);

    			gtk_widget_show_all(window);
            }
             
            else if (strcmp(package_type, ".rpm") == 0) 
            {
                g_print("Start install RPM.\n");
                system("cd ~/Downlaods/");
                // create window
    			window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    			gtk_window_set_title(GTK_WINDOW(window), "Aktualisieren");
    			gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
    			g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    			vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    			gtk_container_add(GTK_CONTAINER(window), vbox);

    			// password input 
    			password_entry = gtk_entry_new();
    			gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);  // hide the password
    			gtk_box_pack_start(GTK_BOX(vbox), password_entry, TRUE, TRUE, 0);

    			// install button
    			install_rpm_button = gtk_button_new_with_label("Installieren");
    			g_signal_connect(install_rpm_button, "clicked", G_CALLBACK(install_rpm), password_entry);
   	 			gtk_box_pack_start(GTK_BOX(vbox), install_rpm_button, TRUE, TRUE, 0);

    			gtk_widget_show_all(window);
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

    				// create window
    				window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    				gtk_window_set_title(GTK_WINDOW(window), "Aktualisieren");
    				gtk_window_set_default_size(GTK_WINDOW(window), 500, 200);
    				g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    				vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    				gtk_container_add(GTK_CONTAINER(window), vbox);

    				// password input 
    				password_entry = gtk_entry_new();
    				gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);  // hide the password
    				gtk_box_pack_start(GTK_BOX(vbox), password_entry, TRUE, TRUE, 0);

    				// install button
    				install_wsl_button = gtk_button_new_with_label("Installieren");
    				g_signal_connect(install_wsl_button, "clicked", G_CALLBACK(install_wsl), password_entry);
   	 				gtk_box_pack_start(GTK_BOX(vbox), install_wsl_button, TRUE, TRUE, 0);

    				gtk_widget_show_all(window);
					
					// remove the other files
					system("rm -f WSL_install.bat");
					system("rm -f Enable_WSL.bat");
					system("rm -f README.md");
    			}
    			 
    			else 
    			{
        			fprintf(stderr, "Fehler beim Herunterladen des ZIP-Pakets\n");
        			exit(EXIT_FAILURE);
    			}
			}
			g_print(remove_command);
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

