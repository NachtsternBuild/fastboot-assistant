/**
* instructions.h
*
* (C) Copyright 2025 @NachtsternBuild
*
* License: GNU GENERAL PUBLIC LICENSE Version 3
*
* Usage:
* #include "instructions.h"
*/

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

void instruction_adb(GtkWidget *widget, gpointer stack);
void instruction_flash(GtkWidget *widget, gpointer stack);
void instruction_prepare_flash(GtkWidget *widget, gpointer stack);
void instruction_info(GtkWidget *widget, gpointer stack);

// function for instruction_flash
void instruction_recovery(GtkWidget *widget, gpointer stack);
void instruction_root(GtkWidget *widget, gpointer stack);
void instruction_vendor(GtkWidget *widget, gpointer stack);
void instruction_gsi(GtkWidget *widget, gpointer stack);
void instruction_custom_rom(GtkWidget *widget, gpointer stack);
void instruction_others(GtkWidget *widget, gpointer stack);

//function for instruction_preflash-function
void instruction_backup(GtkWidget *widget, gpointer stack);
void instruction_preflash(GtkWidget *widget, gpointer stack);

#ifdef __cplusplus
}
#endif

#endif // INSTRUCTIONS_H
