#include <Windows.h>
#include <iostream>
#include <cstring>

#include "Engine.h"
#include "Game.h"

int main( int argc, const char* argv[] )
{
	CGame *game = new CGame;
	game->start();

	delete game;

	return 0;
}