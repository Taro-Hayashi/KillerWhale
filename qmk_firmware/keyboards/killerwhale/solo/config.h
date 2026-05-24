// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#define KEY_INPUT 0
#define CURSOR_MODE 1
#define SCROLL_MODE 2
#define GAME_MODE 3
#define SHOW_LAYER 0
#define SHOW_STATS 1
#define TURN_OFF 2






//////////////////////
/*    ユーザー設定    */
//////////////////////

// 入力モードデフォルト
// KEY_INPUT / CURSOR_MODE / SCROLL_MODE
#define MODE_DEFAULT CURSOR_MODE

// CPI = 400 + spd * 200 / AMP = 4.0 + (double)spd * 3.0
#define SPD_OPTION_MAX 15 // 固定: 最大値
#define SPD_DEFAULT 5

// 角度 = angle * 6
#define ANGLE_OPTION_MAX 59 // 固定: 最大値
#define ANGLE_DEFAULT_LEFT  16 // 左手の場合のデフォルト
#define ANGLE_DEFAULT_RIGHT 15 // 右手の場合のデフォルト

#define INVERT_DEFAULT true            // X軸の反転
#define INVERT_SCROLL_DEFAULT false    // スクロールの反転

// 移動量が小さい時の調節
#define SENSITIVITY_MULTIPLIER 1.1 // 一時的倍率
#define SENSITIVITY_DIVISOR 0.5    // 最終的な感度調整
#define SMOOTHING_FACTOR 0.7 // 前の動きの影響度

// スローモード時カーソル速度
#define CPI_SLOW 300
#define AMP_SLOW 4.0

// オートマウスの設定
#define AUTO_MOUSE_DEFAULT true     // デフォルトのオン/オフ
#define AUTO_MOUSE_DEFAULT_LAYER 7  // 使用レイヤー
#define AUTO_MOUSE_THRESHOLD 80     // オートマウスが反応する移動量
#define AUTO_MOUSE_TIME  750        // レイヤー切り替え時間
#define AUTO_MOUSE_DEBOUNCE 40      // 再度オートマウスさせるまでの時間
#define AUTO_MOUSE_DELAY 750        // 一般ボタン使用時のオートマウスオフ時間


#define NO_JOYSTICK_VAL 100         // ジョイスティックの有無判定閾値
#define JOYSTICK_OFFSET_MIN_DEFAULT 70 // ジョイスティックの小さい値を無視する範囲 最大200
#define JOYSTICK_OFFSET_MAX_DEFAULT 0 // ジョイスティックの大きい値を無視する範囲 最大200
#define JOYSTICK_DIVISOR 40.0       // ジョイスティック用調整用

#define SCROLL_DIVISOR 100.0        // スクロール用数値調整

#define KEY_OFFSET 5                // キー入力閾値
#define TIMEOUT_KEY 50              // キー入力間隔

// OLED設定
// SHOW_LAYER / SHOW_STATS / TURN_OFF
#define OLED_DEFAULT SHOW_LAYER
#define INTERRUPT_TIME 600          // OLED割り込み時間

// RGBレイヤーデフォルト
#define RGB_LAYER_DEFAULT true

// 一時的モード変更タップ判定ms
#define TERM_TEMP 100

// 斜め入力防止のデフォルト
#define DPAD_EX_DEFAULT true








/* ハードウェア設定（変更不要） */
// SPI SETTINGS
#define PMW33XX_CS_PIN  GP0
#define SPI_SCK_PIN GP18
#define SPI_MISO_PIN GP16
#define SPI_MOSI_PIN GP19
// I2C SETTINGS
#define I2C_DRIVER I2CD0
#define I2C1_SCL_PIN        GP9
#define I2C1_SDA_PIN        GP8
#define OLED_FONT_H "./lib/glcdfont.c"
// AUTO MOUSE
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
// JOYSTICK
#define JOYSTICK_AXIS_COUNT 2
#define JOYSTICK_AXIS_RESOLUTION 10
// RGBLIGHT LAYERS
#define RGBLIGHT_LAYERS_RETAIN_VAL
