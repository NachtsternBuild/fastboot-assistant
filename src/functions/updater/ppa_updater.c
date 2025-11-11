/**
* ppa_updater.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// run updater for PPA installed DEB packages
void ppa_updater()
{	
	char tmp_pkg_cmd[512];
	snprintf(tmp_pkg_cmd, sizeof(tmp_pkg_cmd), "pkexec sh -c \"apt update && apt upgrade\"");
    // start child process that waits for FA to terminate
    spawn_updater_helper(tmp_pkg_cmd);
}

