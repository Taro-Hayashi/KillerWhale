// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lib/add_oled.h"
#include "os_detection.h"
#include "lib/common_killerwhale.h"
#include "lib/glcdfont.c"
#include "lib/add_keycodes.h"

uint8_t pre_layer, cur_layer;
bool interrupted;
uint16_t interrupted_time, tempch_time;
uint16_t interrupt_type, tempch_type;
bool tempch;

// 初期化
void oled_init_addedoled(void){
    pre_layer = 0;
    cur_layer = 0;
    interrupted = false;
    interrupted_time = 0;
    interrupt_type = 0;
    tempch = 0;
    tempch_time = 0;
    tempch_type = 0;
}

// OLED表示
bool oled_task_addedoled(void) {
    if(!(kw_config.oled_mode == TURN_OFF)){
        // 割り込み表示
        if(interrupted){
            if(timer_elapsed(interrupted_time) < INTERRUPT_TIME){
                oled_set_cursor(0, 3);
                switch (interrupt_type){
                    case UG_HUEU:
                        oled_write_P(PSTR("INCREASE HUE         "), false);
                        break;
                    case UG_HUED:
                        oled_write_P(PSTR("DECREASE HUE         "), false);
                        break;
                    case UG_SATU:
                        oled_write_P(PSTR("INCREASE SATURATION  "), false);
                        break;
                    case UG_SATD:
                        oled_write_P(PSTR("DECREASE SATURATION  "), false);
                        break;
                    case UG_VALU:
                        oled_write_P(PSTR("INCREASE VALUE       "), false);
                        break;
                    case UG_VALD:
                        oled_write_P(PSTR("DECREASE VALUE       "), false);
                        break;
                    case UG_SPDU:
                        oled_write_P(PSTR("INCREASE LIGHT SPEED "), false);
                        break;
                    case UG_SPDD:
                        oled_write_P(PSTR("DECREASE LIGHT SPEED "), false);
                        break;
                    case UG_NEXT:
                        oled_write_P(PSTR("NEXT LIGHT PATTERN   "), false);
                        break;
                    case UG_PREV:
                        oled_write_P(PSTR("PREV LIGHT PATTERN   "), false);
                        break;
                    case UG_TOGG:
                        if(rgblight_is_enabled()){
                            oled_write_P(PSTR("RGB ON               "), false);
                        }else{
                            oled_write_P(PSTR("RGB OFF              "), false);
                        }
                        break;
                    // ショートカット系
                    case UNDO:
                        oled_write_P(PSTR("UNDO                 "), false);
                        break;
                    case REDO:
                        oled_write_P(PSTR("REDO                 "), false);
                        break;
                    case COPY:
                        oled_write_P(PSTR("COPY                 "), false);
                        break;
                    case CUT:
                        oled_write_P(PSTR("CUT                  "), false);
                        break;
                    case PASTE:
                        oled_write_P(PSTR("PASTE                "), false);
                        break;
                    case SC_UP:
                        oled_write_P(PSTR("SCALE UP             "), false);
                        break;
                    case SC_DOWN:
                        oled_write_P(PSTR("SCALE DOWN           "), false);
                        break;
                    case SC_RESET:
                        oled_write_P(PSTR("SCALE RESET          "), false);
                        break;
                    case CAPTCHA:
                        oled_write_P(PSTR("SCREEN CAPTHA        "), false);
                        break;
                    case SAVE:
                        oled_write_P(PSTR("SAVE                 "), false);
                        break;
                    case SAVEAS:
                        oled_write_P(PSTR("SAVE AS...           "), false);
                        break;
                    case NEXTTAB:
                        oled_write_P(PSTR("NEXT TAB             "), false);
                        break;
                    case PREVTAB:
                        oled_write_P(PSTR("PREV TAB             "), false);
                        break;
                    case CLOSETAB:
                        oled_write_P(PSTR("CLOSE TAB            "), false);
                        break;
                    case RSTRTAB:
                        oled_write_P(PSTR("RESTORE TAB          "), false);
                        break;
                    // 設定系
                    case L_SPD_I:
                    case R_SPD_I:
                        oled_write_P(PSTR("SPEED UP             "), false);
                        break;
                    case L_SPD_D:
                    case R_SPD_D:
                        oled_write_P(PSTR("SPEED DOWN           "), false);
                        break;
                    case L_ANG_I:
                    case R_ANG_I:
                        oled_write_P(PSTR("ANGLE TURNED CW      "), false);
                        break;
                    case L_ANG_D:
                    case R_ANG_D:
                        oled_write_P(PSTR("ANGLE TURNED CCW     "), false);
                        break;
                    case L_INV:
                    case R_INV:
                        oled_write_P(PSTR("AXIS INVERTED        "), false);
                        break;
                    case INV_SCRL:
                        oled_write_P(PSTR("SCROLL INVERTED      "), false);
                        break;
                    case L_CHMOD:
                    case R_CHMOD:
                        if(kw_config.pd_mode == SCROLL_MODE){
                            oled_write_P(PSTR("SCROLL MODE          "), false);
                        }else if(kw_config.pd_mode == CURSOR_MODE){
                            oled_write_P(PSTR("CURSOR MODE          "), false);
                        }else if(kw_config.pd_mode == KEY_INPUT){
                            oled_write_P(PSTR("KEY INPUT MODE       "), false);
                        }else if(kw_config.pd_mode == GAME_MODE){
                            oled_write_P(PSTR("GAME MODE            "), false);
                        }
                        break;
                    case AUTO_MOUSE:
                        if(kw_config.auto_mouse){
                            oled_write_P(PSTR("AUTO MOUSE ON        "), false);
                        }else{
                            oled_write_P(PSTR("AUTO MOUSE OFF       "), false);
                        }
                        break;
                    case OLED_MOD:
                        if(kw_config.oled_mode == SHOW_LAYER){
                            oled_write_P(PSTR("SHOW LAYER           "), false);
                        }else{
                            oled_write_P(PSTR("SHOW STATS           "), false);
                        }
                        break;
                    case QK_USER_14:
                        if(kw_config.dpad_exclusion){
                            oled_write_P(PSTR("DPAD EXCLUSION ON   "), false);
                        }else{
                            oled_write_P(PSTR("DPAD EXCLUSION OFF  "), false);
                        }
                        break;
                    case QK_USER_15:
                        if(kw_config.rgb_layers){
                            oled_write_P(PSTR("RGBLIGHT LAYER ON   "), false);
                        }else{
                            oled_write_P(PSTR("RGBLIGHT LAYER OFF  "), false);
                        }
                        break;
                    case QK_USER_16:
                            oled_write_P(PSTR("JOYSTICK INITIALIZED "), false);
                        break;
                    case QK_USER_22:
                    case QK_USER_23:
                            oled_write_P(PSTR("OFFSET MIN: "), false);
                            oled_write(get_u16_str(get_joystick_offset_min(), ' '), false);
                            oled_write_P(PSTR("   "), false);
                        break;
                    case QK_USER_24:
                    case QK_USER_25:
                            oled_write_P(PSTR("OFFSET MAX: "), false);
                            oled_write(get_u16_str(get_joystick_offset_max(), ' '), false);
                            oled_write_P(PSTR("   "), false);
                        break;
                }
            }else{
                interrupted = false;
            }
        // 切り替え表示
        }else if(tempch && timer_elapsed(tempch_time) > TERM_TEMP){
            oled_set_cursor(0, 3);
            switch (tempch_type){
                case MOD_SCRL:
                case QK_USER_0:
                case QK_USER_1:
                case QK_USER_2:
                case QK_USER_3:
                    oled_write_P(PSTR("SCROLL MODE          "), false);
                    break;
                case QK_USER_4:
                case QK_USER_5:
                case QK_USER_6:
                case QK_USER_7:
                case QK_USER_8:
                case QK_USER_9:
                case QK_USER_10:
                case QK_USER_11:
                    oled_write_P(PSTR("SLOW MODE            "), false);
                    break;
                case QK_USER_12:
                    oled_write_P(PSTR("CURSOR MODE          "), false);
                    break;
                case QK_USER_13:
                    oled_write_P(PSTR("KEY INPUT MODE       "), false);
                    break;
                case QK_USER_21:
                    oled_write_P(PSTR("GAME MODE            "), false);
                    break;
            }
        // レイヤー表示処理
        }else if(kw_config.oled_mode == SHOW_LAYER){
            oled_set_cursor(0, 0);
            cur_layer = get_highest_layer(layer_state);
            if (gpio_read_pin(GP10)) {
                oled_write_raw_P(reverse_number[cur_layer], sizeof(reverse_number[cur_layer]));
            }else{
                oled_write_raw_P(number[cur_layer], sizeof(number[cur_layer]));
            }
        // スタッツ表示処理
        } else if(get_joystick_attached()){
            oled_set_cursor(0, 0);
            oled_write_P(PSTR("JOYSTICK"), false);

            oled_set_cursor(0, 1);
            oled_write_P(PSTR("MODE :"), false);
            if(kw_config.pd_mode == KEY_INPUT){
                oled_write_P(PSTR("KEY INPUT"), false);
            } else if (kw_config.pd_mode == CURSOR_MODE){
                oled_write_P(PSTR("CURSOR   "), false);
            } else if (kw_config.pd_mode == GAME_MODE){
                oled_write_P(PSTR("GAMEPAD  "), false);
            } else if (kw_config.pd_mode == SCROLL_MODE){
                oled_write_P(PSTR("SCROLL"), false);
                if(kw_config.inv_sc){
                    oled_write_P(PSTR(" INVERT"), false);
                } else{
                    oled_write_P(PSTR("       "), false);
                }
            }

            oled_set_cursor(0, 2);

            oled_write_P(PSTR("SPEED: "), false);
            oled_write(get_u16_str(4 + (uint16_t)kw_config.spd * 3, ' '), false);

            oled_set_cursor(0, 3);

            oled_write_P(PSTR("ANGLE: "), false);
            oled_write(get_u16_str((uint16_t)kw_config.angle * 6, ' '), false);
            if(kw_config.inv){
                    oled_write_P(PSTR(" INVERT"), false);
            }else{
                    oled_write_P(PSTR("       "), false);
            }
        } else{
            oled_set_cursor(0, 0);
            oled_write_P(PSTR("CPI:   "), false);
            oled_write(get_u16_str(400 + (uint16_t)kw_config.spd * 200, ' '), false);
            if(kw_config.pd_mode == SCROLL_MODE){
                oled_write_P(PSTR(" SCRLMODE"), false);
            }else if(kw_config.pd_mode == CURSOR_MODE){
                oled_write_P(PSTR(" CRSLMODE"), false);
            }else if(kw_config.pd_mode == KEY_INPUT){
                oled_write_P(PSTR(" KEY MODE"), false);
            }
            oled_set_cursor(0, 1);
            oled_write_P(PSTR("ANGLE: "), false);
            oled_write(get_u16_str((uint16_t)kw_config.angle * 6, ' '), false);

                if(kw_config.auto_mouse){
                oled_write_P(PSTR(" AT MOUSE"), false);
            }else{
                oled_write_P(PSTR("         "), false);
            }

            oled_set_cursor(0, 2);
            if (kw_config.inv){
                oled_write_P(PSTR("INV AXIS"), false);
            }else{
                oled_write_P(PSTR("        "), false);
            }

            cur_layer = get_highest_layer(layer_state);

            if(kw_config.dpad_exclusion){
                oled_write_P(PSTR("     DPAD FIX"), false);
            }else{
                oled_write_P(PSTR("             "), false);
            }

            oled_set_cursor(0, 3);
            if (kw_config.inv_sc){
                oled_write_P(PSTR("INV SCRL"), false);
            }else{
                oled_write_P(PSTR("        "), false);
            }

            oled_write_P(PSTR("     Lyr:"), false);
            if(get_auto_mouse_enable()){
                oled_write(get_u8_str(cur_layer , ' '), false);
            }else{
                pre_layer = cur_layer;
                oled_write(get_u8_str(cur_layer , ' '), false);
            }
        }
        // 修飾キー処理
        uint8_t mod_state = get_mods();
        if(mod_state){
            oled_set_cursor(0, 3);
            if(mod_state & MOD_MASK_SHIFT){
                oled_write_P(PSTR("SHIFT  "), false);
            }else{
                oled_write_P(PSTR("       "), false);
            }
            if(mod_state & MOD_MASK_CTRL){
                oled_write_P(PSTR("CTRL  "), false);
            }else{
                oled_write_P(PSTR("      "), false);
            }
            if(mod_state & MOD_MASK_ALT){
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    oled_write_P(PSTR("OPT  "), false);
                }else{
                    oled_write_P(PSTR("ALT  "), false);
                }
            }else{
                oled_write_P(PSTR("     "), false);
            }
            if(mod_state & MOD_MASK_GUI){
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    oled_write_P(PSTR("CMD"), false);
                }else{
                    oled_write_P(PSTR("WIN"), false);
                }
            }else{
                oled_write_P(PSTR("   "), false);
            }
        }
    }

    return true;
}

void oled_interrupt(uint16_t keycode){
    interrupted = true;
    interrupted_time = timer_read();
    interrupt_type = keycode;
}

void oled_tempch(bool on, uint16_t keycode){
    tempch = on;
    tempch_time = timer_read();
    tempch_type = keycode;
}
