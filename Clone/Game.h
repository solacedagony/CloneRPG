#ifndef _GAME_H
#define _GAME_H

#include <string>
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "Randomizer.h"

#include "MainMenu.h"
#include "NewGame.h"
#include "Fight.h"

class CScene;
class CMainMenu;
class CNewGame;
class CWorldMap;
class CFight;
class CShop;

#define SCENE_MAINMENU	1
#define SCENE_NEWGAME	2
#define SCENE_WORLDMAP	3
#define SCENE_FIGHT		4
#define SCENE_SHOP		5

class CGame
{
public:
	CGame(void);
	~CGame(void);

	void start();
	string getGameName();
	int getMajorVersion();
	int getMinorVersion();	
	void setExit();

	void setScene( unsigned int newScene );
	void resetGame();

	void setEnemy(CPlayer *newEnemy);

	CEngine *engine;
	CPlayer *player;
	CRandomizer randomizer;

private:
	CMainMenu *scene_MainMenu;
	CNewGame *scene_NewGame;
	CWorldMap *scene_WorldMap;
	CFight *scene_Fight;
	CShop *scene_Shop;

	unsigned int scene;
	unsigned int lastScene;

	string gameName;
	int majorVersion;
	int minorVersion;
	bool exit;
};

#endif