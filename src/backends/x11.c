#include "backend.h"

#if LV_USE_X11

lv_display_t * x11_init(uint32_t width, uint32_t height)
{
    lv_display_t * disp = lv_x11_window_create("LVGL Linux", width, height);

    if(!disp) {
        return NULL;
    }
    lv_x11_inputs_create(disp, NULL);
    return disp;
}
#endif
