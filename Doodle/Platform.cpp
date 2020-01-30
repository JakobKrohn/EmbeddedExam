#include "Platform.h"

const int PLATFORM_TOP = 6;
const int PLATFORM_BOTTOM = 10;
const int PLATFORM_LEFT_SIDE = 34;
const int PLATFORM_RIGHT_SIDE = 10;

Platform::Platform()
{
  
}

Platform::Platform(int xpos, int ypos)
{
  setXpos(xpos);
  setYpos(ypos);
}

int Platform::getRight() const
{
  return getXpos() - PLATFORM_RIGHT_SIDE;
}

int Platform::getLeft() const
{
  return getXpos() + PLATFORM_LEFT_SIDE;
}

int Platform::getTop() const
{
  return getYpos() - PLATFORM_TOP;
}

int Platform::getBottom() const
{
  return getYpos() + PLATFORM_BOTTOM;
}

void Platform::setXpos(int x)
{
  _xpos = x;
}

void Platform::setYpos(int y)
{
  _ypos = y;
}

int Platform::getXpos() const
{
  return _xpos;
}

int Platform::getYpos() const
{
  return _ypos;
}
