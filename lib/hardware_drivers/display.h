#ifndef DISPLAY_H
#define DISPLAY_H

#include <lvgl.h>
#include <LovyanGFX.hpp>

// LovyanGFX instance for the SH8601 display
class LGFX : public lgfx::LGFX_Device {
public:
    lgfx::Bus_QSPI _bus;
    lgfx::Panel_SH8601 _panel;
    LGFX(void);
};

void display_init();
void my_disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p);

#endif // DISPLAY_H
