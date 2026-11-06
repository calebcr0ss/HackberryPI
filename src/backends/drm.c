#include "backend.h"

#if LV_USE_LINUX_DRM

static uint32_t pref_width;
static uint32_t pref_height;

static size_t drm_mode_selector(lv_display_t * disp, const lv_linux_drm_mode_t * modes, size_t mode_count);

lv_display_t * drm_init(uint32_t width, uint32_t height)
{
    lv_display_t * disp = lv_linux_drm_create();

    if(disp == NULL) {
        LV_LOG_WARN("failed");
        return NULL;
    }

    pref_width = width;
    pref_height = height;
    lv_linux_drm_set_mode_cb(disp, drm_mode_selector);

    char * device = lv_linux_drm_find_device_path();
    lv_result_t res = lv_linux_drm_set_file(disp, device, -1);
    lv_free(device);
    if(res != LV_RESULT_OK) {
        lv_display_delete(disp);
        return NULL;
    }

#if LV_USE_EVDEV
    res = evdev_init(disp);
    if(res != LV_RESULT_OK) {
        LV_LOG_WARN("Failed to initialize evdev");
    }
#endif /*LV_USE_EVDEV*/
    return disp;

}

static size_t drm_mode_selector(lv_display_t * disp, const lv_linux_drm_mode_t * modes, size_t mode_count)
{
    for(size_t i = 0; i < mode_count; i++) {
        int32_t width = lv_linux_drm_mode_get_horizontal_resolution(&modes[i]);
        int32_t height = lv_linux_drm_mode_get_vertical_resolution(&modes[i]);
        int32_t refresh = lv_linux_drm_mode_get_refresh_rate(&modes[i]);

        if(width == pref_width && height == pref_height) {
            return i;
        }
    }
    return 0;
}
#endif /*LV_USE_LINUX_DRM*/
