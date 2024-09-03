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
 *      (C) Copyright 2024 Elias Mörz 		 *
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
#include "program_functions.h"

void flash_payload(GtkWidget *widget, gpointer data)
{
    // flash payload.zip via adb sideload
    const char *title, *message;
    
    // first dialog called 'Hinweis'
    title = "Hinweis";
    message = "Der Prozess zum flashen des payload.zip geht davon aus, dass sie sich im Recovery befinden und 'Updates über ADB erlauben' aktiviert haben.\n";
    show_message_with_title(title, message);
    
    // Show a message that the flash is starting
    const char *message1 = "Sideload payload.zip.\n";
    show_message(message1);
    
    char image_path[2048];
    set_main_dir_with_wsl(image_path, sizeof(image_path), "payload.zip");

    char function_command[3071];
    snprintf(function_command, sizeof(function_command), "adb sideload %s && exit", image_path);
    g_print(function_command);
    open_terminal_by_desktop(function_command);

    // Show a message that the flash is completed
    const char *message2 = "Sideload beendet!\n";
    show_message(message2);
}
