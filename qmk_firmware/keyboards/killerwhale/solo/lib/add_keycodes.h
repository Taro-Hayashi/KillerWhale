// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

// 追加するキーコード
enum TH_keycodes{
    CMD_CTL = QK_KB_0,
    UNDO,
    REDO,
    COPY,
    CUT,
    PASTE,
    SC_UP,
    SC_DOWN,
    SC_RESET,
    CAPTCHA,
    SAVE,
    SAVEAS,
    NEXTTAB,
    PREVTAB,
    CLOSETAB,
    RSTRTAB,
    L_SPD_I,
    L_SPD_D,
    R_SPD_I,
    R_SPD_D,
    L_ANG_I,
    L_ANG_D,
    L_INV,
    L_CHMOD,
    R_ANG_I,
    R_ANG_D,
    R_INV,
    R_CHMOD,
    INV_SCRL,
    MOD_SCRL,
    AUTO_MOUSE,
    OLED_MOD
};

bool process_record_addedkeycodes(uint16_t keycode, keyrecord_t *record);