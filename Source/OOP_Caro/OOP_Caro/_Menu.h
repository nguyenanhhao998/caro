#ifndef __MENU_H__
#define __MENU_H__
#include "_Game.h"
#include "string.h"


class _Menu
{
public:
	static CONTROL getKey(int);   //hàm xác định mã ASCII phím nhập từ user, trả về thao tác điều khiển cần thực hiện
	static int Menu();
	static int MenuBOT();
	static void LOGO2();

};

#endif