#include <iostream>
#include <conio.h>

#include "Shop.h"
#include "SelectorMenu.h"
#include "Defines.h"

using std::cout;
using std::endl;

CShop::CShop(CGame *gameArg)
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
	printMainMenu();
}

void CShop::printMainMenu()
{
	COORD printPos;
	printPos.X = 5;
	printPos.Y = Y_BUY;
	this->game->engine->consoleSetPosition(printPos);
	this->game->engine->consolePrint("Buy");

	printPos.Y += 1;
	this->game->engine->consoleSetPosition(printPos);
	this->game->engine->consolePrint("Sell");

	printPos.Y += 1;
	this->game->engine->consoleSetPosition(printPos);
	this->game->engine->consolePrint("Exit");

	// Print cursor
	printCursor();

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
			vector< CItem > itemList;
			CItem potion;
			potion.name = "Small Potion";
			potion.cost = 50;
			potion.hpRestore = 50;
			potion.type = ItemType::ITEMTYPE_POTION;

			for (int i = 0; i < 28; i++)
			{
				potion.name = "Small Potion" + std::to_string((long long)i);
				itemList.push_back(potion);
			}

			CSelectorMenu menu(this->game);
			menu.printShopList("Dude", itemList);
		}
		else if (cursorPos.Y == Y_SELL)
		{
			CSelectorMenu menu(this->game);
			menu.printPlayerList();
		}
		else if (cursorPos.Y == Y_EXIT)
		{
			this->game->setScene(SCENE_WORLDMAP);
		}
	}
	else if (input == KEY_ESCAPE)
	{
		this->game->setScene(SCENE_WORLDMAP);
	}
}

void CShop::printCursor()
{
	this->game->engine->consoleSetPosition(this->cursorPos);
	this->game->engine->consolePrint("*");
}