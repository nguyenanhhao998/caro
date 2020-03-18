#ifndef __GAME_H__
#define __GAME_H__
#include "_Board.h"
#include "_BOT.h"
#include <fstream>
#include <time.h>
#include <string>
#include <stack>
#pragma comment (lib, "winmm.lib")
#define COLOR_CHOOSE 63    //Màu thao tác đang được chọn
#define COLOR_NOTCHOOSE 11

#define Width 99
#define Height 39
enum CONTROL { UP, DOWN, LEFT, RIGHT, ENTER, NOTHING };  //Tượng trưng cho các điều khiển điều hướng
class _Game
{
private:
	_Board* _b; //Một bàn cờ
	stack <_Point> _undo; //Ngăn xếp hỗ trợ việc undo;
	bool _turn;//lượt chơi: true lượt người một & false lượt người thứ hai
	int _x, _y; //Tọa độ hiện hành của nháy chuột
	int _winX, _winY;
	int _command; //Phím gõ từ người dùng
	bool _loop; //Biến quyết định thoát game hay không
public:
	_Game(int, int, int);
	~_Game();
	int getCommand();
	bool isContinue();
	char waitKeyBoard(); //Hàm nhận phím từ người dùng
	char askContinue();
	bool askSaveGame();
	void startGame(); //Hàm bắt đầu game
	void startLoadgame();
	void Undo(int isBOT); //Hàm lùi lại 1 bước
	void ResetStack(); //Làm mới ngăn xếp
	void exitGame();  //Ham kết thúc game
	int processFinish();
	bool processCheckBoard();
	void moveRight();
	void moveLeft();
	void moveDown();
	void moveUp();
	//Cac ham lien quan den man hinh chinh cua game
	void ShowInfo();
	void printXO();
	//Hàm play game: isload=0: chơi game mới, isload=1: chơi game đã lưu
	//               BOT=0: 2 người chơi, BOT=1: chơi với máy, máy đánh sau, BOT=2: máy đánh trước
	void playGame(bool isload, int isBOT);
	bool saveGame(int isBOT);
	bool loadGame(int &isBOT);
	//Cac ham lien quan den hieu ung thang thua
	void HieuUng(int n);
	void PrintXWin(int, int);
	void PrintYWin(int, int);
	void PrintDraw(int, int);
};

#endif