/**
* info.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

GtkWidget *root_status_label;
char command[256];

// create function to show info windows
void get_android_info(char *android_version, char *kernel_version, char *device_name, char *project_treble, char *active_slot, char *get_soc, char *get_distro, char *get_version, char *get_desktop, char *get_language, char *get_session_type) 
{
    if (!is_android_device_connected()) 
    {
        LOGE("No Android device connected.");
        return;
    }
    char *test_output = execute_command("adb devices");
	LOGD("ADB Output: %s\n", test_output);

    auto_free char *info_command = adb_command();

    // android version
    snprintf(android_version, 2048, "%s", execute_command(g_strdup_printf("%s shell getprop ro.build.version.release", info_command)));
    
    // android kernel version
    snprintf(kernel_version, 2048, "%s", execute_command(g_strdup_printf("%s shell uname -r", info_command)));

    // device name
    snprintf(device_name, 2048, "%s", execute_command(g_strdup_printf("%s shell getprop ro.product.model", info_command)));

    // project treble support
    snprintf(project_treble, 2048, "%s", execute_command(g_strdup_printf("%s shell getprop ro.treble.enabled", info_command)));

    // get active slot
    snprintf(active_slot, 2048, "%s", execute_command(g_strdup_printf("%s shell getprop ro.boot.slot_suffix", info_command)));
       
    // soc info
    snprintf(get_soc, 2048, "%s", execute_command(g_strdup_printf("%s shell grep \"model name\" /proc/cpuinfo | head -1 | awk -F ': ' '{print $2}'", info_command)));

    // get other infos 
    snprintf(get_distro, 2048, "%s", execute_command("grep '^NAME=' /etc/os-release | cut -d'=' -f2 | tr -d '\"'"));
    snprintf(get_version, 2048, "%s", execute_command("grep '^VERSION=' /etc/os-release | cut -d'=' -f2 | cut -d' ' -f1 | tr -d '\"'"));
    snprintf(get_desktop, 2048, "%s", execute_command("echo $XDG_CURRENT_DESKTOP"));
    snprintf(get_language, 2048, "%s", execute_command("echo $LANG | cut -d'_' -f1"));
    snprintf(get_session_type, 2048, "%s", execute_command("echo $XDG_SESSION_TYPE"));
}

/* main function - info */
void info(GtkWidget *widget, gpointer stack) 
{  
	LOGI("info");
	
    // Define labels based on the selected language
    const char *android_info_title = _("Android Info:");
    const char *android_version_label = _("Android Version: ");
    const char *kernel_version_label = _("Kernel Version: ");
    const char *device_name_label = _("Device Name: ");
    const char *project_treble_label = _("Project Treble: ");
    const char *active_slot_label = _("Active Slot: ");
    const char *root_access_label = _("Root Access: ");
    const char *soc_label = _("System-on-Chip: ");
    const char *computer_info_title = _("Computer Info:");
    const char *distro_label = _("Distribution: ");
    const char *version_label = _("Version: ");
    const char *desktop_label = _("Desktop: ");
    const char *language_label = _("Language: ");
    const char *session_type_label = _("Session Type: ");
    
    if (!is_android_device_connected_adb()) 
    {      
        const char *error_message = _("No device detected.");
        show_error_dialog(GTK_WIDGET(main_window), error_message);
        return;
    }
	
	// safe memory for the infos
	// declare them as char
    char android_version[2048] = {0};
    char kernel_version[2048] = {0};
    char device_name[2048] = {0};
    char project_treble[2048] = {0};
    char active_slot[2048] = {0};
    char get_soc[2048] = {0};
    char get_distro[2048] = {0};
    char get_version[2048] = {0};
    char get_desktop[2048] = {0};
    char get_language[2048] = {0};
    char get_session_type[2048] = {0};
    
    // Get all infos
    get_android_info(android_version, kernel_version, device_name, project_treble, active_slot, get_soc, get_distro, get_version, get_desktop, get_language, get_session_type);
	
	// test if stack work's with scrolled window
	GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_window_set_child(GTK_WINDOW(main_window), scrolled_window);
	
    // create box for get_devices
    GtkWidget *info = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    //gtk_window_set_child(GTK_WINDOW(scrolled_window), info);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), info);
    gtk_widget_set_halign(info, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(info, GTK_ALIGN_CENTER);
	
    // labels and add them to the window
    GtkWidget *info1_label = gtk_button_new_with_label(android_info_title);
    gtk_box_append(GTK_BOX(info), info1_label);
	
	// android-version	
    GtkWidget *android_label = gtk_label_new(g_strdup_printf("%s%s", android_version_label, android_version));
    gtk_box_append(GTK_BOX(info), android_label);
	
	// kernel-version
    GtkWidget *kernel_label = gtk_label_new(g_strdup_printf("%s%s", kernel_version_label, kernel_version));
    gtk_box_append(GTK_BOX(info), kernel_label);
	
	// device-name 
    GtkWidget *device_label = gtk_label_new(g_strdup_printf("%s%s", device_name_label, device_name));
    gtk_box_append(GTK_BOX(info), device_label);
	
	// project treble support
    GtkWidget *treble_label = gtk_label_new(g_strdup_printf("%s%s", project_treble_label, project_treble));
    gtk_box_append(GTK_BOX(info), treble_label);
	
	// get the active slot
    GtkWidget *slot_label = gtk_label_new(g_strdup_printf("%s%s", active_slot_label, active_slot));
    gtk_box_append(GTK_BOX(info), slot_label);
	
	// get the SoC info
    GtkWidget *soc_info_label = gtk_label_new(g_strdup_printf("%s%s", soc_label, get_soc));
    gtk_box_append(GTK_BOX(info), soc_info_label);
    
    // get info for root
    GtkWidget *root_label = gtk_label_new(g_strdup_printf("%s", root_access_label));
    root_status_label = gtk_label_new(_("Check for root permissions..."));
    gtk_box_append(GTK_BOX(info), root_label);
    gtk_box_append(GTK_BOX(info), root_status_label);

    GtkWidget *info2_label = gtk_button_new_with_label(computer_info_title);
    gtk_box_append(GTK_BOX(info), info2_label);
	
	// get the distro
    GtkWidget *distro_info_label = gtk_label_new(g_strdup_printf("%s%s", distro_label, get_distro));
    gtk_box_append(GTK_BOX(info), distro_info_label);
	
	// get the distro version
    GtkWidget *version_info_label = gtk_label_new(g_strdup_printf("%s%s", version_label, get_version));
    gtk_box_append(GTK_BOX(info), version_info_label);
	
	// get desktop
    GtkWidget *desktop_info_label = gtk_label_new(g_strdup_printf("%s%s", desktop_label, get_desktop));
    gtk_box_append(GTK_BOX(info), desktop_info_label);
	
	// get the language
    GtkWidget *language_info_label = gtk_label_new(g_strdup_printf("%s%s", language_label, get_language));
    gtk_box_append(GTK_BOX(info), language_info_label);
	
	// get the session type of the desktop
    GtkWidget *session_type_info_label = gtk_label_new(g_strdup_printf("%s%s", session_type_label, get_session_type));
    gtk_box_append(GTK_BOX(info), session_type_info_label);
		
	// is needed to prevent it from being stacked again when called again
    if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "info")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), scrolled_window, "info");
    }
    
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "info");
	
	// check for root
	check_root_access(root_status_label);
	
    LOGD("end info");
}
