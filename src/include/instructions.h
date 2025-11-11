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

void instruction_adb();
void instruction_flash();
void instruction_prepare_flash();
void instruction_info();

// function for instruction_flash
void instruction_recovery();
void instruction_root();
void instruction_vendor();
void instruction_gsi();
void instruction_custom_rom();
void instruction_others();

//function for instruction_preflash-function
void instruction_backup();
void instruction_preflash();

#ifdef __cplusplus
}
#endif

#endif // INSTRUCTIONS_H
