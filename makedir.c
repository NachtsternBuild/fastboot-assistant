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
 *              makedir						 *
 *											 *
 *-------------------------------------------*
 */
 
 /* headers that used in the main programm */
#include <stdio.h>
#include <stdlib.h>

// make dir function
void makedir()
{
	printf("Verzeichnis wird erstellt...\n");
	system("mkdir ~/Downloads/ROM-Install");
}
