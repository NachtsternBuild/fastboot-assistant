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
void get_android_info(char *android_version, char *kernel_version, char *device_name, char *project_treble, char *active_slot, char *get_soc) 
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
}

/* main function - info */
void info(GtkWidget *widget, gpointer stack) 
{  
	LOGD("info");
	
    // Define labels based on the selected language
    const char *android_info_title = _("Android Info:");
    const char *android_version_label = _("Android Version: ");
    const char *kernel_version_label = _("Kernel Version: ");
    const char *device_name_label = _("Device Name: ");
    const char *project_treble_label = _("Project Treble: ");
    const char *active_slot_label = _("Active Slot: ");
    const char *root_access_label = _("Root Access: ");
    const char *soc_label = _("System-on-Chip: ");
    
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
    
    // Get all infos
    get_android_info(android_version, kernel_version, device_name, project_treble, active_slot, get_soc);
	
	// create the main window
    AdwApplicationWindow *info_window = ADW_APPLICATION_WINDOW(adw_application_window_new(app));
    
    // create toolbar for header and content
    GtkWidget *toolbar_view = adw_toolbar_view_new();

    // create headerbar
    GtkWidget *header_bar = adw_header_bar_new();
    GtkWidget *title = gtk_label_new(_("Info"));
    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header_bar), title);

    adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(toolbar_view), header_bar);
    gtk_window_set_default_size(GTK_WINDOW(info_window), WINDOW_WIDTH, WINDOW_HEIGHT);
	
	GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	
    // create box for get_devices
    GtkWidget *info = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), info);
    gtk_widget_set_halign(info, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(info, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(info, TRUE);
    gtk_widget_set_vexpand(info, TRUE);
	
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
		
	//
	adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(toolbar_view), scrolled_window);
	adw_application_window_set_content(info_window, toolbar_view);
	
	gtk_window_present(GTK_WINDOW(info_window));
	
	// check for root
	check_root_access(root_status_label);
	
    LOGD("end info");
}
