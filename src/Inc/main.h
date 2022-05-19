#ifndef __OLED_H
#define __OLED_H	
#include <Arduino.h>
#include"TFT_eSPI.h"
#include "ttl.h"
#include <string.h>
#include <stdio.h>

#define LCD_BACKLIGHT (72Ul) // Control Pin of LCD

#define lq_NULL 0
#define lq_RED 0xF800
#define lq_GREEN 0x07E0
#define lq_BLUE 0x001F
#define lq_Circle 4
#define lq_Triangle 5
#define lq_Rectangle 6

extern int xp;
extern int yp;
extern uint16_t bg;
extern uint16_t fg;
extern int screenWd;
extern int screenHt;
extern int wrap;
extern int bold;
extern int sx;
extern int sy; 
extern int horizontal;
extern int scrollMode;
extern const uint16_t *fontRects;
extern const uint16_t *fontOffs;
extern int charWd;
extern int charHt; // real 8
extern int charYoffs;
void handleCMD(char* string);
void drawShape(uint32_t flagColor, int flagShape);

#endif