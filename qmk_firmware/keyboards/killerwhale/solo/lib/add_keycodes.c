// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lib/add_keycodes.h"
#include "os_detection.h"
#include "lib/common_killerwhale.h"
#include "lib/add_oled.h"


uint16_t startup_timer;

bool process_record_addedkeycodes(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CMD_CTL:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                }
            } else {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    unregister_code(KC_LGUI);
                } else {
                    unregister_code(KC_LCTL);
                }
            }
            oled_tempch(record->event.pressed, keycode);
            return false;
            break;
        case UNDO:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_Z);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_Z);
                    unregister_code(KC_LCTL);
                }
                oled_interrupt(keycode);
            }
            return false;
            break;
        case REDO:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_Z);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_LCTL);
                    tap_code(KC_Z);
                    unregister_code(KC_LCTL);
                    unregister_code(KC_LSFT);
                }
                oled_interrupt(keycode);
            }
            return false;
            break;
        case COPY:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_C);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_C);
                    unregister_code(KC_LCTL);
                }
                oled_interrupt(keycode);
            }
            return false;
            break;
        case CUT:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_X);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_X);
                    unregister_code(KC_LCTL);
                }
                oled_interrupt(keycode);
            }
            return false;
            break;
        case PASTE:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_V);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_V);
                    unregister_code(KC_LCTL);
                }
                oled_interrupt(keycode);
            }
            return false;
            break;
        case SC_UP:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_PPLS);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_PPLS);
                    unregister_code(KC_LCTL);
                }
                oled_interrupt(keycode);
            }
            return false;
            break;
        case SC_DOWN:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_PMNS);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_PMNS);
                    unregister_code(KC_LCTL);
                }
                oled_interrupt(keycode);
            }
            return false;
            break;
        case SC_RESET:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_0);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_0);
                    unregister_code(KC_LCTL);
                }
                oled_interrupt(keycode);
            }
            return false;
            break;
        case CAPTCHA:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_4);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_S);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                }
                oled_interrupt(keycode);
            }
            return false;
            break;
        case SAVE:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_S);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_S);
                    unregister_code(KC_LCTL);
                }
                oled_interrupt(keycode);
            }
            return false;
            break;
        case SAVEAS:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_S);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_LCTL);
                    tap_code(KC_S);
                    unregister_code(KC_LCTL);
                    unregister_code(KC_LSFT);
                }
                oled_interrupt(keycode);
            }
            return false;
            break;
        case NEXTTAB:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_TAB);
                unregister_code(KC_LCTL);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case PREVTAB:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_LCTL);
                tap_code(KC_TAB);
                unregister_code(KC_LCTL);
                unregister_code(KC_LSFT);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case CLOSETAB:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LGUI);
                    tap_code(KC_W);
                    unregister_code(KC_LGUI);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_W);
                    unregister_code(KC_LCTL);
                }
                oled_interrupt(keycode);
            }
            return false;
            break;
        case RSTRTAB:
            if (record->event.pressed) {
                if (detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS){
                    register_code(KC_LSFT);
                    register_code(KC_LGUI);
                    tap_code(KC_T);
                    unregister_code(KC_LGUI);
                    unregister_code(KC_LSFT);
                } else {
                    register_code(KC_LSFT);
                    register_code(KC_LCTL);
                    tap_code(KC_T);
                    unregister_code(KC_LCTL);
                    unregister_code(KC_LSFT);
                }
                oled_interrupt(keycode);
            }
            return false;
            break;
        case L_SPD_I:
        case R_SPD_I:
            if (record->event.pressed) {
                kw_config.spd = kw_config.spd + 1;
                if(kw_config.spd >= SPD_OPTION_MAX){
                    kw_config.spd = SPD_OPTION_MAX-1;
                }
                eeconfig_update_kb(kw_config.raw);
                pointing_device_set_cpi(400 + kw_config.spd * 200);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case L_SPD_D:
        case R_SPD_D:
            if (record->event.pressed) {
                if(kw_config.spd > 0){
                    kw_config.spd = kw_config.spd - 1;
                }
                eeconfig_update_kb(kw_config.raw);
                pointing_device_set_cpi(400 + kw_config.spd * 200);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case L_ANG_I:
        case R_ANG_I:
            if (record->event.pressed) {
                kw_config.angle = (kw_config.angle + 1) % ANGLE_OPTION_MAX;
                eeconfig_update_kb(kw_config.raw);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case L_ANG_D:
        case R_ANG_D:
            if (record->event.pressed) {
                kw_config.angle = (ANGLE_OPTION_MAX + kw_config.angle - 1) % ANGLE_OPTION_MAX;
                eeconfig_update_kb(kw_config.raw);
                oled_interrupt(L_ANG_D);
            }
            return false;
            break;
        case L_INV:
        case R_INV:
            if (record->event.pressed) {
                kw_config.inv = !kw_config.inv;
                eeconfig_update_kb(kw_config.raw);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case INV_SCRL:
            if (record->event.pressed) {
                kw_config.inv_sc = !kw_config.inv_sc;
                eeconfig_update_kb(kw_config.raw);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case L_CHMOD:
        case R_CHMOD:
            if (record->event.pressed) {
                cycle_mode();
                oled_interrupt(keycode);
            }
            return false;
            break;
        case AUTO_MOUSE:
            if (record->event.pressed) {
                kw_config.auto_mouse = !kw_config.auto_mouse;
                set_auto_mouse_enable(kw_config.auto_mouse);
                eeconfig_update_kb(kw_config.raw);
                oled_interrupt(keycode);
            }
            return false;
            break;
        case OLED_MOD:
            if (record->event.pressed) {
                kw_config.oled_mode = (kw_config.oled_mode + 1) % 3;
                oled_clear();
                if(kw_config.oled_mode == TURN_OFF){
                    oled_off();
                }else{
                    oled_on();
                    oled_interrupt(keycode);
                }
                eeconfig_update_kb(kw_config.raw);
            }
            return false;
            break;
        case MOD_SCRL:
            is_scroll_mode(record->event.pressed);
            oled_tempch(record->event.pressed, keycode);
            return false;
            break;
        // ESC SCROLL
        case QK_USER_0:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_scroll_mode(true);
                oled_tempch(record->event.pressed, keycode);
            } else {
                is_scroll_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_ESC);
                }
                oled_tempch(record->event.pressed, keycode);
            }
            return false;
            break;
        // TAB SCROLL
        case QK_USER_1:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_scroll_mode(true);
                oled_tempch(record->event.pressed, keycode);
            } else {
                is_scroll_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_TAB);
                }
                oled_tempch(record->event.pressed, keycode);
            }
            return false;
            break;
        // Lang1 SCROLL
        case QK_USER_2:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_scroll_mode(true);
                oled_tempch(record->event.pressed, keycode);
            } else {
                is_scroll_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_LNG1);
                }
                oled_tempch(record->event.pressed, keycode);
            }
            return false;
            break;
        // Lang2 SCROLL
        case QK_USER_3:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_scroll_mode(true);
                oled_tempch(record->event.pressed, keycode);
            } else {
                is_scroll_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_LNG2);
                }
                oled_tempch(record->event.pressed, keycode);
            }
            return false;
            break;
        // SLOW MODE
        case QK_USER_4:
            is_slow_mode(record->event.pressed);
            oled_tempch(record->event.pressed, keycode);
            return false;
            break;
        // ESC SLOW
        case QK_USER_5:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_slow_mode(record->event.pressed);
                oled_tempch(record->event.pressed, keycode);
            } else {
                is_slow_mode(record->event.pressed);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_ESC);
                }
                oled_tempch(record->event.pressed, keycode);
            }
            return false;
            break;
        // TAB SLOW
        case QK_USER_6:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_slow_mode(true);
                oled_tempch(record->event.pressed, keycode);
            } else {
                is_slow_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_TAB);
                }
                oled_tempch(record->event.pressed, keycode);
            }
            return false;
            break;
        // Lang1 SLOW
        case QK_USER_7:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_slow_mode(true);
                oled_tempch(record->event.pressed, keycode);
            } else {
                is_slow_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_LNG1);
                }
                oled_tempch(record->event.pressed, keycode);
            }
            return false;
            break;
        // Lang2 SLOW
        case QK_USER_8:
            if (record->event.pressed) {
                startup_timer = timer_read();
                is_slow_mode(true);
                oled_tempch(record->event.pressed, keycode);
            } else {
                is_slow_mode(false);
                if(timer_elapsed(startup_timer) < TERM_TEMP){
                    tap_code(KC_LNG2);
                }
                oled_tempch(record->event.pressed, keycode);
            }
            return false;
            break;
        // BTN1 SLOW
        case QK_USER_9:
            if (record->event.pressed) {
                register_code(MS_BTN1);
                is_slow_mode(true);
                oled_tempch(record->event.pressed, keycode);
            } else {
                is_slow_mode(false);
                unregister_code(MS_BTN1);
                oled_tempch(record->event.pressed, keycode);
            }
            return false;
            break;
        // BTN2 SLOW
        case QK_USER_10:
            if (record->event.pressed) {
                register_code(MS_BTN2);
                is_slow_mode(true);
                oled_interrupt(QK_USER_4);
                oled_tempch(record->event.pressed, keycode);
            } else {
                is_slow_mode(false);
                unregister_code(MS_BTN2);
                oled_tempch(record->event.pressed, keycode);
            }
            return false;
            break;
        // BTN3 SLOW
        case QK_USER_11:
            if (record->event.pressed) {
                register_code(MS_BTN3);
                is_slow_mode(true);
                oled_tempch(record->event.pressed, keycode);
            } else {
                is_slow_mode(false);
                unregister_code(MS_BTN3);
                oled_tempch(record->event.pressed, keycode);
            }
            return false;
            break;
        // 押している間カーソル移動
        case QK_USER_12:
            is_cursor_mode(record->event.pressed);
            oled_tempch(record->event.pressed, keycode);
            return false;
            break;
        // 押している間キー入力
        case QK_USER_13:
            is_key_mode(record->event.pressed);
            oled_tempch(record->event.pressed, keycode);
            return false;
            break;
        // 十字キー同時押しオンオフ
        case QK_USER_14:
            if (record->event.pressed) {
                kw_config.dpad_exclusion = !kw_config.dpad_exclusion;
                eeconfig_update_kb(kw_config.raw);
                oled_interrupt(keycode);
            }
            return false;
            break;
        // RGBレイヤーオンオフ
        case QK_USER_15:
            if (record->event.pressed) {
                kw_config.rgb_layers = !kw_config.rgb_layers;
                eeconfig_update_kb(kw_config.raw);
                oled_interrupt(keycode);
            }
            return false;
            break;
        // ジョイスティックの値を初期化
        case QK_USER_16:
                if (record->event.pressed) {
                    reset_joystick();
                    oled_interrupt(keycode);
                }
                return false;
                break;
        // ゲームパッド上
        case QK_USER_17:
                if (record->event.pressed) {
                    joystick_set_axis(1, -511);
                }else{
                    joystick_set_axis(1, 0);
                }
                return false;
                break;
        // ゲームパッド下
        case QK_USER_18:
                if (record->event.pressed) {
                    joystick_set_axis(1, 511);
                }else{
                    joystick_set_axis(1, 0);
                }
                return false;
                break;
        // ゲームパッド左
        case QK_USER_19:
                if (record->event.pressed) {
                    joystick_set_axis(0, -511);
                }else{
                    joystick_set_axis(0, 0);
                }
                return false;
                break;
        // ゲームパッド右
        case QK_USER_20:
                if (record->event.pressed) {
                    joystick_set_axis(0, 511);
                }else{
                    joystick_set_axis(0, 0);
                }
                return false;
                break;
        case QK_USER_21:
                if(get_joystick_attached()){
                    is_game_mode(record->event.pressed);
                    oled_tempch(record->event.pressed, keycode);
                }
                return false;
                break;
        case QK_USER_22:
                if(get_joystick_offset_min() > 4){
                    set_joystick_offset_min(get_joystick_offset_min() - 5);
                }
                oled_interrupt(keycode);
                return false;
                break;
        case QK_USER_23:
                if(get_joystick_offset_min() < 196){
                    set_joystick_offset_min(get_joystick_offset_min() + 5);
                }
                oled_interrupt(keycode);
                return false;
                break;
        case QK_USER_24:
                if(get_joystick_offset_max() > 4){
                    set_joystick_offset_max(get_joystick_offset_max() - 5);
                }
                oled_interrupt(keycode);
                return false;
                break;
        case QK_USER_25:
                if(get_joystick_offset_max() < 196){
                    set_joystick_offset_max(get_joystick_offset_max() + 5);
                }
                oled_interrupt(keycode);
                return false;
                break;
}
    if (record->event.pressed) {
        oled_interrupt(keycode);
    }
    return true;
}
