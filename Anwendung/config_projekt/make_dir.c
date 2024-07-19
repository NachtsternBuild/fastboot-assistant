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
 *              make_dir					 *
 *											 *
 *-------------------------------------------*
 */
 
 /* headers that used in the main programm */
#include <stdio.h>
#include <stdlib.h>

// make dir function
void make_dir()
{
	printf("Verzeichnise wird erstellt.\n");
	system("mkdir ~/Downloads/ROM-Install");
	system("mkdir ~/Downloads/ROM-Install/Backup");
	system("mkdir ~/Downloads/ROM-Install/Images");
}
