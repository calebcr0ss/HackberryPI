/**
 * @file text_box_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "text_box_gen.h"
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

static lv_style_t * text_box_style_panel_dark_ref; /* set in create(), read by a binding callback */
static void text_box_lv_textarea_0_style_enabled_cb(lv_observer_t * observer, lv_subject_t * subject);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * text_box_create(lv_obj_t * parent, const char * text, const char * placeholder)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * the_root = NULL;

    #if UI_CHECK_COMPILE_TARGET(UI_TARGET_ALL)
    if (ui_check_target(UI_TARGET_ALL)) {
        lv_obj_t * lv_textarea_0 = lv_textarea_create(parent);
        lv_obj_set_name_static(lv_textarea_0, "text_box_#");
        lv_obj_set_width(lv_textarea_0, 260);
        lv_obj_set_height(lv_textarea_0, 120);
        lv_textarea_set_text(lv_textarea_0, text);
        lv_textarea_set_placeholder_text(lv_textarea_0, placeholder);

        lv_obj_add_style(lv_textarea_0, &style_panel_light, 0);
        lv_obj_add_style(lv_textarea_0, &style_panel_dark, 0);
        text_box_style_panel_dark_ref = &style_panel_dark;
        lv_subject_add_observer_obj(subject_theme_dark, text_box_lv_textarea_0_style_enabled_cb, lv_textarea_0, NULL);
        lv_obj_add_style(lv_textarea_0, &style_text_muted, LV_PART_TEXTAREA_PLACEHOLDER);

        the_root = lv_textarea_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void text_box_lv_textarea_0_style_enabled_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_enabled(obj, text_box_style_panel_dark_ref, 0, lv_subject_get_int(subject_theme_dark) == 1);
}

