// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef RP_ADC_USE_ADC1
#define RP_ADC_USE_ADC1 TRUE
#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE
#undef RP_SPI_USE_SPI1
#define RP_SPI_USE_SPI1 FALSE
#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE
#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 FALSE
