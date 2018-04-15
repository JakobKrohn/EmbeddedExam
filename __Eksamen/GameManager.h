#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Sprite.h"
#include "Platform.h"

#define NUM_PLATFORMS 4

class GameManager 
{
public:
  GameManager();

  void initialize();
  void restart();
  void updateComponents();

  Sprite * getSprite();
  Platform * getPlatforms();

  int getNumberOfPlatforms() const;

  bool gameIsOver() const;
  bool positionsHasChanged() const;
  bool platformsHasChanged() const;
  void platformsArePrinted();

  void moveSpriteLeft(int increment);
  void moveSpriteRight(int increment);

  void moveSpriteUp(int increment);
  void moveSpriteDown(int increment);

private:
  Sprite sprite = Sprite();
  Platform platforms[NUM_PLATFORMS] {
    Platform(),
    Platform(),
    Platform(), 
    Platform()
  };
  
  bool _jumping;
  bool _gameOver;
  bool _platformChange;

  void updateSprite();
  void initPlatforms();
  void shiftPlatforms();
  
  bool hitPlatformTop();
  bool hitPlatformBottom();
  bool hitPlatformRight();
  bool hitPlatformLeft();
  
};


#endif //!GAME_MANAGER_H
