/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *      Apache License, Version 2.0          *
 *-------------------------------------------*
 *                                           *
 *  Programm um das Installieren von         *
 *  Custom-ROM und GSIs auf Android-Geräte   *
 *  zu erleichtern                           *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2024 Elias Mörz        *
 *-------------------------------------------*
 *                                           *
 *         Headerpart - flash_image          *
 *                                           *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <pthread.h>
#include "program_functions.h"
#include "language_check.h"

// global vars
GtkWidget *spinner_window_flash;
GtkWidget *spinner_flash;

// Usage:
/*
// Flashing the boot partitions for an A/B device (without additional flags)
flash_image(widget, parent_window, "boot_a", "boot_b", "boot.img", NULL);

// Flashing vbmeta with specific flags for Verity and Verification
flash_image(widget, parent_window, "vbmeta", NULL, "vbmeta.img", "--disable-verity --disable-verification");

*/

// list of errors from fastboot
// if you know some others, please add it to this list
const char* check_fastboot_error(const char *fastboot_output)
{
    // I'll remove this
    apply_language();

    if (strstr(fastboot_output, "target didn't report max-download-size"))
    {
        return g_strcmp0(language, "de") == 0
            ? "Fehler: Das Zielgerät hat keine maximale Download-Größe gemeldet."
            : "Error: Target did not report max-download-size.";
    }
    
    if (strstr(fastboot_output, "FAILED"))
    {
        return g_strcmp0(language, "de") == 0
            ? "Fehler: Ein allgemeiner Fehler ist aufgetreten. Siehe Log für Details."
            : "Error: A general error occurred. Check the log for details.";
    }
    
    if (strstr(fastboot_output, "Invalid sparse file format at header magic"))
    {
        return g_strcmp0(language, "de") == 0
            ? "Fehler: Ungültiges Sparse-Dateiformat. Überprüfen Sie das Image."
            : "Error: Invalid sparse file format. Please check the image.";
    }
    
    if (strstr(fastboot_output, "Writing 'system' FAILED"))
    {
        return g_strcmp0(language, "de") == 0
            ? "Fehler: Schreiben der Partition 'system' fehlgeschlagen. Gerät und Verbindung prüfen."
            : "Error: Writing to partition 'system' failed. Check the device and connection.";
    }
    
    if (strstr(fastboot_output, "Writing 'system_a' FAILED"))
    {
        return g_strcmp0(language, "de") == 0
            ? "Fehler: Schreiben der Partition 'system' fehlgeschlagen. Gerät und Verbindung prüfen."
            : "Error: Writing to partition 'system' failed. Check the device and connection.";
    }
    
    if (strstr(fastboot_output, "Writing 'system_b' FAILED"))
    {
        return g_strcmp0(language, "de") == 0
            ? "Fehler: Schreiben der Partition 'system' fehlgeschlagen. Gerät und Verbindung prüfen."
            : "Error: Writing to partition 'system' failed. Check the device and connection.";
    }
    
    if (strstr(fastboot_output, "Resizing 'system' FAILED"))
    {
        return g_strcmp0(language, "de") == 0
            ? "Fehler: Vergrößern der Partition 'system_a' fehlgeschlagen."
            : "Error: Resizing partition 'system_a' failed.";
    }
    
    if (strstr(fastboot_output, "Resizing 'system_a' FAILED"))
    {
        return g_strcmp0(language, "de") == 0
            ? "Fehler: Vergrößern der Partition 'system_a' fehlgeschlagen."
            : "Error: Resizing partition 'system_a' failed.";
    }
    
    if (strstr(fastboot_output, "Resizing 'system_b' FAILED"))
    {
        return g_strcmp0(language, "de") == 0
            ? "Fehler: Vergrößern der Partition 'system_a' fehlgeschlagen."
            : "Error: Resizing partition 'system_a' failed.";
    }
    
    if (strstr(fastboot_output, "Partition not found"))
    {
    	return g_strcmp0(language, "de") == 0
    		? "Fehler: Die angegebene Partition wurde nicht gefunden. Bitte Partition überprüfen."
    		: "Error: The specified partition was not found. Please check the partition.";
    }
    
    if (strstr(fastboot_output, "timeout"))
    {
    	return g_strcmp0(language, "de") == 0
    		? "Fehler: Die Verbindung zu Fastboot ist abgelaufen. Bitte Gerät und USB-Verbindung prüfen."
    		: "Error: The connection to Fastboot has expired. Please check the device and USB connection.";
    }
    
    if (strstr(fastboot_output, "Permission denied"))
    {
    	return g_strcmp0(language, "de") == 0
    		? "Fehler: Keine Berechtigung, Fastboot-Befehl auszuführen. Bitte als root versuchen."
    		: "Error: No authorization to execute fastboot command. Please try as root.";
    }
    
    if (strstr(fastboot_output, "device is locked"))
    {
    	return g_strcmp0(language, "de") == 0
    		? "Fehler: Das Gerät ist gesperrt. Bitte Bootloader entsperren und erneut versuchen."
    		: "Error: The device is locked. Please unlock the bootloader and try again.";
    }
    
    if (strstr(fastboot_output, "remote: Operation not permitted"))
    {
        return g_strcmp0(language, "de") == 0
        	? "Fehler: Die Operation ist nicht zugelassen. Bitte Gerät prüfen."
        	: "Error: The operation is not permitted. Please check the device.";
    }
    
    if (strstr(fastboot_output, "Command not allowed"))
    {
        return g_strcmp0(language, "de") == 0
        	? "Fehler: Der Befehl ist nicht erlaubt."
        	: "Error: The command is not allowed.";
    }
    
    if (strstr(fastboot_output, "No such file or directory"))
    {
        return g_strcmp0(language, "de") == 0
        	? "Fehler: Datei oder Verzeichnis nicht gefunden. Bitte Pfad und Datei prüfen."
        	: "Error: File or directory not found. Please check path and file.";
    }
    
    if (strstr(fastboot_output, "cannot load"))
    {
        return g_strcmp0(language, "de") == 0
        	? "Fehler: Image konnte nicht geladen werden. Bitte die Datei überprüfen."
        	: "Error: Image could not be loaded. Please check the file.";
    }
    
    if (strstr(fastboot_output, "Unknown partition"))
    {
        return g_strcmp0(language, "de") == 0
        	? "Fehler: Unbekannte Partition. Bitte Partition prüfen."
        	: "Error: Unknown partition. Please check partition.";
    }

    return NULL; // unknown error
}

