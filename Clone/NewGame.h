#ifndef NEWGAME_H
#define NEWGAME_H

#include "Game.h"

class CNewGame
{
public:
	CNewGame(CGame *game);
	~CNewGame();

	void draw();
private:
	CGame *game;
};

#endif