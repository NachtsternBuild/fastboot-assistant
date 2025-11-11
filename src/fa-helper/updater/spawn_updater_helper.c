/**
* spawn_updater_helper.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// create a new child process, that run the update
void spawn_updater_helper(const char *pkg_cmd)
{
    notify_init("Fastboot-Assistant Updater");
    // create childprocess
    pid_t pid = fork();
    if (pid < 0) 
    {
        perror("fork failed");
        return;
    }

    if (pid == 0) 
    {
        // child process
        pid_t parent = getppid();

        if (setsid() < 0) 
        {
            perror("setsid failed");
		}
		
        LOGD("Updater child started, waiting for parent process %d to finish...", parent);
        const char *title = _("Fastboot-Assistant Updater");
        const char *text1 = _("Exit Fastboot Assistant to install the update.");
        const char *text2 = _("Update successfully installed!");
        const char *text3 = _("Error during installation!");
		notify_notification_show(notify_notification_new(title, text1, "software-update-available"), NULL);
		
		// wait for parent process
        while (kill(parent, 0) == 0) 
        {
            sleep(1);
		}
        printf("Elternprozess beendet. Starte Update...\n");

        // run command with pkexec
        int ret = system(pkg_cmd);

    	NotifyNotification *n;
    	if (ret == 0) 
    	{
        	n = notify_notification_new(title, text2, "software-update-available");
    	} 
    	else 
    	{
        	n = notify_notification_new(title, text3, "dialog-error");
    	}
    	notify_notification_show(n, NULL);
    	notify_uninit();

        exit(0);
    }

    // parent process run normal 
    LOGD("Updater child started.");
}
