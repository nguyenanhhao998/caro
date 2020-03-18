#ifndef __POINT_H__
#define __POINT_H__

class _Point
{
	int _x, _y, _check;
public:
	_Point();
	_Point(int, int);
	_Point(int, int, int);
	bool setCheck(int);
	int getX();
	int getY();
	int getCheck();
	void setX(int);
	void setY(int);
};



#endif

