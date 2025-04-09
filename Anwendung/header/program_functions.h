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
 *       Headerfile - program_functions		 *
 *											 *
 *-------------------------------------------*
 */

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>

#ifndef PROGRAM_FUNCTIONS_H
#define PROGRAM_FUNCTIONS_H

/* 
* some makros 
*/
/*
* makros for the GTK window 
*/
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

/* 
* makros for the logging *
*/
// the makro for infos
#define LOG_INFO(msg, ...) { \
    time_t now = time(NULL); \
    struct tm *tm_info = localtime(&now); \
    char time_buf[20]; \
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info); \
    g_print("[%s] [INFO]: " msg "\n", time_buf, ##__VA_ARGS__); \
}

// the makro for errors
#define LOG_ERROR(msg, ...) { \
    time_t now = time(NULL); \
    struct tm *tm_info = localtime(&now); \
    char time_buf[20]; \
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info); \
    g_print("[%s] [ERROR]: " msg "\n", time_buf, ##__VA_ARGS__); \
}
/*
* log output: 
* [yy-mm-dd HH:MM:SS] [INFO]: This are a message for the program. 
* [yy-mm-dd HH:MM:SS] [ERROR]: This shows a error from the program.
*
* Usage:
* LOG_INFO("This are a message for the program.");
* LOG_ERROR("This shows a error from the program.");
*/

/* 
* makro for autofree the memory *
*/
// declare the wrapper for autofree the memory
void free_wrapper(void *p);

// the makro that use the wrapper
#define auto_free __attribute__((cleanup(free_wrapper)))
/*
* this only works with GCC
*
* Usage:
* auto_free char *output = execute_command("ls /");
* char *output = execute_command("ls -l");
* g_print("%s", output);
*/


/*
* makro for the a/b device info
*/
#define NOT_AB_DEVICE 0
#define AB_DEVICE 1
#define AB_DEVICE_ERROR -1

// function for a/b device info
int ab_partition_info(void);
/*
* Usage:
* int status = ab_partition_info();
* if (status == AB_DEVICE) 
* {
*     g_print("a/b-device");
* } 
* else if (status == NOT_AB_DEVICE) 
* {
*     g_print("only-a-device");
* } 
* else if (status == AB_DEVICE_ERROR) 
* {
*     g_print("Error");
* }
*/

/* 
* global variables that are used in each file *
*/

// for the css-provider
extern GtkCssProvider *provider;

// global use of the theme 
extern const char *current_theme;

// and the language
extern const char *language;

// and the auto theme function
extern const char *auto_theme;

// for GTK main loop
extern GMainLoop *main_loop;

// for check root access
extern GtkWidget *root_status_label;

// for detecting the android bootctl
extern GtkWidget *bootctl_status_label;

// for the main window of the program
extern GtkWindow *main_window;

/* 
* function from the header *
*/
/* 
* functions for single windows UI
*/
// create button
GtkWidget *create_nav_button(const char *label, GCallback callback, gpointer data);
// show home page
void show_home_page(GtkWidget *widget, gpointer stack);

// button connection for UI
void next_page(GtkButton *button, gpointer data);
// void button_finish(GtkButton *button, gpointer data);
void switch_page(GtkWidget *widget, gpointer user_data);

/* 
* destroy window/dialog/loops
*/
// end  GTK main loop
void on_window_destroy(GtkWidget *widget, gpointer data);

// close window
void close_window(GtkButton *button, GtkWidget *window);

// close dialog
void close_dialog(GtkButton *button, GtkWidget *dialog);

// close window and mainloop
void close_window_mainloop(GtkWidget *widget, gpointer data);

/* 
* execute command
*/
char *execute_command();

/* 
* function that write the log to a file
*/
void write_log();

// function to create dirs, use g_mkdir
void create_directory(const char *path); 

// functions for standard path of the program
void save_path_to_file(const char *path, const char *file_path);
char *load_path_from_file(const char *file_path);
void show_folder_chooser(GtkWidget *widget, gpointer data);

