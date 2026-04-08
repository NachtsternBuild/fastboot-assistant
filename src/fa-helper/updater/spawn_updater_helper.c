/**
* spawn_updater_helper.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

#define UPDATE_DIR "/var/lib/fastboot-assistant"
#define SCRIPT_PATH UPDATE_DIR "/fa-updater.sh"

// content of the updater script
const char *script_content =
"#!/bin/bash\n"
"PID=\"$1\"\n"
"PKG_PATH=\"$2\"\n"
"APP_NAME=\"fastboot-assistant\"\n"
"CHECK_INTERVAL=2\n"
"\n"
"notify_user() {\n"
"    if command -v notify-send >/dev/null 2>&1; then\n"
"        notify-send \"Update available for the Fastboot-Assistant\" \"$1\"\n"
"    fi\n"
"}\n"
"\n"
"if [ -z \"$PID\" ] || [ -z \"$PKG_PATH\" ]; then\n"
"    notify_user \"[ERROR] Update script started without PID or package path.\"\n"
"    exit 1\n"
"fi\n"
"\n"
"notify_user \"Please close $APP_NAME to perform the update.\"\n"
"\n"
"while kill -0 \"$PID\" >/dev/null 2>&1; do\n"
"    sleep \"$CHECK_INTERVAL\"\n"
"done\n"
"\n"
"if pkexec apt install \"$PKG_PATH\" -y; then\n"
"    notify_user \"Update successfully installed!\"\n"
"else\n"
"    notify_user \"[ERROR] Error with Update!\"\n"
"    exit 1\n"
"fi\n"
"\n"
"exit 0\n";

/**
* @brief Function to create a helper script for the updater
*/
int spawn_updater_helper() 
{
    struct stat st;

    // check directory 
    if (stat(UPDATE_DIR, &st) == -1) 
    {
        LOGD("Directory '%s' does not exist. Create it.", UPDATE_DIR);
        // create directory with 755 in /var
        if (mkdir(UPDATE_DIR, 0755) == -1) 
        {
            LOGE("mkdir");
            perror("mkdir");
            return -1;
        }
    }

    // create file with 755 permissions
    int fd = open(SCRIPT_PATH, O_WRONLY | O_CREAT | O_EXCL, S_IRWXU | S_IRGRP | S_IXGRP);
    
    if (fd == -1) 
    {
        if (errno == EEXIST) 
        {
            LOGI("Script '%s' already exists.", SCRIPT_PATH);
            return 0;
        }
        LOGE("Could not create updater script: %s", strerror(errno));
        return -1;
    }

    // convert for writing
    FILE *f = fdopen(fd, "w");
    if (!f) 
    {
        LOGE("fdopen");
        close(fd);
        return -1;
    }

    LOGD("Writing update script to '%s'...", SCRIPT_PATH);
    if (fwrite(script_content, 1, strlen(script_content), f) < strlen(script_content)) 
    {
        LOGE("fwrite failed");
        fclose(f); // close fd
        return -1;
    }
    
    fclose(f);

    LOGD("Update script successfully created and made executable.");
    return 0;
}