// function for handle error
void handle_flash_error(GtkWindow *parent_window, const char *error_details)
{
    char error_message[4096];
    snprintf(error_message, sizeof(error_message), g_strcmp0(language, "de") == 0 ? "Fehler: %s\n" : "Error: %s\n", error_details);
    LOG_ERROR("%s", error_details); 
    show_error_message(GTK_WIDGET(parent_window), error_message);
}

// function to create the flash command
char *build_flash_command(const char *device_command, const char *partition1, const char *partition2, const char *image_info, const char *optional_flags)
{
    char *command = malloc(8192);  

	// for a/b devices
    if (partition2) 
    {
        snprintf(command, 8192, "%s flash %s %s %s && %s flash %s %s %s",
                 device_command, partition1, image_info, optional_flags ? optional_flags : "",
                 device_command, partition2, image_info, optional_flags ? optional_flags : "");
    }
    
    // for only-a devices
    else  
    {
        snprintf(command, 8192, "%s flash %s %s %s",
                 device_command, partition1, image_info, optional_flags ? optional_flags : "");
    }

    return command;
}

// run the command
void *run_flash_command(void *command)
{
    char *function_command = (char *)command;
    char buffer[8192];
    FILE *pipe;

    LOG_INFO("Run: %s", function_command);

    // use popen for the command
    pipe = popen(function_command, "r");
    if (!pipe)
    {
        // errors with fastboot
        const char *handle_flash_error_text = strcmp(language, "de") == 0 ? "Fehler: Fastboot konnte nicht gestartet werden." : "Error: Fastboot could not be started.";
        handle_flash_error(GTK_WINDOW(spinner_window_flash), handle_flash_error_text);
        LOG_ERROR("Fastboot could not be started.");
        gtk_spinner_stop(GTK_SPINNER(spinner_flash));
        gtk_window_destroy(GTK_WINDOW(spinner_window_flash));
        free(function_command);
        return NULL;
    }

    // read the output of the command
    while (fgets(buffer, sizeof(buffer), pipe) != NULL)
    {
        LOG_INFO("Fastboot-Output: %s", buffer);

        // check for errors
        const char *error_message = check_fastboot_error(buffer);
        if (error_message)
        {
            // errors in the flash process
            handle_flash_error(GTK_WINDOW(spinner_window_flash), error_message);
            LOG_ERROR("%s", error_message);
            pclose(pipe); // close the pipe
            gtk_spinner_stop(GTK_SPINNER(spinner_flash));
            gtk_window_destroy(GTK_WINDOW(spinner_window_flash));
            free(function_command);
            return NULL;
        }
    }


    int ret = pclose(pipe); // close pipe and save return value

    if (ret != 0)
    {
        // text for errors in flash
        const char *handle_error_text = strcmp(language, "de") == 0 ? "Das Flashen wurde nicht erfolgreich abgeschlossen." : "The flashing was not completed successfully.";
        handle_flash_error(GTK_WINDOW(spinner_window_flash), handle_error_text);
        LOG_ERROR("%s", handle_error_text);
    }

    // stop spinner
    gtk_spinner_stop(GTK_SPINNER(spinner_flash));
    gtk_window_destroy(GTK_WINDOW(spinner_window_flash));

    free(function_command);  // free memory
    return NULL;
}