// config function for themeing
gboolean file_exists_theme(const char *filename);
char *config_path_theme();
char *auto_path_theme();
char *dark_path_theme();

/* 
* messages, entrys and others 
*/

// normal messsage
void show_message();
// with special title
void show_message_with_title();
// open the terminal by desktop
void open_terminal_by_desktop();
// show error message
void show_error_message();
// function that get the input number → for show_number_input_dialog
typedef void (*NumberCallback)(int number);
// function that show the dialog with entry
void show_dialog_with_entry(const char *title, const char *placeholder, NumberCallback callback);
/*
* Usage:
* GMainLoop *main_loop = NULL;
* // callback for the show_dialog_with_entry
* void get_number(int number) 
* {
*     g_print("Number from the main program: %d\n", number);
*     g_main_loop_quit(main_loop);
* }
*
* int main(int argc, char *argv[]) 
* {
*     gtk_init();
*     main_loop = g_main_loop_new(NULL, FALSE);
*
*     show_number_input_dialog("Input a number", "e.g. 42 :)", get_number);
*
*     g_main_loop_run(main_loop);
*     if (main_loop != NULL) 
*     {
*         g_main_loop_unref(main_loop);
*         main_loop = NULL;
*     }
*     return 0;
* }
*/

/*
* function from the header *
*/
// check and get the slot
int get_slot_of_device();
void check_active_slot();
// this get the active slot via adb
char *get_inactive_slot(); 

// get devices
void get_info();
int is_android_device_connected();
void connected_devices();
void get_android_info();

// check root access
void check_root_access();

// detect the android bootctl
void get_bootctl();

// show file chooser
void show_file_chooser(GtkWidget *widget, gpointer data);

// get home
gchar* get_home(const gchar *path);
const char* get_home_directory_flash();

// open url in browser
void open_url();

/* 
* for work with dirs or WSL
*/
// there are new function, that replace some of these functions
void get_config_dir(char *config_folder, size_t size); 
void get_config_file_path(char *config_file, size_t size); 
void set_main_dir(); // this → replaced
void get_wsl_directory(char* wsl_dir, size_t size); // this → replaced
void set_main_dir_with_wsl(char *path, size_t size, const char *filename); // this → replaced
void convert_wsl_path(char *windows_path, size_t size, const char *wsl_path);
int directory_exists(const char *path);
void delete_files_in_dir(const char *path);
void delete_config_files(const char *path);
void delete_directory(const char *path);
void create_directory_if_not_exists(const char *path);

// delete config file
void delete_config_file();

// flash functions
void flash_image(GtkWidget *widget, GtkWindow *parent_window, const char *partition1, const char *partition2, const char *image_name, const char *optional_flags);
void flash_heimdall(GtkWidget *widget, GtkWindow *parent_window, const char *partition, const char *image_name);

// adb/fastboot command
char* adb_command();
char* fastboot_command();

/* 
* everything for the themeing
*/

// creating a css provider
GtkCssProvider* create_css_provider(void);
// unload the provider
void unload_css_provider(GtkCssProvider *provider);
// config functions for the provider
void write_dark_file();
void check_dark_file();
void check_dark_file_light();
// config for auto theme
void write_auto_theme_file();
void check_auto_theme();
void set_mode_by_libadwaita();
// load the provider
void add_css_provider(GtkWidget *widget, GtkCssProvider *provider);
void load_css();
void load_css_adw();
// apply to the provider
void apply_theme_css_adw();
void apply_theme_css_only();
// apply the theme → css_only / css_adw
void apply_theme();
// functions to switch themes
void toggle_theme();
void toggle_theme_css(GtkWidget *button, gpointer user_data);

/* 
* functions with spinner
*/

void command_with_spinner(const gchar *command);

/* 
* function with pkexec
*/
void install_with_pkexec(const gchar *command);

/* 
* for setup
*/

void config_start();
void config_dir_setup(const char *pfad); 

/* 
* for the updater
*/
int download_file(const char *url, const char *outfilename);
int verify_package_type(const char *filepath, const char *expected_extension);

#endif
