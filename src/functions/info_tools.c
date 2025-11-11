/**
* info_tools.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// function to get the package 
void get_package_status(const char *command, char *output, size_t size, gboolean *is_installed) 
{
    FILE *fp = popen(command, "r");
    if (fp == NULL) 
    {
        snprintf(output, size, "Error: Unable to fetch version");
        *is_installed = FALSE;
        return;
    }

    if (fgets(output, size, fp) != NULL) 
    {
        strtok(output, "\n"); // remove linbreak
        *is_installed = TRUE;
    } 
    
    else 
    {
        snprintf(output, size, "Not Installed");
        *is_installed = FALSE;
    }

    pclose(fp);
}

/* main function - info_tools */
void info_tools(GtkWidget *widget, gpointer stack)  
{  
    LOGD("info_tools");
    
    char versions[12][2048] = {0};
    char informations[15][2048] = {0};
    gboolean is_installed[12] = {FALSE};

    // define labels 
    //const char *version_info_title = _("System and Package Informations");
    const char *system_infos = _("System and Package Informations:");
    const char *version_package = _("Package Informations:");
	
	// commands for system informations
    const char *commands_system[] = {
        "grep '^NAME=' /etc/os-release | cut -d'=' -f2 | tr -d '\"'",
        "grep '^VERSION=' /etc/os-release | cut -d'=' -f2 | cut -d' ' -f1 | tr -d '\"'",
        "uname -r",
        "grep \"model name\" /proc/cpuinfo | head -1 | awk -F ': ' '{print $2}'",
        "lspci | grep -i \"vga\" | awk -F ': ' '{print $2}'",
        "echo $XDG_CURRENT_DESKTOP",
        "echo $LANG | cut -d'_' -f1",
        "echo $XDG_SESSION_TYPE",
    };
    
	// labels for system informations
    const char *labels_system[] = {
        _("Distribution: "),
        _("Version: "),
        _("Kernel-Version: "),
        _("Processor: "),
        _("Graphics card: "),
        _("Desktop: "),
        _("Language: "),
        _("Session: "),
    };

    // commands for the packages
    const char *commands_packages[] = {
        "which adb",
        "which fastboot",
        "which xz",
        "which unzip",
        "which zip",
        "which wget",
        "which curl",
        "which pkexec",
        "which heimdall",
        "which gtk4-demo",
        "which ls",
        "which ldd",
    };
	
	// lables for the packages
	const char *labels_packages[] = {
	    _("ADB: "),
	    _("Fastboot: "),
	    _("XZ-Utils: "),
	    _("Unzip: "),
	    _("Zip: "),
	    _("Wget: "),
	    _("Curl: "),
	    _("Pkexec: "),
	    _("Heimdall: "),
	    _("GTK+: "),
	    _("Coreutils: "),
	    _("Libc6: "),
	};
    
    // function to get the infos
    for (int i = 0; i < 8; i++) 
    {
        get_package_status(commands_system[i], informations[i], sizeof(informations[i]), &is_installed[i]);
    }
    
    // function to get the installed packages
    for (int i = 0; i < 12; i++) 
    {
        get_package_status(commands_packages[i], versions[i], sizeof(versions[i]), &is_installed[i]);
    }

    // test if stack work's with scrolled window
	GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_window_set_child(GTK_WINDOW(main_window), scrolled_window);
	
    // create box for get_devices
    GtkWidget *info_tools = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    //gtk_window_set_child(GTK_WINDOW(scrolled_window), info);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), info_tools);
    gtk_widget_set_halign(info_tools, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(info_tools, GTK_ALIGN_CENTER);
	
	// system informations
	GtkWidget *system_info_title_label = gtk_button_new_with_label(system_infos);
    gtk_box_append(GTK_BOX(info_tools), system_info_title_label);
    
    GtkWidget *assistant_version_label = gtk_button_new_with_label(_("Fastboot-Assistant: v.0.9.1.dev"));
    gtk_box_append(GTK_BOX(info_tools), assistant_version_label);

    // add system info labels to the window
    for (int i = 0; i < 8; i++) 
    {
        GtkWidget *label = gtk_label_new(g_strdup_printf("%s%s", labels_system[i], informations[i]));
        gtk_box_append(GTK_BOX(info_tools), label);
    }
	
	// packages versions
    GtkWidget *version_title_label = gtk_button_new_with_label(version_package);
    gtk_box_append(GTK_BOX(info_tools), version_title_label);
    
    // add version info labels to the window
    // packageinforamtions with labels
    for (int i = 0; i < 12; i++) 
    {
        const char *checkmark = is_installed[i] ? "✅ " : "❌ ";
        GtkWidget *label = gtk_label_new(g_strdup_printf("%s%s%s", labels_packages[i], checkmark, versions[i]));
        gtk_box_append(GTK_BOX(info_tools), label);
    }
    
    // is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "info_tools")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), scrolled_window, "info_tools");
    }
    
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "info_tools");
	
    LOGD("end info_tools");
}

