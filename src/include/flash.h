/**
* flash.h
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
* Usage:
* #include "flash.h"
*/

#ifndef FLASH_H
#define FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "atlbase.h"

void flash_recovery(GtkWidget *widget, gpointer stack);
void flash_boot(GtkWidget *widget, gpointer stack);
void flash_vendor(GtkWidget *widget, gpointer stack);
void flash_payload(GtkWidget *widget, gpointer stack);
void flash_system(GtkWidget *widget, gpointer stack);
void flash_vbmeta_dtbo(GtkWidget *widget, gpointer stack);
void flash_preloader_super(GtkWidget *widget, gpointer stack);
void flash_data(GtkWidget *widget, gpointer stack);
void flash_others(GtkWidget *widget, gpointer stack);
void flash_images(GtkWidget *widget, gpointer stack);
void flash_list_images(GtkWidget *widget, gpointer stack);

#ifdef __cplusplus
}
#endif

#endif // FLASH_H
