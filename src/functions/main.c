/**
* main.c
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
*/
#include "fastboot_assistant.h"

// for the main window
GtkWidget *main_window = NULL;
GtkApplication* app;


// function that show the about site
static void about(GtkWidget *widget, gpointer stack)
{
	show_about_dialog(widget);
}

// function that show the fastboot-assistant window
void activate_fastboot_assistant(GtkApplication* app, gpointer user_data) 
{
    // start logging
    // 0 → manual logging
    // 1 → syslog
    set_logging_mode(1);
    
    // apply language
    init_language();
    
    // use the advanced custom css provider
    use_adw_provider();
    
    // run post update function
    post_update();
	
	// run config check
	// check if first setup
    const char *content = "Fisch";
    char fish_path[512];
    char setup_dir[1024];
    char setup_file[1050];
    char setup_info[20];

    // get config path
    get_config_dir(fish_path, sizeof(fish_path));
    snprintf(setup_dir, sizeof(setup_dir), "%s/config", fish_path);
    LOGD("Config path: %s", setup_dir);
    // create dir 
    create_directory(setup_dir);

    // create config file
    snprintf(setup_file, sizeof(setup_file), "%s/config.txt", setup_dir);

    FILE *file;

    // check if file exists
    if ((file = fopen(setup_file, "r")) != NULL) 
    {
        fclose(file);
        snprintf(setup_info, sizeof(setup_info), "old_fish");
        LOGD("old fish!");
    } 
    
    else 
    {
        file = fopen(setup_file, "w");
        if (file == NULL) 
        {
            LOGE("Could not create the file.");
            exit(1);
        }
        fprintf(file, "%s", content);
        fclose(file);
        snprintf(setup_info, sizeof(setup_info), "fish");
        LOGD("fish");
    }
    
    // create the main window
    AdwApplicationWindow *main_window = ADW_APPLICATION_WINDOW(adw_application_window_new(app));
    
    // create toolbar for header and content
    GtkWidget *toolbar_view = adw_toolbar_view_new();

    // create headerbar
    GtkWidget *header_bar = adw_header_bar_new();
    GtkWidget *title = gtk_label_new(_("Fastboot-Assistant"));
    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header_bar), title);

    adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(toolbar_view), header_bar);
        
    //main_window = gtk_application_window_new(app);
    //gtk_window_set_title(GTK_WINDOW(main_window), _("Fastboot-Assistant"));
    gtk_window_set_default_size(GTK_WINDOW(main_window), WINDOW_WIDTH, WINDOW_HEIGHT);

    // create a box container for the main content
    GtkWidget *content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    //gtk_window_set_child(GTK_WINDOW(main_window), content_box);
    //adw_application_window_set_content(main_window, content_box);
    gtk_widget_set_halign(content_box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(content_box, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(content_box, TRUE);
    gtk_widget_set_vexpand(content_box, TRUE);

    // create the stack for navigation
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
    gtk_stack_set_transition_duration(GTK_STACK(stack), 300);
    gtk_widget_set_hexpand(stack, TRUE);
    gtk_widget_set_vexpand(stack, TRUE);

    // add the headerbar
    GtkWidget *headerbar = create_custom_headerbar(stack);
    gtk_box_append(GTK_BOX(content_box), headerbar);

    // add the stack to the box
    gtk_box_append(GTK_BOX(content_box), stack);

    // create the home page grid
    GtkWidget *home_page = gtk_grid_new();
    gtk_grid_set_row_homogeneous(GTK_GRID(home_page), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(home_page), TRUE);
    gtk_widget_set_halign(home_page, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(home_page, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(home_page, TRUE);
    gtk_widget_set_vexpand(home_page, TRUE);

    // create the buttons with translated labels
    GtkWidget *btn1 = create_button_icon_position("folder-publicshare-symbolic", _("Devices"), G_CALLBACK(get_devices), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn2 = create_button_icon_position("system-reboot-symbolic", _("Reboot Device"), G_CALLBACK(reboot_GUI), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn3 = create_button_icon_position("applications-system-symbolic", _("Settings"), G_CALLBACK(config_project_GUI), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn4 = create_button_icon_position("applications-engineering-symbolic", _("Prepare Flashing"), G_CALLBACK(preflash_GUI), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn5 = create_button_icon_position("drive-multidisk-symbolic", _("Flash"), G_CALLBACK(flash_GUI), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn6 = create_button_icon_position("system-help-symbolic", _("Instructions"), G_CALLBACK(instruction_GUI), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn7 = create_button_icon_position("phone-apple-iphone-symbolic", _("Info"), G_CALLBACK(info), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn8 = create_button_icon_position("drive-harddisk-system-symbolic", _("Treble Updater"), G_CALLBACK(treble_updater), stack, GTK_ALIGN_CENTER);
    GtkWidget *btn9 = create_button_icon_position("help-about-symbolic", _("About"), G_CALLBACK(about), stack, GTK_ALIGN_CENTER);

    // add buttons to grid
    gtk_grid_attach(GTK_GRID(home_page), btn1, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(home_page), btn2, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(home_page), btn3, 2, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(home_page), btn4, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(home_page), btn5, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(home_page), btn6, 2, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(home_page), btn7, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(home_page), btn8, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(home_page), btn9, 2, 2, 1, 1);

    // add grid to stack
    gtk_stack_add_named(GTK_STACK(stack), home_page, "home_page");
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "home_page");
	
	adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(toolbar_view), content_box);
	
	adw_application_window_set_content(main_window, toolbar_view);
	
    gtk_window_present(GTK_WINDOW(main_window));
	
	// run setup if needed
    if (g_strcmp0(setup_info, "fish") == 0) 
    {
        LOGD("run setup");
        run_first_run_setup(GTK_WIDGET(main_window), stack);
        LOGD("setup completed.");
    } 
    
    else 
    {
        LOGD("no setup");
    }
    
    check_ab_file_light();
	
	// stop logging
    close_logging();
}

