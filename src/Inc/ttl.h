#ifndef __TTL_H
#define __TTL_H	
#define ILI9341_VSCRDEF  0x33
#define ILI9341_VSCRSADD 0x37

#include "TFT_eSPI.h"
#include <SPI.h>



#define WRAP_PIN    BCM18
#define HORIZ_PIN   BCM23
//#define TFT_CS      PA4                  
//#define TFT_DC      PA12              
//#define TFT_RST     PA11 




void drawChar(int16_t x, int16_t y, unsigned char c,
              uint16_t color, uint16_t bg, uint8_t sx, uint8_t sy);


void scroll();


void printChar(char c);


void printString(char *str);


void setupScroll(uint16_t tfa, uint16_t bfa);


void scrollFrame(uint16_t vsp);


void checkButtons();


#endif