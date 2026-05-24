// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "lib/common_killerwhale.h"

// レイヤーごとの発光場所、発光色の設定
const rgblight_segment_t PROGMEM base_layer[] = RGBLIGHT_LAYER_SEGMENTS( { 0, 0, HSV_YELLOW} );
const rgblight_segment_t PROGMEM onoff_layer[] = RGBLIGHT_LAYER_SEGMENTS( { 0, 66, HSV_YELLOW} );
const rgblight_segment_t PROGMEM offon_layer[] = RGBLIGHT_LAYER_SEGMENTS( { 0, 66, HSV_MAGENTA} );
const rgblight_segment_t PROGMEM onon_layer[] = RGBLIGHT_LAYER_SEGMENTS( { 0, 66, HSV_WHITE} );
const rgblight_segment_t PROGMEM lower_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 66, HSV_BLUE} );
const rgblight_segment_t PROGMEM upper_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 66, HSV_CYAN} );
const rgblight_segment_t PROGMEM util_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 66, HSV_CORAL} );
const rgblight_segment_t PROGMEM mouse_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 66, HSV_AZURE} );
const rgblight_segment_t PROGMEM ball_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 66, HSV_GREEN} );
const rgblight_segment_t PROGMEM light_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 66, HSV_PINK} );

// レイヤーごとの発光方法の指定
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    base_layer,
    onoff_layer,
    offon_layer,
    onon_layer,
    lower_layer,
    upper_layer,
    util_layer,
    mouse_layer,
    ball_layer,
    light_layer
);

// 初期化
void keyboard_post_init_kb(void) {
    rgblight_layers = my_rgb_layers;
}

// 発光条件の設定
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, kw_config.rgb_layers && layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, kw_config.rgb_layers && layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, kw_config.rgb_layers && layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, kw_config.rgb_layers && layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, kw_config.rgb_layers && layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, kw_config.rgb_layers && layer_state_cmp(state, 5));
    rgblight_set_layer_state(6, kw_config.rgb_layers && layer_state_cmp(state, 6));
    rgblight_set_layer_state(7, kw_config.rgb_layers && layer_state_cmp(state, 7));
    rgblight_set_layer_state(8, kw_config.rgb_layers && layer_state_cmp(state, 8));
    rgblight_set_layer_state(9, kw_config.rgb_layers && layer_state_cmp(state, 9));
    return state;
}
