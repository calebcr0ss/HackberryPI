#include "backend.h"

#if LV_USE_SDL

lv_display_t * sdl_init(uint32_t width, uint32_t height)
{
    lv_display_t * disp = lv_sdl_window_create(width, height);

    if(!disp) {
        return NULL;
    }

    lv_group_set_default(lv_group_create());

    lv_indev_t * mouse = lv_sdl_mouse_create();

    lv_indev_t * mousewheel = lv_sdl_mousewheel_create();
    if(mousewheel) {
        lv_indev_set_display(mousewheel, disp);
        lv_indev_set_group(mousewheel, lv_group_get_default());
    }

    lv_indev_t * kb = lv_sdl_keyboard_create();
    if(kb) {
        lv_indev_set_display(kb, disp);
        lv_indev_set_group(kb, lv_group_get_default());
    }

    return disp;
}
#endif /*LV_USE_SDL*/
