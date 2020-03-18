#include "_EvaluatingBoard.h"



_EvaluatingBoard::_EvaluatingBoard()
{
	_size = 0;
}
_EvaluatingBoard::_EvaluatingBoard(int size)
{
	_size = size;
	_Value = new long *[_size];

	for (int y = 0; y < _size; y++)
		_Value[y] = new long[_size];
}
// Đưa tất cả các ô giá trị về lại 0
void _EvaluatingBoard::ResetValue()
{
	for (int y = 0; y < _size; y++)
		for (int x = 0; x < _size; x++)
			_Value[y][x] = 0;
}
_Point _EvaluatingBoard::GetIndexMax()
{
	_Point index(0, 0);
	for (int y = 0; y < _size; y++)
		for (int x = 0; x < _size; x++)
		{
			if (_Value[index.getY()][index.getX()] < _Value[y][x])
				index = _Point(x, y);
		}

	return index;
}

