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
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              flash_payload				 *
 *											 *
 *-------------------------------------------*
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "language_check.h"
#include "program_functions.h"

void flash_payload(GtkWidget *widget, gpointer data)
{
    LOG_INFO("flash_payload");
    apply_language();
    // flash payload.zip via adb sideload
    // first dialog
    const char *message = strcmp(language, "de") == 0 ? "Der Prozess zum flashen des payload.zip geht davon aus, \ndass sie sich im Recovery befinden und 'Updates über ADB erlauben' aktiviert haben." : "The process for flashing the payload.zip assumes that \nyou are in Recovery and have activated 'Allow updates via ADB'.";
    show_message(message);
    
    // Show a message that the flash is starting
    const char *message1 = "Sideloading payload.zip.";
    show_message(message1);
    
    char image_path[2048];
    set_main_dir_with_wsl(image_path, sizeof(image_path), "payload.zip");

    char function_command[3072];
    char *device_command = adb_command();
    snprintf(function_command, 3072, "%s sideload %s", device_command, image_path);
    LOG_INFO("Run: %s", function_command);
    command_with_spinner(function_command);
    free(device_command);

    // Show a message that the flash is completed
    const char *message2 =  strcmp(language, "de") == 0 ? "Sideload beendet!" : "Sideload finished!";
    show_message(message2);
    LOG_INFO("end flash_payload");
}
