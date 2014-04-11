#ifndef CSHOP_H
#define CSHOP_H

#include <vector>
#include "Game.h"

enum ShopMode
{
	SHOPMODE_MAINMENU = 1,
	SHOPMODE_BUY,
	SHOPMODE_SELL
};

class CShop
{
public:
	CShop( CGame *game );
	~CShop();

	void draw();
	void printMainMenu();
	void printShopList(vector< CItem > itemList);

	void printCursor();

private:
	CGame *game;
	ShopMode mode;

	COORD cursorPos;
};

#endif