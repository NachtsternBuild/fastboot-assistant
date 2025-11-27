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

// helper to run the updater script
static void run_update(char *package_path)
{
    char cmd[512];
    pid_t pid = getpid();  // PID of fastboot-assistant

    snprintf(cmd, sizeof(cmd), "bash /var/lib/fastboot-assistant/fa-updater.sh %d \"%s\" &", pid, package_path);

    system(cmd);
}

/**
* Run updater for local installed DEB packages
*/
void local_updater()
{
    if (!notify_init("Fastboot-Assistant Updater"))
    {
        fprintf(stderr, "Libnotify could not be initialized.\n");
        return;
    }

    NotifyNotification *n = NULL;
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
        n = notify_notification_new(title, _("Update check failed."), "dialog-error");
        notify_notification_set_timeout(n, 5000);
        notify_notification_show(n, NULL);
        goto cleanup;
    }

	
	// get the config values
    char *local_version = get_config_value(local_file, "version");
    char *remote_version = get_config_value(update_file, "version");
    char *package_url = get_config_value(update_file, "packageurl");
    char *package_name = get_config_value(update_file, "package");

    if (!local_version || !remote_version || !package_url) 
    {
        LOGE("Invalid configuration files.");
        n = notify_notification_new(title, _("Error: Invalid configuration files."), "dialog-error");
        notify_notification_set_timeout(n, 5000);
        notify_notification_show(n, NULL);
        goto cleanup;
    }

    LOGI("Local version: %s", local_version);
    LOGI("Remote version: %s", remote_version);
	
	// check version
    if (strcmp(local_version, remote_version) == 0) 
    {
         n = notify_notification_new(title, _("No updates available."), "emblem-ok-symbolic");
        notify_notification_set_timeout(n, 3000);
        notify_notification_show(n, NULL);
        goto cleanup;
    }

    // update avaible
    char msg[256];
    snprintf(msg, sizeof(msg), _("Update to version %s available."), remote_version);
    n = notify_notification_new(title, msg, "software-update-available");
    notify_notification_show(n, NULL);

    // download package
    LOGD("Download package: %s", package_url);
    char cmd[1024];
    char package_path[128];
    snprintf(package_path, sizeof(package_path), "/tmp/%s", package_name);
    snprintf(cmd, sizeof(cmd), "wget -q -O %s %s", package_path, package_url);
    
    if (!run_command_bool(cmd)) 
    {
        n = notify_notification_new(title, _("Error downloading the package."), "dialog-error");
        notify_notification_show(n, NULL);
        goto cleanup;
    }
	
	// install the update
    run_update(package_path);

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

