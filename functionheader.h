/*
 *-------------------------------------------*
 *            Projekt 122 - Header 	         *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern  - functionheader		 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "flashheader.h"
#include "flashfunctionheader.h"

#ifndef FUNCTIONHEADER_H
#define FUNCTIONHEADER_H

void adbcheck();
void makedir();
void changedir();
void bootrecover();
void bootfastboot();
void rebootfastboot();
void lockunlockbootloader();
void erasedata();
void renameGUI();
void flashGUI();
void flashrecovery();
void flashboot();
void flashvendor();
void flashsystem();
void flashpayload();
void flashvbmeta();
void info();
void about(); 

#endif
