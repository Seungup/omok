#include "omok.h"

int main() {

	// AI는 검은돌
	Omok game = Omok();
	cout << "this is my first C++ programing thx for help Google" << endl;
	cout << "this program is only use <iostream>" << endl;
	cout << "this program code is suck do not see" << endl;
	cout << "this program have a lot of bugs" << endl;
	system("pause");

	char x;
	int y;

	while (1) {
		while (1)
		{
			system("cls");
			game.showGameTime();
			cout << endl << endl << endl;
			game.GAME_printBinMap();
			game.GAME_showWhosTurn();
			cout << "\nX con = Alphabets" << endl;
			cout << "Y con = integers" << endl;
			cout << "set : ";
			cin >> x >> y;
			if (cin.fail()) {
				cin.clear();
			}
			else
			{
				break;
			}
		}
		if (game.GAME_playGame(game.char2int(x), y) == 0)
		{
			game.AI_wightRule(game.char2int(x), y);
			//game.AI_printBinMap();
			game.incGameTime();
			game.AI_turn();
			game.incGameTime();
			//cout << endl;
			//game.AI_printBinMap();
			//system("pause");
			continue;
		}

		if (game.GAME_isWin()) {
			break;
		}
	}

	game.GAME_printGameSet();

	return 0;

}