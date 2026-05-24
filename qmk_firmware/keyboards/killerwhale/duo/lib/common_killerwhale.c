// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lib/common_killerwhale.h"
#include "analog.h"
#include "math.h"
#include "os_detection.h"
#include "joystick.h"
#include "lib/add_keycodes.h"
#include "lib/add_oled.h"

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_VIRTUAL,
    JOYSTICK_AXIS_VIRTUAL
};

/* ポインティングデバイス用変数 */
kw_config_t kw_config;         // eeprom保存用
bool force_scrolling, force_cursoring, force_key_input, force_gaming, slow_mode;  // 一時的モード変更用
uint8_t joystick_attached;     // ジョイスティックの有無
float h_accumulator_l, v_accumulator_l, h_accumulator_r, v_accumulator_r;  //端数保存用
float x_accumulator_l, y_accumulator_l, x_accumulator_r, y_accumulator_r;
float prev_x_l, prev_y_l, prev_x_r, prev_y_r;
int16_t gp27_newt, gp28_newt;              // ジョイスティックの初期値
int16_t gp27_max, gp28_max, gp27_min, gp28_min; // ジョイスティックの最大値、最小値
uint16_t joystick_offset_min, joystick_offset_max; // ジョイスティックの小さい値、大きい値を無視する範囲

// 仮想十字キー設定用変数
keypos_t key_up_l, key_up_r, key_left_l, key_left_r, key_right_l, key_right_r, key_down_l, key_down_r;
bool pressed_up_l, pressed_up_r, pressed_down_l, pressed_down_r, pressed_left_l, pressed_left_r, pressed_right_l, pressed_right_r;
int8_t layer;
int16_t keycode_up_l, keycode_up_r, keycode_down_l, keycode_down_r, keycode_left_l, keycode_left_r, keycode_right_l,  keycode_right_r;
int16_t key_timer_l, key_timer_r;

// 斜め入力防止用変数
bool dpad_exclusion;
uint8_t dpad_pressed_l, dpad_pressed_r;

/* eeprom */
// 初期化
void eeconfig_init_kb(void) {
    kw_config.spd_l = SPD_DEFAULT_LEFT;
    kw_config.spd_r = SPD_DEFAULT_RIGHT;
    kw_config.angle_l = ANGLE_DEFAULT_LEFT;
    kw_config.angle_r = ANGLE_DEFAULT_RIGHT;
    kw_config.pd_mode_l = MODE_DEFAULT_LEFT;
    kw_config.pd_mode_r = MODE_DEFAULT_RIGHT;
    kw_config.inv_l = INVERT_LEFT_DEFAULT;
    kw_config.inv_r = INVERT_RIGHT_DEFAULT;
    kw_config.inv_sc = INVERT_SCROLL_DEFAULT;
    kw_config.auto_mouse = AUTO_MOUSE_DEFAULT;
    kw_config.rgb_layers = RGB_LAYER_DEFAULT;
    kw_config.oled_mode = OLED_DEFAULT;
    eeconfig_update_kb(kw_config.raw);

    eeconfig_init_user();
}

/* キースキャン */
// マウスキー登録
bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case MOD_SCRL: // 一時的にスクロール
            return true;
        case QK_USER_4: // 一時的に減速
            return true;
        case QK_USER_9: // マウス1 / 長押しスロー
            return true;
        case QK_USER_10: // マウス2 / 長押しスロー
            return true;
        case QK_USER_11: // マウス3 / 長押しスロー
            return true;
        case QK_USER_12: // 一時的にカーソル移動
            return true;
        default:
            return false;
    }

    return  is_mouse_record_user(keycode, record);
}
// 実タスク
bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    // 追加キーコードタスク
    process_record_addedkeycodes(keycode, record);

    // D-Padの同時押しを防ぐ
    keypos_t key = record->event.key;
    if(key.col == 6 && dpad_exclusion){
        switch (key.row){
            case 1:
            case 2:
            case 3:
            case 4:
                if(dpad_pressed_l == 0 && record->event.pressed){
                    if(record->event.pressed){
                        dpad_pressed_l  = key.row;
                    }
                }else if(dpad_pressed_l == key.row && !record->event.pressed){
                    dpad_pressed_l  = 0;
                }else if(record->event.pressed){
                    return false;
                }
                break;
            case 8:
            case 9:
            case 10:
            case 11:
                if(dpad_pressed_r == 0 && record->event.pressed){
                    if(record->event.pressed){
                        dpad_pressed_r = key.row;
                    }
                }else if(dpad_pressed_r == key.row && !record->event.pressed){
                    dpad_pressed_r = 0;
                }else if(record->event.pressed){
                    return false;
                }
                break;
        }
    }

    return process_record_user(keycode, record);
}

