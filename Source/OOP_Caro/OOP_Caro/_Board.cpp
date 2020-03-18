#include "_Board.h"

_Board::_Board(int pSize, int pX, int pY)
{
	_size = pSize;
	_left = pX;
	_top = pY;
	_pArr = new _Point*[pSize];
	for (int i = 0; i < pSize; i++) _pArr[i] = new _Point[pSize];
}
_Board::~_Board()
{
	for (int i = 0; i < _size; i++) delete[] _pArr[i];
	delete[] _pArr;
}

int _Board::getSize() { return _size; }
int _Board::getLeft() { return _left; }
int _Board::getTop() { return _top; }
int _Board::getXAt(int i, int j) {
	return _pArr[i][j].getX();
}
int _Board::getYAt(int i, int j) {
	return _pArr[i][j].getY();
}
int _Board::getCheckAt(int i, int j) {
	return _pArr[i][j].getCheck();
}
bool _Board::setCheckAt(int i, int j, int k)
{
	return _pArr[i][j].setCheck(k);
}
void _Board::resetData()
{
	if (_size == 0) return; // Phải gọi constructor trước khi resetData
	for (int i = 0; i < _size; i++) 
	{
		for (int j = 0; j < _size; j++) 
		{
			_pArr[i][j].setX(4 * j + _left + 2); // Trùng với hoành độ màn hình bàn cờ
			_pArr[i][j].setY(2 * i + _top + 1); // Trùng với tung độ màn hình bàn cờ
			_pArr[i][j].setCheck(0);

		}
	}
}
void _Board::drawBoard()
{
	if (_pArr == NULL) return; //phải gọi constructor trước
	_Common::textcolor(5);
	_Common::DrawTable(_left, _top, 4 * _size, 2 * _size, _size, _size);
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			_Common::gotoXY(getXAt(i,j),getYAt(i,j));
			switch (_pArr[i][j].getCheck())
			{
			case -1:
				_Common::textcolor(12);
				printf("x");
				_Common::textcolor(7);
				break;
			case 1:
				_Common::textcolor(10);
				printf("o");
				_Common::textcolor(7);
				break;
			case 0: cout << " ";
			}
		}
	}
	_Common::textcolor(7);
	_Common::gotoXY(_pArr[0][0].getX(), _pArr[0][0].getY()); // di chuyển vào ô đầu
}
int _Board::checkBoard(int pX, int pY, bool pTurn)
{
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY && _pArr[i][j].getCheck() == 0)
			{
				if (pTurn) _pArr[i][j].setCheck(-1);// Nếu lượt hiện hành là true: c = -1
				else _pArr[i][j].setCheck(1);// Nếu lượt hiện hành là false: c = 1
				return _pArr[i][j].getCheck();
			}
		}
	}
	return 0;
}
int _Board::testBoard()
{
	int dem = 0;  //Biến đếm số ô đã được đánh: Để xác định bảng đã đầy hay chưa
	//Qui ước theo luật không chặn 2 đầu
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			//neu gap o X hoac O thi tang dem len 1 và kiểm tra thắng thua tai điểm đó
			if (_pArr[i][j].getCheck() == -1 || _pArr[i][j].getCheck() == 1)
			{
				dem++;
				int test = testPoint(i, j);
				if (test == -1 || test == 1) return test;
			}
			//Nếu là ô trống thì sang ô kê tiếp
		}
	}
	if (dem == _size*_size) return 0; //Nếu bảng không còn ô trống thì xác định hòa
	return 2;  //Đánh tiếp
}
int _Board::testPoint(int i, int j)
{
	//Nếu là ô X xét 4 ô tiếp theo
	if (_pArr[i][j].getCheck() == -1)
	{
		//Khởi tạo các biến đếm
		int demdocX = 1;    //hàng dọc
		int demngangX = 1;  //hàng ngang
		int demcheochinhX = 1;   //đường chéo chính (trái trên ->phải dưới)
		int demcheophuX = 1; //đường chéo phụ (phải trên -> trái dưới)
							 //Xét 4 ô kế tiếp dọc theo mỗi đường. Nếu đếm đủ 5 ô trong một đường là X thì trả về 1
		for (int k = 1; k <= 4; k++)
		{
			//đường ngang
			if (j + k < _size && _pArr[i][j + k].getCheck() == -1) demngangX++;
			if (demngangX == 5) return -1;
			//đường dọc
			if (i + k < _size && _pArr[i + k][j].getCheck() == -1) demdocX++;
			if (demdocX == 5) return -1;
			//đường chéo chính
			if (i + k < _size && j + k < _size && _pArr[i + k][j + k].getCheck() == -1) demcheochinhX++;
			if (demcheochinhX == 5) return -1;
			//đường chéo phụ
			if (i + k < _size && j - k >= 0 && _pArr[i + k][j - k].getCheck() == -1) demcheophuX++;
			if (demcheophuX == 5) return -1;
		}
	}
	//Xét ô O thì tăng dem lên 1, xét 4 ô tiếp theo: Tương tự ô X
	if (_pArr[i][j].getCheck() == 1)
	{
		int demdocO = 1;
		int demngangO = 1;
		int demcheochinhO = 1;
		int demcheophuO = 1;
		for (int k = 1; k <= 4; k++)
		{
			if (j + k < _size && _pArr[i][j + k].getCheck() == 1) demngangO++;
			if (demngangO == 5) return 1;
			if (i + k < _size && _pArr[i + k][j].getCheck() == 1) demdocO++;
			if (demdocO == 5) return 1;
			if (i + k < _size && j + k < _size && _pArr[i + k][j + k].getCheck() == 1) demcheochinhO++;
			if (demcheochinhO == 5) return 1;
			if (i + k < _size && j - k >= 0 && _pArr[i + k][j - k].getCheck() == 1) demcheophuO++;
			if (demcheophuO == 5) return 1;
		}
	}
	return 0;
}
// Trả về true nếu chỉ số nằm ngoài phạm vi chỉ số thực
bool _Board::OutOfRange(int i, int j)
{
	if (i<0 || j<0 || i>=_size|| j>=_size)
	{
		return true;
	}
	return false;
}
