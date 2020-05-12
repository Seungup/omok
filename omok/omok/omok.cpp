/*

가중치 룰 :

0. 돌을 둔 곳의 가중치는 항상 0이된다.
1. 인접한 곳에 돌이 있을 경우 돌의 개수만큼 (|, /, \, ㅡ) 의 각 돌의 끝자락에 자기자신의 돌을 제외한 돌의 개수만큼 흑의 경우 +N, 백의 경우 -N 시켜준다.
2. 상대방의 가중치의 절대값이 나의 최고 가중치 절대값의 두배 이상 날 경우 상대방 최고 가중치에 돌을 둔다.

*/

#include "omok.h"

Omok::Omok()
{
	cout << "init now.." << endl;
	for (int i = 0; i < GameX; i++) {
		for (int j = 0; j < GameY; j++) {
			AI_Wight[i][j] = 0;
			GAME_mapArray[i][j] = 0;
		}
	} 
	GAME_gameTime = 0;
	before_W = 0;
}

Omok::~Omok()
{

}

void Omok::incGameTime() {
	GAME_gameTime++;
}


int Omok::AI_whosTurn() {
	if (GAME_gameTime % 2 == 0) {
		return BLACK_W;
	}
	else
	{
		return WHITE_W;
	}
}


void Omok::AI_printBinMap() {
	for (int i = 0; i < GameY; i++) {
		for (int j = 0; j < GameX; j++) {
			if (AI_Wight[i][j] >= 0) {
				cout << " " << AI_Wight[i][j] << "  ";
			}
			else if (AI_Wight[i][j] < 0)
			{
				cout << AI_Wight[i][j] << "  ";
			}
			else
			{
				cout << AI_Wight[i][j];
			}
		}
		cout << endl;
	}
}

int Omok::AI_isAble(int x, int y) {
	if (GAME_mapArray[y][x] == BlackStone || GAME_mapArray[y][x] == WhiteStone) {
		return 0;
	}
	else
	{
		return 1;
	}
}


int Omok::char2int(char alphabet) {
	if ((int)alphabet <= (int)'S') {
		return (int)alphabet - (int)'A';
	}
	else if ((int)alphabet <= (int)'s')
	{
		return (int)alphabet - (int)'a';
	}
	else
	{
		return 0;
	}
}


