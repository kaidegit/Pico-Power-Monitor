// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0
// LVGL VERSION: 8.2
// PROJECT: Monitor_UI

#ifndef _MONITOR_UI_UI_H
#define _MONITOR_UI_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_Voltage;
extern lv_obj_t * ui_Current;
extern lv_obj_t * ui_Power;




LV_FONT_DECLARE(ui_font_SourceHanMono16);
LV_FONT_DECLARE(ui_font_SourceHanMono20);
LV_FONT_DECLARE(ui_font_SourceHanSan16);
LV_FONT_DECLARE(ui_font_SourceHanSan20);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
