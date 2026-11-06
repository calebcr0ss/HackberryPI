/**
 * @file monoicon_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "monoicon_gen.h"
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

static lv_style_t * monoicon_style_monoicon_dark_ref; /* set in create(), read by a binding callback */
static void monoicon_image_0_style_enabled_cb(lv_observer_t * observer, lv_subject_t * subject);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * monoicon_create(lv_obj_t * parent, const void * src)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_monoicon_light;
    static lv_style_t style_monoicon_dark;

    static bool style_inited = false;

    if (!style_inited) {
        /*Init all styles*/
        lv_style_init(&style_monoicon_light);
        lv_style_init(&style_monoicon_dark);

        lv_style_set_image_recolor(&style_monoicon_light, COLOR_LIGHT_TEXT);
        lv_style_set_image_recolor_opa(&style_monoicon_light, (255 * 100 / 100));
        lv_style_set_image_recolor(&style_monoicon_dark, COLOR_DARK_TEXT);
        lv_style_set_image_recolor_opa(&style_monoicon_dark, (255 * 100 / 100));

        style_inited = true;
    }


    lv_obj_t * the_root = NULL;

    #if UI_CHECK_COMPILE_TARGET(UI_TARGET_ALL)
    if (ui_check_target(UI_TARGET_ALL)) {
        lv_obj_t * image_0 = image_create(parent, src);
        lv_obj_set_name_static(image_0, "monoicon_#");

        lv_obj_add_style(image_0, &style_monoicon_light, 0);
        lv_obj_add_style(image_0, &style_monoicon_dark, 0);
        monoicon_style_monoicon_dark_ref = &style_monoicon_dark;
        lv_subject_add_observer_obj(subject_theme_dark, monoicon_image_0_style_enabled_cb, image_0, NULL);

        the_root = image_0;
    }
    #endif

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void monoicon_image_0_style_enabled_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_enabled(obj, monoicon_style_monoicon_dark_ref, 0, lv_subject_get_int(subject_theme_dark) == 1);
}