void Omok::AI_wightRule(int x, int y)
{
	int new_y = y;
	int new_x = x;
	int count = 0;

	if (y == 0)
	{
		if (x == 0)
		{
			AI_Wight[y][x] = 0;
			// 직선 : 현 위치 -> 우
			while (1) {
				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || 
					GAME_mapArray[new_y][new_x + 1] == BlankSpace) {
					new_x++;
				}
				else {
					break;
				}

				if (GAME_mapArray[new_y][new_x] == BlankSpace) {
					break;
				}

				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {
					count = 1;
					new_x++;
					break;
				}
			}

			int left = (new_x - x);

			if (count == 1) {
				left = (new_x - x - 1);
			}

			int left_x = new_x;
			int left_y = new_y;

			new_x = x;
			new_y = y;

			if (count == 0) {
				if (GAME_whosTurn() == BlackStone) {
					AI_Wight[left_y][left_x] += left;
					AI_Wight[y][x] = 0;
				}
				else
				{
					AI_Wight[left_y][left_x] += -(left);
					AI_Wight[y][x] = 0;
				}
			}
			else
			{
				count = 0;
				if (GAME_whosTurn() == BlackStone) {
					AI_Wight[left_y][left_x] += -1;
					AI_Wight[y][x] = 0;
				}
				else
				{
					AI_Wight[left_y][left_x] += -1;
					AI_Wight[y][x] = 0;
				}
			}

			new_x = x;
			new_y = y;

			// 막대 : 현 위치 -> 아래

			while (1) {
				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || 
					GAME_mapArray[new_y + 1][new_x] == BlankSpace) {
					new_y++;
				}
				else {
					break;
				}

				if (GAME_mapArray[new_y][new_x] == BlankSpace) {
					break;
				}

				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {
					count = 1;
					new_y++;
					break;
				}
			}

			int stick_up = (new_y - y);

			if (count == 1) {
				stick_up = (new_y - y - 1);
			}

			int stick_up_x = new_x;
			int stick_up_y = new_y;

			new_x = x;
			new_y = y;

			if (count == 0) {
				if (GAME_whosTurn() == BlackStone) {
					AI_Wight[stick_up_y][stick_up_x] += stick_up;
					AI_Wight[y][x] = 0;
				}
				else
				{
					AI_Wight[stick_up_y][stick_up_x] += -(stick_up);
					AI_Wight[y][x] = 0;
				}
			}
			else
			{
				count = 0;
				if (GAME_whosTurn() == BlackStone) {
					AI_Wight[stick_up_y][stick_up_x] += -1;
					AI_Wight[y][x] = 0;
				}
				else
				{
					AI_Wight[stick_up_y][stick_up_x] += 1;
					AI_Wight[y][x] = 0;
				}
			}

			// 우측 대각선 : 현 위치 -> 우측 하단

			while (1) {
				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || 
					GAME_mapArray[new_y + 1][new_x + 1] == BlankSpace) {
					new_x++;
					new_y++;
				} else { break; }


				if (GAME_mapArray[new_y][new_x] == BlankSpace) { break; }



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {
					count = 1;
					new_x++;
					new_y++;
					break;
				}
			}



			int right_dia_line_down = (new_x - x);

			if (count == 1) {
				right_dia_line_down = (new_x - x - 1);
			}

			int right_dia_line_down_x = new_x;
			int right_dia_line_down_y = new_y;

			new_x = x;
			new_y = y;

			if (count == 0) {
				if (GAME_whosTurn() == BlackStone) {
					AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += right_dia_line_down;
					AI_Wight[y][x] = 0;
				}
				else
				{
					AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += -(right_dia_line_down);
					AI_Wight[y][x] = 0;
				}
			}
			else
			{
				count = 0;
				if (GAME_whosTurn() == BlackStone) {
					AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += -1;
					AI_Wight[y][x] = 0;
				}
				else
				{
					AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += 1;
					AI_Wight[y][x] = 0;
				}
			}
			new_x = x;
			new_y = y;
		}
		else if (x == 18)
		{
			AI_Wight[y][x] = 0;

			new_x = x;
			new_y = y;

			// 직선 : 현 위치 -> 좌
			while (1) {
				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || 
					GAME_mapArray[new_y][new_x - 1] == BlankSpace) {
					new_x--;
				}
				else {
					break;
				}

				if (GAME_mapArray[new_y][new_x] == BlankSpace) {
					break;
				}

				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {
					count = 1;
					new_x--;
					break;
				}
			}

			int right = (x - new_x);
			if (count == 1) {
				right = (x - new_x - 1);
			}

			int right_x = new_x;
			int right_y = new_y;

			if (count == 0) {
				if (GAME_whosTurn() == BlackStone) {
					AI_Wight[right_y][right_x] += right;
					AI_Wight[y][x] = 0;
				}
				else
				{
					AI_Wight[right_y][right_x] += -(right);
					AI_Wight[y][x] = 0;
				}
			}
			else
			{
				count = 0;
				if (GAME_whosTurn() == BlackStone) {
					AI_Wight[right_y][right_x] += -1;
					AI_Wight[y][x] = 0;
				}
				else
				{
					AI_Wight[right_y][right_x] += 1;
					AI_Wight[y][x] = 0;
				}
			}

			new_x = x;
			new_y = y;

			// 막대 : 현 위치 -> 아래

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || 
					GAME_mapArray[new_y + 1][new_x] == BlankSpace) {
					new_y++;
				}
				else 
				{
					break;
				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {
					break;
				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {
					count = 1;
					new_y++;
					break;
				}
			}



			int stick_up = (new_y - y);

			if (count == 1) {
				stick_up = (new_y - y - 1);
			}

			int stick_up_x = new_x;
			int stick_up_y = new_y;

			new_x = x;
			new_y = y;



			if (count == 0) {
				if (GAME_whosTurn() == BlackStone) {
					AI_Wight[stick_up_y][stick_up_x] += stick_up;
					AI_Wight[y][x] = 0;
				}
				else
				{
					AI_Wight[stick_up_y][stick_up_x] += -(stick_up);
					AI_Wight[y][x] = 0;
				}
			}
			else
			{
				count = 0;
				if (GAME_whosTurn() == BlackStone) {
					AI_Wight[stick_up_y][stick_up_x] += -1;
					AI_Wight[y][x] = 0;
				}
				else
				{
					AI_Wight[stick_up_y][stick_up_x] += 1;
					AI_Wight[y][x] = 0;
				}
			}



			// 좌측 대각선 : 현 위치 -> 좌측 하단

			while (1) {
				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || 
					GAME_mapArray[new_y + 1][new_x - 1] == BlankSpace) {
					new_x--;
					new_y++;
				}
				else {
					break;
				}

				if (GAME_mapArray[new_y][new_x] == BlankSpace) {
					break;
				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {
					count = 1;
					new_x--;
					new_y++;
					break;
				}
			}



			int left_dia_line_down = (new_y - y);

			if (count == 1) {
				left_dia_line_down = (new_y - y - 1);
			}

			int left_dia_line_down_x = new_x;
			int left_dia_line_down_y = new_y;

			if (count == 0) {
				if (GAME_whosTurn() == BlackStone) {
					AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += left_dia_line_down;
					AI_Wight[y][x] = 0;
				}
				else
				{
					AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += -(left_dia_line_down);
					AI_Wight[y][x] = 0;
				}
			}
			else
			{
				count = 0;
				if (GAME_whosTurn() == BlackStone) {
					AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += -1;
					AI_Wight[y][x] = 0;
				}
				else
				{
					AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += 1;
					AI_Wight[y][x] = 0;
				}
			}
		}
		else
		{
			AI_Wight[y][x] = 0;
			// 직선 : 현 위치 -> 우

			while (1) {
				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || 
					GAME_mapArray[new_y][new_x + 1] == BlankSpace) {
					new_x++;
				}
				else 
				{
					break;
				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {
					break;
				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {
					count = 1;
					new_x++;
					break;
				}
			}



			int left = (new_x - x);
			if (count == 1) {
				left = (new_x - x - 1);
			}
			int left_x = new_x;
			int left_y = new_y;

			new_x = x;

			new_y = y;



			// 직선 : 현 위치 -> 좌

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y][new_x - 1] == BlankSpace) {

					new_x--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x--;

					break;

				}

			}



			int right = (x - new_x);

			if (count == 1) {

				right = (x - new_x - 1);

			}

			int right_x = new_x;

			int right_y = new_y;



			if (GAME_whosTurn() == BlackStone) {

				AI_Wight[left_y][left_x] += right + left - 1;

				AI_Wight[right_y][right_x] += right + left - 1;



				if ((AI_Wight[left_y][left_x]) < (AI_Wight[right_y][right_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[left_y][left_x] += -1;

					}

				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[right_y][right_x] += -1;

					}

				}



				AI_Wight[y][x] = 0;

			}

			else

			{

				AI_Wight[left_y][left_x] += -(right + left - 1);

				AI_Wight[right_y][right_x] += -(right + left - 1);



				if ((AI_Wight[left_y][left_x]) < (AI_Wight[right_y][right_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[left_y][left_x] += 1;

					}

				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[right_y][right_x] += 1;

					}

				}



				AI_Wight[y][x] = 0;

			}





			new_x = x;

			new_y = y;



			// 막대 : 현 위치 -> 아래

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y + 1][new_x] == BlankSpace) {

					new_y++;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_y++;

					break;

				}

			}



			int stick_up = (new_y - y);

			if (count == 1) {

				stick_up = (new_y - y - 1);

			}

			int stick_up_x = new_x;

			int stick_up_y = new_y;



			new_x = x;

			new_y = y;

			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[stick_up_y][stick_up_x] += stick_up;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[stick_up_y][stick_up_x] += -(stick_up);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[stick_up_y][stick_up_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[stick_up_y][stick_up_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}



			// 우측 대각선 : 현 위치 -> 우측 하단

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y + 1][new_x + 1] == BlankSpace) {

					new_x++;

					new_y++;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x++;

					new_y++;

					break;

				}

			}



			int right_dia_line_down = (new_x - x);

			if (count == 1) {

				right_dia_line_down = (new_x - x - 1);

			}

			int right_dia_line_down_x = new_x;

			int right_dia_line_down_y = new_y;



			new_x = x;

			new_y = y;



			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += right_dia_line_down;

					AI_Wight[y][x] = 0;

				}

				else



				{

					AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += -(right_dia_line_down);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else



				{

					AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}



			// 좌측 대각선 : 현 위치 -> 좌측 하단

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y + 1][new_x - 1] == BlankSpace) {

					new_x--;

					new_y++;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x--;

					new_y++;

					break;

				}

			}



			int left_dia_line_down = (new_y - y);

			if (count == 1) {

				left_dia_line_down = (new_y - y - 1);

			}

			int left_dia_line_down_x = new_x;

			int left_dia_line_down_y = new_y;



			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += left_dia_line_down;

					AI_Wight[y][x] = 0;

				}

				else {

					AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += -(left_dia_line_down);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else {

					AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}

		}

	}

	else if (y == 18)

	{

		if (x == 0)

		{

			AI_Wight[y][x] = 0;

			// 직선 : 현 위치 -> 우

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y][new_x + 1] == BlankSpace) {

					new_x++;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x++;

					break;

				}

			}



			int left = (new_x - x);

			if (count == 1) {

				left = (new_x - x - 1);

			}

			int left_x = new_x;

			int left_y = new_y;



			new_x = x;

			new_y = y;



			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[left_y][left_x] += left;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[left_y][left_x] += -(left);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[left_y][left_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[left_y][left_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}



			// 막대 : 현 위치 -> 위

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y - 1][new_x] == BlankSpace) {

					new_y--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_y--;

					break;

				}

			}



			int stick_down = (y - new_y);

			if (count == 1) {

				stick_down = (y - new_y - 1);

			}

			int stick_down_x = new_x;

			int stick_down_y = new_y;



			new_x = x;

			new_y = y;



			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[stick_down_y][stick_down_x] += stick_down;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[stick_down_y][stick_down_x] += -(stick_down);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[stick_down_y][stick_down_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[stick_down_y][stick_down_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}





			// 좌측 대각선 : 현 위치 -> 우측 상단

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y - 1][new_x + 1] == BlankSpace) {

					new_x++;

					new_y--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x++;

					new_y--;

					break;

				}

			}



			int left_dia_line_up = (new_x - x);

			if (count == 1) {

				left_dia_line_up = (new_x - x - 1);

			}

			int left_dia_line_up_x = new_x;

			int left_dia_line_up_y = new_y;



			new_x = x;

			new_y = y;



			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += left_dia_line_up;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += -(left_dia_line_up);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}

		}





		else if (x == 18)

		{

			AI_Wight[y][x] = 0;





			// 직선 : 현 위치 -> 좌

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y][new_x - 1] == BlankSpace) {

					new_x--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x--;

					break;

				}

			}



			int right = (x - new_x);

			if (count == 1) {

				right = (x - new_x - 1);

			}

			int right_x = new_x;

			int right_y = new_y;



			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[right_y][right_x] += right;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[right_y][right_x] += -(right);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[right_y][right_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[right_y][right_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}











			new_x = x;

			new_y = y;





			// 막대 : 현 위치 -> 위

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y - 1][new_x] == BlankSpace) {

					new_y--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_y--;

					break;

				}

			}



			int stick_down = (y - new_y);

			if (count == 1) {

				stick_down = (y - new_y - 1);

			}

			int stick_down_x = new_x;

			int stick_down_y = new_y;



			new_x = x;

			new_y = y;

			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[stick_down_y][stick_down_x] += stick_down;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[stick_down_y][stick_down_x] += -(stick_down);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[stick_down_y][stick_down_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[stick_down_y][stick_down_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}



			// 우측 대각선 : 현 위치 -> 좌측 상단

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y - 1][new_x - 1] == BlankSpace) {

					new_x--;

					new_y--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x--;

					new_y--;

					break;

				}

			}



			int right_dia_line_up = (x - new_x);

			if (count == 1) {

				right_dia_line_up = (x - new_x - 1);

			}

			int right_dia_line_up_x = new_x;

			int right_dia_line_up_y = new_y;



			new_x = x;

			new_y = y;

			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += right_dia_line_up;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += -(right_dia_line_up);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}

		}

		else

		{

			AI_Wight[y][x] = 0;

			// 직선 : 현 위치 -> 우

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y][new_x + 1] == BlankSpace) {

					new_x++;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x++;

					break;

				}

			}



			int left = (new_x - x);

			if (count == 1) {

				left = (new_x - x - 1);

			}

			int left_x = new_x;

			int left_y = new_y;



			new_x = x;

			new_y = y;



			// 직선 : 현 위치 -> 좌

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y][new_x - 1] == BlankSpace) {

					new_x--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x--;

					break;

				}

			}



			int right = (x - new_x);

			if (count == 1) {

				right = (x - new_x - 1);

			}

			int right_x = new_x;

			int right_y = new_y;



			if (GAME_whosTurn() == BlackStone) {

				AI_Wight[left_y][left_x] += right + left - 1;

				AI_Wight[right_y][right_x] += right + left - 1;



				if ((AI_Wight[left_y][left_x]) < (AI_Wight[right_y][right_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[left_y][left_x] += -1;

					}

				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[right_y][right_x] += -1;

					}

				}



				AI_Wight[y][x] = 0;

			}

			else

			{

				AI_Wight[left_y][left_x] += -(right + left - 1);

				AI_Wight[right_y][right_x] += -(right + left - 1);





				if ((AI_Wight[left_y][left_x]) < (AI_Wight[right_y][right_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[left_y][left_x] += 1;

					}

				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[right_y][right_x] += 1;

					}

				}



				AI_Wight[y][x] = 0;

			}











			new_x = x;

			new_y = y;





			// 막대 : 현 위치 -> 위

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y - 1][new_x] == BlankSpace) {

					new_y--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_y--;

					break;

				}

			}



			int stick_down = (y - new_y);

			if (count == 1) {

				stick_down = (y - new_y - 1);

			}

			int stick_down_x = new_x;

			int stick_down_y = new_y;



			new_x = x;

			new_y = y;

			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[stick_down_y][stick_down_x] += stick_down;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[stick_down_y][stick_down_x] += -(stick_down);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[stick_down_y][stick_down_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[stick_down_y][stick_down_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}





			// 우측 대각선 : 현 위치 -> 좌측 상단

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y - 1][new_x - 1] == BlankSpace) {

					new_x--;

					new_y--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x--;

					new_y--;

					break;

				}

			}



			int right_dia_line_up = (x - new_x);

			if (count == 1) {

				right_dia_line_up = (x - new_x - 1);

			}

			int right_dia_line_up_x = new_x;

			int right_dia_line_up_y = new_y;



			new_x = x;

			new_y = y;

			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += right_dia_line_up;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += -(right_dia_line_up);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}





			// 좌측 대각선 : 현 위치 -> 우측 상단

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y - 1][new_x + 1] == BlankSpace) {

					new_x++;

					new_y--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x++;

					new_y--;

					break;

				}

			}



			int left_dia_line_up = (new_x - x);

			if (count == 1) {

				left_dia_line_up = (new_x - x - 1);

			}

			int left_dia_line_up_x = new_x;

			int left_dia_line_up_y = new_y;



			new_x = x;

			new_y = y;



			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += left_dia_line_up;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += -(left_dia_line_up);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}

		}

	}

	else {

		if (x == 0) {

			AI_Wight[y][x] = 0;

			// 직선 : 현 위치 -> 우

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y][new_x + 1] == BlankSpace) {

					new_x++;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x++;

					break;

				}

			}



			int left = (new_x - x);

			if (count == 1) {

				left = (new_x - x - 1);

			}

			int left_x = new_x;

			int left_y = new_y;



			new_x = x;

			new_y = y;

			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[left_y][left_x] += left;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[left_y][left_x] += -(left);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[left_y][left_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[left_y][left_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}





			new_x = x;

			new_y = y;



			// 막대 : 현 위치 -> 위

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y - 1][new_x] == BlankSpace) {

					new_y--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_y--;

					break;

				}

			}



			int stick_down = (y - new_y);

			if (count == 1) {

				stick_down = (y - new_y - 1);

			}

			int stick_down_x = new_x;

			int stick_down_y = new_y;



			new_x = x;

			new_y = y;



			// 막대 : 현 위치 -> 아래

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y + 1][new_x] == BlankSpace) {

					new_y++;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_y++;

					break;

				}

			}



			int stick_up = (new_y - y);

			if (count == 1) {

				stick_up = (new_y - y - 1);

			}

			int stick_up_x = new_x;

			int stick_up_y = new_y;



			new_x = x;

			new_y = y;





			if (GAME_whosTurn() == BlackStone) {

				AI_Wight[stick_up_y][stick_up_x] += (stick_up + stick_down - 1);

				AI_Wight[stick_down_y][stick_down_x] += (stick_up + stick_down - 1);







				if ((AI_Wight[stick_up_y][stick_up_x]) < (AI_Wight[stick_down_y][stick_down_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[stick_up_y][stick_up_x] += -1;

					}

				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[stick_down_y][stick_down_x] += -1;

					}

				}





				AI_Wight[y][x] = 0;

			}

			else

			{

				AI_Wight[stick_up_y][stick_up_x] += -(stick_up + stick_down - 1);

				AI_Wight[stick_down_y][stick_down_x] += -(stick_up + stick_down - 1);





				if ((AI_Wight[stick_up_y][stick_up_x]) < (AI_Wight[stick_down_y][stick_down_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[stick_up_y][stick_up_x] += 1;

					}

				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[stick_down_y][stick_down_x] += 1;

					}

				}





				AI_Wight[y][x] = 0;

			}



			new_x = x;

			new_y = y;



			// 좌측 대각선 : 현 위치 -> 우측 상단

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y - 1][new_x + 1] == BlankSpace) {

					new_x++;

					new_y--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x++;

					new_y--;

					break;

				}

			}



			int left_dia_line_up = (new_x - x);

			if (count == 1) {

				left_dia_line_up = (new_x - x - 1);

			}

			int left_dia_line_up_x = new_x;

			int left_dia_line_up_y = new_y;



			new_x = x;

			new_y = y;



			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += left_dia_line_up;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += -(left_dia_line_up);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}



			// 우측 대각선 : 현 위치 -> 우측 하단

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y + 1][new_x + 1] == BlankSpace) {

					new_x++;

					new_y++;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x++;

					new_y++;

					break;

				}

			}



			int right_dia_line_down = (new_x - x);

			if (count == 1) {

				right_dia_line_down = (new_x - x - 1);

			}

			int right_dia_line_down_x = new_x;

			int right_dia_line_down_y = new_y;

			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += right_dia_line_down;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += -(right_dia_line_down);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}



			new_x = x;

			new_y = y;

		}

		else if (x == 18)

		{

			AI_Wight[y][x] = 0;



			// 직선 : 현 위치 -> 좌

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y][new_x - 1] == BlankSpace) {

					new_x--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x--;

					break;

				}

			}



			int right = (x - new_x);

			if (count == 1) {

				right = (x - new_x - 1);

			}

			int right_x = new_x;

			int right_y = new_y;



			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[right_y][right_x] += right;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[right_y][right_x] += -(right);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[right_y][right_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[right_y][right_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}





			new_x = x;

			new_y = y;





			// 막대 : 현 위치 -> 위

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y - 1][new_x] == BlankSpace) {

					new_y--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_y--;

					break;

				}

			}



			int stick_down;

			if (count == 0) {

				stick_down = (y - new_y);

			}

			else

			{

				stick_down = (y - new_y - 1);

			}

			int stick_down_x = new_x;

			int stick_down_y = new_y;



			new_x = x;

			new_y = y;



			// 막대 : 현 위치 -> 아래

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y + 1][new_x] == BlankSpace) {

					new_y++;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_y++;

					break;

				}

			}



			int stick_up;

			if (count == 0) {

				stick_up = (new_y - y);

			}

			else

			{

				stick_up = (new_y - y - 1);

			}

			int stick_up_x = new_x;

			int stick_up_y = new_y;



			new_x = x;

			new_y = y;

			/////////////////////////////////////////

			if (GAME_whosTurn() == BlackStone) {

				int addNumber = (stick_up + stick_down - 1);

				AI_Wight[stick_down_y][stick_down_x] += addNumber;

				AI_Wight[stick_up_y][stick_up_x] += addNumber;



				if ((AI_Wight[stick_down_y][stick_down_x]) < (AI_Wight[stick_up_y][stick_up_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[stick_down_y][stick_down_x] += -1;

					}

				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[stick_up_y][stick_up_x] += -1;

					}

				}



				AI_Wight[y][x] = 0;

			}

			else

			{

				AI_Wight[stick_down_y][stick_down_x] += -(stick_down + stick_up - 1);

				AI_Wight[stick_up_y][stick_up_x] += -(stick_down + stick_up - 1);



				// 둘이 더한값 중에 가장 큰 수를 적용시킨다.

				if ((AI_Wight[stick_down_y][stick_down_x]) < (AI_Wight[stick_up_y][stick_up_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[stick_down_y][stick_down_x] += 1;

					}

				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[stick_up_y][stick_up_x] += 1;

					}

				}



				AI_Wight[y][x] = 0;

			}



			// 우측 대각선 : 현 위치 -> 좌측 상단

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y - 1][new_x - 1] == BlankSpace) {

					new_x--;

					new_y--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x--;

					new_y--;

					break;

				}

			}



			int right_dia_line_up;

			if (count == 0) {

				right_dia_line_up = (x - new_x);

			}

			else

			{

				right_dia_line_up = (x - new_x - 1);

			}

			int right_dia_line_up_x = new_x;

			int right_dia_line_up_y = new_y;



			new_x = x;

			new_y = y;

			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += right_dia_line_up;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += -(right_dia_line_up);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}



			// 좌측 대각선 : 현 위치 -> 좌측 하단

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y + 1][new_x - 1] == BlankSpace) {

					new_x--;

					new_y++;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x--;

					new_y++;

					break;

				}

			}



			int left_dia_line_down;

			if (count == 0) {

				left_dia_line_down = (new_y - y);

			}

			else

			{

				left_dia_line_down = (new_y - y - 1);

			}

			int left_dia_line_down_x = new_x;

			int left_dia_line_down_y = new_y;



			if (count == 0) {

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += left_dia_line_down;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += -(left_dia_line_down);

					AI_Wight[y][x] = 0;

				}

			}

			else

			{

				count = 0;

				if (GAME_whosTurn() == BlackStone) {

					AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += -1;

					AI_Wight[y][x] = 0;

				}

				else

				{

					AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += 1;

					AI_Wight[y][x] = 0;

				}

			}

		}

		else

		{

			AI_Wight[y][x] = 0;

			// 직선 : 현 위치 -> 우

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y][new_x + 1] == BlankSpace) {

					new_x++;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x++;

					break;

				}

			}



			int left;

			if (count == 0) {

				left = (new_x - x);

			}

			else

			{

				left = (new_x - x - 1);

			}

			int left_x = new_x;

			int left_y = new_y;



			new_x = x;

			new_y = y;



			// 직선 : 현 위치 -> 좌

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 ||
					GAME_mapArray[new_y][new_x - 1] == BlankSpace) {

					new_x--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x--;

					break;

				}

			}

			int right;

			if (count == 0) {

				right = (x - new_x);

			}

			else

			{

				right = (x - new_x - 1);

			}

			int right_x = new_x;

			int right_y = new_y;

			if (GAME_whosTurn() == BlackStone) {
				AI_Wight[left_y][left_x] += right + left - 1;
				AI_Wight[right_y][right_x] += right + left - 1;

				if ((AI_Wight[left_y][left_x]) < (AI_Wight[right_y][right_x])) {
					if (count == 1)
					{
						count = 0;
						AI_Wight[left_y][left_x] += -1;
					}
				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[right_y][right_x] += -1;

					}

				}



				AI_Wight[y][x] = 0;

			}

			else

			{

				AI_Wight[left_y][left_x] += -(right + left - 1);

				AI_Wight[right_y][right_x] += -(right + left - 1);

				if ((AI_Wight[left_y][left_x]) < (AI_Wight[right_y][right_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[left_y][left_x] += -1;

					}

				}



				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[right_y][right_x] += 1;

					}

				}



				AI_Wight[y][x] = 0;

			}



			new_x = x;

			new_y = y;



			// 막대 : 현 위치 -> 위

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y + 1][new_x] == BlankSpace) {

					new_y--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_y--;

					break;

				}

			}

			int stick_down;

			if (count == 0) {

				stick_down = (y - new_y);

			}

			else

			{

				stick_down = (y - new_y - 1);

			}

			int stick_down_x = new_x;

			int stick_down_y = new_y;



			new_x = x;

			new_y = y;



			// 막대 : 현 위치 -> 아래

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y + 1][new_x] == BlankSpace) {

					new_y++;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_y++;

					break;

				}

			}

			int stick_up;

			if (count == 0) {

				stick_up = (new_y - y);

			}

			else

			{

				stick_up = (new_y - y - 1);

			}

			int stick_up_x = new_x;

			int stick_up_y = new_y;



			new_x = x;

			new_y = y;



			if (GAME_whosTurn() == BlackStone) {

				AI_Wight[stick_up_y][stick_up_x] += stick_down + stick_up - 1;

				AI_Wight[stick_down_y][stick_down_x] += stick_down + stick_up - 1;





				if ((AI_Wight[stick_up_y][stick_up_x]) < (AI_Wight[stick_down_y][stick_down_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[stick_up_y][stick_up_x] += -1;

					}

				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[stick_down_y][stick_down_x] += -1;

					}

				}







				AI_Wight[y][x] = 0;

			}

			else

			{

				AI_Wight[stick_up_y][stick_up_x] += -(stick_down + stick_up - 1);

				AI_Wight[stick_down_y][stick_down_x] += -(stick_down + stick_up - 1);



				if ((AI_Wight[stick_up_y][stick_up_x]) < (AI_Wight[stick_down_y][stick_down_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[stick_up_y][stick_up_x] += 1;

					}

				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[stick_down_y][stick_down_x] += 1;

					}

				}



				AI_Wight[y][x] = 0;

			}





			// 우측 대각선 : 현 위치 -> 우측 하단

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y + 1][new_x + 1] == BlankSpace) {

					new_x++;

					new_y++;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x++;

					new_y++;

					break;

				}

			}

			int right_dia_line_down;

			if (count == 0) {

				right_dia_line_down = (new_x - x);

			}

			else

			{

				right_dia_line_down = (new_x - x - 1);

			}

			int right_dia_line_down_x = new_x;

			int right_dia_line_down_y = new_y;



			new_x = x;

			new_y = y;



			// 우측 대각선 : 현 위치 -> 좌측 상단

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y - 1][new_x - 1] == BlankSpace) {

					new_x--;

					new_y--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x--;

					new_y--;

					break;

				}

			}

			int right_dia_line_up;

			if (count == 0) {

				right_dia_line_up = (x - new_x);

			}

			else

			{

				right_dia_line_up = (x - new_x - 1);

			}

			int right_dia_line_up_x = new_x;

			int right_dia_line_up_y = new_y;



			new_x = x;

			new_y = y;



			if (GAME_whosTurn() == BlackStone) {

				AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += right_dia_line_up + right_dia_line_down - 1;

				AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += right_dia_line_up + right_dia_line_down - 1;



				if ((AI_Wight[right_dia_line_down_y][right_dia_line_down_x]) < (AI_Wight[right_dia_line_up_y][right_dia_line_up_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += -1;

					}

				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += -1;

					}

				}



				AI_Wight[y][x] = 0;

			}

			else

			{

				AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += -(right_dia_line_up + right_dia_line_down - 1);

				AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += -(right_dia_line_up + right_dia_line_down - 1);





				if ((AI_Wight[right_dia_line_down_y][right_dia_line_down_x]) < (AI_Wight[right_dia_line_up_y][right_dia_line_up_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[right_dia_line_down_y][right_dia_line_down_x] += 1;

					}

				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[right_dia_line_up_y][right_dia_line_up_x] += 1;

					}

				}







				AI_Wight[y][x] = 0;

			}





			// 좌측 대각선 : 현 위치 -> 우측 상단

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y - 1][new_x + 1] == BlankSpace) {

					new_x++;

					new_y--;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x++;

					new_y--;

					break;

				}

			}



			int left_dia_line_up = (new_x - x);

			int left_dia_line_up_x = new_x;

			int left_dia_line_up_y = new_y;



			new_x = x;

			new_y = y;



			// 좌측 대각선 : 현 위치 -> 좌측 하단

			while (1) {

				if (new_x > 0 && new_x < 19 && new_y > 0 && new_y < 19 || GAME_mapArray[new_y + 1][new_x - 1] == BlankSpace) {

					new_x--;

					new_y++;

				}

				else {

					break;

				}



				if (GAME_mapArray[new_y][new_x] == BlankSpace) {

					break;

				}



				if (GAME_mapArray[new_y][new_x] != GAME_whosTurn()) {

					count = 1;

					new_x--;

					new_y++;

					break;

				}

			}



			int left_dia_line_down = (new_y - y);

			int left_dia_line_down_x = new_x;

			int left_dia_line_down_y = new_y;



			if (GAME_whosTurn() == BlackStone) {

				AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += left_dia_line_up + left_dia_line_down - 1;

				AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += left_dia_line_up + left_dia_line_down - 1;





				if ((AI_Wight[left_dia_line_down_y][left_dia_line_down_x]) < (AI_Wight[left_dia_line_up_y][left_dia_line_up_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += -1;

					}

				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += -1;
					}
				}

				AI_Wight[y][x] = 0;

			}
			else
			{
				AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += -(left_dia_line_up + left_dia_line_down - 1);

				AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += -(left_dia_line_up + left_dia_line_down - 1);

				if ((AI_Wight[left_dia_line_down_y][left_dia_line_down_x]) < (AI_Wight[left_dia_line_up_y][left_dia_line_up_x])) {

					if (count == 1)

					{

						count = 0;

						AI_Wight[left_dia_line_down_y][left_dia_line_down_x] += 1;

					}

				}

				else

				{

					if (count == 1)

					{

						count = 0;

						AI_Wight[left_dia_line_up_y][left_dia_line_up_x] += 1;

					}

				}

				AI_Wight[y][x] = 0;

			}

		}

	}





	// 초기화

	for (int i = 0; i < 19; i++) {

		for (int j = 0; j < 19; j++) {

			if (GAME_mapArray[i][j] == BlackStone || GAME_mapArray[i][j] == WhiteStone) {

				AI_Wight[i][j] = 0;

			}

		}

	}

}


