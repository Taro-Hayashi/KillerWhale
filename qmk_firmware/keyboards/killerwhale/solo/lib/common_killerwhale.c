// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lib/common_killerwhale.h"
#include "analog.h"
#include "math.h"
#include "joystick.h"
#include "lib/add_keycodes.h"
#include "lib/add_oled.h"

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_VIRTUAL,
    JOYSTICK_AXIS_VIRTUAL
};

// ポインティングデバイス用変数
kw_config_t kw_config;      // eeprom保存用
bool force_scrolling, force_cursoring, force_key_input, force_gaming, slow_mode;   // 一時的モード変更用
bool joystick_attached;     // ジョイスティックの有無
float prev_x, prev_y;
float x_accumulator, y_accumulator, h_accumulator, v_accumulator; // 端数保存用
int16_t gp27_newt, gp28_newt; // ジョイスティックの初期値
int16_t gp27_max, gp28_max, gp27_min, gp28_min; // ジョイスティックの最大値、最小値
uint16_t joystick_offset_min, joystick_offset_max; // ジョイスティックの小さい値、大きい値を無視する範囲

// 仮想十字キー設定用変数
keypos_t key_up, key_left, key_right, key_down;
bool pressed_up, pressed_down, pressed_left, pressed_right;
int8_t layer;
int16_t keycode_up, keycode_down, keycode_left, keycode_right, key_timer;

// 十字キー排他設定変数
uint8_t dpad_pressed;

/* eeprom */
// 初期化
void eeconfig_init_kb(void) {
    kw_config.spd = SPD_DEFAULT;
    if(gpio_read_pin(GP10)){
        kw_config.angle = ANGLE_DEFAULT_RIGHT;
    }else {
        kw_config.angle = ANGLE_DEFAULT_LEFT;
    }
    kw_config.rgb_layers = RGB_LAYER_DEFAULT;
    kw_config.pd_mode = MODE_DEFAULT;
    kw_config.inv = INVERT_DEFAULT;
    kw_config.inv_sc = INVERT_SCROLL_DEFAULT;
    kw_config.auto_mouse = AUTO_MOUSE_DEFAULT;
    kw_config.oled_mode = OLED_DEFAULT;
    kw_config.dpad_exclusion = DPAD_EX_DEFAULT ;
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
    keypos_t key = record->event.key;
    if(key.col == 6 && kw_config.dpad_exclusion){
        switch (key.row){
            case 1:
            case 2:
            case 3:
            case 4:
                if(dpad_pressed == 0 && record->event.pressed){
                    if(record->event.pressed){
                        dpad_pressed = key.row;
                    }
                }else if(dpad_pressed == key.row && !record->event.pressed){
                    dpad_pressed = 0;
                }else if(record->event.pressed){
                    return false;
                }
        }
    }

    return process_record_user(keycode, record);
}

/* マトリクス走査 */
// 初期化
void matrix_init_kb(void) {
    key_up.row = 3;
    key_up.col = 6;
    key_left.row = 2;
    key_left.col = 6;
    key_right.row = 4;
    key_right.col = 6;
    key_down.row = 1;
    key_down.col = 6;
    pressed_up = false;
    pressed_down = false;
    pressed_left = false;
    pressed_right = false;
    dpad_pressed = 0;
    force_scrolling = false;
    force_cursoring = false;
    force_key_input = false;
    force_gaming = false;
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
        joystick_attached = true;
    }
    key_timer = timer_read();

    matrix_init_user();
}

/* カーソル操作 */
// 初期化
void pointing_device_init_kb(void){
    kw_config.raw = eeconfig_read_kb();
    x_accumulator = 0.0;
    y_accumulator = 0.0;
    h_accumulator = 0.0;
    v_accumulator = 0.0;
    prev_x = 0.0;
    prev_y = 0.0;
    pointing_device_set_cpi(400 + kw_config.spd * 200);
    set_auto_mouse_enable(kw_config.auto_mouse);

    pointing_device_init_user();
}

