// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0
// LVGL VERSION: 8.2
// PROJECT: Monitor_UI

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void ui_event_Screen1(lv_event_t * e);
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Voltage;
lv_obj_t * ui_Current;
lv_obj_t * ui_Power;
lv_obj_t * ui_CurDirection;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_Screen1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        main_screen_init(e);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Voltage = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Voltage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Voltage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Voltage, -30);
    lv_obj_set_y(ui_Voltage, -25);
    lv_obj_set_align(ui_Voltage, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Voltage, "0.0000V");
    lv_obj_set_style_text_color(ui_Voltage, lv_color_hex(0x00FF23), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Voltage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Voltage, &ui_font_SourceHanMono20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Current = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Current, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Current, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Current, -30);
    lv_obj_set_y(ui_Current, 0);
    lv_obj_set_align(ui_Current, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Current, "0.0000A");
    lv_obj_set_style_text_color(ui_Current, lv_color_hex(0xE0FF04), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Current, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Current, &ui_font_SourceHanMono20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Power = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Power, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Power, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Power, -30);
    lv_obj_set_y(ui_Power, 25);
    lv_obj_set_align(ui_Power, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Power, "0.0000W");
    lv_obj_set_style_text_color(ui_Power, lv_color_hex(0xFF04DB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Power, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Power, &ui_font_SourceHanMono20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CurDirection = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_CurDirection, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CurDirection, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CurDirection, 50);
    lv_obj_set_y(ui_CurDirection, 25);
    lv_obj_set_align(ui_CurDirection, LV_ALIGN_CENTER);
    lv_label_set_text(ui_CurDirection, "<---");
    lv_obj_set_style_text_color(ui_CurDirection, lv_color_hex(0x5168F8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CurDirection, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CurDirection, &ui_font_SourceHanMono20, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Screen1, ui_event_Screen1, LV_EVENT_ALL, NULL);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    lv_disp_load_scr(ui_Screen1);
}