/* マトリクス走査 */
// 初期化
void matrix_init_kb(void) {
    key_up_l.row = 3;
    key_up_l.col = 6;
    key_down_l.row = 1;
    key_down_l.col = 6;
    key_left_l.row = 2;
    key_left_l.col = 6;
    key_right_l.row = 4;
    key_right_l.col = 6;
    key_up_r.row = 11;
    key_up_r.col = 6;
    key_down_r.row = 9;
    key_down_r.col = 6;
    key_left_r.row = 10;
    key_left_r.col = 6;
    key_right_r.row = 8;
    key_right_r.col = 6;
    dpad_pressed_l = 0;
    dpad_pressed_r = 0;
    force_scrolling = false;
    force_cursoring = false;
    force_key_input = false;
    pressed_up_l = false;
    pressed_up_r = false;
    pressed_down_l = false;
    pressed_down_r = false;
    pressed_left_l = false;
    pressed_left_r = false;
    pressed_right_l = false;
    pressed_right_r = false;
    slow_mode = false;
    gp27_newt = analogReadPin(GP27);
    gp28_newt = analogReadPin(GP28);
    gp27_max = gp27_newt;
    gp28_max = gp28_newt;
    gp27_min = gp27_newt;
    gp28_min = gp28_newt;
    joystick_offset_min = JOYSTICK_OFFSET_MIN_DEFAULT;
    joystick_offset_max = JOYSTICK_OFFSET_MAX_DEFAULT;
    if(gp27_newt < NO_JOYSTICK_VAL ||  gp28_newt < NO_JOYSTICK_VAL ){
        joystick_attached = false;
    }else{
        if(is_keyboard_left()){
            joystick_attached = JOYSTICK_LEFT;
        }else{
            joystick_attached = JOYSTICK_RIGHT;
        }
    }
    key_timer_l = timer_read();
    key_timer_r = timer_read();
    dpad_exclusion = DPAD_EX_DEFAULT;

    matrix_init_user();
}

/* カーソル操作 */
// 初期化
void pointing_device_init_kb(void){
    kw_config.raw = eeconfig_read_kb();
    h_accumulator_l = 0.0;
    v_accumulator_l = 0.0;
    h_accumulator_r = 0.0;
    v_accumulator_r = 0.0;
    x_accumulator_l = 0.0;
    y_accumulator_l = 0.0;
    x_accumulator_r = 0.0;
    y_accumulator_r = 0.0;
    prev_x_l = 0.0;
    prev_y_l = 0.0;
    prev_x_r = 0.0;
    prev_y_r = 0.0;
    pointing_device_set_cpi_on_side(true,  400 + kw_config.spd_l * 200);
    pointing_device_set_cpi_on_side(false, 400 + kw_config.spd_r * 200);
    set_auto_mouse_enable(kw_config.auto_mouse);

    pointing_device_init_user();
}


