#ifndef CSHOP_H
#define CSHOP_H

#include <vector>
#include "Game.h"

#define SHOP_CURSORX_COLLEFT 2
#define SHOP_CURSORX_COLRIGHT 38
#define SHOP_STARTROW 4
#define SHOP_ENDROW 13

#define Y_BUY	5
#define Y_SELL	6
#define Y_EXIT	7
#define SHOP_MAINMENU_X 3;

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
	void processListInput();

	void printCursor();

private:
	CGame *game;
	ShopMode mode;

	COORD cursorPos;
};

#endif