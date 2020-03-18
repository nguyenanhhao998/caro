#ifndef __BOT_H__
#define __BOT_H__
#include "_Board.h"
#include "_EvaluatingBoard.h"
//Máy chơi
class _BOT
{
private:
	static const int MAX_DEPTH = 20;
	static const int MAX_BREADTH = 10;

	_Board* Board;
	_EvaluatingBoard eBoard;
	bool foundBestWay;
	int currDepth;
	long attackScore[9];
	long defenceScore[9];
	_Point bestMoves[MAX_DEPTH];
	_Point BOTMoves[MAX_BREADTH];
	_Point playerMoves[MAX_BREADTH];

public:
	_BOT();
	~_BOT();
	_BOT(_Board*);
	//Kiểm tra thắng thua
	bool IsGameOver(int, int);
	//Trả về người thắng
	int GameOver(int, int);	
	//Đánh giá các nước đi theo từng hướng thông qua xvl và yvl
	void EvaluateBoard(int checkObject, int checkBOT, int checkPlayer, int xvl, int yvl);
	//Đánh bảng giá trị thông qua 4 hướng
	void EvaluateBoard(int checkObject, int checkBOT, int checkPlayer);
	//Tạo ra các nước đi
	void MoveGeneration(int checkBOT, int checkPlayer);
	void GenerateResult(int checkBOT, int checkPlayer);
	//Quyết định nước đi của máy
	_Point GetMoveOfCom(int checkBOT, int checkPlayer, int fistMove=0);
};



#endif

