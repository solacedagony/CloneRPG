#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <Windows.h>

#include "Game.h"

class CScene;

#define	FIGHT_CHANCE 0

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

	void inventoryMenu();

private:
	CGame *game;

	std::vector< std::string > map;
	std::vector< Region > region;

	COORD playerPosition;
};

#endif