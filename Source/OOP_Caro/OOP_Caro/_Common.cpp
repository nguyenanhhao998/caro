#include "_Common.h"

void _Common::gotoXY(int pX, int pY)
{
	COORD coord;
	coord.X = pX;
	coord.Y = pY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void _Common::fixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void _Common::SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size
}

void _Common::cleanscr()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
void _Common::textcolor(int x)
{
	HANDLE color;
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, x);
}
void _Common::textcolorAt(int x, int y, char* a, int color)
{
	gotoXY(x, y);
	textcolor(color);
	cout << a;
	textcolor(7);
}
void _Common::DrawRectangle(int x, int y, int width, int height, bool insert)
{
	gotoXY(x, y);
	cout << char(218);
	gotoXY(x + width, y);
	cout << char(191);
	gotoXY(x, y + height);
	cout << char(192);
	gotoXY(x + width, y + height);
	cout << char(217);
	if (insert)
	{
		for (int i = x + 1; i <= x + width - 1; i++)
		{
			for (int j = y + 1; j <= y + height - 1; j++)
			{
				gotoXY(i, j);
				cout << " ";
			}
		}
	}
	gotoXY(x, y);
	for (int i = x + 1; i < x + width; i++)
	{
		gotoXY(i, y);
		cout << char(196);
	}
	gotoXY(x, y + height);
	for (int i = x + 1; i < x + width; i++)
	{
		gotoXY(i, y + height);
		cout << char(196);
	}
	gotoXY(x, y);
	for (int i = y + 1; i < y+height; i++)
	{
		gotoXY(x, i);
		cout << char(179);
	}
	gotoXY(x + width, y);
	for (int i = y + 1; i < y+height; i++)
	{
		gotoXY(x + width, i);
		cout << char(179);
	}
}
void _Common::DrawTable(int x, int y, int width, int height, int row, int col)
{
	int wid1 = width / col;
	int hei1 = height / row;
	_Common::gotoXY(x, y);
	cout << char(218);
	_Common::gotoXY(x + width, y);
	cout << char(191);
	_Common::gotoXY(x, y + height);
	cout << char(192);
	_Common::gotoXY(x + width, y + height);
	cout << char(217);
	for (int i = x + 1; i < x + width; i++)
	{
		_Common::gotoXY(i, y);
		if ((i - x) % wid1 == 0) cout << char(194);
		else cout << char(196);
		_Common::gotoXY(i, y + height);
		if ((i - x) % wid1 == 0) cout << char(193);
		else cout << char(196);
	}
	for (int i = y + 1; i < y + height; i++)
	{
		_Common::gotoXY(x, i);
		if ((i - y) % hei1 == 0) cout << char(195);
		else cout << char(179);
		_Common::gotoXY(x+width, i);
		if ((i - y) % hei1 == 0) cout << char(180);
		else cout << char(179);
	
	}
	for (int i = y + hei1; i < y + height; i += hei1)
	{
		for (int j = x + 1; j < x + width; j++)
		{
			_Common::gotoXY(j, i);
			if ((j - x) % wid1 == 0) cout << char(197);
			else cout << char(196);
		}
	}
	for (int i = x + wid1; i < x + width; i += wid1)
	{
		for (int j = y + 1; j < y + height; j++)
		{
			_Common::gotoXY(i, j);
			if ((j-y) % hei1 != 0) cout << char(179);
		}
	}
}