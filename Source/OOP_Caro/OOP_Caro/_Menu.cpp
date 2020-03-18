#include "_Menu.h"

int _Menu::Menu()
{
	int tt = 0; //Biến chỉ ra đang ở thao tác hiện tại nào, tt=0 chỉ thao tác đầu tiên
	int n = 4;//Số thao tác có trong menu
	int* mau = new int[n];  //Tạo mảng lưu giá trị các màu chữ và nền ứng với mỗi dòng in ra thao tác
	HANDLE Color;
	Color = GetStdHandle(STD_OUTPUT_HANDLE);
	while (1)
	{
		SetConsoleTextAttribute(Color, 0);
		//Trước tiên cài đặt các màu của từng thao tác:
		for (int i = 0; i < n; i++)
		{
			mau[i] = COLOR_NOTCHOOSE; //Màu thao tác không được chọn
		}
		mau[tt] = COLOR_CHOOSE;  //Màu thao tác được chọn
		_Common::cleanscr();
		cout << endl << endl;
		LOGO2();
		cout << endl << endl;
		//In MENU với list các thao tác
		cout << "                                      "; 
		SetConsoleTextAttribute(Color, mau[0]);
		cout<<"  2 PLAYER MODE  " << endl << endl;
		SetConsoleTextAttribute(Color, 0);
		cout << "                                        ";
		SetConsoleTextAttribute(Color, mau[1]);
		cout << "  BOT  MODE  " << endl << endl;
		SetConsoleTextAttribute(Color, 0);
		cout << "                                        ";
		SetConsoleTextAttribute(Color, mau[2]);
		cout<<"  LOAD GAME  " << endl << endl;
		SetConsoleTextAttribute(Color, 0);
		cout << "                                          ";
		SetConsoleTextAttribute(Color, mau[3]);
		cout<<"  EXIT  " << endl;
		//Chờ và nhận phím từ user
		int k = _getch();
		CONTROL control = getKey(k);
		switch (control)
		{
		case UP:
			if (tt == 0) tt = n - 1;
			else tt--;
			break;
		case DOWN:
			if (tt == n - 1) tt = 0;
			else tt++;
			break;
		case ENTER:
			delete mau; //Xóa mảng lưu giá trị màu trước khi return giá trị
			return tt;
		}

	}
}
int _Menu::MenuBOT()
{
	int tt = 0;
	int* mau = new int[2];
	HANDLE Color;
	Color = GetStdHandle(STD_OUTPUT_HANDLE);
	while (1)
	{
		SetConsoleTextAttribute(Color, 0);
		for (int i = 0; i < 2; i++)
		{
			mau[i] = COLOR_NOTCHOOSE;
		}
		mau[tt] = COLOR_CHOOSE;
		_Common::cleanscr();
		cout << endl << endl;
		LOGO2();
		cout << endl << endl << endl;
		//In MENU với list các thao tác
		cout << "                                      ";
		SetConsoleTextAttribute(Color, mau[0]);
		cout << "  May danh sau  " << endl << endl;
		SetConsoleTextAttribute(Color, 0);
		cout << "                                     ";
		SetConsoleTextAttribute(Color, mau[1]);
		cout << "  May danh truoc  " << endl << endl;
		SetConsoleTextAttribute(Color, 0);
		//Chờ và nhận phím từ user
		int k = _getch();
		CONTROL control = getKey(k);
		switch (control)
		{
		case UP:
			if (tt == 0) tt = 1;
			else tt--;
			break;
		case DOWN:
			if (tt == 1) tt = 0;
			else tt++;
			break;
		case ENTER:
			delete mau; //Xóa mảng lưu giá trị màu trước khi return giá trị
			return tt;
		}

	}
}
CONTROL _Menu::getKey(int k)
{
	switch (toupper(k))
	{
	case 'W': return UP;
	case 'S': return DOWN;
	case 'D': return RIGHT;
	case 'A': return LEFT;
	}
	if (k == 224)
	{
		char c;
		c = _getch();
		switch (c)
		{
		case 72: return UP;
		case 80: return DOWN;
		case 77: return RIGHT;
		case 75: return LEFT;
		}
	}
	else if (k == 13) return ENTER;
	return NOTHING;
}

void _Menu::LOGO2()
{
	HANDLE Color;
	int mauchu=10;
	Color = GetStdHandle(STD_OUTPUT_HANDLE);
	int c0[34] = { 32,219,219,219,219,219,219,187,32,219,219,219,219,219,187,32,219,219,219,219,219,219,187,32,32,219,219,219,219,219,219,187,32 };
	int c1[34] = { 219,219,201,205,205,205,205,188,219,219,201,205,205,219,219,187,219,219,201,205,205,219,219,187,219,219,201,205,205,205,219,219,187 };
	int c2[34] = { 219,219,186,32,32,32,32,32,219,219,219,219,219,219,219,186,219,219,219,219,219,219,201,188,219,219,186,32,32,32,219,219,186 };
	int c3[34] = { 219,219,186,32,32,32,32,32,219,219,201,205,205,219,219,186,219,219,201,205,205,219,219,187,219,219,186,32,32,32,219,219,186 };
	int c4[34] = { 200,219,219,219,219,219,219,187,219,219,186,32,32,219,219,186,219,219,186,32,32,219,219,186,200,219,219,219,219,219,219,201,188 };
	int c5[34] = { 32,200,205,205,205,205,205,188,200,205,188,32,32,200,205,188,200,205,188,32,32,200,205,188,32,200,205,205,205,205,205,188,32 };
	SetConsoleTextAttribute(Color, 0);
	cout << "\n\n\n\n                               ";
	SetConsoleTextAttribute(Color, mauchu);
	for (int i = 0; i < 33; i++)
	{
		cout << char(c0[i]);
	}
	cout << endl;
	SetConsoleTextAttribute(Color, 0);
	cout << "                               ";
	SetConsoleTextAttribute(Color, mauchu);
	for (int i = 0; i < 33; i++)
	{
		cout << char(c1[i]);
	}
	cout << endl;
	SetConsoleTextAttribute(Color, 0);
	cout << "                               ";
	SetConsoleTextAttribute(Color, mauchu);
	for (int i = 0; i < 33; i++)
	{
		cout << char(c2[i]);
	}
	cout << endl;
	SetConsoleTextAttribute(Color, 0);
	cout << "                               ";
	SetConsoleTextAttribute(Color, mauchu);
	for (int i = 0; i < 33; i++)
	{
		cout << char(c3[i]);
	}
	cout << endl;
	SetConsoleTextAttribute(Color, 0);
	cout << "                               ";
	SetConsoleTextAttribute(Color, mauchu);
	for (int i = 0; i < 33; i++)
	{
		cout << char(c4[i]);
	}
	cout << endl;
	SetConsoleTextAttribute(Color, 0);
	cout << "                               ";
	SetConsoleTextAttribute(Color, mauchu);
	for (int i = 0; i < 33; i++)
	{
		cout << char(c5[i]);
	}
	SetConsoleTextAttribute(Color, 7);
	cout << endl;
}