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
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *											 *
 *              flashvbmeta					 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <gtk/gtk.h>
#include <stdlib.h>

// Function to flash vbmeta.img
void flashvbmetafunction(const char *option) 
{
    GtkWidget *dialog;
    const char *title, *message;

    if (strcmp(option, "only_a_device") == 0) 
    {
        title = "flash vbmeta.img only-a-device";
        message = "Starte flash!\n";
        system("fastboot devices");
        system("fastboot flash --disable-verity --disable-verification vbmeta ~/Downloads/ROM-Install/vbmeta.img");
        message = "Fertig!\n";
    } 
    
    else if (strcmp(option, "a_b_device") == 0) 
    {
        title = "flash boot.img a/b-device";
        message = "Starte flash!\n";
        system("fastboot devices");
        system("fastboot flash --disable-verity --disable-verification vbmeta_a ~/Downloads/ROM-Install/vbmeta.img");
        system("fastboot flash --disable-verity --disable-verification vbmeta_b ~/Downloads/ROM-Install/vbmeta.img");
        message = "Fertig!\n";
    } 
    
    else 
    {
        title = "Unbekannte Option";
        message = "Sie wissen auch nicht was sie wollen, oder?";
    }

    dialog = gtk_message_dialog_new(NULL,
                                     GTK_DIALOG_MODAL,
                                     GTK_MESSAGE_INFO,
                                     GTK_BUTTONS_OK,
                                     "%s\n\n%s", title, message);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// Callback function when the button is clicked
void buttonfvb_clicked(GtkWidget *widget, gpointer data) 
{
    const char *option = (const char *)data;
    flashvbmetafunction(option);
}

void flashvbmeta(int argc, char *argv[]) 
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Flash vbmeta.img:");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create buttons
    GtkWidget *button_only_a_vbmeta = gtk_button_new_with_label("only-a-device");
    g_signal_connect(button_only_a_vbmeta, "clicked", G_CALLBACK(buttonfvb_clicked), "only-a-device");

    GtkWidget *button_a_b_vbmeta = gtk_button_new_with_label("a/b-device");
    g_signal_connect(button_a_b_vbmeta, "clicked", G_CALLBACK(buttonfvb_clicked), "a_b_device");

    // Pack buttons into the box
    gtk_box_pack_start(GTK_BOX(vbox), button_only_a_vbmeta, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_a_b_vbmeta, TRUE, TRUE, 0);
    
    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
