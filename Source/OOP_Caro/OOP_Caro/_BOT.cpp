#include "_BOT.h"



_BOT::_BOT()
{
}


_BOT::~_BOT()
{
}
_BOT::_BOT(_Board* b)
{
	this->Board = b;
	eBoard = _EvaluatingBoard(b->getSize());
	int attackScore[] = { 0, 2, 18, 162, 2458, 13122, 118098, 1062882, 9565938 };
	int defenceScore[] = { 0, 1, 9, 81, 729, 6561, 59049, 531441, 4782969 };

	for (int i = 0; i < 9; i++)
	{
		this->attackScore[i] = attackScore[i];
		this->defenceScore[i] = defenceScore[i];
	}
}
bool _BOT::IsGameOver(int i, int j)
{
	int test = Board->testPoint(i, j);
	if (test == -1 || test == 1) return true;
	return false;
}
int _BOT::GameOver(int i, int j)
{
	return Board->testPoint(i, j);
}
void _BOT::EvaluateBoard(int checkObject, int checkBOT, int checkPlayer, int xvl, int yvl)
{
	int iBOT;												// Số quân đồng minh
	int iPlayer;											// Số quân địch
	_Point lowerBound(0, 0);									// Tọa độ mặc định bắt đầu vòng lặp
	_Point upperBound(Board->getSize(), Board->getSize());	// Tọa độ mặc định kết thúc vòng lặp
	// Hiệu chỉnh lại tọa độ bắt đầu và kết thúc tùy theo hướng đang đánh giá
	if (xvl == -1)
		lowerBound.setX(lowerBound.getX() + 4);
	if (yvl == -1)
		lowerBound.setY(lowerBound.getY() + 4);
	if (xvl == 1)
		upperBound.setX(upperBound.getX() - 4);
	if (yvl == 1)
		upperBound.setY(upperBound.getY() - 4);
	for (int y = lowerBound.getY(); y < upperBound.getY(); y++)
	{
		for (int x = lowerBound.getX(); x < upperBound.getX(); x++)
		{
			iBOT = 0;
			iPlayer = 0;
			// Đếm theo hướng xem có bao nhiêu đồng minh, quân địch
			for (int i = 0; i < 5; i++)
			{
				if (Board->getCheckAt(y + yvl * i, x + xvl * i) == checkBOT)
					iBOT++;

				if (Board->getCheckAt(y + yvl * i, x + xvl * i) == checkPlayer)
					iPlayer++;
			}
			if (iBOT * iPlayer == 0 && iBOT != iPlayer)
			{
				for (int i = 0; i < 5; i++)
				{
					if (Board->getCheckAt(y + yvl * i, x + xvl * i) == 0) //Nếu là ô trống
					{
						if (iBOT == 0)
						{
							// Dựa vào đối tượng đang xét là ai để đánh giá điểm hợp lệ
							if (checkObject == checkBOT)
								eBoard._Value[y + yvl * i][x + xvl * i] += defenceScore[iPlayer];
							else
								eBoard._Value[y + yvl * i][x + xvl * i] += attackScore[iPlayer];
						}
						if (iPlayer == 0)
						{
							// Dựa vào đối tượng đang xét là ai để đánh giá điểm hợp lệ
							if (checkObject == checkPlayer)
								eBoard._Value[y + yvl * i][x + xvl * i] += defenceScore[iBOT];
							else
								eBoard._Value[y + yvl * i][x + xvl * i] += attackScore[iBOT];
						}
						// 4 quân trên một đường (có thể của địch hoặc của ta) thì ưu tiên cho nước đi này
						if (!(Board->OutOfRange(x + xvl * (i - 1), y + yvl * (i - 1)) || Board->OutOfRange(x + xvl * (i + 1), y + yvl * (i + 1))))
						{
							if ((iBOT == 4 || iPlayer == 4) && Board->getCheckAt(y + yvl * (i - 1), x + xvl * (i - 1)) == 0 && Board->getCheckAt(y + yvl * (i + 1), x + xvl * (i + 1)) == 0)
								eBoard._Value[y + yvl * i][x + xvl * i] *= 3;
						}
					}
				}
			}

		}
	}
}
void _BOT::EvaluateBoard(int checkObject, int checkBOT, int checkPlayer)
{
	// Khởi tạo giá trị mặc định cho bảng
	eBoard.ResetValue();

	// Đánh giá bảng giá trị thông qua 4 hướng
	EvaluateBoard(checkObject, checkBOT, checkPlayer, 1, 0); //Đường ngang
	EvaluateBoard(checkObject, checkBOT, checkPlayer, 0, 1); //Đường dọc
	EvaluateBoard(checkObject, checkBOT, checkPlayer, 1, 1);  //Đường chéo chính
	EvaluateBoard(checkObject, checkBOT, checkPlayer, 1, -1);  //Đường chéo phụ
}
void _BOT::MoveGeneration(int checkBOT, int checkPlayer)
{
	//Xét đến 1 độ sâu nhất định
	if (currDepth >= MAX_DEPTH) return;
	currDepth++;
	_Point BOTIndex;		// Chỉ số mảng của nước đi đang xét hiện tại của máy
	_Point playerIndex;	// Chỉ số mảng của nước đi đang xét hiện tại của người chơi
	bool foundWorstWay = false;
	// Đánh giá nước đi tốt cho máy
	EvaluateBoard(checkBOT, checkBOT, checkPlayer);

	for (int i = 0; i < MAX_BREADTH; i++)
	{
		BOTIndex = eBoard.GetIndexMax();
		BOTMoves[i] = BOTIndex;
		eBoard._Value[BOTIndex.getY()][BOTIndex.getX()] = 0;
	}
	for (int i = 0; i < MAX_BREADTH; i++)
	{
		BOTIndex = BOTMoves[i];
		bestMoves[currDepth] = BOTIndex;
		Board->setCheckAt(BOTIndex.getY(), BOTIndex.getX(), checkBOT);

		//Đánh giá nước đi tốt cho người chơi
		EvaluateBoard(checkPlayer, checkBOT, checkPlayer);

		for (int j = 0; j < MAX_BREADTH; j++)
		{
			playerIndex = eBoard.GetIndexMax();
			playerMoves[j] = playerIndex;
			eBoard._Value[playerIndex.getY()][playerIndex.getX()] = 0;
		}
		for (int j = 0; j < MAX_BREADTH; j++)
		{
			playerIndex = playerMoves[j];
			Board->setCheckAt(playerIndex.getY(), playerIndex.getX(), checkPlayer);

			if (GameOver(BOTIndex.getY(),BOTIndex.getX()) == checkBOT)
				foundBestWay = true;

			if (GameOver(playerIndex.getY(), playerIndex.getX()) == checkPlayer)
				foundWorstWay = true;

			if (foundBestWay || foundWorstWay)
			{
				Board->setCheckAt(BOTIndex.getY(), BOTIndex.getX(), 0);
				Board->setCheckAt(playerIndex.getY(), playerIndex.getX(), 0);
				return;
			}

			MoveGeneration(checkBOT, checkPlayer);

			Board->setCheckAt(playerIndex.getY(), playerIndex.getX(), 0);
		}
		Board->setCheckAt(BOTIndex.getY(), BOTIndex.getX(), 0);
	}
}
void _BOT::GenerateResult(int checkBOT, int checkPlayer)
{
	for (int i = 0; i < MAX_DEPTH; i++)
		bestMoves[i] = _Point();
	for (int i = 0; i < MAX_BREADTH; i++)
		BOTMoves[i] = _Point();
	for (int i = 0; i < MAX_BREADTH; i++)
		playerMoves[i] = _Point();
	foundBestWay = false;
	currDepth = -1;

	MoveGeneration(checkBOT, checkPlayer);
}
_Point _BOT::GetMoveOfCom(int checkBOT, int checkPlayer, int firstMove)
{
	_Point index;
	if (firstMove)
	{
		index.setX(Board->getSize() / 2-2);
		index.setY(Board->getSize() / 2-2);
		return index;
	}
	GenerateResult(checkBOT, checkPlayer);
	if (foundBestWay)
	{
		index = bestMoves[0];
	}
	else
	{
		EvaluateBoard(checkBOT, checkBOT, checkPlayer);
		index = eBoard.GetIndexMax();
	}

	return index;
}