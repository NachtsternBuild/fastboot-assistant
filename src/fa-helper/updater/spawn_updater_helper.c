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
* Function to create a helper script for the updater
*/
int spawn_updater_helper() 
{
    struct stat st;

    // check for directory and create it
    if (stat(UPDATE_DIR, &st) == -1) 
    {
        LOGD("Directory '%s' does not exist. Create it.", UPDATE_DIR);
        if (mkdir(UPDATE_DIR, 0755) == -1) 
        {
            LOGE("mkdir");
            perror("mkdir");
            return -1;
        }
    }

    // check for the updater script
    if (stat(SCRIPT_PATH, &st) == 0) 
    {
        LOGI("Script '%s' already exists.", SCRIPT_PATH);
        return 0;
    }

    // create the updater script
    LOGD("Create update script at '%s'...", SCRIPT_PATH);
    FILE *f = fopen(SCRIPT_PATH, "w");
    if (!f) 
    {
        LOGE("fopen");
        perror("fopen");
        return -1;
    }

    if (fwrite(script_content, 1, strlen(script_content), f) < strlen(script_content)) 
    {
        LOGE("fwrite");
        perror("fwrite");
        fclose(f);
        return -1;
    }
    fclose(f);

    // make executable script
    if (chmod(SCRIPT_PATH, 0755) == -1) 
    {
        LOGE("chmod");
        perror("chmod");
        return -1;
    }

    LOGD("Update script successfully created and made executable.");
    return 0;
}
