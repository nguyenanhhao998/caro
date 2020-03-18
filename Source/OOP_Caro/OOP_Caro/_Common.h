#ifndef __COMMON_H__
#define __COMMON_H__
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include<MMsystem.h>
using namespace std;
class _Common
{
public:
	static void fixConsoleWindow();
	static void SetWindow(int, int);
	static void gotoXY(int, int);
	static void cleanscr();  // Chuyển con trỏ màn hình về (0,0): có tác dụng như xóa màn hình nếu chỉ cần ghi đè
	static void textcolor(int x); //Hàm cài đặt màu chữ (nền)
	static void textcolorAt(int x, int y, char* a, int color); //In ra chuỗi a với màu color tại vị trí (x,y)
	static void DrawRectangle(int x, int y, int width, int height, bool insert=false);
	static void DrawTable(int x, int y, int width, int height, int row, int col);
};




#endif
