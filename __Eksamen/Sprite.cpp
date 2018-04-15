#include "Sprite.h"

Sprite::Sprite()
{
  setXpos(50);
  setYpos(20);
  setWidth(10);
  setHeight(10);
  oldSprite = new Sprite(50, 20, 10, 10);
}

Sprite::Sprite(int xpos, int ypos, int width, int height)
{
  setXpos(xpos);
  setYpos(ypos);
  setWidth(width);
  setHeight(height);
}

void Sprite::updatePositions()
{
  oldSprite->setXpos(getXpos());
  oldSprite->setYpos(getYpos());
}

void Sprite::incrementXpos(int increment)
{
  
  if (getXpos() == XMAX)
    return;
  setXpos(getXpos() + increment);
}

void Sprite::incrementYpos(int increment)
{
  
  if (getYpos() == YMAX)
    return;
  setYpos(getYpos() + increment);
}

void Sprite::decrementXpos(int decrement)
{
  
  if (getXpos() <= 0)
    return;
  setXpos(getXpos() - decrement);
}

void Sprite::decrementYpos(int decrement)
{
  
  if (getYpos() <= 0)
    return;
  setYpos(getYpos() - decrement);
}

void Sprite::setXpos(int x)
{
  _xpos = x;
}

void Sprite::setYpos(int y)
{
  _ypos = y;
}

void Sprite::setWidth(int width)
{
  _width = width;
}

void Sprite::setHeight(int height)
{
  _height = height;
}

void Sprite::setColor(int color)
{
  _color = color;
}

int Sprite::getXpos() const
{
  return _xpos;
}

int Sprite::getYpos() const
{
  return _ypos;
}

int Sprite::getWidth() const
{
  return _width;
}

int Sprite::getHeight() const
{
  return _height;
}

int Sprite::getColor() const
{
  return _color;
}