// function to flash an image
void flash_image(GtkWidget *widget, GtkWindow *parent_window, const char *partition1, const char *partition2, const char *image_name, const char *optional_flags)
{
    if (!parent_window) parent_window = main_window;
    
    setenv("GSK_RENDERER", "cairo", 1);
    
    char config_file[4096];
    char image_info[4096];
    apply_theme();
    apply_language();

    // create the path for the image
    // use the new methode
    //set_main_dir_with_wsl(image_path, sizeof(image_path), image_name);
    get_config_file_path(config_file, sizeof(config_file));
    // load the path
    const char *image_path = load_path_from_file(config_file);

    if (image_path) 
    {
        LOG_INFO("Loaded path: %s", image_path);
    }
	
	// create the image path
	snprintf(image_info, sizeof(image_info), "%s/%s", image_path, image_name);
	
    // check if the image not exists
    if (access(image_info, F_OK) == -1)
    {      
        const char *error_message = g_strcmp0(language, "de") == 0 ? "Image nicht gefunden." : "Image file not found.";
        show_error_message(GTK_WIDGET(parent_window), error_message);
        LOG_ERROR("%s", error_message);
        return;
    }
    
    // prevention of crashes
    if (!is_android_device_connected_fastboot()) 
    {      
        const char *error_message = strcmp(language, "de") == 0 ? "Kein Gerät erkannt." : "No device detected.";
        show_error_message(GTK_WIDGET(main_window), error_message);
        return;
    }
    
    // create the command
    auto_free const char *device_command = fastboot_command();
    char *function_command = build_flash_command(device_command, partition1, partition2, image_info, optional_flags);

    // create a new window
    spinner_window_flash = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(spinner_window_flash), " ");
    gtk_window_set_default_size(GTK_WINDOW(spinner_window_flash), 200, 200);

    // create spinner
    spinner_flash = gtk_spinner_new();
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(vbox), spinner_flash);
    gtk_widget_set_size_request(spinner_flash, 150, 150);
    gtk_window_set_child(GTK_WINDOW(spinner_window_flash), vbox);

    // start the spinner
    gtk_spinner_start(GTK_SPINNER(spinner_flash));

    // show the window
    gtk_widget_set_visible(spinner_window_flash, TRUE);

    // run command in a new thread
    pthread_t thread;
    pthread_create(&thread, NULL, run_flash_command, function_command);
    pthread_detach(thread);  // thread in the background
    
	if (image_path != NULL) 
	{
    	g_free((gpointer)image_path); // free the info (because g_file_get_contents was used)
	}
}
