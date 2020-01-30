#ifndef PLATFORM_H
#define PLATFORM_H


class Platform 
{
public:
  Platform();
  Platform(int xpos, int ypos);

  int getRight() const;
  int getLeft() const;
  int getTop() const;
  int getBottom() const;

  void setXpos(int x);
  void setYpos(int y);
  
  int getXpos() const;
  int getYpos() const;

private:
  const int XMAX = 118;
  const int YMAX = 150;
  int _xpos;
  int _ypos;

};


#endif //!PLATFORM_H
