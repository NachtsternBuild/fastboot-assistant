/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm, um das Installieren von 		 *
 *	Custom-ROMs und GSIs auf Android-Geräte *
 *	zu erleichtern - updater				 *
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
#include "language_check.h"
#include "program_functions.h"

char output_file[2048];
char deb_on_wsl[2048];
char install_command[2048];
char output_path[2048];
char unzip_command[2048];
char cd_command[2048];
char output_path[2048];
char wsl_dir[2048];
GtkWidget *update_window_install;
GtkWidget *info_button;

static void install_wsl(GtkButton *button) 
{ 
    g_print("Log: install_wsl\n");
    get_wsl_directory(wsl_dir, sizeof(wsl_dir));
    g_print("Log: Directory: %s\n", wsl_dir);
    
    snprintf(output_file, sizeof(output_file), "%s/fastboot-assistant.zip", wsl_dir);
    snprintf(output_path, sizeof(output_path), "%s/ROM-Install", wsl_dir);
    snprintf(deb_on_wsl, sizeof(deb_on_wsl), "%s/fastboot-assistant.deb", output_path);
    
    g_print("Log: Package downloaded: %s\n", output_file);

    snprintf(unzip_command, sizeof(unzip_command), "unzip %s -d %s", output_file, output_path);
    g_print("Log: Run: %s\n", unzip_command);
    system(unzip_command);       			
    
    snprintf(cd_command, sizeof(cd_command), "cd %s", output_path);
    g_print("Log: Run: %s\n", cd_command);
    system(cd_command);
    snprintf(install_command, sizeof(install_command), "dpkg -i %s && rm -f %s", deb_on_wsl, deb_on_wsl);
    install_with_pkexec(install_command);
    gtk_window_destroy(GTK_WINDOW(update_window_install));
    g_print("Log: end install_wsl\n");
}

static void install_rpm(GtkButton *button) 
{
    g_print("Log: install_rpm\n");
    snprintf(install_command, sizeof(install_command), "rpm -U %s && rm -f %s", output_file, output_file);
    install_with_pkexec(install_command);
    gtk_window_destroy(GTK_WINDOW(update_window_install));
    g_print("Log: end install_rpm\n");
}

static void install_deb(GtkButton *button) 
{
    g_print("Log: install_deb\n");
    snprintf(install_command, sizeof(install_command), "dpkg -i %s && rm -f %s", output_file, output_file);
    install_with_pkexec(install_command);
    gtk_window_destroy(GTK_WINDOW(update_window_install));
    g_print("Log: end install_deb\n");
}

// create window for install
static void create_install_window(GtkWidget **install_button, void (*install_callback)(GtkButton*)) 
{
    const char *update_install = strcmp(language, "de") == 0 ? "Installieren" : "Install";
    update_window_install = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(update_window_install), update_install);
    gtk_window_set_default_size(GTK_WINDOW(update_window_install), 500, 200);
    g_signal_connect(update_window_install, "destroy", G_CALLBACK(on_window_destroy), main_loop);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(update_window_install), vbox);

    info_button = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Autorisierung erforderlich" : "Authorization Required");
    gtk_box_append(GTK_BOX(vbox), info_button);

    *install_button = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Installieren" : "Install");
    g_signal_connect(*install_button, "clicked", G_CALLBACK(install_callback), NULL);
    gtk_box_append(GTK_BOX(vbox), *install_button);
	
    // show all widgets
    gtk_window_present(GTK_WINDOW(update_window_install));
}

static void install_window_deb(GtkButton *button)
{
    g_print("Log: install_window_deb\n");
    GtkWidget *install_button;
    create_install_window(&install_button, install_deb);
}

static void install_window_rpm(GtkButton *button)
{
    g_print("Log: install_window_rpm\n");
    GtkWidget *install_button;
    create_install_window(&install_button, install_rpm);
}

static void install_window_wsl(GtkButton *button)
{
    g_print("Log: install_window_wsl\n");
    GtkWidget *install_button;
    create_install_window(&install_button, install_wsl);
}

// Function to retrieve the latest release URL from GitHub
void get_latest_release_url(const char *repo, const char *package_type, char *url_buffer, size_t buffer_size) 
{
    g_print("Log: get_latest_release_url\n");
    char command[2048];
    // get the url from the github api
    snprintf(command, sizeof(command),
             "curl -s https://api.github.com/repos/%s/releases/latest | grep 'browser_download_url' | grep '%s' | head -n 1 | cut -d '\"' -f 4",
             repo, package_type);
    FILE *fp = popen(command, "r");
    if (fp == NULL) 
    {
        perror("Log: Error when executing the command.\n");
        exit(EXIT_FAILURE);
    }

    if (fgets(url_buffer, buffer_size, fp) == NULL) 
    {
        fprintf(stderr, "Log: Error when retrieving the URL.\n");
        pclose(fp);
        exit(EXIT_FAILURE);
    }

    url_buffer[strcspn(url_buffer, "\n")] = '\0';  // remove linebreak
    pclose(fp);
    g_print("Log: end get_latest_release_url\n");
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
    return ext && strcmp(ext, expected_extension) == 0;
}

