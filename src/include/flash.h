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

void flash_recovery();
void flash_boot();
void flash_vendor();
void flash_payload();
void flash_system();
void flash_vbmeta_dtbo();
void flash_preloader_super();
void flash_data();
void flash_others();
void flash_images();
void flash_list_images();

#ifdef __cplusplus
}
#endif

#endif // FLASH_H
