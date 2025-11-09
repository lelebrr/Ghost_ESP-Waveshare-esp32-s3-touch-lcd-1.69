/*
 * Copyright 2023 LVGL LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

/*====================
   COLOR SETTINGS
 *====================*/

/*Color depth: 1, 8, 16, 24, 32*/
#define LV_COLOR_DEPTH 16

/*Swap the 2 bytes of RGB565 color. Useful if the display controller requires it.*/
#define LV_COLOR_16_SWAP 0

/*Enable features to draw on transparent background.
 *It's required if opa_scale is used. Needs LV_COLOR_DEPTH = 32 color depth.*/
#define LV_COLOR_SCREEN_TRANSP 0

/* Adjust color mix functions rounding. If it is 0 then rounding is simple.*/
#define LV_COLOR_MIX_ROUND_OFS 0

/*Images pixels with this color will not be drawn if they are  chroma keyed)*/
#define LV_COLOR_CHROMA_KEY lv_color_hex(0x00ff00)

/*=========================
   MEMORY SETTINGS
 *=========================*/

/*1: use custom malloc/free, 0: use the built-in `lv_mem_alloc` and `lv_mem_free`*/
#define LV_MEM_CUSTOM 0
#if LV_MEM_CUSTOM == 0
/*Size of the memory available for `lv_mem_alloc` in bytes (>= 2kB)*/
#  define LV_MEM_SIZE (32U * 1024U)

/*Set an address for the memory pool instead of allocating it as a static array.*/
#  define LV_MEM_ADR 0
#else       /*LV_MEM_CUSTOM*/
#  define LV_MEM_CUSTOM_INCLUDE <stdlib.h>   /*Header for the dynamic memory function*/
#  define LV_MEM_CUSTOM_ALLOC   malloc
#  define LV_MEM_CUSTOM_FREE    free
#  define LV_MEM_CUSTOM_REALLOC realloc
#endif     /*LV_MEM_CUSTOM*/

/*====================
   HAL SETTINGS
 *====================*/

/*Default display refresh period. LVG will redraw changed areas with this period time*/
#define LV_DISP_DEF_REFR_PERIOD 30      /*[ms]*/

/*Input device read period in milliseconds*/
#define LV_INDEV_DEF_READ_PERIOD 30     /*[ms]*/

/*Use a custom tick source that tells the elapsed time in milliseconds.
 *It removes the need to manually update the tick with `lv_tick_inc()`)*/
#define LV_TICK_CUSTOM 0

/*================
 * FONT SETTINGS
 *===============*/

/*Enable the use of fonts*/
#define LV_USE_FONT_SUBPX 1
#if LV_USE_FONT_SUBPX
/*Set the pixel order of the display. Physical order of the subpixels.*/
#define LV_FONT_SUBPX_BGR 0  /*0: RGB; 1: BGR order*/
#endif

/*Enable built-in fonts*/
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_32 1

/*=================
 *  TEXT SETTINGS
 *=================*/

/**
 * Select a character encoding for strings.
 * Your IDE or editor should have the same character encoding
 * - LV_TXT_ENC_UTF8
 * - LV_TXT_ENC_ASCII
 */
#define LV_TXT_ENC LV_TXT_ENC_UTF8

/*Can break (wrap) texts on white spaces*/
#define LV_TXT_BREAK_CHARS " ,.;"

/*==================
 *  WIDGET USAGE
 *================*/

/*Documentation of the widgets: https://docs.lvgl.io/master/widgets/index.html*/
#define LV_USE_LABEL    1
#define LV_USE_BTN      1
#define LV_USE_IMG      1

/*==================
*  THEME USAGE
*==================*/

/*Always enable at least on theme*/
#define LV_USE_THEME_DEFAULT 1

/*==================
 *    OTHERS
 *==================*/

/*-----------
 * Logging
 *-----------*/
#define LV_USE_LOG 1
#if LV_USE_LOG
/*How important log should be added:
 *LV_LOG_LEVEL_TRACE       A lot of logs to give detailed information
 *LV_LOG_LEVEL_INFO        Log important events
 *LV_LOG_LEVEL_WARN        Log if something unwanted happened but didn't cause a problem
 *LV_LOG_LEVEL_ERROR       Only critical issue, when the system may fail
 *LV_LOG_LEVEL_USER        Only logs added by the user
 *LV_LOG_LEVEL_NONE        Do not log anything*/
#define LV_LOG_LEVEL LV_LOG_LEVEL_WARN
#endif  /*LV_USE_LOG*/

#endif /*LV_CONF_H*/