/* main function of the updater */
void updater(void) 
{
    g_print("Log: updater\n");

    gtk_init();
    main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();

    const char *repo = "NachtsternBuild/fastboot-assistant";
    char download_url[2048];
    /* please change the package type for the different packages → .rpm or .deb or .zip*/
    //const char *package_type = ".deb"; 
    // const char *package_type = ".rpm";
	const char *package_type =".zip";

    get_latest_release_url(repo, package_type, download_url, sizeof(download_url));

    if (strlen(download_url) > 0) 
    {
        g_print("Log: Latest version URL: %s\n", download_url);
        const char *output_directory = getenv("HOME");
        if (!output_directory) 
        {
            fprintf(stderr, "Log: Fehler: HOME-Verzeichnis nicht gefunden.\n");
            exit(EXIT_FAILURE);
        }

         // get the user
        const char *user = getenv("USER");
		if (user == NULL) 
		{	
    		g_print("Log: Error: Could not determine the user name.\n");
    		exit(1);  // close the program if there are errors
		}

		char wsl_setup_base[2048];
		snprintf(wsl_setup_base, sizeof(wsl_setup_base), "/mnt/c/Users/%s", user);
		
		// for linux
        //snprintf(output_file, sizeof(output_file), "%s/Downloads/fastboot-assistant%s", output_directory, package_type);
        
        // for wsl
		snprintf(output_file, sizeof(output_file), "%s/Downloads/fastboot-assistant%s", wsl_setup_base, package_type);

        snprintf(output_file, sizeof(output_file), "%s/Downloads/fastboot-assistant%s", output_directory, package_type);
        const char *message = strcmp(language, "de") == 0 ? "Heruntergeladen" : "Package downloaded.";
        show_message(message);

        if (download_file(download_url, output_file) == 0) 
        {
            g_print("Log: Package downloaded: %s\n", output_file);
            if (!verify_package_type(output_file, package_type)) 
            {
                fprintf(stderr, "Log: Error: The downloaded package is not a %s package.\n", package_type);
                exit(EXIT_FAILURE);
            }

            const char *confirmation = strcmp(language, "de") == 0 ? "Bestätigung" : "Confirmation";
            GtkWidget *confirmation_window = gtk_window_new();  
            gtk_window_set_title(GTK_WINDOW(confirmation_window), confirmation);

            gtk_window_set_default_size(GTK_WINDOW(confirmation_window), 400, 350);
            g_signal_connect(confirmation_window, "destroy", G_CALLBACK(gtk_window_destroy), NULL);

            GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
            gtk_window_set_child(GTK_WINDOW(confirmation_window), vbox);

            GtkWidget *message_label = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Das Paket wurde heruntergeladen. \nMöchten Sie es jetzt installieren?" : "The package has been downloaded. \nWould you like to install it now?");
            gtk_box_append(GTK_BOX(vbox), message_label);

            GtkWidget *confirm_button = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Installieren" : "Install");
            gtk_box_append(GTK_BOX(vbox), confirm_button);

            if (strcmp(package_type, ".deb") == 0) 
            {
                g_signal_connect(confirm_button, "clicked", G_CALLBACK(install_window_deb), NULL);
            } 
            
            else if (strcmp(package_type, ".rpm") == 0) 
            {
                g_signal_connect(confirm_button, "clicked", G_CALLBACK(install_window_rpm), NULL);
            }
			
			else if (strcmp(package_type, ".zip") == 0)
			{
				g_signal_connect(confirm_button, "clicked", G_CALLBACK(install_window_wsl), NULL);
			}
			
            GtkWidget *cancel_button = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Später Installieren" : "Install later");
            gtk_box_append(GTK_BOX(vbox), cancel_button);
            g_signal_connect(cancel_button, "clicked", G_CALLBACK(on_window_destroy), confirmation_window);

            // show all widgets
    		gtk_window_present(GTK_WINDOW(confirmation_window)); // gtk_window_present instead of gtk_widget_show
        } 
        else 
        {
            fprintf(stderr, "Log: Error downloading the file.\n");
        }
    } 
    else 
    {
        fprintf(stderr, "Log: No release URL found.\n");
    }
	
	// run GTK main loop
    g_main_loop_run(main_loop); 
    
    // free the provider
    if (provider != NULL) 
    {
    	g_object_unref(provider);
    	provider = NULL;
	}

	if (main_loop != NULL) 
	{
    	g_main_loop_unref(main_loop);
    	main_loop = NULL;
	}
	
    g_print("Log: end updater\n");
}

