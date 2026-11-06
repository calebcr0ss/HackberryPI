/**
 * @file ui.h
 */

#ifndef LVGL_PRO_UI_H
#define LVGL_PRO_UI_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      DEFINES
 *********************/

/* Target(s) select at startup: one or more UI_TARGET_* values OR-ed together. */
#ifndef UI_COMPILE_TARGET
#define UI_COMPILE_TARGET UI_TARGET_ALL
#endif

/*********************
 *      INCLUDES
 *********************/

#include "ui_gen.h"

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Initialize the component library
 */
void ui_init(const char * asset_path);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_PRO_UI_H*/