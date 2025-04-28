/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *          Apache License, Version 2.0      *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von         *
 *  Custom-ROM und GSIs auf Android-Geräte   *
 *  zu erleichtern - run_first_run_setup     *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2025 Elias Mörz        *
 *-------------------------------------------*
 *
 */
 
#include <glib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include "function_header.h"
#include "program_functions.h"
#include "language_check.h"
#include "icon_update.h"

GtkWidget *window;

// function that start the config of the fastboot-assistant
static void start_config_setup(GtkButton *button, gpointer user_data) 
{
	LOG_INFO("Config depended directories.");
    // create the depended directories
    make_dir();
    LOG_INFO("Directories created.");
    LOG_INFO("Config system.");
	LOG_INFO("Check if the system are native linux or WSL.");
	// check if system are native linux or wsl
	wsl_config();
	LOG_INFO("System checked.");
	LOG_INFO("Set last label active.");	
	// set the last label active
	GtkWidget *last_label = GTK_WIDGET(user_data);
    gtk_widget_set_visible(last_label, TRUE);
}

// function to quit the application
gboolean quit_application(gpointer data)
{
    exit(1);
    return FALSE;  // Return FALSE to ensure the timeout callback is called only once
}

// callback to switch the language in the setup
void toggle_language_setup(GtkWidget *button, gpointer user_data) 
{

    if (strcmp(language, "de") == 0) 
    {
        language = "en";
        write_language_file();
        delete_config_file();
        apply_language();
        const char *message = "Please restart the Fastboot Assistant.";
        show_message(message);
    }
     
    else 
    {
        language = "de";
        check_language_file_light();
        delete_config_file();
        apply_language();
        const char *message = "Bitte starten Sie den Fastboot-Assistant erneut.";
        show_message(message);
    }

    // set a timeout and quit the application
    g_timeout_add(2000, (GSourceFunc)quit_application, NULL); // After 5 seconds
}

