#include "backend.h"

#if LV_USE_EVDEV

static void discovery_cb(lv_indev_t * indev, lv_evdev_type_t type, void * user_data);

lv_result_t evdev_init(lv_display_t * disp)
{
    return lv_evdev_discovery_start(discovery_cb, disp);
}

static void discovery_cb(lv_indev_t * indev, lv_evdev_type_t type, void * user_data)
{
    LV_LOG_USER("new '%s' device discovered", type == LV_EVDEV_TYPE_REL ? "REL" :
                type == LV_EVDEV_TYPE_ABS ? "ABS" :
                type == LV_EVDEV_TYPE_KEY ? "KEY" :
                "unknown");

    lv_display_t * disp = user_data;
    lv_indev_set_display(indev, disp);
}
#endif /*LV_USE_EVDEV*/
