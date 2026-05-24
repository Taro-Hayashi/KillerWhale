// Copyright 2021 Hayashi (@w_vwbw)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"

void oled_init_addedoled(void);
bool oled_task_addedoled(void);
void oled_interrupt(uint16_t keycode);
void oled_tempch(bool on, uint16_t keycode);