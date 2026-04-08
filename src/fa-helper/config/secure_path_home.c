/**
* secure_path_home.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

/**
* @brief Validate that the string is a single, safe path component (e.g. a user name).
* It must not be empty, must not contain path separators, and must not contain "..".
*/ 
int is_safe_single_path_component(const char *s)
{
    size_t len;

    if (s == NULL) {
        return 0;
    }

    len = strlen(s);
    if (len == 0 || len > 255) {
        return 0;
    }

    if (strchr(s, '/') != NULL || strchr(s, '\\') != NULL) {
        return 0;
    }

    if (strstr(s, "..") != NULL) {
        return 0;
    }

    return 1;
}

/** 
* @brief Basic validation for HOME-like directory variables.
* Require a non-empty absolute path (starting with '/').
*/
int is_safe_home_dir(const char *s)
{
    if (s == NULL) {
        return 0;
    }

    if (s[0] != '\0' && s[0] == '/') {
        return 1;
    }

    return 0;
}
