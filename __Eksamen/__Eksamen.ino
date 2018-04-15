
#include "GameManager.h"
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7735.h> 
#include <SPI.h>
#include <SD.h>

#define SD_CS    4  // Chip select line for SD card
#define TFT_CS  10  // Chip select line for TFT display
#define TFT_DC   9  // Data/command line for TFT
#define TFT_RST  8  // Reset line for TFT (or connect to +5V)

const int xPin = A0;     //Connected to A0
const int yPin = A1;     //Connected to A1
const int zPin = A2;     //Connected to A2

const int joy_x_pin = A3;
const int joy_y_pin = A4;
const int joy_swt_pin = 2;

const uint16_t BACKGROUND_COLOR = ST7735_BLACK;
const uint16_t SPRITE_COLOR = ST7735_YELLOW;
const uint16_t PLATFORM_COLOR = ST7735_WHITE;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

GameManager gm;

void setup() 
{
  Serial.begin(9600);

  pinMode(joy_swt_pin, INPUT_PULLUP);

  tft.initR(INITR_BLACKTAB);   
  tft.fillScreen(BACKGROUND_COLOR);
  tft.setTextColor(PLATFORM_COLOR, BACKGROUND_COLOR);
  tft.setTextSize(2);

  gm.initialize();

  drawPlatforms();

  int x = gm.getSprite()->getXpos();
  int y = gm.getSprite()->getYpos();
  int w = gm.getSprite()->getWidth();
  int h = gm.getSprite()->getHeight();
  
  tft.fillRect(x, y, w, h, SPRITE_COLOR);
}

void loop() 
{
  readJoystick();
  gm.updateComponents();
  updateUI();
  delay(8);
}

void updateUI()
{
  if (gm.positionsHasChanged())
  {
    int x = gm.getSprite()->oldSprite->getXpos();
    int y = gm.getSprite()->oldSprite->getYpos();
    int w = gm.getSprite()->oldSprite->getWidth();
    int h = gm.getSprite()->oldSprite->getHeight();
    tft.fillRect(x, y, w, h, BACKGROUND_COLOR);
    tft.fillRect(gm.getSprite()->getXpos(), gm.getSprite()->getYpos(), gm.getSprite()->getWidth(), gm.getSprite()->getHeight(), SPRITE_COLOR);
    gm.getSprite()->updatePositions();
  }

  if (gm.platformsHasChanged())
  {
    //Serial.println("Redrawing platforms");
    drawPlatforms();
    gm.platformsArePrinted();
  }
}

void drawPlatforms()
{
  //tft.fillScreen(BACKGROUND_COLOR);
  for (int i = 0; i < gm.getNumberOfPlatforms(); i++)
  {
    int x = gm.getPlatforms()[i].getXpos();
    int y = gm.getPlatforms()[i].getYpos();
    tft.setCursor(x, y);
    tft.print("===");
  }
  /*tft.setCursor(0, 145);
  tft.setTextSize(3);
  tft.print("         ");
  tft.setTextSize(2);*/
}

void readJoystick()
{
  int joy_x_read = analogRead(joy_x_pin);
  int joy_y_read = analogRead(joy_y_pin);
  //int joy_swt_read = analogRead(joy_swt_pin);

  //if (joy_x_read < 400)           // MOVE UP
    //gm.moveSpriteUp(1);
  if (joy_y_read < 400)             // MOVE RIGHT
    gm.moveSpriteRight(1);
  //if (joy_x_read > 600)           // MOVE DOWN
    //gm.moveSpriteDown(1);
  if (joy_y_read > 600)             // MOVE LEFT
    gm.moveSpriteLeft(1);

  if (gm.gameIsOver())
    if (digitalRead(joy_swt_pin) == LOW) {
      Serial.println("Restarting game");
      tft.fillScreen(BACKGROUND_COLOR);
      gm.restart();
      drawPlatforms();
    }
      
    
/*
  Serial.print("JOY X: ");
  Serial.print(joy_x_read);
  Serial.print("\tJOY Y: ");
  Serial.print(joy_y_read);
  Serial.print("\txpos: ");
  Serial.print(xpos);
  Serial.print("\txpos: ");
  Serial.println(ypos);
  */
}

