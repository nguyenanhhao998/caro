#include "_Game.h"

_Game::_Game(int pSize, int pLeft, int pTop)
{
	_b = new _Board(pSize, pLeft, pTop);
	_loop = _turn = true;
	_command = -1; // Gán lượt và phím mặc định
	_winX = 0; _winY = 0;
	_x = pLeft; _y = pTop;
}
_Game::~_Game() { delete _b; }
int _Game::getCommand() { return _command; }
bool _Game::isContinue() { return _loop; }
char _Game::waitKeyBoard()
{
	_command = toupper(_getch());
	return _command;
}
char _Game::askContinue()
{
	_Common::textcolor(11);
	_Common::DrawRectangle(13, 8, 30, 7, 1);
	int tt = 0; //Biến chỉ ra đang ở thao tác hiện tại nào, tt=0 chỉ thao tác đầu tiên
	int* mau = new int[2];  //Tạo mảng lưu giá trị các màu chữ và nền ứng với mỗi dòng in ra thao tác
	while (1)
	{
		_Common::textcolor(0);
		//Trước tiên cài đặt các màu của từng thao tác:
		for (int i = 0; i < 2; i++)
		{
			mau[i] = COLOR_NOTCHOOSE; //Màu thao tác không được chọn
		}
		mau[tt] = COLOR_CHOOSE;  //Màu thao tác được chọn
		_Common::textcolor(11);
		_Common::DrawRectangle(13, 8, 30, 7);
		_Common::gotoXY(18, 10);
		_Common::textcolor(14);
		cout << "Ban co muon choi tiep?";
		_Common::gotoXY(20, 12);
		_Common::textcolor(mau[0]);
		cout << "  YES  " << endl << endl;
		_Common::gotoXY(30, 12);
		_Common::textcolor(mau[1]);
		cout << "  NO  " << endl << endl;
		_Common::textcolor(0);
		//Chờ và nhận phím từ user
		int k = _getch();
		k = toupper(k);
		switch (k)
		{
		case 'A':
			if (tt == 0) tt = 1;
			else tt = 0;
			break;
		case 'D':
			if (tt == 1) tt = 0;
			else tt = 1;
			break;
		case 13:
			delete mau; //Xóa mảng lưu giá trị màu trước khi return giá trị
			return 1 - tt;
		}

	}
}
bool _Game::askSaveGame()
{
	_Common::textcolor(11);
	_Common::DrawRectangle(13, 8, 30, 7, 1);
	int tt = 0; //Biến chỉ ra đang ở thao tác hiện tại nào, tt=0 chỉ thao tác đầu tiên
	int* mau = new int[2];  //Tạo mảng lưu giá trị các màu chữ và nền ứng với mỗi dòng in ra thao tác
	while (1)
	{
		_Common::textcolor(0);
		//Trước tiên cài đặt các màu của từng thao tác:
		for (int i = 0; i < 2; i++)
		{
			mau[i] = COLOR_NOTCHOOSE; //Màu thao tác không được chọn
		}
		mau[tt] = COLOR_CHOOSE;  //Màu thao tác được chọn
		_Common::textcolor(11);
		_Common::DrawRectangle(13, 8, 30, 7);
		_Common::gotoXY(18, 10);
		_Common::textcolor(14);
		cout << "Ban co muon luu game?";
		_Common::gotoXY(20, 12);
		_Common::textcolor(mau[0]);
		cout << "  YES  " << endl << endl;
		_Common::gotoXY(30, 12);
		_Common::textcolor(mau[1]);
		cout << "  NO  " << endl << endl;
		_Common::textcolor(0);
		//Chờ và nhận phím từ user
		int k = _getch();
		k = toupper(k);
		switch (k)
		{
		case 'A':
			if (tt == 0) tt = 1;
			else tt = 0;
			break;
		case 'D':
			if (tt == 1) tt = 0;
			else tt = 1;
			break;
		case 13:
			delete mau; //Xóa mảng lưu giá trị màu trước khi return giá trị
			return 1-tt;
		}

	}
}
void _Game::startGame()
{
	ResetStack();//Làm mới ngăn xếp undo
	system("cls");
	PlaySound(NULL, NULL, SND_FILENAME);
	_loop = _turn = true;
	_b->resetData(); // Khởi tạo dữ liệu gốc
	ShowInfo();
	printXO();
	_b->drawBoard(); // Vẽ màn hình game
	_x = _b->getXAt(0, 0);
	_y = _b->getYAt(0, 0);
}
void _Game::startLoadgame()
{
	system("cls");
	PlaySound(NULL, NULL, SND_FILENAME);
	_loop = true;
	ShowInfo();
	printXO();
	_b->drawBoard();
	_Common::gotoXY(_x, _y);
}
void _Game::Undo(int isBOT)
{
	_Point p;
	if (_undo.empty() == 0)
	{
		if (isBOT != 0) //Nếu có máy đánh thì xóa 2 nước đi gần nhất. 2 người đánh xóa 1 nước đi gần nhất
		{
			p = _undo.top();
			_undo.pop();
			for (int i = 0; i < _b->getSize(); i++) {
				for (int j = 0; j < _b->getSize(); j++) {
					if (_b->getXAt(i, j) == p.getX() && _b->getYAt(i, j) == p.getY())
					{
						_b->setCheckAt(i, j, 0);
						break;
					}
				}
			}
			_x = p.getX();
			_y = p.getY();
			_Common::gotoXY(_x, _y);
			cout << " ";
		}
		//
		p = _undo.top();
		_undo.pop();
		for (int i = 0; i < _b->getSize(); i++) {
			for (int j = 0; j < _b->getSize(); j++) {
				if (_b->getXAt(i, j) == p.getX() && _b->getYAt(i, j) == p.getY())
				{
					_b->setCheckAt(i, j, 0);
					break;
				}
			}
		}
		_x = p.getX();
		_y = p.getY();
		_Common::gotoXY(_x, _y);
		cout << " ";
		_Common::gotoXY(_x, _y);

	}
}
void _Game::ResetStack()
{
	while (_undo.empty()!=1)
	{
		_undo.pop();
	}
}
void _Game::exitGame()
{
	system("cls");
	_loop = false;
}
bool _Game::processCheckBoard()
{
	switch (_b->checkBoard(_x, _y, _turn))
	{
	case -1:
		Beep(700, 200); //tạo tiếng kêu thanh
		_Common::textcolor(12);
		printf("x");
		_Common::textcolor(7);
		break;
	case 1:
		Beep(700, 200); //tạo tiếng kêu thanh
		_Common::textcolor(10);
		printf("o");
		_Common::textcolor(7);
		break;
	case 0:
		Beep(400, 200); //tạo tiếng kêu trầm
		return false; //Khi đánh vào ô đánh rồi
	}
	return true;
}
int _Game::processFinish()
{
	int pWhoWin = _b->testBoard();
	switch (pWhoWin)
	{
	case -1: case 1: case 0:
		PlaySound("musicwin.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
		HieuUng(pWhoWin);
	case 2:
		_turn = !_turn; // Đổi lượt nếu không có gì xảy ra
	}
	_Common::gotoXY(_x, _y);//Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
	return pWhoWin;
}
void _Game::moveRight()
{
	if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1))
	{
		_x += 4;
		_Common::gotoXY(_x, _y);
	}

}
void _Game::moveLeft()
{
	if (_x > _b->getXAt(0, 0))
	{
		_x -= 4;
		_Common::gotoXY(_x, _y);
	}

}
void _Game::moveDown()
{
	if (_y < _b->getYAt(_b->getSize() - 1, _b->getSize() - 1))
	{
		_y += 2;
		_Common::gotoXY(_x, _y);
	}
}
void _Game::moveUp()
{
	if (_y > _b->getYAt(0, 0))
	{
		_y -= 2;
		_Common::gotoXY(_x, _y);
	}
}
void _Game::ShowInfo()
{
	_Common::textcolor(11);
	_Common::DrawTable(_b->getLeft() + 4 * _b->getSize() + 6, _b->getTop(), 24, 4, 2, 2);
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 8, _b->getTop() + 1);
	_Common::DrawRectangle(_b->getLeft() + 4 * _b->getSize() + 6, _b->getTop() + 4, 24, 13);
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 6, _b->getTop() + 4);
	cout << char(195);
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 30, _b->getTop() + 4);
	cout << char(180);
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 18, _b->getTop() + 4);
	cout << char(193);
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 8, _b->getTop() + 1);
	_Common::textcolor(15);
	cout << "Player ";
	_Common::textcolor(12);
	cout << "X";
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 12, _b->getTop() + 3);
	_Common::textcolor(13);
	cout << _winX;
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 20, _b->getTop() + 1);
	_Common::textcolor(15);
	cout << "Player ";
	_Common::textcolor(10);
	cout << "O";
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 24, _b->getTop() + 3);
	_Common::textcolor(13);
	cout << _winY;
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 8, _b->getTop() + 28);
	_Common::textcolor(14);
	cout << "L: Save game  ";
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 8, _b->getTop() + 29);
	cout << "Esc: Quit game";
	_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 8, _b->getTop() + 31);
	cout << "SPACE: Undo";
	_Common::textcolor(7);



}
void _Game::printXO()
{
	if (_turn == true)
	{
		_Common::textcolor(12);
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 6);
		cout << "Y88b   d88P " << endl;
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 7);
		cout << " Y88b d88P " << endl;
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 8);
		cout << "  Y88o88P  " << endl;
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 9);
		cout << "   Y888P   " << endl;
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 10);
		cout << "   d888b    " << endl;
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 11);
		cout << "  d88888b   " << endl;
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 12);
		cout << " d88P Y88b  " << endl;
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 13);
		cout << "d88P   Y88b " << endl;
	}
	else
	{
		_Common::textcolor(10);
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 6);
		cout << " .d88888b. " << endl;
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 7);
		cout << "d88P\" \"Y88b" << endl;
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 8);
		cout << "888     888" << endl;
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 9);
		cout << "888     888" << endl;
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 10);
		cout << "888     888" << endl;
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 11);
		cout << "888     888" << endl;
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 12);
		cout << "Y88b. .d88P" << endl;
		_Common::gotoXY(_b->getLeft() + 4 * _b->getSize() + 13, _b->getTop() + 13);
		cout << " \"Y88888P\" " << endl;
	}
	_Common::textcolor(7);

}
void _Game::playGame(bool isLoad, int isBOT)
{
	system("cls");
	_BOT Com(_b); //Khởi tạo máy đánh
	int fisrtmoveofBOT = 0; //Biến xác định có phải nước đi đầu tiên của máy
	if (isLoad == 0 && isBOT == 2) fisrtmoveofBOT = 1; //Nếu là máy đánh trước
	if (isLoad == 1) startLoadgame(); //Nếu mở game đã lưu trước, dùng hàm startLoadgame để không reset lại các giá trị
	else startGame();
	while (isContinue())
	{
		//Nếu là máy đánh trước và là nước đi đầu tiên của máy, máy sẽ đánh giữa bàn cờ
		if (isBOT == 2 && fisrtmoveofBOT==1)
		{
			_Point Index = Com.GetMoveOfCom(-1, 1, 1);
			_x = _b->getXAt(Index.getY(), Index.getX());
			_y = _b->getYAt(Index.getY(), Index.getX());
			fisrtmoveofBOT = 0;

			_Common::gotoXY(_x, _y);
			processCheckBoard();
			processFinish();
		}
		//Người đánh
		waitKeyBoard();
		if (getCommand() == 27)
		{
			if (askSaveGame()) saveGame(isBOT);
			exitGame();
		}
		else
		{
			switch (getCommand())
			{
			case 'A':
				moveLeft();
				break;
			case 'W':
				moveUp();
				break;
			case 'S':
				moveDown();
				break;
			case 'D':
				moveRight();
				break;
			case 'L':
				saveGame(isBOT);
				startLoadgame();
				break;
			case 32: //undo
				Undo(isBOT);
				break;
			case 13:
				//Đánh dấu bàn cờ, sau đó kiểm tra và xử lý thắng/thua/hòa/tiếp tục
				if (processCheckBoard())
				{
					_Point newpoint;
					newpoint = _Point(_x, _y, -2 * _turn + 1);
					_undo.push(newpoint);    //Đưa điểm vừa mới đánh vào ngăn xếp undo
					int whoWin = processFinish();
					switch (whoWin)
					{
					case -1: case 1: case 0:
						if (whoWin == -1) _winX++;
						if (whoWin == 1) _winY++;
						startLoadgame();
						if (askContinue() == 0) exitGame();
						else startGame();
						break;
					}
					if (_loop == 0) break;

					printXO();
					_Common::gotoXY(_x, _y);

					//Máy đánh
					if (isBOT!=0)
					{
						_Point Index;
						if (isBOT==1) Index = Com.GetMoveOfCom(1, -1);
						else Index = Com.GetMoveOfCom(-1, 1);
						_x = _b->getXAt(Index.getY(), Index.getX());
						_y = _b->getYAt(Index.getY(), Index.getX());
						//Đưa điểm vừa mới đánh vào ngăn xếp undo
						_Point newpoint;
						newpoint = _Point(_x, _y, -2 * _turn + 1);
						_Common::gotoXY(_x, _y);
						_undo.push(newpoint);    
						//Kiểm tra thắng thua
						if (processCheckBoard())
						{
							int whoWin = processFinish();
							switch (whoWin)
							{
							case -1: case 1: case 0:
								if (whoWin == -1) _winX++;
								if (whoWin == 1) _winY++;
								startLoadgame();
								if (askContinue() == 0) exitGame();
								else startGame();
								if (isBOT == 2) fisrtmoveofBOT = 1;
								break;
							}
						}
						if (_loop == 0) break;
						printXO();
						_Common::gotoXY(_x, _y);
					}
				}
			}
		}
	}
	//Reset số trận thắng khi kết thúc game
	_winX = 0;
	_winY = 0;
	//Reset lại ngăn xếp
	ResetStack();
	system("cls");
}
bool _Game::saveGame(int isBOT)
{
	ofstream outfile;
	char filename[255];
	_Common::textcolor(11);
	_Common::DrawRectangle(13, 8, 30, 7, 1);
	_Common::gotoXY(18, 10);
	_Common::textcolor(14);
	cout << "Nhap duong dan file: ";
	_Common::textcolor(15);
	_Common::gotoXY(17, 11);
	cin >> filename;
	outfile.open(filename);
	if (outfile.fail())
	{
		_Common::textcolor(11);
		_Common::DrawRectangle(13, 8, 30, 7, 1);
		_Common::gotoXY(18, 10);
		_Common::textcolor(14);
		cout << "Cannot open this file";
		_Common::gotoXY(18, 11);
		cout << "  Fail to save game";
		_getch();
		return false;
	}
	outfile << _b->getSize() << endl;
	outfile << _b->getLeft() << " " << _b->getTop() << endl;
	for (int i = 0; i < _b->getSize(); i++)
	{
		for (int j = 0; j < _b->getSize(); j++)
		{
			outfile << _b->getCheckAt(i, j) << " ";
		}
		outfile << endl;
	}
	outfile << _turn << endl;
	outfile << _x << " " << _y << endl;
	outfile << _winX << " " << _winY << endl;
	outfile << isBOT << endl;
	outfile.close();
	_Common::textcolor(14);
	_Common::DrawRectangle(13, 8, 30, 7, 1);
	_Common::gotoXY(18, 10);
	_Common::textcolor(14);
	cout << "Save game successfully";
	_getch();
	return true;
}

