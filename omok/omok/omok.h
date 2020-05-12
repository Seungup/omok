#pragma once
#include "define.h"
class Omok
{
public:
	Omok();
	~Omok();
	void incGameTime();
	void GAME_printBinMap();
	void GAME_printGameSet();
	void GAME_showWhosTurn();
	void showGameTime();
	int GAME_playGame(int x, int y);
	int GAME_whosTurn();
	int GAME_isWin();
	int GAME_isThere(int x, int y);
	int AI_isAble(int x, int y);
	int AI_whosTurn();
	void AI_printBinMap();
	void AI_wightRule(int x, int y);
	int char2int(char alphabet);
	void AI_turn();

private:
	int AI_Wight[19][19];
	int GAME_mapArray[19][19];
	int GAME_gameTime;
	int before_W;
};