#include <iostream>
#include <conio.h>

#include "Shop.h"
#include "Defines.h"

using std::cout;
using std::endl;

CShop::CShop( CGame *gameArg )
{
	this->game = gameArg;
	this->mode = ShopMode::SHOPMODE_MAINMENU;
	this->cursorPos.X = 3;
	this->cursorPos.Y = 5;
}

CShop::~CShop()
{
}

void CShop::draw()
{
	vector< CItem > itemList;
	CItem potion;
	potion.name = "Small Potion";
	potion.cost = 50;
	potion.hpRestore = 50;
	potion.type = ItemType::ITEMTYPE_POTION;
	itemList.push_back(potion);

	CItem sword;
	sword.name = "Short Sword";
	sword.damageBase = 5;
	sword.damageMod = 1;
	sword.type = ItemType::ITEMTYPE_WEAPON;
	itemList.push_back(sword);

	cout << "Shop keeper" << endl;
	cout << endl;
	
	// Print cursor
	printCursor();

	// Pick shop mode
	if (mode == SHOPMODE_MAINMENU)
	{
		printMainMenu();
	}
	else if (mode == SHOPMODE_BUY)
	{
		// Print contents and gold prices
		printShopList(itemList);
	}
	else if (mode == SHOPMODE_SELL)
	{
	}	
}

void CShop::printMainMenu()
{
#define Y_BUY	5
#define Y_SELL	6
#define Y_EXIT	7

	COORD printPos;
	printPos.X = 5;
	printPos.Y = 5;
	this->game->engine->consoleSetPosition(printPos);
	this->game->engine->consolePrint("Buy");

	printPos.Y += 1;
	this->game->engine->consoleSetPosition(printPos);
	this->game->engine->consolePrint("Sell");

	printPos.Y += 1;
	this->game->engine->consoleSetPosition(printPos);
	this->game->engine->consolePrint("Exit");

	char input = _getch();

	if (input == KEY_DOWNARROW)
	{
		if (cursorPos.Y == Y_EXIT)
		{
			cursorPos.Y = Y_BUY;
		}
		else
		{
			this->cursorPos.Y += 1;
		}
	}
	else if (input == KEY_UPARROW)
	{
		if (cursorPos.Y == Y_BUY)
		{
			cursorPos.Y = Y_EXIT;
		}
		else
		{
			this->cursorPos.Y -= 1;
		}
	}
	else if (input == KEY_ENTER)
	{
		if (cursorPos.Y == Y_BUY)
		{
			this->mode = ShopMode::SHOPMODE_BUY;
		}
		else if (cursorPos.Y == Y_SELL)
		{
			this->mode = ShopMode::SHOPMODE_SELL;
		}
		else if (cursorPos.Y == Y_EXIT)
		{
			this->game->setScene(SCENE_WORLDMAP);
		}
	}
}

void CShop::printShopList(vector< CItem > itemList)
{
	unsigned int nameX1 = 4;
	unsigned int costX1 = 25;

	unsigned int nameX2 = 40;
	unsigned int costX2 = 51;

	COORD writePos;
	writePos.X = 5;
	writePos.Y = 4;

	COORD itemHeader1;
	itemHeader1.X = nameX1;
	itemHeader1.Y = 2;
	this->game->engine->consoleSetPosition(itemHeader1);
	this->game->engine->consolePrint("Item");

	itemHeader1.Y += 1;
	this->game->engine->consoleSetPosition(itemHeader1);
	this->game->engine->consolePrint("=========================");

	COORD costHeader1;
	costHeader1.X = 25;
	costHeader1.Y = 2;
	this->game->engine->consoleSetPosition(costHeader1);
	this->game->engine->consolePrint("Price");

	// Print items
	for (int i = 0; i < itemList.size(); i++)
	{
		if (i < 10)
		{
			writePos.X = nameX1;
		}
		else
		{
			writePos.X = nameX2;
		}
		
		this->game->engine->consoleSetPosition(writePos);
		this->game->engine->consolePrint(itemList[i].name);

		if (i < 10)
		{
			writePos.X = costX1;
		}
		else
		{
			writePos.X = costX2;
		}

		this->game->engine->consoleSetPosition(writePos);
		this->game->engine->consolePrint(std::to_string( (long long)itemList[i].cost ));


		if (i == 10)
		{
			writePos.Y = 4;
		}
		else
		{
			writePos.Y++;
		}
	}
}

void CShop::printCursor()
{
	this->game->engine->consoleSetPosition(this->cursorPos);
	this->game->engine->consolePrint("*");
}