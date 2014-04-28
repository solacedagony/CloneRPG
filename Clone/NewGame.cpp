#include <iostream>

#include "NewGame.h"
#include "Scene.h"

using std::cout;
using std::endl;
using std::cin;

CNewGame::CNewGame( CGame *gameArg )
{
	this->game = gameArg;
}

CNewGame::~CNewGame()
{
}

void CNewGame::draw()
{
	string name = "";

	// Print characters
	cout << this->game->getGameName() << " v" << this->game->getMajorVersion() << "." << this->game->getMinorVersion() << endl;
	cout << endl;
	cout << "Enter new character's name: ";

	// Input
	cin >> name;

	// Set name
	this->game->player->name = name;

	// Setup the player here
	this->game->player->hpMax = 100;
	this->game->player->hpCurrent = this->game->player->hpMax;
	this->game->player->mpMax = 0;
	this->game->player->mpCurrent = this->game->player->mpMax;
	this->game->player->str = 5;
	this->game->player->dex = 5;
	this->game->player->intel = 5;
	this->game->player->weapon.damageBase = 10;
	this->game->player->weapon.damageMod = 1;
	this->game->player->level = 1;
	this->game->player->xp = 0;
	this->game->player->gold = 200;
	
	this->game->setScene(SCENE_WORLDMAP);

	return;
}