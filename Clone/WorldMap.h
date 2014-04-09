#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <Windows.h>

#include "Game.h"

class CScene;

#define	FIGHT_CHANCE 0

struct Region
{
	std::string name;
	COORD topleft;
	COORD bottomright;

	bool hasEnemies;
};

class CWorldMap
{
public:
	CWorldMap(CGame *game);
	~CWorldMap();

	// Drawing and logic functions
	void draw();
	void printBorder();
	void printMenu();
	void printMap();

	// Menu options
	void printCharStats();
	void checkForInteraction();

	// Map functions
	bool checkCollision(int posX, int posY);
	void loadMap();
	std::string returnRegion();

private:
	CGame *game;

	std::vector< std::string > map;
	std::vector< Region > region;

	COORD playerPosition;
};

#endif