/* the setup wizard */
void run_first_run_setup(GtkWidget *widget, gpointer stack) 
{
	LOG_INFO("run_first_run_setup");
	
	apply_theme();
	apply_language();
	
	char *auto_theme = auto_path_theme();
	
	// style provider for the setup
	// with underline
	GtkCssProvider *provider_welcome_1 = gtk_css_provider_new();
        gtk_css_provider_load_from_string(provider_welcome_1,
    	".welcome { text-decoration: underline; font-weight: bold; font-size: 32px;}"
    	);
    	/*
    // without underline
    GtkCssProvider *provider_welcome_1 = gtk_css_provider_new();
        gtk_css_provider_load_from_string(provider_welcome_1,
    	".highlight { font-weight: bold; font-size: 32px;}"
    	);
	*/
	// second css provider
	GtkCssProvider *provider_welcome_2 = gtk_css_provider_new();
        gtk_css_provider_load_from_string(provider_welcome_2,
    	".welcome2 { text-decoration: underline; font-weight: bold; font-size: 24px;}"
    	);
	
	// 3. provider
	GtkCssProvider *provider_welcome_3 = gtk_css_provider_new();
        gtk_css_provider_load_from_string(provider_welcome_3,
    	".welcome3 { font-weight: bold; font-size: 24px;}"
    	);
	
	// char for the next page button
	const char *next_page_char = strcmp(language, "de") == 0 ? "Weiter" : "Next";
		
	/* page 1 */
    GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
	
    // button and label
    GtkWidget *label_welcome_1 = gtk_label_new(" ");
    GtkWidget *logo;
    // add the fastboot-assistant logo  
    const char *main_icon[] = {
    		"./sweet_unix.png",
    		"/usr/share/fastboot-assistant/icons/sweet_unix.png"
	};

	for (int i = 0; i < 2; ++i) 
	{
    	if (g_file_test(main_icon[i], G_FILE_TEST_EXISTS)) 
    	{
       		// add the logo
       		logo = gtk_image_new_from_file(main_icon[i]);
       		break;
    	}
	} 
	gtk_widget_set_size_request(logo, 128, 128);
	//gtk_image_set_pixel_size(GTK_IMAGE(logo), 64);
	
	// labels
	GtkWidget *label_welcome_2 = gtk_label_new(" "); 
	GtkWidget *label_welcome_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Willkommen beim Fastboot-Assistant!" : "Welcome to the Fastboot Assistant!");
	gtk_widget_set_halign(label_welcome_3, GTK_ALIGN_CENTER);
	gtk_widget_add_css_class(label_welcome_3, "welcome");
    GtkWidget *label_welcome_4 = gtk_label_new(" ");
    GtkWidget *label_welcome_5 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Lass uns gemeinsam alles einrichten." : " Let's get everything set up together.");
    gtk_widget_set_halign(label_welcome_5, GTK_ALIGN_CENTER);
    gtk_widget_add_css_class(label_welcome_5, "welcome3");
    GtkWidget *label_welcome_6 = gtk_label_new(" "); 
    GtkWidget *button_welcome_1 = create_icon_nav_button_no_callback("pan-end-symbolic", next_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page1), label_welcome_1);
    gtk_box_append(GTK_BOX(page1), logo);
    gtk_box_append(GTK_BOX(page1), label_welcome_2);
    gtk_box_append(GTK_BOX(page1), label_welcome_3);
    gtk_box_append(GTK_BOX(page1), label_welcome_4);
    gtk_box_append(GTK_BOX(page1), label_welcome_5);
    gtk_box_append(GTK_BOX(page1), label_welcome_6);
    gtk_box_append(GTK_BOX(page1), button_welcome_1);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "welcome")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page1, "welcome");
	}
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "welcome");
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_welcome_1), "stack", stack);
	g_signal_connect(button_welcome_1, "clicked", G_CALLBACK(switch_page), "config_1");
	
	// run css for gtk4
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider_welcome_1),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
    // run css for gtk4
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider_welcome_2),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
    // run css for gtk4
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(provider_welcome_3),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
    
	
	/* page 2 */
    GtkWidget *page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and labels 
    GtkWidget *label_2_1 = gtk_label_new(" ");
    // main label
    GtkWidget *hbox2_1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *icon_info2 = gtk_image_new_from_icon_name("help-about");
    GtkWidget *label_page_info2 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Hier können Sie wichtige Einstellungen für den Fastboot-Assistant festlegen." : "Here you can set important preferences for your Fastboot Assistant.");
    // automatic linebreak
    gtk_label_set_wrap(GTK_LABEL(label_page_info2), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_page_info2), PANGO_WRAP_WORD_CHAR);	// Wrap at word boundary + character
	gtk_widget_add_css_class(label_page_info2, "welcome3");
	gtk_image_set_pixel_size(GTK_IMAGE(icon_info2), 32);
	gtk_box_append(GTK_BOX(hbox2_1), icon_info2);
	gtk_box_append(GTK_BOX(hbox2_1), label_page_info2);
    
    GtkWidget *label_2_2 = gtk_label_new(" ");
    // button
    const char *toggle_language_char = strcmp(language, "de") == 0 ? "Sprache wechseln/Switch Language (Deutsch/Englisch)" : "Switch Language/Sprache wechseln (English/German)";    
    GtkWidget *button_toggle_language = create_icon_nav_button("preferences-desktop-locale", toggle_language_char, G_CALLBACK(toggle_language_setup), stack);
    const char *setup_dir_char = strcmp(language, "de") == 0 ? "Ordner für den Flash-Vorgang auswählen" : "Choose folder for flashing files";
    GtkWidget *button_setup_dir = create_icon_nav_button("folder-new", setup_dir_char, G_CALLBACK(show_folder_chooser), stack);
    const char *toggle_theme_char = strcmp(language, "de") == 0 ? "Thema wechseln (Hell/Dunkel)" : "Toggle theme (Light/Dark)";
    GtkWidget *button_toggle_theme = create_icon_nav_button("applications-system-symbolic", toggle_theme_char, G_CALLBACK(toggle_theme_css), stack);
    GtkWidget *button_welcome_2 = create_icon_nav_button_no_callback("pan-end-symbolic", next_page_char);
	
	// check if theme is auto or css only
	// theme = auto (css + libadwaita)
	if (file_exists_theme(auto_theme))
	{
        // disable the button 
        gtk_widget_set_visible(GTK_WIDGET(button_toggle_theme), FALSE);
    } 
    // theme = css only
    else 
    {
        // enable the button
        gtk_widget_set_visible(GTK_WIDGET(button_toggle_theme), TRUE);
    }
    
    // add the widgets to the box
    gtk_box_append(GTK_BOX(page2), label_2_1);
    gtk_box_append(GTK_BOX(page2), hbox2_1);
    gtk_box_append(GTK_BOX(page2), label_2_2);
    gtk_box_append(GTK_BOX(page2), button_toggle_language);
    gtk_box_append(GTK_BOX(page2), button_setup_dir);
    gtk_box_append(GTK_BOX(page2), button_toggle_theme);
    gtk_box_append(GTK_BOX(page2), button_welcome_2);
    
    gtk_widget_set_halign(hbox2_1, GTK_ALIGN_CENTER);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "config_1")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page2, "config_1");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_welcome_2), "stack", stack);
	g_signal_connect(button_welcome_2, "clicked", G_CALLBACK(switch_page), "config_2");
    
    /* page 3 */
    GtkWidget *page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // 0. label 
    GtkWidget *label_page3_0 = gtk_label_new(" ");
    // 1. label
    GtkWidget *label_page3_1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *icon_info3 = gtk_image_new_from_icon_name("help-about");
    GtkWidget *label_page_info3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Damit der Fastboot-Assistant korrekt funktioniert, müssen einige Konfigurationen vorgenommen werden." : "To work correctly, the Fastboot Assistant needs to perform some initial setup.");
    
    gtk_label_set_wrap(GTK_LABEL(label_page_info3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_page_info3), PANGO_WRAP_WORD_CHAR);	
	gtk_image_set_pixel_size(GTK_IMAGE(icon_info3), 32);
	gtk_widget_add_css_class(label_page_info3, "welcome3");
	gtk_box_append(GTK_BOX(label_page3_1), icon_info3);
	gtk_box_append(GTK_BOX(label_page3_1), label_page_info3);
       
    // 2. label
    GtkWidget *label_page3_2 = gtk_label_new(" ");
    
    // 3. label
    GtkWidget *hbox3_1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *icon_setup1 = gtk_image_new_from_icon_name("software-update-urgent-symbolic");
    GtkWidget *label_folders = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Erstellen aller benötigten Ordner" : "1. Creating all required folders");
    gtk_box_append(GTK_BOX(hbox3_1), icon_setup1);
    gtk_box_append(GTK_BOX(hbox3_1), label_folders);

    // 4. label
    GtkWidget *hbox3_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *icon_setup2 = gtk_image_new_from_icon_name("software-update-urgent-symbolic");
    GtkWidget *label_system_config = gtk_label_new(g_strcmp0(language, "de") == 0 ? "2. Anpassen des Systems an die Umgebung." : "2. Adjusting the system environment");
    gtk_box_append(GTK_BOX(hbox3_2), icon_setup2);
    gtk_box_append(GTK_BOX(hbox3_2), label_system_config);
    
    // 5. label
    GtkWidget *hbox3_3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *icon_setup3 = gtk_image_new_from_icon_name("emblem-default");
    GtkWidget *label_completed = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Konfiguration abgeschlossen." : "Configuration completed.");
    gtk_box_append(GTK_BOX(hbox3_3), icon_setup3);
    gtk_box_append(GTK_BOX(hbox3_3), label_completed);
    
    // set the label unvisible
    gtk_widget_set_visible(hbox3_3, FALSE);
    
    // 6. label
    GtkWidget *label_page3_3 = gtk_label_new(" ");
    
    // start config button
    const char *config_dir_char = strcmp(language, "de") == 0 ? "Konfigurieren" : "Configure";
    GtkWidget *button_config_dir = create_icon_nav_button_no_callback("applications-system-symbolic", config_dir_char);
    
    // next page  
    GtkWidget *button_welcome_3 = create_icon_nav_button_no_callback("pan-end-symbolic", next_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page3), label_page3_0);
    gtk_box_append(GTK_BOX(page3), label_page3_1);
    gtk_box_append(GTK_BOX(page3), label_page3_2);
    gtk_box_append(GTK_BOX(page3), hbox3_1);
    gtk_box_append(GTK_BOX(page3), hbox3_2);
    gtk_box_append(GTK_BOX(page3), hbox3_3);
    gtk_box_append(GTK_BOX(page3), label_page3_3);
    gtk_box_append(GTK_BOX(page3), button_config_dir);
    gtk_box_append(GTK_BOX(page3), button_welcome_3);
    
    // center the label
    gtk_widget_set_halign(label_page3_1, GTK_ALIGN_CENTER);
    // set the label to the same start point
    gtk_widget_set_margin_start(hbox3_1, 15);
	gtk_widget_set_margin_start(hbox3_2, 15);
	gtk_widget_set_margin_start(hbox3_3, 15);

	// connect the button
    g_signal_connect(button_config_dir, "clicked", G_CALLBACK(start_config_setup), hbox3_3);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "config_2")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page3, "config_2");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_welcome_3), "stack", stack);
	g_signal_connect(button_welcome_3, "clicked", G_CALLBACK(switch_page), "use");
    
    /* page 4 */
    GtkWidget *page4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    GtkWidget *label_page4_0 = gtk_label_new(" ");
    
    GtkWidget *logo_page4 = gtk_image_new_from_icon_name("software-update-urgent-symbolic");
    gtk_image_set_pixel_size(GTK_IMAGE(logo_page4), 64);
    //gtk_widget_set_size_request(logo_page4, 64, 64);
    
    // button and label
    // button 1
    GtkWidget *button_page4_1 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Verwendung" : "Use");
    gtk_widget_add_css_class(button_page4_1, "welcome2");
	
	GtkWidget *label_page4_2 = gtk_label_new(" ");
	// label 1
	GtkWidget *label_page4_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "1. Bitte lesen Sie vor der Nutzung die Anleitung und Dokumentation." : "1. Please read the manual and documentation before using the program.");
	gtk_label_set_wrap(GTK_LABEL(label_page4_3), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_page4_3), PANGO_WRAP_WORD_CHAR);
	// label 2
	GtkWidget *label_page4_4 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "2. Kopieren Sie alle zu flashenden Images in den Ordner 'ROM-Install'." : "2. Always copy all images to be flashed into the 'ROM-Install' folder.");
	gtk_label_set_wrap(GTK_LABEL(label_page4_4), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_page4_4), PANGO_WRAP_WORD_CHAR);
	// label 3
	GtkWidget *label_page4_5 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "3. Für Samsung-Geräte verwenden Sie bitte immer 'heimdall'." : "3. If flashing Samsung devices, always use 'heimdall'.");
	gtk_label_set_wrap(GTK_LABEL(label_page4_5), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_page4_5), PANGO_WRAP_WORD_CHAR);
	// label 4
	GtkWidget *label_page4_6 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "4. Überprüfen Sie regelmäßig, ob Updates für den Fastboot-Assistant verfügbar sind." : "4. Check regularly for Fastboot-Assistant updates.");
	gtk_label_set_wrap(GTK_LABEL(label_page4_6), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_page4_6), PANGO_WRAP_WORD_CHAR);
	// button 2
    GtkWidget *button_welcome_4 = create_icon_nav_button_no_callback("pan-end-symbolic", next_page_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page4), label_page4_0);
    gtk_box_append(GTK_BOX(page4), logo_page4);
    gtk_box_append(GTK_BOX(page4), button_page4_1);
    gtk_box_append(GTK_BOX(page4), label_page4_2);
    gtk_box_append(GTK_BOX(page4), label_page4_3);
    gtk_box_append(GTK_BOX(page4), label_page4_4);
    gtk_box_append(GTK_BOX(page4), label_page4_5);
    gtk_box_append(GTK_BOX(page4), label_page4_6);
    gtk_box_append(GTK_BOX(page4), button_welcome_4);
    
    // set the label to the left side
    gtk_widget_set_halign(label_page4_2, GTK_ALIGN_START);
    gtk_widget_set_halign(label_page4_3, GTK_ALIGN_START);
    gtk_widget_set_halign(label_page4_4, GTK_ALIGN_START);
    gtk_widget_set_halign(label_page4_5, GTK_ALIGN_START);
    gtk_widget_set_halign(label_page4_6, GTK_ALIGN_START);
    
    // set the label to the same start point
    gtk_widget_set_margin_start(label_page4_2, 15);
	gtk_widget_set_margin_start(label_page4_3, 15);
	gtk_widget_set_margin_start(label_page4_4, 15);
	gtk_widget_set_margin_start(label_page4_5, 15);
	gtk_widget_set_margin_start(label_page4_6, 15);
       
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "use")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page4, "use");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_welcome_4), "stack", stack);
	g_signal_connect(button_welcome_4, "clicked", G_CALLBACK(switch_page), "end");
       
    /* page 5 */
    GtkWidget *page5 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    
    // button and label
    GtkWidget *label_end_1 = gtk_label_new(" ");
    GtkWidget *logo_end;

	for (int i = 0; i < 2; ++i) 
	{
    	if (g_file_test(main_icon[i], G_FILE_TEST_EXISTS)) 
    	{
       		// add the logo
       		logo_end = gtk_image_new_from_file(main_icon[i]);
       		break;
    	}
	} 
	gtk_widget_set_size_request(logo_end, 128, 128);
	//gtk_image_set_pixel_size(GTK_IMAGE(logo), 64);
	
	// labels  
    GtkWidget *label_end_2 = gtk_label_new(" ");
    GtkWidget *label_end_3 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Viel Spaß mit dem Fastboot-Assistants!" : "Have fun with the Fastboot-Assistants!");
    gtk_widget_set_halign(label_end_3, GTK_ALIGN_CENTER);
	gtk_widget_add_css_class(label_end_3, "welcome");
	GtkWidget *label_end_4 = gtk_label_new(" ");
	GtkWidget *label_end_5 = gtk_label_new(g_strcmp0(language, "de") == 0 ? "Die Einrichtung ist abgeschlossen. Der Fastboot-Assistant ist jetzt bereit." : "The setup is complete. The Fastboot-Assistant is now ready.");
	gtk_widget_set_halign(label_end_4, GTK_ALIGN_CENTER);
	gtk_label_set_wrap(GTK_LABEL(label_end_4), TRUE);
	gtk_label_set_wrap_mode(GTK_LABEL(label_end_4), PANGO_WRAP_WORD_CHAR);
	gtk_widget_add_css_class(label_end_3, "welcome3");
    GtkWidget *label_end_6 = gtk_label_new(" ");
    const char *end_setup_char = strcmp(language, "de") == 0 ? "Fertig" : "Finished";
    GtkWidget *button_welcome_5 = create_icon_nav_button_no_callback("emblem-default-symbolic", end_setup_char);
    
    // add everything to the page
    gtk_box_append(GTK_BOX(page5), label_end_1);
    gtk_box_append(GTK_BOX(page5), logo_end);
    gtk_box_append(GTK_BOX(page5), label_end_2);
    gtk_box_append(GTK_BOX(page5), label_end_3);
    gtk_box_append(GTK_BOX(page5), label_end_4);
    gtk_box_append(GTK_BOX(page5), label_end_5);
    gtk_box_append(GTK_BOX(page5), label_end_6);
    gtk_box_append(GTK_BOX(page5), button_welcome_5);
    
    // add page to the stack
	if (!gtk_stack_get_child_by_name(GTK_STACK(stack), "end")) 
    {
        gtk_stack_add_named(GTK_STACK(stack), page5, "end");
	}
	
	// set stack reference for the button function
	g_object_set_data(G_OBJECT(button_welcome_5), "stack", stack);
	g_signal_connect(button_welcome_5, "clicked", G_CALLBACK(show_home_page), stack);
	
	LOG_INFO("end run_first_setup");
}	
    
