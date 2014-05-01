#ifndef CSELECTORMENU_H
#define CSELECTORMENU_H

#include <string>
#include "Game.h"

#define MENU_MAXROWS		15
#define MENU_YOFFSET		4
#define MENU_COLUMN1_Y		4
#define MENU_COLUMN2_Y		25

class CSelectorMenu
{
public:
	CSelectorMenu( CGame *gameArg );
	~CSelectorMenu();
	
	void reset();

	// Main writing functions
	void printShopList(string nameArg, vector< CItem > itemList);
	void printPlayerList();

private:
	// Helper functions
	void printShopHeader();
	void printKeys();
	void printCursor();
	void printList(vector<CItem> itemList);

	// Parsing
	void parseInputShop(char input, vector<CItem> itemList);
	void parseInputPlayer(char input, vector<CItem> itemList);

	CGame *game;

	COORD cursorPos;
	unsigned int menuOffset;
	string name;

	bool menuComplete;
};

#endif