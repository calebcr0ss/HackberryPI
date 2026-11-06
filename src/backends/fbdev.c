#include "backend.h"

#if LV_USE_LINUX_FBDEV

#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

static lv_result_t find_dev_fb_entry(char * path);

lv_display_t * fbdev_init(uint32_t width, uint32_t height)
{
    char path[PATH_MAX];
    lv_result_t res = find_dev_fb_entry(path);
    if(res != LV_RESULT_OK) {
        LV_LOG_WARN("Couldn't find a fb entry inside /dev");
        return NULL;
    }
    lv_display_t * disp = lv_linux_fbdev_create();
    if(disp != NULL) {
        LV_LOG_WARN("failed to create display");
        return NULL;
    }
    res = lv_linux_fbdev_set_file(disp, path);
    if(res != LV_RESULT_OK) {
        LV_LOG_WARN("failed to initialize display");
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

static lv_result_t find_dev_fb_entry(char * path)
{
    struct dirent * entry;
    DIR * dir = opendir("/dev");
    if(!dir) return LV_RESULT_INVALID;

    while((entry = readdir(dir)) != NULL) {
        if(strncmp(entry->d_name, "fb", 2) == 0) {
            snprintf(path, sizeof(path), "/dev/%s", entry->d_name);
            closedir(dir);
            return LV_RESULT_OK;
        }
    }

    closedir(dir);
    return LV_RESULT_INVALID;
}
#endif /*LV_USE_LINUX_FBDEV*/
