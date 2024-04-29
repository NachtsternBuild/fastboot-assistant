/*
 *-------------------------------------------*
 *                Projekt 122 - GUI          *
 *-------------------------------------------*
 *			funkelnde Datenkristalle		 *
 *-------------------------------------------*
 *  	Apache License, Version 2.0		     *
 *-------------------------------------------*
 *                                           *
 *  Programm um das installieren von 		 *
 *	Custom-ROM und GSIs auf Android-Geräte 	 *
 *	zu erleichtern - updatefunction			 *
 *                                           *
 *-------------------------------------------*
 *      (C) Copyright 2023 Elias Mörz 		 *
 *-------------------------------------------*
 *
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "program_functions.h"
 
 void update_function()
 {
 	system("mkdir ~/Downloads/UpdateProjekt122");
 	system("cp update.sh ~/Downloads/UpdateProjekt122/");
 	open_terminal_by_desktop();
 	system("bash ~/Downloads/UpdateProjekt122/update.sh");
 }
