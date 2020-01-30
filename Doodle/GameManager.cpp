#include "GameManager.h"
#include "Arduino.h"

const int XMAX = 118;
const int YMAX = 150;

unsigned long _previousMillis = 0;

unsigned long _prevTone = 0;
const int toneTime = 100;

const int SCREEN_POSITIONS[4] = {
  10, 
  50, 
  90, 
  135
};

// http://javl.github.io/image2cpp/
// https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives

GameManager::GameManager()
{
}

void GameManager::initialize()
{
  _jumping = false;
  _gameOver = false;
  _platformChange = false;
  _score = 0;
  _delayTime = 5;
  _jumpTime = 500;
  randomSeed(analogRead(5));
  initPlatforms();
}

void GameManager::restart()
{
  _jumping = false;
  _gameOver = false;
  _score = 0;
  playTone(0);
  initPlatforms();
  sprite.setXpos(50);
  sprite.setYpos(20);
}

void GameManager::updateComponents()
{
  updateSprite();

  if (sprite.getYpos() <= 15 && _jumping)
  {
    _score++;
    shiftPlatforms();
  }

  if (sprite.getYpos() == YMAX)
  {
    _gameOver = true;
  }

  updateTone();
}

Sprite * GameManager::getSprite()
{
  return &sprite;
}

Platform * GameManager::getPlatforms()
{
  return platforms;
}

int GameManager::getNumberOfPlatforms() const
{
  return NUM_PLATFORMS;
}

bool GameManager::gameIsOver() const
{
  return _gameOver;
}

int GameManager::getScore() const
{
  return _score;
}

int GameManager::getDelayTime() const
{
  return _delayTime;
}

bool GameManager::positionsHasChanged() const
{
  if (sprite.oldSprite->getXpos() != sprite.getXpos() || sprite.oldSprite->getYpos() != sprite.getYpos())
  {
    return true;
  }
  return false;
}

bool GameManager::platformsHasChanged() const
{
  return _platformChange;
}

void GameManager::platformsArePrinted()
{
  _platformChange = false;
}

void GameManager::moveSpriteLeft(int increment)
{
  if (hitPlatformLeft())
    return;
  sprite.decrementXpos(1);
}

void GameManager::moveSpriteRight(int increment)
{
  if (hitPlatformRight())
    return;
  sprite.incrementXpos(1);
}

void GameManager::moveSpriteUp(int increment)
{
  if (hitPlatformBottom())
    return;
  sprite.decrementYpos(increment);
}

void GameManager::moveSpriteDown(int increment)
{
  if (hitPlatformTop())
    return;
  sprite.incrementYpos(increment);
}

  /*  PRIVATE  */

void GameManager::updateSprite()
{
  if (hitPlatformTop()) {
    playTone(1);
    _jumping = true;
  }

  if (hitPlatformBottom()) {
    playTone(2);
    _jumping = false;
  }

  if (millis() - _previousMillis >= _jumpTime) {
    _jumping = false;
  }

  if (_jumping) {
    moveSpriteUp(1);
  }
  else {
    moveSpriteDown(1);
  }
}

void GameManager::initPlatforms()
{
  for (int i = 0; i < NUM_PLATFORMS; i++)
  {
    platforms[i].setXpos(random(0, XMAX - 25));
    platforms[i].setYpos(SCREEN_POSITIONS[i]);
  } 
}

void GameManager::shiftPlatforms()
{
  for (int i = 0; i < NUM_PLATFORMS; i++)
  {
    platforms[i].setYpos(platforms[i].getYpos() + 4);
    if (platforms[i].getYpos() >= YMAX + 20) {
      platforms[i].setYpos(SCREEN_POSITIONS[0]);
      platforms[i].setXpos(random(0, XMAX - 25));
    }
  }
  _platformChange = true;
}

bool GameManager::hitPlatform() 
{
  if (hitPlatformTop())
    return true;
  if (hitPlatformBottom())
    return true;
  if (hitPlatformLeft())
    return true;
  if (hitPlatformRight())
    return true;
  return false;
}

bool GameManager::hitPlatformTop()
{
  for (int i = 0; i < NUM_PLATFORMS; i++)
  {
    if (sprite.getXpos() <= (platforms[i].getXpos() + 33))
      if (sprite.getXpos() >= (platforms[i].getXpos() - 9))
        if (sprite.getYpos() == platforms[i].getYpos() - 6) 
        {
          //playTone(1);
          //tone(8, 1700);
          //noTone(8);
          _previousMillis = millis();
          return true;
        }
  }
  return false;
}

bool GameManager::hitPlatformBottom()
{
  for (int i = 0; i < NUM_PLATFORMS; i++)
  {
    if (sprite.getXpos() <= (platforms[i].getXpos() + 33))
      if (sprite.getXpos() >= (platforms[i].getXpos() - 9))
        if (sprite.getYpos() == platforms[i].getYpos() + 10) 
        {
          return true;
        }
  }
  return false;
}

bool GameManager::hitPlatformRight()
{
  int x = sprite.getXpos();
  int y = sprite.getYpos();
  for (int i = 0; i < NUM_PLATFORMS; i++)
  {
    if (x == platforms[i].getRight())
      if (y >= platforms[i].getTop())
        if (y <= platforms[i].getBottom())
          return true;
  }
  return false;
}

bool GameManager::hitPlatformLeft()
{
  int x = sprite.getXpos();
  int y = sprite.getYpos();
  for (int i = 0; i < NUM_PLATFORMS; i++)
  {
    int p = platforms[i].getLeft();
    if (x == platforms[i].getLeft())
      if (y >= platforms[i].getTop())
        if (y <= platforms[i].getBottom())
          return true;
  }
  return false;
}

void GameManager::playTone(int tune)
{
  switch(tune)
  {
    case 0: 
      noTone(8);
      break;
    case 1:
      //tone(8, 1000);
      break;
    case 2:
      //tone(8, 100);
      break;
  }
  _prevTone = millis();
}

void GameManager::updateTone()
{
  if (millis() - _prevTone >= toneTime) {
    noTone(8);
  }
}