/* 諸関数 */
#define constrain_hid(amt) ((amt) < -127 ? -127 : ((amt) > 127 ? 127 : (amt)))
// カーソル移動
report_mouse_t pointing_device_cursoring(bool is_left, float x_rev, float y_rev){
    report_mouse_t mouse_report;
    if(is_left){
        x_accumulator_l += x_rev * SENSITIVITY_DIVISOR;
        y_accumulator_l += y_rev * SENSITIVITY_DIVISOR;
        mouse_report.x = (int8_t)constrain_hid(x_accumulator_l);
        mouse_report.y = (int8_t)constrain_hid(y_accumulator_l);
        x_accumulator_l -= mouse_report.x;
        y_accumulator_l -= mouse_report.y;
    }else{
        x_accumulator_r += x_rev * SENSITIVITY_DIVISOR;
        y_accumulator_r += y_rev * SENSITIVITY_DIVISOR;
        mouse_report.x = (int8_t)constrain_hid(x_accumulator_r);
        mouse_report.y = (int8_t)constrain_hid(y_accumulator_r);
        x_accumulator_r -= mouse_report.x;
        y_accumulator_r -= mouse_report.y;
    }

    return mouse_report;
}

// スクロール
report_mouse_t pointing_device_scrolling(bool is_left, float x_rev, float y_rev){
    report_mouse_t mouse_report;
    mouse_report.x = 0;
    mouse_report.y = 0;

    // 斜め成分を消す
    if (abs(x_rev) > abs(y_rev)) {
        y_rev = 0.0;
    } else {
        x_rev = 0.0;
    }

    // スクロール反転処理
    if(!kw_config.inv_sc ){
        x_rev = -1.0 * x_rev;
        y_rev = -1.0 * y_rev;
    }

    // 端数処理
    if(is_left){
        h_accumulator_l += x_rev * SENSITIVITY_DIVISOR / SCROLL_DIVISOR;
        v_accumulator_l += y_rev * SENSITIVITY_DIVISOR / SCROLL_DIVISOR;
        mouse_report.h = (int8_t)constrain_hid(h_accumulator_l);
        mouse_report.v = (int8_t)constrain_hid(v_accumulator_l);
        h_accumulator_l -= mouse_report.h ;
        v_accumulator_l -= mouse_report.v ;
    }else{
        h_accumulator_r += x_rev * SENSITIVITY_DIVISOR / SCROLL_DIVISOR;
        v_accumulator_r += y_rev * SENSITIVITY_DIVISOR / SCROLL_DIVISOR;
        mouse_report.h = (int8_t)constrain_hid(h_accumulator_r);
        mouse_report.v = (int8_t)constrain_hid(v_accumulator_r);
        h_accumulator_r -= mouse_report.h ;
        v_accumulator_r -= mouse_report.v ;
    }

    return mouse_report;
}
// キー入力
report_mouse_t pointing_device_key_input(bool is_left, float x_rev, float y_rev){
    report_mouse_t mouse_report;
    mouse_report.x = 0;
    mouse_report.y = 0;
    mouse_report.h = 0;
    mouse_report.v = 0;

    // 斜めを除外
    if(dpad_exclusion){
        if (abs(x_rev) > abs(y_rev)) {
            y_rev = 0;
        } else {
            x_rev = 0;
        }
    }

    if(is_left){
        // 入力キーの座標指定
        layer = layer_switch_get_layer(key_up_l);
        keycode_up_l = keymap_key_to_keycode(layer, key_up_l);
        keycode_left_l = keymap_key_to_keycode(layer, key_left_l);
        keycode_right_l = keymap_key_to_keycode(layer, key_right_l);
        keycode_down_l = keymap_key_to_keycode(layer, key_down_l);
        // ジョイスティック時は倒している間押しっぱなし
        if(joystick_attached == JOYSTICK_LEFT){
            if(!pressed_left_l && (int16_t)x_rev > KEY_OFFSET){
                pressed_left_l = true;
                register_code(keycode_right_l);
            }else if(pressed_left_l && (int16_t)x_rev  < KEY_OFFSET){
                pressed_left_l = false;
                unregister_code(keycode_right_l);
            }else if(!pressed_right_l && (int16_t)x_rev  < -KEY_OFFSET){
                pressed_right_l = true;
                register_code(keycode_left_l);
            }else if (pressed_right_l && (int16_t)x_rev  > -KEY_OFFSET){
                pressed_right_l = false;
                unregister_code(keycode_left_l);
            }

            if(!pressed_up_l && (int16_t)y_rev > KEY_OFFSET){
                pressed_up_l = true;
                register_code(keycode_down_l);
            }else if(pressed_up_l && (int16_t)y_rev < KEY_OFFSET){
                pressed_up_l = false;
                unregister_code(keycode_down_l);
            }else if(!pressed_down_l && (int16_t)y_rev < -KEY_OFFSET){
                pressed_down_l = true;
                register_code(keycode_up_l);
            }else if(pressed_down_l && (int16_t)y_rev > -KEY_OFFSET){
                pressed_down_l = false;
                unregister_code(keycode_up_l);
            }
        // トラックボール時は単入力を一定時間間隔
        }else if(timer_elapsed(key_timer_l) > TIMEOUT_KEY){
            if((int16_t)x_rev > KEY_OFFSET){
                tap_code16(keycode_right_l);
            }else if((int16_t)x_rev  < -KEY_OFFSET){
                tap_code16(keycode_left_l);
            }

            if((int16_t)y_rev > KEY_OFFSET){
                tap_code16(keycode_down_l);
            }else if((int16_t)y_rev < -KEY_OFFSET){
                tap_code16(keycode_up_l);
            }

            key_timer_l = timer_read();
        }
    }else{
        // 入力キーの座標指定
        layer = layer_switch_get_layer(key_up_r);
        keycode_up_r = keymap_key_to_keycode(layer, key_up_r);
        keycode_left_r = keymap_key_to_keycode(layer, key_left_r);
        keycode_right_r = keymap_key_to_keycode(layer, key_right_r);
        keycode_down_r = keymap_key_to_keycode(layer, key_down_r);

        // ジョイスティック時は倒している間押しっぱなし
        if(joystick_attached == JOYSTICK_RIGHT){
            if(!pressed_left_r && (int16_t)x_rev > KEY_OFFSET){
                pressed_left_r = true;
                register_code(keycode_right_r);
            }else if(pressed_left_r && (int16_t)x_rev < KEY_OFFSET){
                pressed_left_r = false;
                unregister_code(keycode_right_r);
            }else if(!pressed_right_r && (int16_t)x_rev < -KEY_OFFSET){
                pressed_right_r = true;
                register_code(keycode_left_r);
            }else if (pressed_right_r && (int16_t)x_rev > -KEY_OFFSET){
                pressed_right_r = false;
                unregister_code(keycode_left_r);
            }

            if(!pressed_up_r && (int16_t)y_rev > KEY_OFFSET){
                pressed_up_r = true;
                register_code(keycode_down_r);
            }else if(pressed_up_r && (int16_t)y_rev < KEY_OFFSET){
                pressed_up_r = false;
                unregister_code(keycode_down_r);
            }else if(!pressed_down_r && (int16_t)y_rev < -KEY_OFFSET){
                pressed_down_r = true;
                register_code(keycode_up_r);
            }else if(pressed_down_r && (int16_t)y_rev > -KEY_OFFSET){
                pressed_down_r = false;
                unregister_code(keycode_up_r);
            }
        // トラックボール時は単入力を一定時間間隔
        }else if(timer_elapsed(key_timer_r) > TIMEOUT_KEY){
            if((int16_t)x_rev > KEY_OFFSET){
                tap_code16(keycode_right_r);
            }else if((int16_t)x_rev  < -KEY_OFFSET){
                tap_code16(keycode_left_r);
            }

            if((int16_t)y_rev > KEY_OFFSET){
                tap_code16(keycode_down_r);
            }else if((int16_t)y_rev < -KEY_OFFSET){
                tap_code16(keycode_up_r);
            }

            key_timer_r = timer_read();
        }
    }

    return mouse_report;
}
// ゲームパッド
report_mouse_t pointing_device_gaming(bool is_left, int16_t gp28_val, int16_t gp27_val){
    report_mouse_t mouse_report;
    mouse_report.x = 0;
    mouse_report.y = 0;
    mouse_report.h = 0;
    mouse_report.v = 0;

    // 初期偏差の計算
    float x_val = (float)(gp28_val - gp28_newt);
    float y_val = (float)(gp27_val - gp27_newt);

    // --- X軸のデッドゾーン処理 ---
    if (abs(gp28_val - gp28_newt) < joystick_offset_min) {
        x_val = 0.0f;
    } else {
        if(gp28_val > gp28_newt){
            x_val = (float)(gp28_val - (gp28_newt + joystick_offset_min));
            float span = (float)(gp28_max - joystick_offset_max - (gp28_newt + joystick_offset_min));
            x_val = (span > 0) ? (x_val / span * 511.0f) : 0.0f;
        } else {
            x_val = (float)(gp28_val - (gp28_newt - joystick_offset_min));
            float span = (float)((gp28_newt - joystick_offset_min) - (gp28_min + joystick_offset_max));
            x_val = (span > 0) ? (x_val / span * 511.0f) : 0.0f;
        }
    }

    // --- Y軸のデッドゾーン処理 ---
    if (abs(gp27_val - gp27_newt) < joystick_offset_min) {
        y_val = 0.0f;
    } else {
        if(gp27_val > gp27_newt){
            y_val = (float)(gp27_val - (gp27_newt + joystick_offset_min));
            float span = (float)(gp27_max - joystick_offset_max - (gp27_newt + joystick_offset_min));
            y_val = (span > 0) ? (y_val / span * 511.0f) : 0.0f;
        } else {
            y_val = (float)(gp27_val - (gp27_newt - joystick_offset_min));
            float span = (float)((gp27_newt - joystick_offset_min) - (gp27_min + joystick_offset_max));
            y_val = (span > 0) ? (y_val / span * 511.0f) : 0.0f;
        }
    }

    // 軸の制限 (念のためオーバーフロー防止)
    x_val = fminf(fmaxf(x_val, -512.0f), 511.0f);
    y_val = fminf(fmaxf(y_val, -512.0f), 511.0f);

    float rad;
    float x_rev;
    float y_rev;

    // 角度と反転の適用
    float current_angle = is_left ? (float)kw_config.angle_l : (float)kw_config.angle_r;
    bool is_inv = is_left ? kw_config.inv_l : kw_config.inv_r;

    rad = current_angle * 12.0f * (M_PI / 180.0f) * -1.0f;
    x_rev = x_val * cosf(rad) - y_val * sinf(rad);
    y_rev = x_val * sinf(rad) + y_val * cosf(rad);

    if(is_inv){
        x_rev = -x_rev;
    }

    // ドリフト防止の最終ダメ押し（非常に小さい値は0にする）
    if (fabsf(x_rev) < 0.01f) x_rev = 0.0f;
    if (fabsf(y_rev) < 0.01f) y_rev = 0.0f;

    joystick_set_axis(0, (int16_t)x_rev);
    joystick_set_axis(1, (int16_t)y_rev);

    return mouse_report;
}
// 実タスク
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    // ジョイスティックの値
    float x_val_js = 0.0;
    float y_val_js = 0.0;
    int16_t gp28_val = 0;
    int16_t gp27_val = 0;
    if((bool)joystick_attached){
        // amprifier値決定
        float amp_temp = 1.0;
        if(joystick_attached == JOYSTICK_LEFT){
            if(slow_mode){
                amp_temp = AMP_SLOW;
            }else{
                amp_temp = 16.0 + (float)kw_config.spd_l * 3.0;
            }
            switch (kw_config.pd_mode_l){
                case KEY_INPUT:
                    amp_temp = amp_temp / 10;
                    break;
                case CURSOR_MODE:
                    amp_temp = amp_temp / 20;
                    break;
                case SCROLL_MODE:
                    amp_temp = amp_temp / 30;
                    break;
            }
        }else if(joystick_attached == JOYSTICK_RIGHT){
            if(slow_mode){
                amp_temp = AMP_SLOW;
            }else{
                amp_temp = 16.0 + (float)kw_config.spd_r * 3.0;
            }
            switch (kw_config.pd_mode_r){
                case KEY_INPUT:
                    amp_temp = amp_temp / 10;
                    break;
                case CURSOR_MODE:
                    amp_temp = amp_temp / 20;
                    break;
                case SCROLL_MODE:
                    amp_temp = amp_temp / 30;
                    break;
            }
        }
        // 数値の取得
                gp28_val = analogReadPin(GP28);
                gp27_val = analogReadPin(GP27);

                // --- ジョイスティック側のドリフト対策 (アナログデッドゾーン) ---
                int16_t temp_x_raw = gp28_val - gp28_newt;
                int16_t temp_y_raw = gp27_val - gp27_newt;
                int16_t temp_x_val = 0;
                int16_t temp_y_val = 0;

                // X軸のデッドゾーン判定
                if (abs(temp_x_raw) > joystick_offset_min) {
                    temp_x_val = (temp_x_raw > 0) ? (temp_x_raw - joystick_offset_min) : (temp_x_raw + joystick_offset_min);
                }
                // Y軸のデッドゾーン判定
                if (abs(temp_y_raw) > joystick_offset_min) {
                    temp_y_val = (temp_y_raw > 0) ? (temp_y_raw - joystick_offset_min) : (temp_y_raw + joystick_offset_min);
                }

                // 最大値最小値の更新（ここも少し遊びを持たせる）
                if(gp28_val > gp28_max) gp28_max = gp28_val;
                else if(gp28_val < gp28_min) gp28_min = gp28_val;
                if(gp27_val > gp27_max) gp27_max = gp27_val;
                else if(gp27_val < gp27_min) gp27_min = gp27_val;

                // 計算された値を使用
                x_val_js = ( (float)temp_x_val / JOYSTICK_DIVISOR ) * amp_temp;
                y_val_js = ( (float)temp_y_val / JOYSTICK_DIVISOR ) * amp_temp;
            }

    // --- トラックボール側のドリフト対策 (生値のカット) ---
        // PMW33xxなどのセンサーが吐き出す微小な「1」カウントのノイズを消去します
        #define TRACKBALL_DEADZONE 1 // 1〜2程度が推奨

        if (abs(left_report.x) <= TRACKBALL_DEADZONE) left_report.x = 0;
        if (abs(left_report.y) <= TRACKBALL_DEADZONE) left_report.y = 0;
        if (abs(right_report.x) <= TRACKBALL_DEADZONE) right_report.x = 0;
        if (abs(right_report.y) <= TRACKBALL_DEADZONE) right_report.y = 0;

    // マウスの数値はそのまま使う
    float x_val_l = 0.0;
    float y_val_l = 0.0;
    float x_val_r = 0.0;
    float y_val_r = 0.0;

    if(joystick_attached == JOYSTICK_LEFT){
        x_val_l = x_val_js;
        y_val_l = y_val_js;
        x_val_r = (float)right_report.x;
        y_val_r = (float)right_report.y;
    }else if(joystick_attached == JOYSTICK_RIGHT){
        x_val_l = (float)left_report.x;
        y_val_l = (float)left_report.y;
        x_val_r = x_val_js;
        y_val_r = y_val_js;
    }else{
        x_val_l = (float)left_report.x;
        y_val_l = (float)left_report.y;
        x_val_r = (float)right_report.x;
        y_val_r = (float)right_report.y;
    }

    // 角度補正
    float rad = (float)kw_config.angle_l * 12.0 * (M_PI / 180.0) * -1.0;
    float x_rev_l =  + x_val_l * cos(rad) - y_val_l * sin(rad);
    float y_rev_l =  + x_val_l * sin(rad) + y_val_l * cos(rad);
    rad = (float)kw_config.angle_r * 12.0 * (M_PI / 180.0) * -1.0;
    float x_rev_r =  + x_val_r * cos(rad) - y_val_r * sin(rad);
    float y_rev_r =  + x_val_r * sin(rad) + y_val_r * cos(rad);

    // 前回移動量を参照して補正
    float smoothed_x_l = prev_x_l * SMOOTHING_FACTOR + x_rev_l * (1.0 - SMOOTHING_FACTOR);
    float smoothed_y_l = prev_y_l * SMOOTHING_FACTOR + y_rev_l * (1.0 - SMOOTHING_FACTOR);
    prev_x_l = smoothed_x_l;
    prev_y_l = smoothed_y_l;
    float smoothed_x_r = prev_x_r * SMOOTHING_FACTOR + x_rev_r * (1.0 - SMOOTHING_FACTOR);
    float smoothed_y_r = prev_y_r * SMOOTHING_FACTOR + y_rev_r * (1.0 - SMOOTHING_FACTOR);
    prev_x_r = smoothed_x_r;
    prev_y_r = smoothed_y_r;

    // 動作量で移動量を変える
    float movement_magnitude_l = sqrt(smoothed_x_l * smoothed_x_l + smoothed_y_l * smoothed_y_l);
    float dynamic_multiplier_l = 1.0 + movement_magnitude_l / 10.0;
    dynamic_multiplier_l = fmin(fmax(dynamic_multiplier_l, 0.5), 3.0);
    x_rev_l *= SENSITIVITY_MULTIPLIER * dynamic_multiplier_l;
    y_rev_l *= SENSITIVITY_MULTIPLIER * dynamic_multiplier_l;
    float movement_magnitude_r = sqrt(smoothed_x_r * smoothed_x_r + smoothed_y_r * smoothed_y_r);
    float dynamic_multiplier_r = 1.0 + movement_magnitude_r / 10.0;
    dynamic_multiplier_r = fmin(fmax(dynamic_multiplier_r, 0.5), 3.0);
    x_rev_r *= SENSITIVITY_MULTIPLIER * dynamic_multiplier_r;
    y_rev_r *= SENSITIVITY_MULTIPLIER * dynamic_multiplier_r;

    // x軸反転処理
    if(kw_config.inv_l){ x_rev_l = -1.0 * x_rev_l; }
    if(kw_config.inv_r){ x_rev_r = -1.0 * x_rev_r; }

    /* 数値処理 */
    // ジョイスティック側だけ一時的モード変更
    uint8_t forced = 0;
    if(force_gaming){
        if(joystick_attached == JOYSTICK_LEFT){
            left_report = pointing_device_gaming(true, gp28_val, gp27_val);
            forced = JOYSTICK_LEFT;
        }else if(joystick_attached == JOYSTICK_RIGHT){
            right_report = pointing_device_gaming(false, gp28_val, gp27_val);
            forced = JOYSTICK_RIGHT;
        }
    }
    // 一時的モード変更
    if(force_cursoring){
        left_report = pointing_device_cursoring(true, x_rev_l, y_rev_l);
        right_report = pointing_device_cursoring(false, x_rev_r, y_rev_r);
    }else if(force_scrolling){
        left_report = pointing_device_scrolling(true, x_rev_l, y_rev_l);
        right_report = pointing_device_scrolling(false, x_rev_r, y_rev_r);
    }else if(force_key_input){
        left_report = pointing_device_key_input(true, x_rev_l, y_rev_l);
        right_report = pointing_device_key_input(false, x_rev_r, y_rev_r);
    }else{
        // 左手処理
        if (forced != JOYSTICK_LEFT){
            if(kw_config.pd_mode_l == CURSOR_MODE){
                left_report = pointing_device_cursoring(true, x_rev_l, y_rev_l);
            }else if(kw_config.pd_mode_l == SCROLL_MODE){
                left_report = pointing_device_scrolling(true, x_rev_l, y_rev_l);
            }else if(kw_config.pd_mode_l == KEY_INPUT){
                left_report = pointing_device_key_input(true, x_rev_l, y_rev_l);
            }else if(kw_config.pd_mode_l == GAME_MODE){
                left_report = pointing_device_gaming(true, gp28_val, gp27_val);
            }
        }
        // 右手処理
        if (forced != JOYSTICK_RIGHT){
            if(kw_config.pd_mode_r == CURSOR_MODE){
                right_report = pointing_device_cursoring(false, x_rev_r, y_rev_r);
            }else if(kw_config.pd_mode_r == SCROLL_MODE){
                right_report = pointing_device_scrolling(false, x_rev_r, y_rev_r);
            }else if(kw_config.pd_mode_r == KEY_INPUT){
                right_report = pointing_device_key_input(false, x_rev_r, y_rev_r);
            }else if(kw_config.pd_mode_r == GAME_MODE){
                right_report = pointing_device_gaming(false, gp28_val, gp27_val);
            }
        }
    }

    return pointing_device_combine_reports(left_report, right_report);
}

