/**
* download_update_conf.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// TODO: test updater with example url
#define GITHUB_API "https://api.github.com/repos/<USER>/<REPO>/releases/latest"
#define CONF_FILE "update.conf"

// download the update.conf from the GitHub API
bool download_update_conf() 
{
    FILE *fp;
    char url[512] = {0};

    // get the latest release and search for update.conf
    fp = popen("curl -s \"" GITHUB_API "\" | grep browser_download_url | grep update.conf | cut -d '\"' -f 4", "r");
    if (!fp)
    {
    	return false;
    }
    if (!fgets(url, sizeof(url), fp)) 
    {
        pclose(fp);
        return false;
    }
    pclose(fp);
    url[strcspn(url, "\n")] = '\0';

    if (strlen(url) == 0) 
    {
        LOGE("No update.conf URL found.");
        fprintf(stderr, "No update.conf URL found.\n");
        return false;
    }

    LOGD("Found update.conf: %s", url);
    char cmd[1024];
    
    char conf_dir[128];
    char update_file[256];
    
    get_config_dir(conf_dir, sizeof(conf_dir));
    snprintf(update_file, sizeof(update_file), "%s/%s", conf_dir, CONF_FILE);
    
    snprintf(cmd, sizeof(cmd), "wget -q -O %s %s", update_file, url);
    run_command(cmd);
    return true; 
}
