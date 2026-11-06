/**
 * @file screen_components_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "screen_components_gen.h"
#include "../ui.h"

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

static lv_style_t * screen_components_style_screen_dark_ref; /* set in create(), read by a binding callback */
static void screen_components_lv_obj_0_style_enabled_cb(lv_observer_t * observer, lv_subject_t * subject);
static void screen_components_lv_label_0_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void screen_components_lv_label_1_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void screen_components_keyboard_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject);
static void screen_components_set_subject_cb(lv_event_t * e);
static void screen_components_set_subject_cb_2(lv_event_t * e);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * screen_components_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static bool screen_created = false;
    if (screen_created) {
        LV_LOG_WARN("`screen_components` is already initialized as a permanent screen. Returning with no change.");
        return screen_components;
    }


    lv_obj_t * the_root = NULL;

    #if UI_CHECK_COMPILE_TARGET(UI_TARGET_ALL)
    if (ui_check_target(UI_TARGET_ALL)) {
        lv_obj_t * lv_obj_0 = screen_components;
        lv_obj_set_name_static(lv_obj_0, "screen_components_#");

        lv_obj_add_style(lv_obj_0, &style_screen_light, 0);
        lv_obj_add_style(lv_obj_0, &style_screen_dark, 0);
        screen_components_style_screen_dark_ref = &style_screen_dark;
        lv_subject_add_observer_obj(subject_theme_dark, screen_components_lv_obj_0_style_enabled_cb, lv_obj_0, NULL);
        lv_obj_add_style(lv_obj_0, &style_scrollbar, LV_PART_SCROLLBAR);
        lv_obj_t * content = column_create(lv_obj_0, SPACE_LG, SPACE_MD, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_set_name(content, "content");
        lv_obj_set_width(content, lv_pct(100));
        lv_obj_set_height(content, LV_SIZE_CONTENT);
        lv_obj_t * row_0 = row_create(content, 0, SPACE_MD, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_set_width(row_0, lv_pct(100));
        h5_create(row_0, "Heading 5", "dark_theme");

        container_create(row_0, 8, 0, LV_FLEX_FLOW_COLUMN, 1);

        switch_create(row_0, subject_theme_dark, COLOR_ACCENT);

        lv_obj_t * panel_0 = panel_create(content, SPACE_LG, SPACE_LG, LV_FLEX_FLOW_COLUMN, 0);
        lv_obj_set_width(panel_0, lv_pct(100));
        h1_create(panel_0, "Heading 1");

        h2_create(panel_0, "Heading 2");

        h3_create(panel_0, "Heading 3");

        h4_create(panel_0, "Heading 4", "");

        h5_create(panel_0, "Heading 5", "");

        lv_obj_t * text_0 = text_create(panel_0, "Body text. Give it a width and it wraps across the panel.");
        lv_obj_set_width(text_0, lv_pct(100));

        lv_obj_t * panel_1 = panel_create(content, SPACE_LG, SPACE_LG, LV_FLEX_FLOW_COLUMN, 0);
        lv_obj_set_width(panel_1, lv_pct(100));
        h4_create(panel_1, "Heading 4", "buttons");

        lv_obj_t * row_1 = row_create(panel_1, 0, SPACE_SM, 0, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        button_create(row_1, "Primary", NULL, COLOR_ACCENT, COLOR_ACCENT_TEXT, RADIUS_DEFAULT);

        button_create(row_1, "Add", icon_plus, COLOR_ACCENT, COLOR_ACCENT_TEXT, RADIUS_DEFAULT);

        button_create(row_1, "Delete", icon_trash, COLOR_DANGER, COLOR_ACCENT_TEXT, RADIUS_DEFAULT);

        lv_obj_t * panel_2 = panel_create(content, SPACE_LG, SPACE_LG, LV_FLEX_FLOW_COLUMN, 0);
        lv_obj_set_width(panel_2, lv_pct(100));
        h4_create(panel_2, "Heading 4", "controls");

        lv_obj_t * slider_0 = slider_create(panel_2, subject_brightness, 0, 100, COLOR_ACCENT);
        lv_obj_set_width(slider_0, lv_pct(100));

        lv_obj_t * bar_0 = bar_create(panel_2, subject_brightness, 0, 100, COLOR_ACCENT);
        lv_obj_set_width(bar_0, lv_pct(100));

        lv_obj_t * arc_0 = arc_create(panel_2, subject_brightness, 0, 100, COLOR_ACCENT);
        lv_obj_t * lv_label_0 = lv_label_create(arc_0);
        lv_obj_set_align(lv_label_0, LV_ALIGN_CENTER);
        lv_subject_add_observer_obj(subject_brightness, screen_components_lv_label_0_text_binding_cb, lv_label_0, NULL);
        lv_obj_set_style_text_color(lv_label_0, COLOR_ACCENT, 0);

        lv_obj_t * panel_3 = panel_create(content, SPACE_LG, SPACE_LG, LV_FLEX_FLOW_COLUMN, 0);
        lv_obj_set_width(panel_3, lv_pct(100));
        h4_create(panel_3, "Heading 4", "text_inputs");

        lv_obj_t * text_innput_user_name = text_input_create(panel_3, "", "Single line", false);
        lv_obj_set_name(text_innput_user_name, "text_innput_user_name");
        lv_obj_set_width(text_innput_user_name, lv_pct(100));
        lv_obj_add_subject_set_int_event(text_innput_user_name, subject_show_keyboard, LV_EVENT_FOCUSED, 1);
        lv_obj_add_subject_set_int_event(text_innput_user_name, subject_show_keyboard, LV_EVENT_DEFOCUSED, 0);

        lv_obj_t * text_input_0 = text_input_create(panel_3, "", "Password", true);
        lv_obj_set_width(text_input_0, lv_pct(100));

        lv_obj_t * text_box_0 = text_box_create(panel_3, "", "Multi-line text box");
        lv_obj_set_width(text_box_0, lv_pct(100));

        lv_obj_t * panel_4 = panel_create(content, SPACE_LG, SPACE_LG, LV_FLEX_FLOW_COLUMN, 0);
        lv_obj_set_width(panel_4, lv_pct(100));
        h4_create(panel_4, "Heading 4", "selection");

        lv_obj_t * dropdown_0 = dropdown_create(panel_4, "Low\nMedium\nHigh", 0, subject_brightness);
        lv_obj_set_width(dropdown_0, lv_pct(100));

        checkbox_create(panel_4, "Enable feature", subject_brightness, COLOR_ACCENT);

        checkbox_create(panel_4, "Subscribe", subject_brightness, COLOR_ACCENT);

        switch_create(panel_4, subject_theme_dark, COLOR_ACCENT);

        lv_obj_t * list_0 = list_create(content, 0, 0);
        lv_obj_set_width(list_0, lv_pct(100));
        list_section_create(list_0, "List");

        list_item_create(list_0, "Simple item", "", NULL);

        list_item_create(list_0, "Simple item with icon", "", icon_bell);

        lv_obj_t * list_item_2 = list_item_create(list_0, "Turn me on!", "", icon_edit);
        lv_obj_t * list_item_2_trailing = list_item_get_trailing(list_item_2);
        if (list_item_2_trailing) {
        switch_create(list_item_2_trailing, subject_theme_dark, COLOR_ACCENT);
        } else {
        LV_LOG_WARN("`trailing` slot of `list_item_2` doesn't exist");
        }

        lv_obj_t * list_item_3 = list_item_create(list_0, "Brightness", "Backlight", icon_sun);
        lv_obj_t * list_item_3_trailing = list_item_get_trailing(list_item_3);
        if (list_item_3_trailing) {
        lv_obj_t * lv_label_1 = lv_label_create(list_item_3_trailing);
        lv_subject_add_observer_obj(subject_brightness, screen_components_lv_label_1_text_binding_cb, lv_label_1, NULL);
        lv_obj_add_style(lv_label_1, &style_text_accent, 0);
        } else {
        LV_LOG_WARN("`trailing` slot of `list_item_3` doesn't exist");
        }

        list_separator_create(list_0);

        list_item_create(list_0, "About", "Version 1.0", icon_info);

        lv_obj_t * keyboard = keyboard_create(lv_obj_0, text_innput_user_name, LV_KEYBOARD_MODE_TEXT_LOWER);
        lv_obj_set_name(keyboard, "keyboard");
        lv_obj_set_floating(keyboard, true);
        lv_obj_set_align(keyboard, LV_ALIGN_BOTTOM_MID);
        lv_subject_add_observer_obj(subject_show_keyboard, screen_components_keyboard_hidden_binding_cb, keyboard, NULL);
        lv_obj_add_event_cb(keyboard, screen_components_set_subject_cb, LV_EVENT_CANCEL, NULL);
        lv_obj_add_event_cb(keyboard, screen_components_set_subject_cb_2, LV_EVENT_READY, NULL);

        the_root = lv_obj_0;
    }
    #endif

    if (the_root) screen_created = true;

    LV_TRACE_OBJ_CREATE("finished");

    return the_root;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void screen_components_lv_obj_0_style_enabled_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_style_enabled(obj, screen_components_style_screen_dark_ref, 0, lv_subject_get_int(subject_theme_dark) == 1);
}

static void screen_components_lv_label_0_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    char eval_buf_1[LV_XML_EVAL_STRING_BUF_SIZE];
    lv_snprintf(eval_buf_1, sizeof(eval_buf_1), "%d%s", (int)(lv_subject_get_int(subject_brightness)), "%");
    lv_label_set_text(obj, eval_buf_1);
}

static void screen_components_lv_label_1_text_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    char eval_buf_1[LV_XML_EVAL_STRING_BUF_SIZE];
    lv_snprintf(eval_buf_1, sizeof(eval_buf_1), "%d%s", (int)(lv_subject_get_int(subject_brightness)), "%");
    lv_label_set_text(obj, eval_buf_1);
}

static void screen_components_keyboard_hidden_binding_cb(lv_observer_t * observer, lv_subject_t * subject)
{
    LV_UNUSED(subject);
    lv_obj_t * obj = lv_observer_get_target_obj(observer);
    lv_obj_set_hidden(obj, !lv_subject_get_int(subject_show_keyboard));
}

static void screen_components_set_subject_cb(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_subject_set_int(subject_show_keyboard, 0);
}

static void screen_components_set_subject_cb_2(lv_event_t * e)
{
    LV_UNUSED(e);
    lv_subject_set_int(subject_show_keyboard, 0);
}

