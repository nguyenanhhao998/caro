#ifndef __EVALUATINGBOARD_H__
#define __EVALUATINGBOARD_H__
#include "_Point.h"
//Class Bảng chứa các giá trị hỗ trợ cho máy chơi
class _EvaluatingBoard
{
public:
	int _size;
	long** _Value;
	_EvaluatingBoard();
	_EvaluatingBoard(int size);
	//Đưa tất cả các giá trị về lại 0
	void ResetValue();
	//Lấy ra chỉ số ô có giá trị lớn nhất
	_Point GetIndexMax();


};


#endif
