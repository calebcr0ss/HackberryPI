
#include "backends/backend.h"
#include <stdlib.h>
#include <time.h>

#define NS_TO_MS (1000 * 1000)

static void app_ui_start(void);

#ifdef UI_PROJECT_EXISTS

#define CONCAT(a, b)      a##b
#define EXPAND(a, b)      CONCAT(a, b)

#define UI_INIT_FN           EXPAND(UI_PROJECT_NAME, _init)
#define UI_SCREEN_CREATE_FN  EXPAND(UI_DEFAULT_SCREEN, _create)

/* Forward-declare the generated init function */
extern void UI_INIT_FN(const char * path);

static void app_ui_start(void)
{
    UI_INIT_FN(UI_DIR_PATH);

#ifdef UI_DEFAULT_SCREEN
    /* Load the auto-discovered screen */
    extern lv_obj_t * UI_SCREEN_CREATE_FN(void);
    lv_obj_t * screen = UI_SCREEN_CREATE_FN();
    lv_screen_load(screen);
#else
    /* Fallback: render a minimal default UI */
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_label_set_text_static(label, "No UI screen found");
#endif
}

#else

static uint32_t press_count;

static void on_button_click(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * label_count = lv_event_get_user_data(e);
    if(code == LV_EVENT_CLICKED) {
        char buf[16];
        lv_snprintf(buf, sizeof(buf), "Pressed %d times", ++press_count);
        lv_label_set_text(label_count, buf);
    }
}

static void app_ui_start(void)
{
    lv_obj_t * container =  lv_obj_create(lv_screen_active());
    lv_obj_set_style_bg_opa(container, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(container, 0, LV_PART_MAIN);
    lv_obj_set_width(container, LV_PCT(25));
    lv_obj_center(container);

    lv_obj_t * btn = lv_button_create(container);
    lv_obj_align(btn, LV_ALIGN_TOP_MID, 0, 0);

    lv_obj_t * label = lv_label_create(btn);
    lv_label_set_text_static(label, "Click me");

    lv_obj_t * label_count = lv_label_create(container);
    lv_label_set_text(label_count, "Pressed 0 times");
    lv_obj_align(label_count, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_obj_add_event_cb(btn, on_button_click, LV_EVENT_CLICKED, label_count);
}

#endif

int main(void)
{
    lv_init();
    lv_display_t * disp = init_backend(1280, 720);
    if(!disp) {
        LV_LOG_ERROR("Failed to initialize a backend");
        return EXIT_FAILURE;
    }

    app_ui_start();

    struct timespec ts;
    while(1) {
        uint32_t ms = lv_timer_handler();
        if(ms == LV_NO_TIMER_READY) {
            ms = LV_DEF_REFR_PERIOD;
        }
        ts.tv_sec = ms /= 1000;
        ts.tv_nsec = ms * NS_TO_MS;
        nanosleep(&ts, NULL);
    }
    lv_deinit();
    return EXIT_SUCCESS;
}
