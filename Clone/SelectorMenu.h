#ifndef CSELECTORMENU_H
#define CSELECTORMENU_H

#include <string>
#include "Game.h"

class CSelectorMenu
{
public:
	CSelectorMenu( CGame *gameArg );
	~CSelectorMenu();
	
	void reset();

	// Main writing functions
	void printShopList(string nameArg, vector< CItem > itemList);

private:
	// Helper functions
	void printShopHeader();
	void printKeys();
	void printCursor();

	CGame *game;

	COORD cursorPos;
	unsigned int menuOffset;
	string name;

	bool menuComplete;
};

#endif