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
    // start child process that waits for FA to terminate
    commands_pkexec_spinner(GTK_WIDGET(main_window), "apt update && apt upgrade", "Updates", "Running Update"); 
}

