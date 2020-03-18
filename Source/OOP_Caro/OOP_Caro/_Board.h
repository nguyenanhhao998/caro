#ifndef __BOARD_H__
#define __BOARD_H__
#include "_Point.h"
#include "_Common.h"
#include <conio.h>
class _Board
{
private:
	int _size;
	int _left, _top;
	_Point** _pArr;
public:
	_Board(int, int, int);
	~_Board();
public:
	int getSize();
	int getLeft();
	int getTop();
	int getXAt(int, int);
	int getYAt(int, int);
	int getCheckAt(int, int);
	bool setCheckAt(int, int, int k);
	void resetData();
	void drawBoard();
	int checkBoard(int, int, bool);
	//Hàm nhận biết thắng thua
	int testBoard();
	int testPoint(int, int);
	// Trả về true nếu chỉ số nằm ngoài phạm vi chỉ số thực
	bool OutOfRange(int, int);
	friend class _Game;
};



#endif