void Omok::showGameTime() {
	cout << GAME_gameTime << "번째 게임" << endl;

}


void Omok::AI_turn() {



	int try_max_x, try_min_x;

	int try_max_y, try_min_y;



	int max_num = AI_Wight[0][0];

	int min_num = AI_Wight[0][0];





	for (int i = 0; i < 19; i++) {

		for (int j = 0; j < 19; j++) {

			if (max_num < AI_Wight[i][j]) {

				max_num = AI_Wight[i][j];

				try_max_x = j;

				try_max_y = i;

			}



			if (min_num > AI_Wight[i][j]) {

				min_num = AI_Wight[i][j];

				try_min_x = j;

				try_min_y = i;

			}

		}

	}



	if (max_num * 2 > abs(min_num)) {

		GAME_playGame(try_max_x, try_max_y);

		AI_wightRule(try_max_x, try_max_y);

	}

	else

	{

		GAME_playGame(try_min_x, try_min_y);

		AI_wightRule(try_min_x, try_min_y);

	}




}


int Omok::GAME_isThere(int x, int y) {



	if (GAME_mapArray[y][x] == BlackStone ||

		GAME_mapArray[y][x] == WhiteStone) {

		return 1;

	}

	else

	{

		return 0;

	}

}


void Omok::GAME_printBinMap() {

	int nowNum = 0;

	for (int y = 0; y < GameY; y++) {

		for (int x = 0; x < GameX; x++) {


			// 만약 확인한 공간이 돌이 없고 비어있는 공간이라면,

			if (GAME_mapArray[y][x] == BlankSpace) {


				// 가장 위에 있는 경우

				if (y == 0) {



					// 가장 첫번째로 출력되는 맵 일경우

					if (x == 0) {

						cout << "┌";

					}



					// 가장 마지막에 출력되는 맵 일경우

					else if (x == 18) {



						// 만약 바로 전 맵 데이터 배열에 흑돌, 백돌이 있는경우

						if (GAME_mapArray[y][x - 1] == BlackStone || GAME_mapArray[y][x - 1] == WhiteStone) {

							cout << "┐ " << nowNum++ << endl;

						}

						else

						{

							// 아무런 돌이 없었을 경우

							cout << "─┐ " << nowNum++ << endl;

						}

					}



					// 가운데 출력

					else

					{

						// 만약 바로 전 맵 데이터 배열에 흑돌, 백돌이 있는경우

						if (GAME_mapArray[y][x - 1] == BlackStone || GAME_mapArray[y][x - 1] == WhiteStone)

						{

							cout << "┬";

						}

						else

						{

							// 아무런 돌이 없었을 경우

							cout << "─┬";

						}

					}

				}



				// 마지막 18번째 Y축일 경우

				else if (y == 18)

				{

					// 마지막 Y축에 첫번째 X값일 경우

					if (x == 0) {

						cout << "└";

					}



					// 마지막 Y축에 마지막번째 X값일 경우

					else if (x == 18)

					{



						// 전 배열에 흑돌 또는 백돌이 존재하였을 경우

						if (GAME_mapArray[y][x - 1] == BlackStone ||

							GAME_mapArray[y][x - 1] == WhiteStone) {

							cout << "┘ " << nowNum++ << endl;

						}

						else

						{

							// 아무런 돌이 놓여있지 않았을 경우

							cout << "─┘ " << nowNum++ << endl;

						}

					}

					else

					{

						if (GAME_mapArray[y][x - 1] == BlackStone ||

							GAME_mapArray[y][x - 1] == WhiteStone) {

							cout << "┴";

						}

						else

						{

							cout << "─┴";

						}

					}

				}

				else

				{

					if (x == 0) {

						// 1

						cout << "├";

					}

					else if (x == 18) {

						if (GAME_mapArray[y][x - 1] == BlackStone ||

							GAME_mapArray[y][x - 1] == WhiteStone) {

							cout << "┤ " << nowNum++ << endl;

						}

						else

						{

							cout << "─┤ " << nowNum++ << endl;

						}

					}

					else

					{

						if (GAME_mapArray[y][x - 1] == BlackStone ||

							GAME_mapArray[y][x - 1] == WhiteStone)

						{

							cout << "┼";

						}

						else

						{

							cout << "─┼";

						}

					}

				}

			}

			else

			{

				if (GAME_mapArray[y][x] == BlackStone) {

					// 흑돌일때

					if (GAME_mapArray[y][x - 1] == BlackStone ||

						GAME_mapArray[y][x - 1] == WhiteStone) {

						if (x == 18) {

							cout << "○" << nowNum++ << endl;

						}

						else

						{

							cout << "○";

						}

					}

					else

					{

						if (x == 0) {

							cout << "○";

						}

						else

						{

							if (x == 18) {

								cout << " ○" << nowNum++ << endl;

							}

							else

							{

								cout << " ○";

							}

						}

					}

				}

				else

				{

					if (GAME_mapArray[y][x - 1] == BlackStone ||

						GAME_mapArray[y][x - 1] == WhiteStone) {

						if (x == 18) {

							cout << "●" << nowNum++ << endl;

						}

						else

						{

							cout << "●";

						}

					}

					else

					{

						if (x == 0) {

							cout << "●";

						}

						else

						{

							if (x == 18) {

								cout << " ●" << nowNum++ << endl;

							}

							else

							{

								cout << " ●";

							}

						}

					}

				}

			}

		}

	}

	for (int i = 0; i < GameX; i++) {

		cout << (char)(i + 65) << " ";

	}

	cout << endl;

}