bool _Game::loadGame(int &isBOT)
{
	system("cls");
	ifstream infile;
	char filename[255];
	_Common::textcolor(11);
	_Common::DrawRectangle(20, 8, 60, 7);
	_Common::gotoXY(40, 9);
	_Common::textcolor(14);
	cout << "Nhap duong dan file: ";
	_Common::textcolor(15);
	_Common::gotoXY(22, 11);
	cin >> filename;
	infile.open(filename);
	if (infile.fail())
	{
		_Common::gotoXY(23, 12);
		_Common::textcolor(14);
		_Common::DrawRectangle(20, 8, 60, 7,1);
		_Common::gotoXY(35, 11);
		cout << "Error: Cannot open this file";
		_getch();
		return false;
	}
	int temp, size = 0, left = 0, top = 0;
	infile >> size;
	infile >> left;
	infile >> top;
	delete _b;
	_b = new _Board(size, left, top);
	for (int i = 0; i < _b->getSize(); i++)
	{
		for (int j = 0; j < _b->getSize(); j++)
		{
			infile >> temp;
			_b->_pArr[i][j].setX(4 * j + left + 2); // Trùng với hoành độ màn hình bàn cờ
			_b->_pArr[i][j].setY(2 * i + top + 1); // Trùng với tung độ màn hình bàn cờ
			_b->setCheckAt(i, j, temp);
		}
	}
	infile >> temp;
	_turn = temp;
	infile >> temp;
	_x = temp;
	infile >> temp;
	_y = temp;
	infile >> temp;
	_winX = temp;
	infile >> temp;
	_winY = temp;
	infile >> temp;
	isBOT = temp;
	return true;
}
void _Game::HieuUng(int n)
{
	system("cls");
	string Chuoi[2];
	Chuoi[0] = "=";
	Chuoi[1] = "|";
	int x = 0;
	int y = 0;
	int flag1 = 0;
	CONTROL tt = RIGHT;
	while (flag1 == 0)
	{
		_Common::gotoXY(x, y);
		_Common::textcolor(8 + rand() % 8);
		if (tt == RIGHT || tt == LEFT)
		{
			cout << Chuoi[0];
		}
		else cout << Chuoi[1];

		// xử lý chạm biên
		if (x == Width - 1 && y == 0)//góc phải trên
			tt = DOWN;
		if (y == Height - 1 && x == Width - 1)//góc phải dưới
			tt = LEFT;
		if (x == 0 && y == Height - 1) //góc trái dưới
			tt = UP;



		if (tt == LEFT)
			x--;
		else if (tt == RIGHT)
			x++;
		else if (tt == DOWN)
			y++;
		else if (tt == UP)
			y--;
		if (y == 0 && x == 0)
			flag1 = 1;
		Sleep(1);//nhịp game

	}
	int flag2 = 0;
	x = 1;
	//A.x = (Width - A.Chuoi.size()) / 2;
	y = 1;
	tt = RIGHT;
	while (flag2 == 0)
	{
		_Common::gotoXY(x, y);
		_Common::textcolor(8 + rand() % 8);
		if (tt == RIGHT || tt == LEFT)
		{
			cout << Chuoi[0];
		}
		else cout << Chuoi[1];

		// xử lý chạm biên
		if (x == Width - 2 && y == 1) //góc phải trên
			tt = DOWN;
		if (y >= Height - 2 && x == Width - 2) //góc phải dưới
			tt = LEFT;
		if (x == 1 && y == Height - 2) //góc trái dưới
			tt = UP;

		if (tt == LEFT)
			x--;
		else if (tt == RIGHT)
			x++;
		else if (tt == DOWN)
			y++;
		else if (tt == UP)
			y--;
		if (y == 1 && x == 1)
			flag2 = 1;
		Sleep(1);//nhịp game
	}
	while (true)
	{
		x = 29;
		y = 14;
		_Common::gotoXY(x, y);
		_Common::textcolor(8 + rand() % 8);
		if (n == -1) PrintXWin(x, y);
		if (n == 1) PrintYWin(x, y);
		if (n == 0) PrintDraw(x, y);
		if (_kbhit())	// phát hiện có phím nhấn vào
		{
			char key = _getch();
			if (key == 13)
			{
				break;//để vòng lặp dừng lại
			}
		}
		Sleep(200);//nhịp game
	}
	_Common::textcolor(7); //trả lại màu mặc định
}
void _Game::PrintXWin(int x, int y)
{
	_Common::gotoXY(x, y);
	cout << "Y88b   d88P      888       888 d8b          " ;
	_Common::gotoXY(x, y+1);
	cout << " Y88b d88P       888   o   888 Y8P          " ;
	_Common::gotoXY(x, y+2);
	cout << "  Y88o88P        888  d8b  888              " ;
	_Common::gotoXY(x, y+3);
	cout << "   Y888P         888 d888b 888 888 88888b.  " ;
	_Common::gotoXY(x, y+4);
	cout << "   d888b         888d88888b888 888 888 \"88b " ;
	_Common::gotoXY(x, y+5);
	cout << "  d88888b        88888P Y88888 888 888  888 " ;
	_Common::gotoXY(x, y+6);
	cout << " d88P Y88b       8888P   Y8888 888 888  888 " ;
	_Common::gotoXY(x, y+7);
	cout << "d88P   Y88b      888P     Y888 888 888  888 " ;
}
void _Game::PrintYWin(int x, int y)
{
	_Common::gotoXY(x, y);
	cout << " .d88888b.       888       888 d8b          " ;
	_Common::gotoXY(x, y+1);
	cout << "d88P\" \"Y88b      888   o   888 Y8P          " ;
	_Common::gotoXY(x, y+2);
	cout << "888     888      888  d8b  888              " ;
	_Common::gotoXY(x, y+3);
	cout << "888     888      888 d888b 888 888 88888b.  " ;
	_Common::gotoXY(x, y+4);
	cout << "888     888      888d88888b888 888 888 \"88b " ;
	_Common::gotoXY(x, y+5);
	cout << "888     888      88888P Y88888 888 888  888 " ;
	_Common::gotoXY(x, y+6);
	cout << "Y88b. .d88P      8888P   Y8888 888 888  888 " ;
	_Common::gotoXY(x, y+7);
	cout << " \"Y88888P\"       888P     Y888 888 888  888 " ;
}
void _Game::PrintDraw(int x, int y)
{
	_Common::gotoXY(x, y);
	cout << "8888888b.  8888888b.         d8888 888       888" ;
	_Common::gotoXY(x, y+1);
	cout << "888  \"Y88b 888   Y88b       d88888 888   o   888" ;
	_Common::gotoXY(x, y+2);
	cout << "888    888 888    888      d88P888 888  d8b  888" ;
	_Common::gotoXY(x, y+3);
	cout << "888    888 888   d88P     d88P 888 888 d888b 888" ;
	_Common::gotoXY(x, y+4);
	cout << "888    888 8888888P\"     d88P  888 888d88888b888" ;
	_Common::gotoXY(x, y+5);
	cout << "888    888 888 T88b     d88P   888 88888P Y88888" ;
	_Common::gotoXY(x, y+6);
	cout << "888  .d88P 888  T88b   d8888888888 8888P   Y8888" ;
	_Common::gotoXY(x, y+7);
	cout << "8888888P\"  888   T88b d88P     888 888P     Y888" ;
}