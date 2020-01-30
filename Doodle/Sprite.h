#ifndef SPRITE_H
#define SPRITE_H

class Sprite 
{
public:
  Sprite();
  Sprite(int xpos, int ypos, int width, int height);

  Sprite * oldSprite;

  void updatePositions();

  void incrementXpos(int increment);
  void incrementYpos(int increment);
  void decrementXpos(int decrement);
  void decrementYpos(int decrement);
  
  void setXpos(int x);
  void setYpos(int y);
  void setWidth(int width);
  void setHeight(int height);
  void setColor(int color);

  int getXpos() const;
  int getYpos() const;
  int getWidth() const;
  int getHeight() const;
  int getColor() const;

private:
  const int XMAX = 118;
  const int YMAX = 150;
  int _xpos;
  int _ypos;
  int _width;
  int _height;
  int _color;

};


#endif //!SPRITE_H