/* 諸関数 */
#define constrain_hid(amt) ((amt) < -127 ? -127 : ((amt) > 127 ? 127 : (amt)))
// カーソル移動
report_mouse_t pointing_device_cursoring(float x_rev, float y_rev){
    report_mouse_t mouse_report;
    x_accumulator += x_rev * SENSITIVITY_DIVISOR;
    y_accumulator += y_rev * SENSITIVITY_DIVISOR;
    mouse_report.x = (int8_t)constrain_hid(x_accumulator);
    mouse_report.y = (int8_t)constrain_hid(y_accumulator);
    x_accumulator -= mouse_report.x;
    y_accumulator -= mouse_report.y;

    return mouse_report;
}
// スクロール
report_mouse_t pointing_device_scrolling(float x_rev, float y_rev){
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
    h_accumulator += x_rev * SENSITIVITY_DIVISOR / SCROLL_DIVISOR;
    v_accumulator += y_rev * SENSITIVITY_DIVISOR / SCROLL_DIVISOR;
    mouse_report.h = (int8_t)constrain_hid(h_accumulator);
    mouse_report.v = (int8_t)constrain_hid(v_accumulator);
    h_accumulator -= mouse_report.h;
    v_accumulator -= mouse_report.v;

    return mouse_report;
}
// キー入力
report_mouse_t pointing_device_key_input(float x_rev, float y_rev){
    report_mouse_t mouse_report;
    // 入力キーの座標指定
    mouse_report.x = 0;
    mouse_report.y = 0;
    mouse_report.h = 0;
    mouse_report.v = 0;
    layer = layer_switch_get_layer(key_up);
    keycode_up = keymap_key_to_keycode(layer, key_up);
    keycode_left = keymap_key_to_keycode(layer, key_left);
    keycode_right = keymap_key_to_keycode(layer, key_right);
    keycode_down = keymap_key_to_keycode(layer, key_down);

    // 斜めを除外
    if(kw_config.dpad_exclusion){
        if (abs(x_rev) > abs(y_rev)) {
            y_rev = 0;
        } else {
            x_rev = 0;
        }
    }

    // ジョイスティック時は倒している間押しっぱなし
    if(joystick_attached){
        if(!pressed_left && (int16_t)x_rev > KEY_OFFSET){
            pressed_left = true;
            register_code(keycode_right);
        }else if(pressed_left && (int16_t)x_rev  < KEY_OFFSET){
            pressed_left = false;
            unregister_code(keycode_right);
        }else if(!pressed_right && (int16_t)x_rev  < -KEY_OFFSET){
            pressed_right = true;
            register_code(keycode_left);
        }else if (pressed_right && (int16_t)x_rev  > -KEY_OFFSET){
            pressed_right = false;
            unregister_code(keycode_left);
        }

        if(!pressed_up && (int16_t)y_rev > KEY_OFFSET){
            pressed_up = true;
            register_code(keycode_down);
        }else if(pressed_up && (int16_t)y_rev < KEY_OFFSET){
            pressed_up = false;
            unregister_code(keycode_down);
        }else if(!pressed_down && (int16_t)y_rev < -KEY_OFFSET){
            pressed_down = true;
            register_code(keycode_up);
        }else if(pressed_down && (int16_t)y_rev > -KEY_OFFSET){
            pressed_down = false;
            unregister_code(keycode_up);
        }
    // トラックボール時は単入力を一定時間間隔
    }else if(timer_elapsed(key_timer) > TIMEOUT_KEY){
        if((int16_t)x_rev > KEY_OFFSET){
            tap_code16(keycode_right);
        }else if((int16_t)x_rev  < -KEY_OFFSET){
            tap_code16(keycode_left);
        }

        if((int16_t)y_rev > KEY_OFFSET){
            tap_code16(keycode_down);
        }else if((int16_t)y_rev < -KEY_OFFSET){
            tap_code16(keycode_up);
        }

        key_timer = timer_read();
    }

    return mouse_report;
}
// ゲームパッド
report_mouse_t pointing_device_gaming(int16_t gp28_val, int16_t gp27_val){
    report_mouse_t mouse_report;
    mouse_report.x = 0;
    mouse_report.y = 0;
    mouse_report.h = 0;
    mouse_report.v = 0;

    float x_val = 0.0f;
    float y_val = 0.0f;

    // --- X軸（GP28）の処理 ---
    if (abs(gp28_val - gp28_newt) < joystick_offset_min) {
        x_val = 0.0f;
    } else {
        if (gp28_val > gp28_newt) {
            // 右方向
            float span = (float)(gp28_max - joystick_offset_max - (gp28_newt + joystick_offset_min));
            x_val = (span > 0) ? (float)(gp28_val - (gp28_newt + joystick_offset_min)) / span * 511.0f : 0.0f;
        } else {
            // 左方向
            float span = (float)((gp28_newt - joystick_offset_min) - (gp28_min + joystick_offset_max));
            x_val = (span > 0) ? (float)(gp28_val - (gp28_newt - joystick_offset_min)) / span * 511.0f : 0.0f;
        }
    }

    // --- Y軸（GP27）の処理 ---
    if (abs(gp27_val - gp27_newt) < joystick_offset_min) {
        y_val = 0.0f;
    } else {
        if (gp27_val > gp27_newt) {
            // 上方向
            float span = (float)(gp27_max - joystick_offset_max - (gp27_newt + joystick_offset_min));
            y_val = (span > 0) ? (float)(gp27_val - (gp27_newt + joystick_offset_min)) / span * 511.0f : 0.0f;
        } else {
            // 下方向
            float span = (float)((gp27_newt - joystick_offset_min) - (gp27_min + joystick_offset_max));
            y_val = (span > 0) ? (float)(gp27_val - (gp27_newt - joystick_offset_min)) / span * 511.0f : 0.0f;
        }
    }

    // 角度補正の計算
    float rad = (float)kw_config.angle * 6.0f * (M_PI / 180.0f) * -1.0f;
    float x_rev = x_val * cosf(rad) - y_val * sinf(rad);
    float y_rev = x_val * sinf(rad) + y_val * cosf(rad);

    // X軸反転
    if (kw_config.inv) {
        x_rev = -x_rev;
    }

    // ドリフト防止の最終カットオフ（計算誤差用）
    if (fabsf(x_rev) < 0.1f) x_rev = 0.0f;
    if (fabsf(y_rev) < 0.1f) y_rev = 0.0f;

    joystick_set_axis(0, (int16_t)x_rev);
    joystick_set_axis(1, (int16_t)y_rev);

    return mouse_report;
}
// 実タスク
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    float x_val = 0.0;
    float y_val = 0.0;
    int16_t gp28_val = 0;
    int16_t gp27_val = 0;


    // --- ドリフト対策用定数 ---
        #define TRACKBALL_DEADZONE 1  // マウスの1ピクセル移動を無視（1〜2で調整）
        #define JS_SMOOTH_CUTOFF 0.01f // ジョイスティック計算後の微小値をカット

        // ジョイスティックの場合は定期的に値を取り出す
            if(joystick_attached){
                float amp_temp = 1.0;
                // (amp_temp の計算ロジックは変更なし)
                if(slow_mode){
                    amp_temp = AMP_SLOW;
                }else{
                    amp_temp = 4.0 + (float)kw_config.spd * 3.0;
                }
                switch (kw_config.pd_mode){
                    case KEY_INPUT:   amp_temp /= 10; break;
                    case CURSOR_MODE: amp_temp /= 20; break;
                    case SCROLL_MODE: amp_temp /= 50; break;
                }

                gp28_val = analogReadPin(GP28);
                gp27_val = analogReadPin(GP27);

                // 偏差の計算
                int16_t js_x_raw = gp28_val - gp28_newt;
                int16_t js_y_raw = gp27_val - gp27_newt;

                // 最大最小更新
                if(gp28_val > gp28_max) gp28_max = gp28_val;
                else if(gp28_val < gp28_min) gp28_min = gp28_val;
                if(gp27_val > gp27_max) gp27_max = gp27_val;
                else if(gp27_val < gp27_min) gp27_min = gp27_val;

                // 【修正】ジョイスティックのデッドゾーンと蓄積クリア
                if(abs(js_x_raw) < joystick_offset_min){
                    x_val = 0.0f;
                    x_accumulator = 0; // 静止時は端数を捨てる
                } else {
                    // 閾値を超えた分だけを計算に回す（スムーズな動き出し）
                    int16_t adjusted_x = (js_x_raw > 0) ? (js_x_raw - joystick_offset_min) : (js_x_raw + joystick_offset_min);
                    x_val = ( (float)adjusted_x / JOYSTICK_DIVISOR ) * amp_temp;
                }

                if(abs(js_y_raw) < joystick_offset_min){
                    y_val = 0.0f;
                    y_accumulator = 0; // 静止時は端数を捨てる
                } else {
                    int16_t adjusted_y = (js_y_raw > 0) ? (js_y_raw - joystick_offset_min) : (js_y_raw + joystick_offset_min);
                    y_val = ( (float)adjusted_y / JOYSTICK_DIVISOR ) * amp_temp;
                }

                // 計算誤差のカット
                if (fabsf(x_val) < JS_SMOOTH_CUTOFF) x_val = 0.0f;
                if (fabsf(y_val) < JS_SMOOTH_CUTOFF) y_val = 0.0f;

            // マウスの時は数値はそのまま使う
            }else{
                // 【修正】マウスの生値に対するデッドゾーン（ドリフト防止の肝）
                if (abs(mouse_report.x) <= TRACKBALL_DEADZONE) mouse_report.x = 0;
                if (abs(mouse_report.y) <= TRACKBALL_DEADZONE) mouse_report.y = 0;

                x_val = (float)mouse_report.x;
                y_val = (float)mouse_report.y;
            }
    // 角度補正
    float rad = (float)kw_config.angle * 6.0 * (M_PI / 180.0) * -1.0;
    float x_rev =  + x_val * cos(rad) - y_val * sin(rad);
    float y_rev =  + x_val * sin(rad) + y_val * cos(rad);

    // 前回移動量を参照して補正
    float smoothed_x = prev_x * SMOOTHING_FACTOR + x_rev * (1.0 - SMOOTHING_FACTOR);
    float smoothed_y = prev_y * SMOOTHING_FACTOR + y_rev * (1.0 - SMOOTHING_FACTOR);

    // 【追加】極低速時のドリフトをカット
        if (fabsf(smoothed_x) < 0.05f) smoothed_x = 0.0f;
        if (fabsf(smoothed_y) < 0.05f) smoothed_y = 0.0f;
    prev_x = smoothed_x;
    prev_y = smoothed_y;

    // 動作量で移動量を変える
    float movement_magnitude = sqrt(smoothed_x * smoothed_x + smoothed_y * smoothed_y);
    float dynamic_multiplier = 1.0 + movement_magnitude / 10.0;
    dynamic_multiplier = fmin(fmax(dynamic_multiplier, 0.5), 3.0);
    x_rev *= SENSITIVITY_MULTIPLIER * dynamic_multiplier;
    y_rev *= SENSITIVITY_MULTIPLIER * dynamic_multiplier;

    // x軸反転処理
    if(kw_config.inv){
            x_rev = -1 * x_rev;
    }

    if(force_cursoring){
        mouse_report = pointing_device_cursoring(x_rev, y_rev);
    }else if(force_scrolling){
        mouse_report = pointing_device_scrolling(x_rev, y_rev);
    }else if(force_key_input){
        mouse_report = pointing_device_key_input(x_rev, y_rev);
    }else if(force_gaming){
        mouse_report = pointing_device_gaming(gp28_val, gp27_val);
    }else if(kw_config.pd_mode == CURSOR_MODE){
        mouse_report = pointing_device_cursoring(x_rev, y_rev);
    }else if(kw_config.pd_mode == SCROLL_MODE){
        mouse_report = pointing_device_scrolling(x_rev, y_rev);
    }else if(kw_config.pd_mode == KEY_INPUT){
        mouse_report = pointing_device_key_input(x_rev, y_rev);
    }else if(kw_config.pd_mode == GAME_MODE){
        mouse_report = pointing_device_gaming(gp28_val, gp27_val);
    }

    return pointing_device_task_user(mouse_report);
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
    unregister_code(keycode_up);
    unregister_code(keycode_down);
    unregister_code(keycode_left);
    unregister_code(keycode_right);
    x_accumulator = 0.0;
    y_accumulator = 0.0;
    v_accumulator = 0.0;
    h_accumulator = 0.0;
    prev_x = 0.0;
    prev_y = 0.0;
}

/* インターフェース */
// ジョイスティックの初期化
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
bool get_joystick_attached(void){ return joystick_attached; }
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
void cycle_mode(void){
    if(joystick_attached){
        kw_config.pd_mode = (kw_config.pd_mode + 1) % 4;
    }else{
        kw_config.pd_mode = (kw_config.pd_mode + 1) % 3;
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
                pointing_device_set_cpi(CPI_SLOW);
    }else{
                pointing_device_set_cpi(400 + kw_config.spd * 200);
    }
    clear_keyinput();
}