/* OLED */
// 初期化
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    // 追加OLED初期化
    oled_init_addedoled();

    return oled_init_user(rotation);
}
// 実タスク
bool oled_task_kb(void) {
    // 追加OLEDタスク
    oled_task_addedoled();

    return oled_task_user();
}

/* 諸関数 */
// モードチェンジ時端数削除
void clear_keyinput(void){
    unregister_code(keycode_up_l);
    unregister_code(keycode_down_l);
    unregister_code(keycode_left_l);
    unregister_code(keycode_right_l);
    x_accumulator_l = 0.0;
    y_accumulator_l = 0.0;
    v_accumulator_l = 0.0;
    h_accumulator_l = 0.0;
    unregister_code(keycode_up_r);
    unregister_code(keycode_down_r);
    unregister_code(keycode_left_r);
    unregister_code(keycode_right_r);
    x_accumulator_r = 0.0;
    y_accumulator_r = 0.0;
    v_accumulator_r = 0.0;
    h_accumulator_r = 0.0;
}
/* インターフェース */
void reset_joystick(void){
    gp27_newt = analogReadPin(GP27);
    gp28_newt = analogReadPin(GP28);
    gp27_min = gp27_newt;
    gp28_min = gp28_newt;
    gp27_max = gp27_newt;
    gp28_max = gp28_newt;
    joystick_offset_min = JOYSTICK_OFFSET_MIN_DEFAULT;
    joystick_offset_max = JOYSTICK_OFFSET_MAX_DEFAULT;
}

