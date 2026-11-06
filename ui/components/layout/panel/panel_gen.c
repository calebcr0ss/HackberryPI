/**
 * @file panel_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "panel_gen.h"
#include "../../../ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

static lv_style_t * panel_style_panel_dark_ref; /* set in create(), read by a binding callback */
static void panel_container_0_style_enabled_cb(lv_observer_t * observer, lv_subject_t * subject);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * panel_create(lv_obj_t * parent, int32_t pad, int32_t gap, lv_flex_flow_t flow, int32_t grow)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if UI_CHECK_COMPILE_TARGET(UI_TARGET_ALL)
    if (ui_check_target(UI_TARGET_ALL)) {
        lv_obj_t * container_0 = container_create(parent, pad, gap, flow, grow);
        lv_obj_set_name_static(container_0, "panel_#");

        lv_obj_add_style(container_0, &style_panel_light, 0);
        lv_obj_add_style(container_0, &style_panel_dark, 0);
        panel_style_panel_dark_ref = &style_panel_dark;
        lv_subject_add_observer_obj(subject_theme_dark, panel_container_0_style_enabled_cb, container_0, NULL);

        the_root = container_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void panel_container_0_style_enabled_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_enabled(obj, panel_style_panel_dark_ref, 0, lv_subject_get_int(subject_theme_dark) == 1);
}

