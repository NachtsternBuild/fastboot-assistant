/**
* local_updater.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

#define LOCAL_CONF "local.conf"
#define UPDATE_CONF "update.conf"

// run updater for local installed DEB packages
void local_updater()
{
    notify_init("Fastboot-Assistant Updater");
    const char *title = _("Fastboot-Assistant Updater");
    char conf_dir[128];
    char update_file[256];
    char local_file[256];
    get_config_dir(conf_dir, sizeof(conf_dir));
    snprintf(update_file, sizeof(update_file), "%s/%s", conf_dir, UPDATE_CONF);
    snprintf(local_file, sizeof(local_file), "%s/%s", conf_dir, LOCAL_CONF);
    	
	// get the update.conf
    if (!download_update_conf()) 
    {
        notify_notification_show(notify_notification_new(title, _("Update check failed."), "dialog-error"), NULL);
        return;
    }
	
	// get the config values
    char *local_version = get_config_value(local_file, "version");
    char *remote_version = get_config_value(update_file, "version");
    char *package_url = get_config_value(update_file, "packageurl");
    char *package_name = get_config_value(update_file, "package");

    if (!local_version || !remote_version || !package_url) 
    {
        LOGE("Invalid configuration files.");
        fprintf(stderr, "Invalid configuration files.\n");
        goto cleanup;
    }

    LOGI("Local version: %s", local_version);
    LOGI("Remote version: %s", remote_version);
	
	// check version
    if (strcmp(local_version, remote_version) == 0) 
    {
        notify_notification_show(notify_notification_new(title, _("No updates available."), "emblem-ok-symbolic"), NULL);
        goto cleanup;
    }

    // update avaible
    char msg[256];
    snprintf(msg, sizeof(msg), _("Update to version %s available."), remote_version);
    notify_notification_show(notify_notification_new(title, msg, "software-update-available"), NULL);

    // download package
    LOGD("Download package: %s", package_url);
    char cmd[1024];
    char package_path[128];
    snprintf(package_path, sizeof(package_path), "/tmp/%s", package_name);
    snprintf(cmd, sizeof(cmd), "wget -q -O %s %s", package_path, package_url);
    
    if (!run_command_bool(cmd)) 
    {
        notify_notification_show(notify_notification_new(title, _("Error downloading the package."), "dialog-error"), NULL);
        goto cleanup;
    }
	
	char tmp_pkg_cmd[512];
	snprintf(tmp_pkg_cmd, sizeof(tmp_pkg_cmd), "pkexec apt install -y \"%s\"", package_path);
    // start child process that waits for FA to terminate
    spawn_updater_helper(tmp_pkg_cmd);

// running cleanup
cleanup:
    if (local_version) 
    {	
    	free(local_version);
    }
    if (remote_version)
    {
    	free(remote_version);
    }
    if (package_url) 
    {
    	free(package_url);
    }
    if (package_name) 
    {
    	free(package_name);
    }
    notify_uninit();
}

