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
 *              flashvendor					 *
 *											 *
 *-------------------------------------------*
 */

/* headers that used in the main programm */
#include <gtk/gtk.h>
#include <stdlib.h>

// Function to flash vendor.img + vendor_boot.img
void flashvendorfunction(const char *option) 
{
    GtkWidget *dialog;
    const char *title, *message;

    if (strcmp(option, "only_a_device") == 0) 
    {
        title = "flash boot.img only-a-device";
        message = "Starte flash!\n";
        system("fastboot devices");
        system("fastboot flash vendor ~/Downloads/ROM-Install/vendor.img");
        message = "Fertig!\n";
    } 
    
    else if (strcmp(option, "a_b_device") == 0) 
    {
        title = "flash boot.img a/b-device";
        message = "Starte flash!\n";
        system("fastboot devices");
        system("fastboot flash vendor_a ~/Downloads/ROM-Install/vendor.img");
        system("fastboot flash vendor_b ~/Downloads/ROM-Install/vendor.img");
        message = "Fertig!\n";
    } 
    
    else if (strcmp(option, "vendor_boot") == 0) 
    {
        title = "flash boot.img a/b-device";
        message = "Starte flash!\n";
        system("fastboot devices");
        system("fastboot flash vendor_boot ~/Downloads/ROM-Install/vendor_boot.img");
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
void buttonfv_clicked(GtkWidget *widget, gpointer data) 
{
    const char *option = (const char *)data;
    flashvendorfunction(option);
}

void flashvendor(int argc, char *argv[]) 
{
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Flash Boot-Image:");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create buttons
    GtkWidget *button_only-a_ven = gtk_button_new_with_label("only-a-device");
    g_signal_connect(button_only-a_ven, "clicked", G_CALLBACK(buttonfv_clicked), "only-a-device");

    GtkWidget *button_a_b_ven = gtk_button_new_with_label("a/b-device");
    g_signal_connect(button_a_b_ven, "clicked", G_CALLBACK(buttonfv_clicked), "a_b_device");
    
    GtkWidget *button_vendor_boot = gtk_button_new_with_label("VENDOR_BOOT-device");
    g_signal_connect(button_vendor_boot, "clicked", G_CALLBACK(buttonfv_clicked), "vendor_boot");

    // Pack buttons into the box
    gtk_box_pack_start(GTK_BOX(vbox), button_only-a_ven, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_a_b_ven, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button_vendor_boot, TRUE, TRUE, 0);
    
    // Show all the widgets
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
}
