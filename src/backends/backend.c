#include "backend.h"

lv_display_t * init_backend(uint32_t width, uint32_t height)
{
    const size_t backend_count = sizeof(backends) / sizeof(backends[0]);
    for(size_t i = 0; i < backend_count; ++i) {
        LV_LOG_USER("trying to initialize %s", backends[i].name);
        lv_display_t * disp = backends[i].init(width, height);
        if(disp) {
            LV_LOG_USER("%s initialized", backends[i].name);
            return disp;
        }
        LV_LOG_WARN("failed to initialize '%s'", backends[i].name);
    }
    return NULL;
}
