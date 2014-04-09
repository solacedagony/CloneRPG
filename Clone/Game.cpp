#include <iostream>
#include <conio.h>
#include <string>
#include <random>

#include "Game.h"
#include "Engine.h"
#include "Player.h"
#include "Scene.h"

#include "Defines.h"
#include "MainMenu.h"
#include "WorldMap.h"
#include "Shop.h"

using std::cout;
using std::endl;
using std::cin;
using std::to_string;

CGame::CGame(void)
{
	// Setup new objects
	this->engine = new CEngine;
	this->player = new CPlayer;

	this->scene_MainMenu = new CMainMenu( this );
	this->scene_NewGame = new CNewGame(this);
	this->scene_WorldMap = new CWorldMap(this);
	this->scene_Fight = new CFight(this);
	this->scene_Shop = new CShop(this);

	// Change starting scene
	this->setScene(SCENE_MAINMENU);

	// Set game name and revision
	this->gameName = "Clone RPG";
	this->majorVersion = 1;
	this->minorVersion = 0;

	this->exit = false;
}

CGame::~CGame(void)
{
	if (this->scene_MainMenu)
	{
		delete this->scene_MainMenu;
	}
	if (this->scene_NewGame)
	{
		delete this->scene_NewGame;
	}
	if (this->scene_WorldMap)
	{
		delete this->scene_WorldMap;
	}
	if (this->scene_Fight)
	{
		delete this->scene_Fight;
	}
	if (this->scene_Shop)
	{
		delete this->scene_Shop;
	}
}

void CGame::start( )
{
	while (!this->exit)
	{
		// Check if objects should be deleted and rebuilt
		if ((this->lastScene == SCENE_WORLDMAP || this->lastScene == SCENE_FIGHT) &&
			(this->scene == SCENE_MAINMENU || this->scene == SCENE_NEWGAME))
		{
			this->resetGame();
		}
		
		// Update last scene to observe a change
		if (this->lastScene != this->scene)
		{
			this->lastScene = this->scene;
		}

		// Run scenes
		if (this->scene == SCENE_MAINMENU)
		{
			this->scene_MainMenu->draw();
		}
		else if (this->scene == SCENE_NEWGAME)
		{
			this->scene_NewGame->draw();
		}
		else if (this->scene == SCENE_WORLDMAP)
		{
			this->scene_WorldMap->draw();
		}
		else if (this->scene == SCENE_FIGHT)
		{
			this->scene_Fight->draw();
		}
		else if (this->scene == SCENE_SHOP)
		{
			this->scene_Shop->draw();
		}

		// Clear screen
		this->engine->consoleClear();
	}

	return;
}

string CGame::getGameName()
{
	return this->gameName;
}

int CGame::getMajorVersion()
{
	return this->majorVersion;
}

int CGame::getMinorVersion()
{
	return this->minorVersion;
}

void CGame::setExit()
{
	this->exit = true;
}

void CGame::setScene( unsigned int newScene )
{
	if (newScene == SCENE_MAINMENU)
	{
		this->scene = SCENE_MAINMENU;
	}
	else if (newScene == SCENE_NEWGAME)
	{
		this->scene = SCENE_NEWGAME;
	}
	else if (newScene == SCENE_WORLDMAP)
	{
		this->scene = SCENE_WORLDMAP;
	}
	else if (newScene == SCENE_FIGHT)
	{
		this->scene = SCENE_FIGHT;
	}
	else if (newScene == SCENE_SHOP)
	{
		this->scene = SCENE_SHOP;
	}
}

void CGame::setEnemy(CPlayer *newEnemy)
{
	this->scene_Fight->setupEnemy(newEnemy);
}

void CGame::resetGame()
{
	delete this->player;
	this->player = new CPlayer; 
	
	delete this->scene_Fight;
	this->scene_Fight = new CFight(this);
	
	delete this->scene_WorldMap;
	this->scene_WorldMap = new CWorldMap(this);
}