#include "_Menu.h"
#define BOARD_SIZE 16
#define LEFT 2
#define TOP 1
void main()
{
	_Game g(BOARD_SIZE, LEFT, TOP);
	_Common::SetWindow(100, 40);
	_Common::fixConsoleWindow();
	while (1)
	{
		PlaySound("musicstart.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
		int choose=_Menu::Menu();
		if (choose == 3) break;
		switch (choose)
		{
		case 0:
			g.playGame(0, 0);
			break;
		case 1:
			int choose1;
			system("cls");
			choose1 = _Menu::MenuBOT();
			if (choose1 == 0) g.playGame(0, 1);
			else g.playGame(0, 2);
			break;
		case 2:
			int isBOT;
			if (g.loadGame(isBOT))
			{
				g.playGame(1, isBOT);
			}
			else
			{
				system("cls");
			}
			break;
		}
	}
}