void Omok::GAME_printGameSet() {

	if (GAME_whosTurn() == BlackStone) {

		cout << "흑돌이 이겼습니다." << endl;

	}

	else

	{

		cout << "백돌이 이겼습니다." << endl;

	}

}

void Omok::GAME_showWhosTurn() {

	cout << endl;

	if (GAME_whosTurn() == BlackStone) {

		cout << "흑돌 차례입니다." << endl;

	}

	else

	{

		cout << "백돌 차례입니다." << endl;

	}

}

int Omok::GAME_whosTurn() {

	if (GAME_gameTime % 2 == 0) {

		return BlackStone;

	}

	else

	{

		return WhiteStone;

	}

}

int Omok::GAME_isWin() {

	// |

	for (int i = 0; i < GameY - 4; i++) {

		for (int j = 0; j < GameX; j++) {

			if (GAME_mapArray[i + 0][j] == GAME_whosTurn() &&

				GAME_mapArray[i + 1][j] == GAME_whosTurn() &&

				GAME_mapArray[i + 2][j] == GAME_whosTurn() &&

				GAME_mapArray[i + 3][j] == GAME_whosTurn() &&

				GAME_mapArray[i + 4][j] == GAME_whosTurn()) {

				return 1;

			}

		}

	}



	// -

	for (int j = 0; j < GameY - 4; j++) {

		for (int i = 0; i < GameX; i++) {

			if (GAME_mapArray[i][j + 0] == GAME_whosTurn() &&

				GAME_mapArray[i][j + 1] == GAME_whosTurn() &&

				GAME_mapArray[i][j + 2] == GAME_whosTurn() &&

				GAME_mapArray[i][j + 3] == GAME_whosTurn() &&

				GAME_mapArray[i][j + 4] == GAME_whosTurn()) {

				return 1;

			}

		}

	}



	// \



	for (int i = 0; i < GameY - 4; i++) {

		for (int j = 0; j < GameX - 4; j++) {

			if (GAME_mapArray[i + 0][j + 0] == GAME_whosTurn() &&

				GAME_mapArray[i + 1][j + 1] == GAME_whosTurn() &&

				GAME_mapArray[i + 2][j + 2] == GAME_whosTurn() &&

				GAME_mapArray[i + 3][j + 3] == GAME_whosTurn() &&

				GAME_mapArray[i + 4][j + 4] == GAME_whosTurn()) {

				return 1;

			}

		}

	}



	for (int i = 0; i < GameY - 4; i++) {

		for (int j = 0; j < GameX - 4; j++) {

			if (GAME_mapArray[GameX - i - 0][j + 0] == GAME_whosTurn() &&

				GAME_mapArray[GameX - i - 1][j + 1] == GAME_whosTurn() &&

				GAME_mapArray[GameX - i - 2][j + 2] == GAME_whosTurn() &&

				GAME_mapArray[GameX - i - 3][j + 3] == GAME_whosTurn() &&

				GAME_mapArray[GameX - i - 4][j + 4] == GAME_whosTurn()) {

				return 1;

			}

		}

	}

	return 0;

}

int Omok::GAME_playGame(int x, int y) {

	if (GAME_isThere(x, y) == BlankSpace) {

		GAME_mapArray[y][x] = GAME_whosTurn();

	}

	// 값을 벗어났을 경우 또는 

	else

	{

		return 1;

	}

	return 0;

}
