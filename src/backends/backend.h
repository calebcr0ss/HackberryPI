#ifndef BACKEND_H
#define BACKEND_H

#include <lvgl.h>

typedef lv_display_t * (*backend_init)(uint32_t width, uint32_t height);

lv_display_t * init_backend(uint32_t width, uint32_t height);

lv_display_t * sdl_init(uint32_t width, uint32_t height);
lv_display_t * wayland_init(uint32_t width, uint32_t height);
lv_display_t * x11_init(uint32_t width, uint32_t height);
lv_display_t * drm_init(uint32_t width, uint32_t height);
lv_display_t * fbdev_init(uint32_t width, uint32_t height);
lv_result_t evdev_init(lv_display_t * display);

typedef struct {
    const char * name;
    backend_init init;
} backend_t;

static const backend_t backends[] = {
#if LV_USE_SDL
    {"sdl", sdl_init},
#endif

#if LV_USE_WAYLAND
    {"wayland", wayland_init},
#endif

#if LV_USE_X11
    {"x11", x11_init},
#endif

#if LV_USE_LINUX_DRM
    {"drm", drm_init},
#endif

#if LV_USE_LINUX_FBDEV
    {"fbdev", fbdev_init},
#endif
};

#endif /*BACKEND_H*/

