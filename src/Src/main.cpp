#include "main.h"

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

void setup() {
  Serial.begin(115200);
  // Serial.println("starting");
  pinMode(WRAP_PIN,  INPUT_PULLUP);
  pinMode(HORIZ_PIN, INPUT_PULLUP);
  tft.begin();
//  tft.setRotation(2);
  setupScroll(5, 0);
  checkButtons();
  
  tft.setCursor(0, 0);
  tft.fillScreen(ILI9341_BLACK);
  sx = 1;
  sy = 2;
  char Terminal_Init[]={"\e[0;44m *** Serial Init *** \e[0m\n"};
  printString(Terminal_Init);
  sy = 1;
}

char cmd[100]={};//初始化字符缓冲

void loop(void) 
{
  checkButtons();
  while(Serial.available()){ 
    char c = Serial.read();//读取一个字符
    if(c == '!'){//收到!以后开始接收字符直到接收到*
      printChar(c);
      char* ptr = cmd;
      *ptr++=c;
      for(int i=1; i<100; i++){//字符限制100字
        c = Serial.read();
        *ptr++=c;
        printChar(c);
        if(c == '*'){
          printChar('\n');
          Serial.printf("ok");
          break;
        }
      }
      *ptr='\0';
      handleCMD(cmd);
      // printString("have received\n");
    }else{
      printChar(c);
    }
  }
}

uint32_t lastColor = 0;
int lastShape = 0;

void handleCMD(char* string){
  int flagColor = lq_NULL;
  int flagShape = lq_NULL;
  char* ch = string;
  while(*ch!='\0'){
    if(*ch == '!'){
      if(!strncmp(ch, "!RED,",5)){
        flagColor = lq_RED;
      }else if(!strncmp(ch, "!GREEN,",7)){
        flagColor = lq_GREEN;
      }else if(!strncmp(ch, "!BLUE,",6)){
        flagColor = lq_BLUE;
      }else{
        flagColor = lq_NULL;
      }
    }else if(*ch == ','){
      if(!strncmp(ch, ",Circle*",8)){
        flagShape = lq_Circle;
      }else if(!strncmp(ch, ",Rectangle*",11)){
        flagShape = lq_Rectangle;
      }else if(!strncmp(ch, ",Triangle*",10)){
        flagShape = lq_Triangle;
      }else{
        flagShape = lq_NULL;
      }
    }
    ch++;
  }
  drawShape(flagColor, flagShape);
}

void drawShape(uint32_t flagColor, int flagShape){
  if( (lastShape == flagShape) && (lastColor == flagColor)){
    return;
  }
  switch (flagShape)
  {
  case lq_Circle :
    tft.fillRect(0,160,240,160,TFT_BLACK);
    tft.fillCircle(120,230,50,flagColor);
    break;
  case lq_Rectangle :
    tft.fillRect(0,160,240,160,TFT_BLACK);
    tft.fillRect(70,180,100,100,flagColor);
    break;
  case lq_Triangle :
    tft.fillRect(0,160,240,160,TFT_BLACK);
    tft.fillTriangle(120,180,70,280,170,280,flagColor);
    break;
  
  default:
    tft.fillRect(0,160,240,160,TFT_BLACK);
    break;
  }
  lastColor = flagColor;
  lastShape = flagShape;
}
