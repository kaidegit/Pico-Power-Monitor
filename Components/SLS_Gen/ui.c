// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0
// LVGL VERSION: 8.2
// PROJECT: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Screen1;
lv_obj_t * ui_voltage;
lv_obj_t * ui_current;
lv_obj_t * ui_power;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=1
    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_voltage = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_voltage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_voltage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_voltage, -30);
    lv_obj_set_y(ui_voltage, -25);
    lv_obj_set_align(ui_voltage, LV_ALIGN_CENTER);
    lv_label_set_text(ui_voltage, "0.0000V");
    lv_obj_set_style_text_font(ui_voltage, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_current = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_current, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_current, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_current, -30);
    lv_obj_set_y(ui_current, 0);
    lv_obj_set_align(ui_current, LV_ALIGN_CENTER);
    lv_label_set_text(ui_current, "0.0000A");
    lv_obj_set_style_text_font(ui_current, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_power = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_power, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_power, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_power, -30);
    lv_obj_set_y(ui_power, 25);
    lv_obj_set_align(ui_power, LV_ALIGN_CENTER);
    lv_label_set_text(ui_power, "0.0000W");
    lv_obj_set_style_text_font(ui_power, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

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
