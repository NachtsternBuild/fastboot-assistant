/*
 *-------------------------------------------*
 *                Projekt 122                *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  						 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *         Headerpart - write_log_text		 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <signal.h>
#include <unistd.h>
#include "function_header.h"
#include "program_functions.h"
#include "language_check.h"

GtkWidget *text_view = NULL;
FILE *log_file_fc;
int log_fd;
gsize last_offset = 0;
guint log_timeout_id = 0;

// function that get the log file
void get_log_filepath(char *log_file, size_t size)
{
    char log_dir[4096];
    get_config_dir(log_dir, sizeof(log_dir));
    snprintf(log_file, size, "%s/log/log.txt", log_dir);

    // create directory if needed
    char create_log_dir[4096];
    snprintf(create_log_dir, sizeof(create_log_dir), "%s/log", log_dir);
    if (access(create_log_dir, F_OK) == -1)
    {
        create_directory(create_log_dir);
    }
}

// function to write string to the textview 
void write_to_textview(GtkWidget *text_view, const char *str)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    if (!buffer) return;

    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(buffer, &iter);
    gtk_text_buffer_insert(buffer, &iter, str, -1);
    gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(text_view), &iter, 0, TRUE, 0.0, 0.0);
}

// function that read new log data and update textview
gboolean update_text_view_from_log(gpointer user_data)
{
    char log_file[4096];
    get_log_filepath(log_file, sizeof(log_file));
	
	// open the log file
    FILE *file = fopen(log_file, "r");
    if (!file) return G_SOURCE_CONTINUE;

    fseek(file, last_offset, SEEK_SET);
    gchar buffer[512];
    // loop to write everything to the textview
    while (fgets(buffer, sizeof(buffer), file)) 
    {
        write_to_textview(text_view, buffer);
    }
    gboolean update_text_view_from_log(gpointer user_data);

    last_offset = ftell(file);
    fclose(file);
    return G_SOURCE_CONTINUE;
}

// cleanup when log viewer is closed 
void log_viewer_destroyed(GtkWidget *widget, gpointer user_data)
{
    if (log_timeout_id > 0)
    {
        g_source_remove(log_timeout_id);
        log_timeout_id = 0;
    }
}

// function that create the 
void log_viewer(GtkButton *button, gpointer user_data)
{
    apply_language();
	
	// create the log window
    GtkWidget *window_log = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window_log), "Log Viewer");
    gtk_window_set_default_size(GTK_WINDOW(window_log), WINDOW_WIDTH, WINDOW_HEIGHT);
    g_signal_connect(window_log, "destroy", G_CALLBACK(log_viewer_destroyed), NULL);
	
	// add the main box
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_window_set_child(GTK_WINDOW(window_log), main_box);
	
	// create the text view
    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);
	
	// create the scrolled window
    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), text_view);
    gtk_widget_set_hexpand(scrolled_window, TRUE); 
    gtk_widget_set_vexpand(scrolled_window, TRUE); 
	
	// add the scrolled window to the box
    gtk_box_append(GTK_BOX(main_box), scrolled_window);

    char log_file[4096];
    get_log_filepath(log_file, sizeof(log_file));
	
	// open the log file
    FILE *tmp = fopen(log_file, "r");
    if (tmp)
    {
        fseek(tmp, 0, SEEK_END);
        last_offset = ftell(tmp);
        fclose(tmp);
    }
	
	// update the log every 250 ms
    log_timeout_id = g_timeout_add(250, update_text_view_from_log, NULL);

    gtk_window_present(GTK_WINDOW(window_log));
}

// function that kill the fastboot-assistant
void kill_fastboot_assistant(GtkButton *button, gpointer user_data)
{
	// get the pid of the fastboot-assistant
	pid_t pid = getpid(); 
	// kill themselve
    kill(pid, SIGKILL);
}

// header that create the popover menu
GtkWidget* create_custom_headerbar(gpointer stack) 
{
    apply_language();
    
    /*
    Icons for the menu:
    - item 1 - utilities-terminal / utilities-terminal-symbolic
    - item 2 - help-about
    - item 3 - phone
    - item 4 - computer
    - item 5 - process-stop / application-exit
    */
    
    // create the headerbar as GTK box and create a menu
    GtkWidget *headerbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *menu_button = gtk_menu_button_new();
    GtkWidget *popover = gtk_popover_new();
    GtkWidget *menu = gtk_list_box_new();
    
    /* item 1 */
    // function: show log window
   	GtkWidget *item1 = gtk_list_box_row_new();
	GtkWidget *icon1 = gtk_image_new_from_icon_name("utilities-system-monitor-symbolic"); // utilities-terminal - utilities-terminal-symbolic - utilities-system-monitor-symbolic
	GtkWidget *label1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Log ansehen" : "Show Log");

	// box for the icon and the label
	GtkWidget *hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6); // 6 px distance
	gtk_box_append(GTK_BOX(hbox1), icon1);
	gtk_box_append(GTK_BOX(hbox1), label1);

	// create the button 
	GtkWidget *button1 = gtk_button_new();
	gtk_button_set_child(GTK_BUTTON(button1), hbox1);
	gtk_widget_set_tooltip_text(button1, "Show Log ");
	gtk_widget_set_halign(button1, GTK_ALIGN_START);
	// connect to the log viewer
	g_signal_connect(button1, "clicked", G_CALLBACK(log_viewer), NULL);

	// add button to the item1
	gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(item1), button1);
	// add the item1 to the menu
	gtk_list_box_append(GTK_LIST_BOX(menu), item1);  
        
	/* item 2 */   
	// function: show connected devices
	GtkWidget *item2 = gtk_list_box_row_new();
	GtkWidget *icon2 = gtk_image_new_from_icon_name("media-optical-symbolic"); // dialog-information help-about-symbolic network-wired media-optical-symbolic
	GtkWidget *label2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Geräte" : "Devices");
	
	// box for the icon and the label
	GtkWidget *hbox2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
	gtk_box_append(GTK_BOX(hbox2), icon2);
	gtk_box_append(GTK_BOX(hbox2), label2);
	
	// create the button 
	GtkWidget *button2 = gtk_button_new();
	gtk_button_set_child(GTK_BUTTON(button2), hbox2);
	gtk_widget_set_tooltip_text(button2, "Connected Devices");
	gtk_widget_set_halign(button2, GTK_ALIGN_START);
	// connect to the get_devices
	g_signal_connect(button2, "clicked", G_CALLBACK(get_devices), stack); 
	
	// add button to the item2
	gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(item2), button2);
	// add the item2 to menu
	gtk_list_box_append(GTK_LIST_BOX(menu), item2);

	/* item 3 */
	// function: show info
    GtkWidget *item3 = gtk_list_box_row_new();
    GtkWidget *icon3 = gtk_image_new_from_icon_name("multimedia-player-apple-ipod-touch-symbolic");
    GtkWidget *label3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Geräte Info" : "Device Info");
    
    // box for the icon and the label
	GtkWidget *hbox3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
	gtk_box_append(GTK_BOX(hbox3), icon3);
	gtk_box_append(GTK_BOX(hbox3), label3);
    
    // create the button 
	GtkWidget *button3 = gtk_button_new();
	gtk_button_set_child(GTK_BUTTON(button3), hbox3);
	gtk_widget_set_tooltip_text(button3, "Device Info");
	gtk_widget_set_halign(button3, GTK_ALIGN_START);
	// connect to the get_devices
	g_signal_connect(button3, "clicked", G_CALLBACK(info), NULL); 
	
	// add button to the item2
	gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(item3), button3);
	// add the item2 to menu
	gtk_list_box_append(GTK_LIST_BOX(menu), item3);
	
	/* item 4 */
	// function: show computer info
    GtkWidget *item4 = gtk_list_box_row_new();
    GtkWidget *icon4 = gtk_image_new_from_icon_name("start-here-symbolic");
    GtkWidget *label4 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "System Info" : "System Info");
    
    // box for the icon and the label
	GtkWidget *hbox4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
	gtk_box_append(GTK_BOX(hbox4), icon4);
	gtk_box_append(GTK_BOX(hbox4), label4);
    
    // create the button 
	GtkWidget *button4 = gtk_button_new();
	gtk_button_set_child(GTK_BUTTON(button4), hbox4);
	gtk_widget_set_tooltip_text(button4, "Computer Info");
	gtk_widget_set_halign(button4, GTK_ALIGN_START);
	// connect to the get_devices
	g_signal_connect(button4, "clicked", G_CALLBACK(info_tools), NULL); 
	
	// add button to the item2
	gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(item4), button4);
	// add the item2 to menu
	gtk_list_box_append(GTK_LIST_BOX(menu), item4);
	
	/* item 5 */
	// function: kill the fastboot-asssistant
    GtkWidget *item5 = gtk_list_box_row_new();
    GtkWidget *icon5 = gtk_image_new_from_icon_name("process-stop"); // process-stop / application-exit
    GtkWidget *label5 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Beenden" : "Exit");
    
    // box for the icon and the label
	GtkWidget *hbox5 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
	gtk_box_append(GTK_BOX(hbox5), icon5);
	gtk_box_append(GTK_BOX(hbox5), label5);
    
    // create the button 
	GtkWidget *button5 = gtk_button_new();
	gtk_button_set_child(GTK_BUTTON(button5), hbox5);
	gtk_widget_set_tooltip_text(button5, "Kill App");
	gtk_widget_set_halign(button5, GTK_ALIGN_START);
	// connect to the get_devices
	g_signal_connect(button5, "clicked", G_CALLBACK(kill_fastboot_assistant), NULL); 
	
	// add button to the item2
	gtk_list_box_row_set_child(GTK_LIST_BOX_ROW(item5), button5);
	// add the item2 to menu
	gtk_list_box_append(GTK_LIST_BOX(menu), item5);
	
	// add the menu to the popover
    gtk_popover_set_child(GTK_POPOVER(popover), menu);
    gtk_menu_button_set_popover(GTK_MENU_BUTTON(menu_button), popover);
    
    // add the menu_button to the headerbar
    gtk_box_append(GTK_BOX(headerbar), menu_button);

    return headerbar;
}
