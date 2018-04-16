#include <SPI.h>
#include <SD.h>  
#include "PDQ_ST7735_config.h"      // PDQ: ST7735 pins and other setup for this sketch                        
//#include <PDQ_GFX.h>                // PDQ: Core graphics library

#include <PDQ_ST7735.h>     // PDQ: Hardware-specific driver library
PDQ_ST7735 tft;             // PDQ: create LCD object (using pins in "PDQ_ST7735_config.h")

#include "GameManager.h"

const int tft_x_pin = A0;     //Connected to A0
const int tft_y_pin = A1;     //Connected to A1
const int tft_z_pin = A2;     //Connected to A2

const int joy_x_pin = A3;
const int joy_y_pin = A4;
const int joy_swt_pin = 2;

const int buzzer_pin = 8;

const uint16_t BACKGROUND_COLOR = ST7735_BLUE;
const uint16_t SPRITE_COLOR = ST7735_YELLOW;
const uint16_t PLATFORM_COLOR = ST7735_WHITE;

GameManager gm;

unsigned long prevMillis = 0;

void setup() 
{
  Serial.begin(9600);

  pinMode(joy_swt_pin, INPUT_PULLUP);
  pinMode(buzzer_pin, OUTPUT);

  tft.begin();
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
  delay(gm.getDelayTime());
  //delay(8);
  //tone(buzzer_pin, 1750);
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

  if (gm.platformsHasChanged() || millis() - prevMillis >= 500)
  {
    readJoystick();
    drawPlatforms();
    gm.platformsArePrinted();
    prevMillis = millis();
  }

  printScore();
}

void printScore()
{
  tft.setTextSize(1);
  tft.setCursor(0, 0);
  tft.print(gm.getScore());
  tft.setTextSize(2);
}

void drawPlatforms()
{
  for (int i = 0; i < gm.getNumberOfPlatforms(); i++)
  {
    int x = gm.getPlatforms()[i].getXpos();
    int y = gm.getPlatforms()[i].getYpos();
    tft.setCursor(x, y);
    tft.print("===");
  }
}

void readJoystick()
{
  int joy_x_read = analogRead(joy_x_pin);
  int joy_y_read = analogRead(joy_y_pin);
  int tft_x_read = analogRead(tft_x_pin);
  
  //Serial.print("TFT X : ");
  //Serial.println(tft_x_read);

  /*if (tft_x_read < 370) {
    gm.moveSpriteLeft(1);
  }
  if (tft_x_read > 390) {
    gm.moveSpriteRight(1);
  }*/

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

}

