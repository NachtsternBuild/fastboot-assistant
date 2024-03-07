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
 *              changedir					 *
 *											 *
 *-------------------------------------------*
 */
 
/* headers that used in the main programm */
#include <stdio.h>
#include <stdlib.h>

void changedir()
{
	printf("Wechseln ins Verzeichnis 'ROM-Install'...\n");
	system("cd ~/Downloads/ROM-Install");
}
