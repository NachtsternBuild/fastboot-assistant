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
#include <gtk/gtk.h>
#include <unistd.h>  
#include <sys/stat.h> 
#include <sys/types.h> 
#include "program_functions.h"

#define LANGUAGE_FILE "language.txt" 
#define LOCALE_DOMAIN "fastboot-assistant"

const char *language = "de";

/* 
* new logic to handle the language file
*/

// set two paths for the .po files
static const char *locale_paths[] = {
    "./locale",   				  // build / run in source tree
    "/usr/share/locale"           // system-wide packages  
    "/usr/local/share/locale",    // self-installed
};

// function that create the dir
// thanks to my book for programming for linux
void create_directory_if_not_exists_lang(const char *path) 
{
    char expanded_path[512];
    snprintf(expanded_path, sizeof(expanded_path), "%s", path);
    char *home = getenv("HOME");
    if (home != NULL) 
    {
        // use the full path
        char *tilde_pos = strchr(expanded_path, '~');
        if (tilde_pos != NULL) 
        {
            memmove(expanded_path + strlen(home), tilde_pos + 1, strlen(tilde_pos));
            memcpy(expanded_path, home, strlen(home));
        }
    }

    struct stat st = {0};
    if (stat(expanded_path, &st) == -1) 
    {
        if (mkdir(expanded_path, 0700) == -1) 
        {
            LOG_ERROR("Error when creating the directory.");
            exit(1);
        }
    }
}


// function that reads the language from the file
int read_language_file(char *langbuf, size_t size)
{
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));
    
    char path[512];
    snprintf(path, sizeof(path), "%s/%s", dir_path, LANGUAGE_FILE);

    FILE *file = fopen(path, "r");
    if (!file) 
    {
    	LOG_ERROR("Error when opening the file for reading.");
    	return 0;
	}
	
    if (fgets(langbuf, size, file) == NULL) 
    {
        LOG_ERROR("Error when reading the content of the file.");
        fclose(file);
        return 0;
    }
    fclose(file);

    // trim newline
    langbuf[strcspn(langbuf, "\n")] = '\0';
    if (strlen(langbuf) < 2) return 0;

    return 1;
}


// function that writes the language to the file
void write_language_file(const char *lang)
{   
    // get the path of the config files
    char dir_path[512];
    get_config_dir(dir_path, sizeof(dir_path));
    
    char filepath[512];
    snprintf(filepath, sizeof(filepath), "%s/%s", dir_path, LANGUAGE_FILE);

    // create the dir 
    create_directory_if_not_exists_lang(dir_path);
	
	// open the language.txt
    FILE *file = fopen(filepath, "w");
    if (file == NULL) 
    {
        LOG_ERROR("Error when opening the file for writing.");
        return;
    }
	
	// write the language to the file
    fprintf(file, "%.*s\n", 2, lang); // only the first two symbols
    fclose(file);
    LOG_INFO("Written '%s' to the file '%s'.", lang, filepath);
}


// try to bind local dir and .mo files
void bind_language(const char *lang)
{
    int found = 0;
    for (int i = 0; i < (int)(sizeof(locale_paths)/sizeof(locale_paths[0])); i++) 
    {
        char testpath[512];
        snprintf(testpath, sizeof(testpath), "%s/%.*s/LC_MESSAGES/%s.mo", locale_paths[i], 2, lang, LOCALE_DOMAIN);

        FILE *file = fopen(testpath, "r");
        if (file) 
        {
            fclose(file);
            bindtextdomain(LOCALE_DOMAIN, locale_paths[i]);
            found = 1;
            LOG_INFO("Using translations from: %s", locale_paths[i]);
            break;
        }
    }

    if (!found) 
    {
        LOG_INFO("No .mo found, fallback to /usr/share/locale");
        bindtextdomain(LOCALE_DOMAIN, "/usr/share/locale");
    }

    textdomain(LOCALE_DOMAIN);
    LOG_INFO("Set textdomain: %s", LOCALE_DOMAIN);
}
