#include "backend.h"

#if LV_USE_WAYLAND

lv_display_t * wayland_init(uint32_t width, uint32_t height)
{
    lv_display_t * disp = lv_wayland_window_create(width, height, "LVGL Linux", NULL);

    if(!disp) {
        return NULL;
    }
    lv_group_set_default(lv_group_create());
    lv_indev_t * kb = lv_wayland_get_keyboard(disp);
    if(kb) {
        lv_indev_set_group(kb, lv_group_get_default());
    }
    lv_indev_t * pointeraxis = lv_wayland_get_pointeraxis(disp);
    if(pointeraxis) {
        lv_indev_set_group(pointeraxis, lv_group_get_default());
    }

    return disp;
}
#endif
