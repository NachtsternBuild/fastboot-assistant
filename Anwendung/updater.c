/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *       Apache License, Version 2.0         *
 *-------------------------------------------*
 *                                           *
 *  Programm, um das Installieren von       *
 *  Custom-ROMs und GSIs auf Android-Geräte  *
 *  zu erleichtern - updater                 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz        *
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
char package_url[2048];
char bash_script_path[2048];
GtkWidget *update_window_install;
GtkWidget *info_button;

// Function to quit the application - updater
gboolean quit_application_updater(gpointer data)
{
    exit(1);
    return FALSE;  // Return FALSE to ensure the timeout callback is called only once
}

// Function to create and execute the Bash script
void create_and_run_bash_script(const char *package_url, const char *package_type)
{
    const char *home_dir = getenv("HOME");
    if (!home_dir)
    {
        fprintf(stderr, "Log: HOME directory not found.\n");
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
	char updater_path[2048];
	char mkdir_command[2048];
	snprintf(wsl_setup_base, sizeof(wsl_setup_base), "/mnt/c/Users/%s", user);
	
	// Create directory for updater
	// for linux
    snprintf(updater_path, sizeof(updater_path), "%s/Downloads/ROM-Install/Updater", home_dir);
        
    // for wsl
	//snprintf(updater_path, sizeof(updater_path), "%s/Downloads/ROM-Install/Updater", wsl_setup_base);
    
    // create ~/ROM-Install/Updater
    snprintf(mkdir_command, sizeof(mkdir_command), "mkdir -p %s", updater_path);
    if (system(mkdir_command) != 0)
    {
        fprintf(stderr, "Log: Failed to create directory.\n");
        exit(EXIT_FAILURE);
    }

    // Path to the Bash script
    snprintf(bash_script_path, sizeof(bash_script_path), "%s/install_update.sh", updater_path);

    // Write Bash script content
    FILE *script_file = fopen(bash_script_path, "w");
    if (!script_file)
    {
        fprintf(stderr, "Log: Failed to create the Bash script.\n");
        exit(EXIT_FAILURE);
    }
	const char *package = ".deb";
	//const char *package = ".zip";
	g_print("Log: %s\n", package);
	g_print("Log: %s\n", package_url);
	g_print("Log: %s\n", package_type);
	
    fprintf(script_file,
        "#!/bin/bash\n"
        "UPDATER_PID=%d\n"
        "PACKAGE_URL=\"%s\"\n"
        "PACKAGE_TYPE=\"%s\"\n"
        "kill -9 $UPDATER_PID\n"
        "echo \"Starting update process...\"\n"
        "curl -L \"$PACKAGE_URL\" -o ~/Downloads/ROM-Install/Updater/fastboot-assistant$PACKAGE_TYPE\n"
        "if [[ \"$PACKAGE_TYPE\" == \".deb\" ]]; then\n"
        "  sudo dpkg -i ~/Downloads/ROM-Install/Updater/fastboot-assistant$PACKAGE_TYPE\n"
        "else\n"
        "  echo \"Unsupported package type: $PACKAGE_TYPE\"\n"
        "  exit 1\n"
        "fi\n"
        "echo \"Update completed.\"\n",
        getpid(), package_type, package);
      
	// the skript for WSL
	/*
	fprintf(script_file,
	    "#!/bin/bash\n\n"
	    "UPDATER_PID=%d\n"
	    "PACKAGE_URL=\"%s\"\n"
        "PACKAGE_TYPE=\"%s\"\n"
	    "USER_NAME=$(whoami)\n"
	    "WSL_DIR=\"/mnt/c/Users/$USER_NAME\"\n"
	    "OUTPUT_PATH=\"$WSL_DIR/ROM-Install/Updater\"\n"
	    "OUTPUT_FILE=\"$OUTPUT_PATH/fastboot-assistant.zip\"\n"
	    "DEB_ON_WSL=\"$OUTPUT_PATH/fastboot-assistant.deb\"\n\n"
	    "UNZIP_COMMAND=\"unzip \\\"$OUTPUT_FILE\\\" -d \\\"$OUTPUT_PATH\\\"\"\n"
	    "kill -9 $UPDATER_PID\n"
	    "echo \"Starting update process...\"\n"
	    "curl -L \"$PACKAGE_URL\" -o \"$OUTPUT_FILE\"\n"
	    "if ! eval $UNZIP_COMMAND; then\n"
	    "    echo \"Error: Failed to unzip $OUTPUT_FILE\"\n"
	    "    exit 1\n"
	    "fi\n\n"
	    "cd \"$OUTPUT_PATH\" || { echo \"Error: Failed to change directory to $OUTPUT_PATH\"; exit 1; }\n\n"
	    "INSTALL_COMMAND=\"sudo dpkg -i \\\"$DEB_ON_WSL\\\" \"\n"
	    "if ! eval $INSTALL_COMMAND; then\n"
	    "    echo \"Error: Failed to install $DEB_ON_WSL\"\n"
	    "    exit 1\n"
	    "fi\n\n"
	    "echo \"Update completed.\"\n",
	    getpid(), package_type, package);
	*/
	// close file
    fclose(script_file);

    // Set executable permissions
    char chmod_command[2048];
    snprintf(chmod_command, sizeof(chmod_command), "chmod a+x %s", bash_script_path);
    if (system(chmod_command) != 0)
    {
        fprintf(stderr, "Log: Failed to set executable permissions.\n");
        exit(EXIT_FAILURE);
    }
    
    char cat_command[2048];
    snprintf(cat_command, sizeof(cat_command), "cat %s", bash_script_path);
    g_print("Log: Run: %s\n", cat_command);
    system(cat_command);

    // Run the script in a new terminal
    open_terminal_by_desktop(bash_script_path);
}

// function to extract the version from the url
const char* extract_version_from_url(const char* url) 
{
    const char* version_start = strstr(url, "/releases/download/");
    if (version_start) 
    {
        version_start += strlen("/releases/download/");
        const char* version_end = strchr(version_start, '/');
        if (version_end) 
        {
            static char version[64];
            size_t version_length = version_end - version_start;
            if (version_length < sizeof(version)) 
            {
                strncpy(version, version_start, version_length);
                version[version_length] = '\0';
                return version;
            }
        }
    }
    return NULL;
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
	
	/* please change the package type for the different packages → .deb or .zip*/
    const char *repo = "NachtsternBuild/fastboot-assistant";
    const char *package_type = ".deb";
    //const char *package_type = ".zip"; 

    get_latest_release_url(repo, package_type, package_url, sizeof(package_url));

    if (strlen(package_url) > 0)
    {
 		g_print("Log: Latest version URL: %s\n", package_url);
                
        const char* version = extract_version_from_url(package_url);
        if (version) 
        {
            g_print("Log: Extracted version: %s\n", version);
        }
        
        else 
        {
            g_print("Log: Could not extract version from URL.\n");
        }
        
        const char *output_directory = getenv("HOME");
        if (!output_directory) 
        {
            fprintf(stderr, "Log: Error: HOME directory not found.\n");
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
        snprintf(output_file, sizeof(output_file), "%s/Downloads/ROM-Install/Updater/fastboot-assistant%s", output_directory, package_type);
        
        // for wsl
		// snprintf(output_file, sizeof(output_file), "%s/Downloads/ROM-Install/Updater/fastboot-assistant%s", wsl_setup_base, package_type);

        snprintf(output_file, sizeof(output_file), "%s/Downloads/ROM-Install/Updater/fastboot-assistant%s", output_directory, package_type);
        
        g_print("Log: Package downloaded: %s\n", output_file);
        if (!verify_package_type(output_file, package_type)) 
        {
            fprintf(stderr, "Log: Error: The downloaded package is not a %s package.\n", package_type);
            exit(EXIT_FAILURE);
        }

        const char *confirmation = strcmp(language, "de") == 0 ? "Bestätigung" : "Confirmation";
        GtkWidget *confirmation_window = gtk_window_new();  
        gtk_window_set_title(GTK_WINDOW(confirmation_window), confirmation);

        gtk_window_set_default_size(GTK_WINDOW(confirmation_window), 500, 500);
        g_signal_connect(confirmation_window, "destroy", G_CALLBACK(on_window_destroy), NULL);

        GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_window_set_child(GTK_WINDOW(confirmation_window), vbox);

        GtkWidget *message_label = gtk_label_new(g_strcmp0(language, "de") == 0 ? "\n\nMöchten sie das Update installieren?\n\n" : "\n\nWould you like to install the update?\n\n");
        gtk_box_append(GTK_BOX(vbox), message_label);
        
        // Version message einfügen
		char version_message[256];
		snprintf(version_message, sizeof(version_message), g_strcmp0(language, "de") == 0 ? "Gefundene Version: %s\n\n" : "Found version: %s\n\n", version);

		GtkWidget *version_label = gtk_label_new(version_message);
		gtk_box_append(GTK_BOX(vbox), version_label);

        GtkWidget *confirm_button = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Installieren" : "Install");
        gtk_box_append(GTK_BOX(vbox), confirm_button);

        g_signal_connect(confirm_button, "clicked", G_CALLBACK(create_and_run_bash_script), package_url);
			
        GtkWidget *cancel_button = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Später Installieren" : "Install later");
        gtk_box_append(GTK_BOX(vbox), cancel_button);
        g_signal_connect(cancel_button, "clicked", G_CALLBACK(close_window_mainloop), confirmation_window);

        // show all widgets
    	gtk_window_present(GTK_WINDOW(confirmation_window)); // gtk_window_present instead of gtk_widget_show 
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
