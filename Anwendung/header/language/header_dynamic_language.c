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
 *              Headerpart - language_check	 *
 *											 *
 *-------------------------------------------*
 */

/* headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "program_functions.h"
#include "language_check.h"


const char *locale_paths[] = {
        "./locale",             //  build or working dir
        "/usr/share/locale"     // systempath
};

// function that init language based on the system language
void init_language(void) 
{
    setlocale(LC_ALL, "");

    const char *lang = getenv("LANG");
    if (!lang || strlen(lang) < 2) 
    {
        lang = "en";  // fallback english
    }

    int found = 0;
    for (int i = 0; i < sizeof(locale_paths)/sizeof(locale_paths[0]); i++) 
    {
        char testpath[512];
        snprintf(testpath, sizeof(testpath),
                 "%s/%.*s/LC_MESSAGES/%s.mo",
                 locale_paths[i], 2, lang, LOCALE_DOMAIN);

        FILE *f = fopen(testpath, "r");
        if (f) 
        {
            fclose(f);
            bindtextdomain(LOCALE_DOMAIN, locale_paths[i]);
            found = 1;
            break;
        }
    }

    if (!found) 
    {
        // fallback auf System
        bindtextdomain(LOCALE_DOMAIN, "/usr/share/locale");
    }

    textdomain(LOCALE_DOMAIN);
}


// function that set the language manuell
void set_language(const char *lang) 
{
    if (!lang || strlen(lang) < 2) lang = "en"; // fallback

    setenv("LANGUAGE", lang, 1);
    setlocale(LC_ALL, "");

    int found = 0;
    for (int i = 0; i < sizeof(locale_paths)/sizeof(locale_paths[0]); i++) 
    {
        char testpath[512];
        snprintf(testpath, sizeof(testpath),
                 "%s/%.*s/LC_MESSAGES/%s.mo",
                 locale_paths[i], 2, lang, LOCALE_DOMAIN);

        FILE *f = fopen(testpath, "r");
        if (f) 
        {
            fclose(f);
            bindtextdomain(LOCALE_DOMAIN, locale_paths[i]);
            found = 1;
            break;
        }
    }

    if (!found) 
    {
        // fallback auf Systempfad
        bindtextdomain(LOCALE_DOMAIN, "/usr/share/locale");
    }

    textdomain(LOCALE_DOMAIN);
}