// ジョイスティックの有無
uint8_t get_joystick_attached(void){ return joystick_attached; }

uint16_t get_joystick_offset_min(void){
    return joystick_offset_min;
}
uint16_t get_joystick_offset_max(void){
    return joystick_offset_max;
}
void set_joystick_offset_min(uint16_t min){
    joystick_offset_min = min;
}
void set_joystick_offset_max(uint16_t max){
    joystick_offset_max = max;
}
// モード変更
void cycle_mode_l(void){
    if(joystick_attached == JOYSTICK_LEFT){
        kw_config.pd_mode_l = (kw_config.pd_mode_l + 1) % 4;
    }else{
        kw_config.pd_mode_l = (kw_config.pd_mode_l + 1) % 3;
    }
    eeconfig_update_kb(kw_config.raw);
    clear_keyinput();
}
void cycle_mode_r(void){
    if(joystick_attached == JOYSTICK_RIGHT){
        kw_config.pd_mode_r = (kw_config.pd_mode_r + 1) % 4;
    }else{
        kw_config.pd_mode_r = (kw_config.pd_mode_r + 1) % 3;
    }
    eeconfig_update_kb(kw_config.raw);
    clear_keyinput();
}
// 一時的モード変更
void is_scroll_mode(bool is_force_scrolling){
    force_scrolling = is_force_scrolling;
    clear_keyinput();
}
void is_cursor_mode(bool is_force_cursoring){
    force_cursoring = is_force_cursoring;
    clear_keyinput();
}
void is_key_mode(bool is_force_key_input){
    force_key_input = is_force_key_input;
    clear_keyinput();
}
void is_game_mode(bool is_force_gaming){
    force_gaming = is_force_gaming;
    clear_keyinput();
}
void is_slow_mode(bool is_slow_mode){
    slow_mode = is_slow_mode;
    if(is_slow_mode){
        pointing_device_set_cpi_on_side(true,  CPI_SLOW);
        pointing_device_set_cpi_on_side(false, CPI_SLOW);
    }else{
        pointing_device_set_cpi_on_side(true,  400 + kw_config.spd_l * 200);
        pointing_device_set_cpi_on_side(false, 400 + kw_config.spd_r * 200);
    }
    clear_keyinput();
}

bool get_dpad_exclusion(void){
    return dpad_exclusion;
}
void toggle_dpad_exclusion(void){
    dpad_exclusion = !dpad_exclusion;
}
