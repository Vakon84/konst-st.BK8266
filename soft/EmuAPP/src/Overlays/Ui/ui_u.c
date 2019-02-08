#include <string.h>

#include "tv.h"
#include "ets.h"
#include "ps2.h"
#include "ps2_codes.h"
#include "timer0.h"
#include "AnyMem.h"
#include "ovl.h"
#include "Key.h"

#include "ui_u.h"
#include "xprintf_u.h"
#include "str_u.h"

#include "../EmuUi/ps2_eu.h"
#include "../EmuUi/Key_eu.h"

#define AT_OVL        __attribute__((section(".ovl3_u.text")))
#define RODATA_AT_OVL __attribute__((section(".ovl3_u.rodata")))
#define BSS_AT_OVL    __attribute__((section(".ovl3_u.bss")))

TUI_OvlData BSS_AT_OVL UI_OvlData;

const static uint8_t RODATA_AT_OVL Font8x10 [] =
{
// Line 0
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x02, 0x10, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x10, 0x28,
    0x10, 0x00, 0x28, 0x00, 0x00, 0x00, 0x28, 0x10, 0x00, 0x10, 0x10, 0x00, 0x10, 0x10, 0x00, 0x33,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
// Line 1
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x10, 0x24, 0x28, 0x44, 0x60, 0x10, 0x18, 0x08, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x38, 0x10, 0x38, 0x7C, 0x08, 0x7C, 0x1C, 0x7C, 0x38, 0x38, 0x00, 0x00, 0x08, 0x00, 0x20, 0x38,
    0x38, 0x10, 0x78, 0x38, 0x78, 0x7C, 0x7C, 0x38, 0x44, 0x38, 0x1C, 0x44, 0x40, 0x44, 0x44, 0x38,
    0x78, 0x38, 0x78, 0x38, 0x7C, 0x44, 0x44, 0x44, 0x44, 0x44, 0x7C, 0x38, 0x00, 0x38, 0x00, 0x00,
    0x30, 0x00, 0x40, 0x00, 0x04, 0x00, 0x18, 0x00, 0x40, 0x10, 0x08, 0x40, 0x30, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x10, 0x60, 0x00, 0x7C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7C, 0x10, 0x6C, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x28, 0x10, 0x10, 0x28,
    0x10, 0x00, 0x28, 0x10, 0x38, 0x00, 0x28, 0x10, 0x10, 0x10, 0x10, 0x00, 0x10, 0x10, 0x00, 0xCC,
    0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x4C, 0x10, 0x7C, 0x44, 0x3C, 0x7C, 0x10, 0x7C, 0x44, 0x44, 0x00, 0x44, 0x1C, 0x44, 0x44, 0x38,
    0x7C, 0x3C, 0x78, 0x38, 0x7C, 0x44, 0x54, 0x78, 0x40, 0x42, 0x38, 0x44, 0x70, 0x44, 0x44, 0xE0,
// Line 2
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x10, 0x24, 0x28, 0x38, 0x64, 0x28, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x04,
    0x44, 0x30, 0x44, 0x04, 0x18, 0x40, 0x20, 0x04, 0x44, 0x44, 0x00, 0x00, 0x10, 0x00, 0x10, 0x44,
    0x4C, 0x28, 0x44, 0x44, 0x24, 0x40, 0x40, 0x44, 0x44, 0x10, 0x08, 0x48, 0x40, 0x6C, 0x44, 0x44,
    0x44, 0x44, 0x44, 0x44, 0x10, 0x44, 0x44, 0x44, 0x44, 0x44, 0x04, 0x20, 0x40, 0x08, 0x00, 0x00,
    0x10, 0x00, 0x40, 0x00, 0x04, 0x00, 0x24, 0x00, 0x40, 0x00, 0x00, 0x40, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x7C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xA8, 0x10, 0xFE, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00, 0x38, 0x00, 0x00, 0x28, 0x10, 0x10, 0x28,
    0x10, 0x10, 0x28, 0x38, 0x38, 0x00, 0x28, 0x10, 0x38, 0x10, 0x10, 0x00, 0x10, 0x10, 0x08, 0x33,
    0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x52, 0x28, 0x40, 0x44, 0x24, 0x40, 0x7C, 0x44, 0x44, 0x44, 0x44, 0x48, 0x24, 0x6C, 0x44, 0x44,
    0x44, 0x44, 0x44, 0x44, 0x10, 0x44, 0x54, 0x44, 0x40, 0x42, 0x44, 0x54, 0x08, 0x54, 0x44, 0xA0,
// Line 3
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x10, 0x48, 0x7C, 0x44, 0x08, 0x28, 0x20, 0x20, 0x08, 0x54, 0x10, 0x00, 0x00, 0x00, 0x08,
    0x4C, 0x50, 0x04, 0x08, 0x28, 0x78, 0x40, 0x08, 0x44, 0x44, 0x30, 0x30, 0x20, 0x7C, 0x08, 0x04,
    0x54, 0x44, 0x44, 0x40, 0x24, 0x40, 0x40, 0x40, 0x44, 0x10, 0x08, 0x50, 0x40, 0x54, 0x64, 0x44,
    0x44, 0x44, 0x44, 0x40, 0x10, 0x44, 0x44, 0x44, 0x28, 0x28, 0x08, 0x20, 0x20, 0x08, 0x7C, 0x00,
    0x08, 0x38, 0x58, 0x38, 0x34, 0x38, 0x20, 0x34, 0x58, 0x30, 0x08, 0x44, 0x10, 0x68, 0x58, 0x38,
    0x58, 0x34, 0x58, 0x38, 0x70, 0x44, 0x44, 0x44, 0x44, 0x44, 0x7C, 0x10, 0x10, 0x10, 0x00, 0x7C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x28, 0x10, 0xFE, 0x00, 0xF0, 0x10, 0x10, 0xFF, 0xFF, 0x7C, 0x00, 0x00, 0x28, 0x10, 0x10, 0x28,
    0x10, 0x20, 0xFF, 0x54, 0xD6, 0x00, 0x28, 0x10, 0x7C, 0x10, 0xFF, 0x00, 0xFF, 0x1F, 0x04, 0xCC,
    0x4C, 0x38, 0x40, 0x48, 0x3C, 0x38, 0x10, 0x7C, 0x44, 0x44, 0x44, 0x44, 0x1C, 0x44, 0x44, 0x38,
    0x7C, 0x3C, 0x58, 0x38, 0x7C, 0x44, 0x54, 0x78, 0x40, 0x42, 0x78, 0x54, 0x78, 0x54, 0x44, 0xE0,
    0x52, 0x44, 0x40, 0x44, 0x24, 0x40, 0x54, 0x40, 0x28, 0x4C, 0x4C, 0x50, 0x24, 0x54, 0x44, 0x44,
    0x44, 0x44, 0x44, 0x40, 0x10, 0x44, 0x54, 0x44, 0x40, 0x42, 0x04, 0x54, 0x04, 0x54, 0x44, 0x20,
// Line 4
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x10, 0x00, 0x28, 0x44, 0x10, 0x30, 0x00, 0x20, 0x08, 0x38, 0x7C, 0x00, 0x7C, 0x00, 0x10,
    0x54, 0x10, 0x18, 0x18, 0x48, 0x04, 0x78, 0x10, 0x38, 0x3C, 0x30, 0x30, 0x40, 0x00, 0x04, 0x08,
    0x54, 0x44, 0x78, 0x40, 0x24, 0x78, 0x78, 0x40, 0x7C, 0x10, 0x08, 0x60, 0x40, 0x54, 0x54, 0x44,
    0x78, 0x44, 0x78, 0x38, 0x10, 0x44, 0x28, 0x54, 0x10, 0x10, 0x10, 0x20, 0x10, 0x08, 0x04, 0x00,
    0x00, 0x04, 0x64, 0x44, 0x4C, 0x44, 0x70, 0x4C, 0x64, 0x10, 0x08, 0x48, 0x10, 0x54, 0x64, 0x44,
    0x64, 0x4C, 0x64, 0x40, 0x20, 0x44, 0x44, 0x44, 0x28, 0x44, 0x08, 0x60, 0x10, 0x0C, 0x00, 0x7C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x28, 0xFF, 0xFE, 0xF0, 0x10, 0x1F, 0x1F, 0x00, 0x00, 0xFE, 0x1F, 0xFF, 0xFF, 0x10, 0xFF, 0x28,
    0xF0, 0x7E, 0x28, 0x10, 0xFE, 0xFF, 0xFF, 0x10, 0xFE, 0xF0, 0x10, 0xFF, 0x00, 0x10, 0x7E, 0x33,
    0x52, 0x04, 0x78, 0x48, 0x24, 0x44, 0x7C, 0x44, 0x28, 0x4C, 0x4C, 0x48, 0x24, 0x6C, 0x44, 0x44,
    0x44, 0x44, 0x64, 0x44, 0x10, 0x44, 0x54, 0x44, 0x40, 0x42, 0x04, 0x54, 0x04, 0x54, 0x44, 0xA0,
    0x72, 0x44, 0x78, 0x44, 0x24, 0x78, 0x54, 0x40, 0x10, 0x54, 0x54, 0x60, 0x24, 0x54, 0x7C, 0x44,
    0x44, 0x3C, 0x78, 0x40, 0x10, 0x28, 0x38, 0x78, 0x78, 0x72, 0x18, 0x54, 0x3C, 0x54, 0x7C, 0x3C,
// Line 5
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x10, 0x00, 0x7C, 0x44, 0x20, 0x54, 0x00, 0x20, 0x08, 0x54, 0x10, 0x00, 0x00, 0x00, 0x20,
    0x64, 0x10, 0x20, 0x04, 0x7C, 0x04, 0x44, 0x20, 0x44, 0x04, 0x00, 0x00, 0x20, 0x7C, 0x08, 0x10,
    0x5C, 0x7C, 0x44, 0x40, 0x24, 0x40, 0x40, 0x4C, 0x44, 0x10, 0x08, 0x50, 0x40, 0x44, 0x4C, 0x44,
    0x40, 0x54, 0x50, 0x04, 0x10, 0x44, 0x28, 0x54, 0x28, 0x10, 0x20, 0x20, 0x08, 0x08, 0x04, 0x00,
    0x00, 0x3C, 0x44, 0x40, 0x44, 0x7C, 0x20, 0x44, 0x44, 0x10, 0x08, 0x70, 0x10, 0x54, 0x44, 0x44,
    0x44, 0x44, 0x40, 0x38, 0x20, 0x44, 0x44, 0x54, 0x10, 0x44, 0x10, 0x10, 0x10, 0x10, 0x00, 0x7C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x28, 0x00, 0x7C, 0x10, 0xF0, 0x10, 0x00, 0xFF, 0xFF, 0xFE, 0x10, 0x10, 0x00, 0x54, 0x10, 0x28,
    0x10, 0x20, 0xFF, 0x10, 0xD6, 0x00, 0x28, 0x10, 0x7C, 0x00, 0xFF, 0x28, 0xFF, 0x1F, 0x04, 0xCC,
    0x72, 0x3C, 0x44, 0x48, 0x24, 0x7C, 0x54, 0x40, 0x10, 0x54, 0x54, 0x70, 0x24, 0x54, 0x7C, 0x44,
    0x44, 0x3C, 0x44, 0x40, 0x10, 0x44, 0x38, 0x78, 0x78, 0x72, 0x18, 0x54, 0x3C, 0x54, 0x7C, 0x3C,
    0x52, 0x7C, 0x44, 0x44, 0x24, 0x40, 0x54, 0x40, 0x28, 0x64, 0x64, 0x50, 0x24, 0x44, 0x44, 0x44,
    0x44, 0x14, 0x40, 0x40, 0x10, 0x10, 0x54, 0x44, 0x44, 0x4A, 0x04, 0x54, 0x04, 0x54, 0x04, 0x22,
// Line 6
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x38, 0x4C, 0x48, 0x00, 0x10, 0x10, 0x10, 0x10, 0x30, 0x00, 0x30, 0x40,
    0x44, 0x10, 0x40, 0x44, 0x08, 0x44, 0x44, 0x20, 0x44, 0x08, 0x30, 0x30, 0x10, 0x00, 0x10, 0x00,
    0x40, 0x44, 0x44, 0x44, 0x24, 0x40, 0x40, 0x44, 0x44, 0x10, 0x48, 0x48, 0x40, 0x44, 0x44, 0x44,
    0x40, 0x48, 0x48, 0x44, 0x10, 0x44, 0x10, 0x54, 0x44, 0x10, 0x40, 0x20, 0x04, 0x08, 0x00, 0x00,
    0x00, 0x44, 0x64, 0x44, 0x4C, 0x40, 0x20, 0x4C, 0x44, 0x10, 0x08, 0x48, 0x10, 0x54, 0x44, 0x44,
    0x64, 0x4C, 0x40, 0x04, 0x24, 0x4C, 0x28, 0x54, 0x28, 0x28, 0x20, 0x10, 0x10, 0x10, 0x00, 0x7C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x28, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x10, 0x38, 0x10, 0x10, 0x00, 0x38, 0x10, 0x28,
    0x10, 0x10, 0x28, 0x10, 0x10, 0x00, 0x28, 0x10, 0x38, 0x00, 0x10, 0x28, 0x00, 0x10, 0x08, 0x33,
    0x52, 0x44, 0x44, 0x48, 0x24, 0x40, 0x54, 0x40, 0x28, 0x64, 0x64, 0x48, 0x24, 0x44, 0x44, 0x44,
    0x44, 0x24, 0x64, 0x44, 0x10, 0x28, 0x54, 0x44, 0x44, 0x4A, 0x04, 0x54, 0x04, 0x54, 0x04, 0x22,
    0x52, 0x44, 0x44, 0x44, 0x24, 0x40, 0x7C, 0x40, 0x44, 0x44, 0x44, 0x48, 0x24, 0x44, 0x44, 0x44,
    0x44, 0x24, 0x40, 0x44, 0x10, 0x20, 0x54, 0x44, 0x44, 0x4A, 0x44, 0x54, 0x08, 0x54, 0x04, 0x22,
// Line 7
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x10, 0x00, 0x28, 0x44, 0x0C, 0x34, 0x00, 0x08, 0x20, 0x00, 0x00, 0x30, 0x00, 0x30, 0x00,
    0x38, 0x7C, 0x7C, 0x38, 0x08, 0x38, 0x38, 0x20, 0x38, 0x70, 0x30, 0x30, 0x08, 0x00, 0x20, 0x10,
    0x38, 0x44, 0x78, 0x38, 0x78, 0x7C, 0x40, 0x3C, 0x44, 0x38, 0x30, 0x44, 0x7C, 0x44, 0x44, 0x38,
    0x40, 0x34, 0x44, 0x38, 0x10, 0x38, 0x10, 0x28, 0x44, 0x10, 0x7C, 0x38, 0x00, 0x38, 0x00, 0x00,
    0x00, 0x3A, 0x58, 0x38, 0x34, 0x3C, 0x20, 0x34, 0x44, 0x38, 0x08, 0x44, 0x38, 0x54, 0x44, 0x38,
    0x58, 0x34, 0x40, 0x78, 0x18, 0x34, 0x10, 0x28, 0x44, 0x10, 0x7C, 0x0C, 0x10, 0x60, 0x00, 0x7C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x44, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x10, 0x7C, 0x10, 0x10, 0x00, 0x10, 0x10, 0x28,
    0x10, 0x00, 0x28, 0x10, 0x38, 0x00, 0x28, 0x10, 0x10, 0x00, 0x10, 0x28, 0x00, 0x10, 0x00, 0xCC,
    0x4C, 0x3A, 0x38, 0x7C, 0x7E, 0x3C, 0x7C, 0x40, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x38,
    0x44, 0x44, 0x58, 0x38, 0x10, 0x10, 0x54, 0x78, 0x78, 0x72, 0x78, 0x7C, 0x78, 0x7E, 0x04, 0x3C,
    0x4C, 0x44, 0x78, 0x7E, 0x7E, 0x7C, 0x10, 0x40, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x38,
    0x44, 0x44, 0x40, 0x38, 0x10, 0x40, 0x54, 0x78, 0x78, 0x72, 0x38, 0x7C, 0x70, 0x7E, 0x04, 0x3C,
// Line 8
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00, 0x10, 0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x28,
    0x10, 0x00, 0x28, 0x00, 0x00, 0x00, 0x28, 0x10, 0x00, 0x00, 0x10, 0x28, 0x00, 0x10, 0x00, 0x33,
    0x00, 0x00, 0x00, 0x04, 0x42, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x40, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x02, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
// Line 9
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00, 0x10, 0x00, 0x10, 0x10, 0x00, 0x00, 0x10, 0x28,
    0x10, 0x00, 0x28, 0x00, 0x00, 0x00, 0x28, 0x10, 0x00, 0x00, 0x10, 0x28, 0x00, 0x10, 0x00, 0xCC,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


static int AT_OVL ui_tv (uint32_t *pBuf, uint_fast16_t Line);

void AT_OVL ui_clear (void)
{
    AnyMem_memset (UI_OvlData.Scr, ' ', sizeof (UI_OvlData.Scr));
}

#define HEADER_X    0
#define HEADER_Y    0
void AT_OVL ui_header (const char *s)
{
    ui_draw_text(HEADER_X, HEADER_Y, s);
}

void AT_OVL ui_header_default(void)
{
    AT_IROM static const char str_MenuHeader [] = " �������� ��-0011� �� ESP8266";
    ui_draw_text(HEADER_X, HEADER_Y, str_MenuHeader);
}

void AT_OVL ui_draw_list(uint8_t x, uint8_t y, const char *s)
{
    ui_draw_text (x + 3,y, s);
}

void AT_OVL ui_draw_text(uint8_t x, uint8_t y, const char *s)
{
    char Ch;

    while ((Ch = AnyMem_r_c (s)) != 0)
    {
        uint8_t xx;
        for (xx = x; Ch && (Ch != '\n'); xx++)
        {
            AnyMem_w_c (&(UI_OvlData.Scr [y].U8 [xx]), Ch);
            Ch = AnyMem_r_c (++s);
        }
        if (Ch) Ch = AnyMem_r_c (++s);    // ���������� '\n'
        y++;
    }
}

int8_t AT_OVL ui_select(uint8_t x, uint8_t y, uint8_t count)
{
    uint8_t n=0, prev=0;
    
    while (1)
    {
    // ������� ���������� �������
    ui_draw_text (x + (prev / 16)*16, y + (prev % 16), "   ");
    
    // ������ ����� �������
    ui_draw_text (x + (n    / 16)*16, y + (n    % 16), "-->");

    // ��������� ������� ������� ��� ���������� ��� �����������
    prev=n;
    
    // ������ �����
    while (1)
    {
        uint_fast16_t c = ui_GetKey ();
        if (c==KEY_MENU_ESC)
        {
        // ������
        return -1;
        } else
        if (c==KEY_MENU_ENTER)
        {
            // ����
            return n;
        } else
        if ( (c==KEY_MENU_UP) && (n > 0) )
        {
        // �����
        n--;
        break;
        } else
        if ( (c==KEY_MENU_DOWN) && (n < count-1) )
        {
        // ����
        n++;
        break;
        } else
        if ( (c==KEY_MENU_LEFT) && (n > 0) )
        {
        // �����
        if (n > 20) n-=20; else n=0;
        break;
        } else
        if ( (c==KEY_MENU_RIGHT) && (n < count-1) )
        {
        // ������
        n+=20;
        if (n >= count) n=count-1;
        break;
        } else
        if ( (c>='1') && (c<='9') )
        {
        // ����� ������� ������ �� ������
        if (c-'1' < count)
        {
            return c-'1';
        }
        }
    }
    }
}

const char* AT_OVL ui_input_text (const char *comment, const char *_text, uint8_t max_len)
{
//  char text [64];
    uint8_t pos;
    uint_fast16_t c;
    
#define EDIT_X  0
#define EDIT_Y  4
    if (_text)
    {
        // ���� �����
        AnyMem_strcpy (UI_OvlData.InputText.Ch, _text);
        pos = str_nlen (UI_OvlData.InputText.Ch, 64);

    } else
    {
        // ��� ������ - �������� � ������ ������
        UI_OvlData.InputText.U32 [0] = 0;
        pos = 0;
    }
    
    UI_OvlData.CursorXY = ((EDIT_X + pos) << 8) | EDIT_Y;
    ui_clear();
    ui_header_default();
    ui_draw_text(0, 3, comment);
    ui_draw_text(EDIT_X, EDIT_Y, UI_OvlData.InputText.Ch);
    while (1)
    {
        c = ui_GetKey ();

        if (c==KEY_MENU_ESC)
        {
            // ������
            UI_OvlData.CursorXY = 0xFFFFU;
            return 0;
        }
        else if ((c == KEY_MENU_ENTER) && (pos > 0))
        {
            // ����������
            AnyMem_w_c (&UI_OvlData.InputText.Ch [pos], 0);
            UI_OvlData.CursorXY = 0xFFFFU;
            return UI_OvlData.InputText.Ch;
        }
        else if ((c == KEY_MENU_BACKSPACE) && (pos > 0))
        {
            // �����
            UI_OvlData.CursorXY -= 0x100;
            pos--;
            AnyMem_w_c (&(UI_OvlData.Scr [EDIT_Y].U8 [EDIT_X + pos]), ' ');
        }
        else if ((((c >= 32) && (c < 128)) || ((c >= 0xC0) && (c < 0x100))) && (pos < max_len))
        {
            // ������
            AnyMem_w_c (&UI_OvlData.InputText.Ch [pos], c);
            AnyMem_w_c (&(UI_OvlData.Scr [EDIT_Y].U8 [EDIT_X + pos]), c);
            UI_OvlData.CursorXY += 0x100;
            pos++;
        }
    }
}

int8_t AT_OVL ui_yes_no(const char *comment)
{
    AT_IROM static const char str_NoYes [] = "���\n��\n";
    ui_clear();
    ui_header_default();
    ui_draw_text(0, 2, comment);
    ui_draw_list(0, 4, str_NoYes);
    return ui_select(0, 4, 2);
}

void AT_OVL ui_Resume (void)
{
    // ������� �����
    ui_clear ();
    UI_OvlData.CursorXY = 0xFFFFU;

    // ����������� ����� � ����� ����
    tv_SetOutFunc (ui_tv);
}

void AT_OVL ui_Suspend (void)
{
    // �������� �����
    tv_SetOutFunc (NULL);
}

void AT_OVL ui_start (void)
{
    // ��������� ��������� ����������
    Key_SaveRusLat ();

    ui_Resume ();
}

void AT_OVL ui_stop(void)
{
    // ��������������� ��������� ����������
    Key_RestoreRusLat ();

    // �������� �����
    tv_SetOutFunc (NULL);
}

void AT_OVL ui_sleep(uint16_t ms)
{
    uint32_t _sleep=getCycleCount()+(ms)*160000;
    while (((uint32_t)(getCycleCount() - _sleep)) & 0x80000000);
}

static int AT_OVL ui_tv (uint32_t *pBuf, uint_fast16_t Line)
{
    uint_fast16_t   CursorXY;
    uint_fast8_t    Count;
    uint_fast8_t    MenuY;
    uint_fast8_t    MenuLine;
    const uint32_t *pText;
    const uint8_t  *pZkg;
    uint_fast32_t   TextBuf = 0;
    uint32_t        AnyMemCtx;

    if (Line <=  30) return 0;
    Line -= 30;
    if (Line >= 250) return 0;


    // 10 * A / (2**B) = 1 + min
    // 10 * A = (2**B) + min
    // A = ((2**B) + 9) / 10
    MenuY    = (uint_fast8_t) ((Line * (uint32_t) (((double) (1UL << 16) + 9.0) / 10.0)) >> 16); // MenuY = Line / 10;
    MenuLine = Line - MenuY * 10;

    pBuf += 5;

    // ������ ������

    pText = UI_OvlData.Scr [MenuY].U32;
    pZkg  = &Font8x10 [MenuLine * 256];

    CursorXY = (int_fast16_t) UI_OvlData.CursorXY;
    if (MenuY != (UI_OvlData.CursorXY & 0xFF)) CursorXY = -1;
    CursorXY >>= 8;

    AnyMemCtx = AnyMem_Data.Buf;

    for (Count = 0; Count < 16; Count++)
    {
        uint_fast32_t U32;

        if ((Count & 1) == 0) TextBuf = *pText++;

        U32  = (uint_fast32_t) AnyMem_r_u8 (pZkg + ( TextBuf       & 0xFF)) << 16;
        U32 |=                 AnyMem_r_u8 (pZkg + ((TextBuf >> 8) & 0xFF));

        TextBuf >>= 16;

        if ((CursorXY >> 1) == Count)
        {
            if (CursorXY & 1) U32 ^= 0x000000FFUL;
            else              U32 ^= 0x00FF0000UL;
        }

        U32 = (U32 & 0x0F0F0F0F) | ((U32 << 4) & 0x0F0F0F0F);
        U32 = (U32 & 0x33333333) | ((U32 << 2) & 0x33333333);
        U32 = (U32 & 0x55555555) | ((U32 << 1) & 0x55555555);
        U32 |= U32 << 1;

        *pBuf++ = (uint32_t) U32;
    }

    AnyMem_Data.Buf = AnyMemCtx;

    return 1;
}

uint_fast16_t AT_OVL ui_GetKey (void)
{
    uint_fast16_t CodeAndFlags;
    uint_fast16_t Key;

    ps2_periodic ();

    CodeAndFlags = ps2_read ();

    if (CodeAndFlags == 0) return 0;

    if (CodeAndFlags == PS2_DELETE) return KEY_MENU_DELETE;

    Key = Key_Translate (CodeAndFlags | KEY_TRANSLATE_UI);

    ps2_leds ((Key_Flags >> KEY_FLAGS_TURBO_POS) & 7);

    if ((CodeAndFlags & 0x8000U) || (Key == KEY_UNKNOWN)) return 0;

    if      (Key == 14) Key_SetRusLat ();
    else if (Key == 15) Key_ClrRusLat ();

//  Key &= ~KEY_AR2_PRESSED;

    if ((Key_Flags & KEY_FLAGS_RUSLAT) && (Key & 0x40)) Key ^= 0x80;

    return Key;
}
