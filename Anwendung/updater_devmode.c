/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *       Apache License, Version 2.0         *
 *-------------------------------------------*
 *                                           *
 *  Programm, um das Installieren von        *
 *  Custom-ROMs und GSIs auf Android-Geräte  *
 *  zu erleichtern - updater_devmode         *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz        *
 *-------------------------------------------*
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

char output_file_devmode[2048];
char package_url_devmode[2048];
char bash_script_path_devmode[2048];
GtkWidget *update_window_install_devmode;
GtkWidget *info_button_devmode;

// Function to quit the application - updater
gboolean quit_application_updater_devmode(gpointer data)
{
    exit(1);
    return FALSE;  // Return FALSE to ensure the timeout callback is called only once
}

// Function to create and execute the Bash script
void create_and_run_bash_script_devmode(const char *package_url_devmode, const char *package_type)
{
    char updater_dir[2048];
	char updater_path[2048];
	char mkdir_command[2048];

	get_config_file_path(updater_dir, sizeof(updater_dir));
	
	// Create directory for updater
    snprintf(updater_path, sizeof(updater_path), "%s/updater", updater_dir);
    
    // create ~/.config/fasboot-assistant/Updater
    snprintf(mkdir_command, sizeof(mkdir_command), "mkdir -p %s", updater_path);
    if (system(mkdir_command) != 0)
    {
        LOG_ERROR("Failed to create directory.");
        exit(1);
    }

    // Path to the Bash script
    snprintf(bash_script_path_devmode, sizeof(bash_script_path_devmode), "%s/install_update.sh", updater_path);

    // Write Bash script content
    FILE *script_file = fopen(bash_script_path_devmode, "w");
    if (!script_file)
    {
        LOG_ERROR("Failed to create the Bash script.\n");
        exit(1);
    }
    
	const char *package = ".deb";
	//const char *package = ".zip";
	LOG_INFO("%s", package);
	LOG_INFO("%s", package_url_devmode);
	LOG_INFO("%s", package_type);
	
    fprintf(script_file,
        "#!/bin/bash\n"
        "UPDATER_PID=%d\n"
        "PACKAGE_URL=\"%s\"\n"
        "PACKAGE_TYPE=\"%s\"\n"
        "kill -9 $UPDATER_PID\n"
        "echo \"Starting update process...\"\n"
        "echo \"Download package...\"\n"
        "curl -L \"$PACKAGE_URL\" -o ~/.config/fastboot-assistant/updater/fastboot-assistant$PACKAGE_TYPE\n"
        "echo \"Installing package...\"\n"
        "if [[ \"$PACKAGE_TYPE\" == \".deb\" ]]; then\n"
        "  sudo apt install ~/.config/fastboot-assistant/updater/fastboot-assistant$PACKAGE_TYPE\n"
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
	    "OUTPUT_PATH=\"$WSL_DIR/.config/fastboot-assistant/updater\"\n"
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
    snprintf(chmod_command, sizeof(chmod_command), "chmod a+x %s", bash_script_path_devmode);
    if (system(chmod_command) != 0)
    {
        LOG_ERROR("Failed to set executable permissions.");
        exit(1);
    }
    
    char cat_command[2048];
    snprintf(cat_command, sizeof(cat_command), "cat %s", bash_script_path_devmode);
    LOG_INFO("Run: %s\n", cat_command);
    system(cat_command);

    // Run the script in a new terminal
    open_terminal_by_desktop(bash_script_path_devmode);
}

// function to extract the version from the url
const char* extract_version_from_url_devmode(const char* url) 
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
void get_latest_release_url_devmode(const char *repo, const char *package_type, char *url_buffer, size_t buffer_size) 
{
    LOG_INFO("get_latest_release_url");
    char command[2048];
    // get the url from the github api 
    // use prerelease tag
    snprintf(command, sizeof(command),
         "curl -s https://api.github.com/repos/%s/releases | grep 'browser_download_url' | grep '%s' | grep '\"prerelease\": true' | head -n 1 | cut -d '\"' -f 4",
         repo, package_type);
         
    FILE *fp = popen(command, "r");
    if (fp == NULL) 
    {
        LOG_ERROR("Error when executing the command.");
        exit(1);
    }

    if (fgets(url_buffer, buffer_size, fp) == NULL) 
    {
        LOG_ERROR("Error when retrieving the URL.");
        pclose(fp);
        exit(1);
    }

    url_buffer[strcspn(url_buffer, "\n")] = '\0';  // remove linebreak
    pclose(fp);
    LOG_INFO("end get_latest_release_url");
}

/* main function of the updater */
void updater_devmode(void)
{
    LOG_INFO("updater");

    gtk_init();
    main_loop = g_main_loop_new(NULL, FALSE);
    apply_theme();
    apply_language();
	
	/* please change the package type for the different packages → .deb or .zip*/
    const char *repo = "NachtsternBuild/fastboot-assistant";
    const char *package_type = ".deb";
    //const char *package_type = ".zip"; 

    get_latest_release_url_devmode(repo, package_type, package_url_devmode, sizeof(package_url_devmode));

    if (strlen(package_url_devmode) > 0)
    {
 		LOG_INFO("Latest version URL: %s", package_url_devmode);
                
        const char* version = extract_version_from_url_devmode(package_url_devmode);
        if (version) 
        {
            LOG_INFO("Extracted version: %s", version);
        }
        
        else 
        {
            LOG_INFO("Could not extract version from URL.");
        }

		char output_directory[4096];
		char updater_version_file[4096];
		
		get_config_file_path(output_directory, sizeof(output_directory));

        snprintf(output_file_devmode, sizeof(output_file_devmode), "%s/updater/fastboot-assistant%s", output_directory, package_type);
        snprintf(updater_version_file, sizeof(updater_version_file), "%s/config/version.txt", output_directory);
        
        // function to verify package type
        LOG_INFO("Package downloading: %s", output_file_devmode);
        if (!verify_package_type(output_file_devmode, package_type)) 
        {
            LOG_ERROR("The downloaded package is not a %s package.", package_type);
            exit(1);
        }
        
        // function to open version file
        FILE *file = fopen(updater_version_file, "r");
        if (!file) 
        {
            LOG_ERROR("Failed to open version file: %s", updater_version_file);
            exit(1);
        }
		
		// get the current version
        char current_version_updater[128];
        if (fgets(current_version_updater, sizeof(current_version_updater), file)) 
        {
            current_version_updater[strcspn(current_version_updater, "\n")] = '\0'; // Remove newline
            LOG_INFO("Current version: %s", current_version_updater);
        } 
        
        else 
        {
            LOG_ERROR("Failed to read version from file.");
            fclose(file);
            exit(1);
        }
        fclose(file);

        const char *confirmation = strcmp(language, "de") == 0 ? "Updater (Dev)" : "Updater (Dev)";
        GtkWidget *confirmation_window = gtk_window_new();  
        gtk_window_set_title(GTK_WINDOW(confirmation_window), confirmation);

        gtk_window_set_default_size(GTK_WINDOW(confirmation_window), 500, 500);
        g_signal_connect(confirmation_window, "destroy", G_CALLBACK(on_window_destroy), NULL);

        GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
        gtk_window_set_child(GTK_WINDOW(confirmation_window), vbox);

        GtkWidget *message_label = gtk_label_new(g_strcmp0(language, "de") == 0 ? "\n\nMöchten sie das Update installieren?\n\n" : "\n\nWould you like to install the update?\n\n");
        gtk_box_append(GTK_BOX(vbox), message_label);
        
        // message with current and new version
        char version_message[256];
		snprintf(version_message, sizeof(version_message), g_strcmp0(language, "de") == 0 ? "Installierte Version: %s\n\nGefundene Version: %s\n\n" : "Installed Version: %s\n\nFound version: %s\n\n", current_version_updater, version);

		GtkWidget *version_label = gtk_label_new(version_message);
		gtk_box_append(GTK_BOX(vbox), version_label);

        GtkWidget *confirm_button = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Installieren" : "Install");
        gtk_box_append(GTK_BOX(vbox), confirm_button);

        g_signal_connect(confirm_button, "clicked", G_CALLBACK(create_and_run_bash_script_devmode), package_url_devmode);
			
        GtkWidget *cancel_button = gtk_button_new_with_label(g_strcmp0(language, "de") == 0 ? "Später Installieren" : "Install later");
        gtk_box_append(GTK_BOX(vbox), cancel_button);
        g_signal_connect(cancel_button, "clicked", G_CALLBACK(close_window_mainloop), confirmation_window);

        // show all widgets
    	gtk_window_present(GTK_WINDOW(confirmation_window)); // gtk_window_present instead of gtk_widget_show 
    }
     
    else 
    {
        LOG_ERROR("No release URL found.");
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
	
    LOG_INFO("end updater");
}
