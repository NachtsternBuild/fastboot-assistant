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
 *        Headerpart - dynamic_language		 *
 *											 *
 *-------------------------------------------*
 */

/* headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <sys/stat.h>
#include <unistd.h>
#include "program_functions.h"
#include "language_check.h"

// function that read the language from files
// function that get the system language and create the language.txt
void init_language(void)
{
    // get the local config
    setlocale(LC_ALL, "");
	
	// try to read the language from the language file
	LOG_INFO("Reading language from language.txt");
    char langbuf[16] = {0};
    if (!read_language_file(langbuf, sizeof(langbuf))) 
    {
        // missing language.txt → get the system language
        LOG_INFO("Missing language.txt.");
        LOG_INFO("Set language by the system language.");
        const char *envlang = getenv("LANG");
        if (!envlang || strlen(envlang) < 2)
        {
            strcpy(langbuf, "en"); // fallback english
        } 
        
        else 
        {
            strncpy(langbuf, envlang, 2);
            langbuf[2] = '\0';
        }
		
		LOG_INFO("Writing %s to language.txt", langbuf);
        // write the language to the file
        write_language_file(langbuf);
    }

    // set global usage of the language
    LOG_INFO("Set new language: %s", langbuf);
    setenv("LANGUAGE", langbuf, 1);
    bind_language(langbuf);
}

// function that set the language manuell
void set_language(const char *lang)
{
    if (!lang || strlen(lang) < 2)
    {
    	LOG_INFO("Using fallback language");
    	lang = "en"; // fallback to english
    }
    write_language_file(lang);
	
	LOG_INFO("Set the new language: %s", lang);
    setenv("LANGUAGE", lang, 1);
    setlocale(LC_ALL, "");
    bind_language(lang);
}



