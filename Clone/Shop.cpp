#include <iostream>
#include <conio.h>

#include "Shop.h"
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
	for (int i = 0; i < 7; i++)
	{
		itemList.push_back(sword);
	}

	cout << "Shop keeper" << endl;
	cout << endl;

	// Pick shop mode
	if (mode == SHOPMODE_MAINMENU)
	{
		printMainMenu();
	}
	else if (mode == SHOPMODE_BUY)
	{
		// Print contents and gold prices
		printShopList(itemList);
		printCursor();
		processListInput();
	}
	else if (mode == SHOPMODE_SELL)
	{
		printShopList(this->game->player->itemList);
		printCursor();
		processListInput();
	}
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
			this->mode = ShopMode::SHOPMODE_BUY;

			this->cursorPos.X = SHOP_CURSORX_COLLEFT;
			this->cursorPos.Y = Y_BUY - 1;
		}
		else if (cursorPos.Y == Y_SELL)
		{
			this->mode = ShopMode::SHOPMODE_SELL;
			
			this->cursorPos.X = SHOP_CURSORX_COLLEFT;
			this->cursorPos.Y = Y_BUY - 1;
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

void CShop::printShopList(vector< CItem > itemList)
{
	unsigned int nameX1 = 4;
	unsigned int costX1 = 25;

	unsigned int nameX2 = 40;
	unsigned int costX2 = 51;

	COORD writePos;
	writePos.X = 5;
	writePos.Y = 4;

	// Setup number of list columns
	bool printComplete = false;
	unsigned int X = nameX1;
	while ( !printComplete)
	{
		if (itemList.size() < 11)
		{
			printComplete = true;
		}
		else if (X == nameX2 &&
				 printComplete == false)
		{
			printComplete = true;
		}

		COORD itemHeader1;
		itemHeader1.X = X;
		itemHeader1.Y = 2;
		this->game->engine->consoleSetPosition(itemHeader1);
		this->game->engine->consolePrint("Item");

		itemHeader1.Y += 1;
		this->game->engine->consoleSetPosition(itemHeader1);
		this->game->engine->consolePrint("==========================");

		COORD costHeader1;
		costHeader1.X = X + 21;
		costHeader1.Y = 2;
		this->game->engine->consoleSetPosition(costHeader1);
		this->game->engine->consolePrint("Price");

		X = nameX2;

		COORD exitText;
		exitText.X = 5;
		exitText.Y = 20;
		this->game->engine->consoleSetPosition(exitText);
		this->game->engine->consolePrint("ESC - Exit menu");
	}

	// Print items
	const int maxRows = 9;
	bool rowChange = false;
	for (int i = 0; i < itemList.size(); i++)
	{
		// Check column to print to
		if (i <= maxRows)
		{
			writePos.X = nameX1;
		}
		else
		{
			writePos.X = nameX2;
		}

		this->game->engine->consoleSetPosition(writePos);
		this->game->engine->consolePrint(itemList[i].name);

		// Check column to print to
		if (i <= maxRows)
		{
			writePos.X = costX1;
		}
		else
		{
			writePos.X = costX2;
		}

		this->game->engine->consoleSetPosition(writePos);
		this->game->engine->consolePrint(std::to_string((long long)itemList[i].cost));

		// Every maxRows, move back up to starting row
		if (i == maxRows)
		{
			writePos.Y = 4;
		}
		else
		{
			writePos.Y++;
		}
	}

	// Print cursor
	this->printCursor();

	// Grab input
	char input = _getch();

	unsigned int maxRowLeft = 0;
	unsigned int maxRowRight = 0;
	if (itemList.size() > 10)
	{
		maxRowLeft = 10 + SHOP_STARTROW - 1;
		maxRowRight = itemList.size() - 10 + SHOP_STARTROW - 1;
	}
	else
	{
		maxRowLeft = itemList.size() + SHOP_STARTROW - 1;
		maxRowRight = 0;
	}

	// Choose 
	unsigned int maxRow = maxRowLeft;
	if (cursorPos.X == SHOP_CURSORX_COLRIGHT)
	{
		maxRow = maxRowRight;
	}	

	// Parse input
	if (input == KEY_DOWNARROW)
	{
		if (cursorPos.Y == maxRow)
		{
			cursorPos.Y = SHOP_STARTROW;
		}
		else
		{
			this->cursorPos.Y += 1;
		}
	}
	else if (input == KEY_UPARROW)
	{
		if (cursorPos.Y <= SHOP_STARTROW)
		{
			cursorPos.Y = maxRow;
		}
		else
		{
			this->cursorPos.Y -= 1;
		}
	}
	else if (input == KEY_RIGHTARROW)
	{
		if (itemList.size() > 10)
		{
			if (cursorPos.X == SHOP_CURSORX_COLLEFT &&
				maxRowRight > 0)
			{
				cursorPos.X = SHOP_CURSORX_COLRIGHT;

				maxRow = maxRowRight;
				if (cursorPos.Y > maxRow)
				{
					cursorPos.Y = maxRow;
				}
			}
			else
			{
				cursorPos.X = SHOP_CURSORX_COLLEFT;
			}
		}
	}
	else if (input == KEY_LEFTARROW)
	{
		if (itemList.size() > 10)
		{
			if (cursorPos.X == SHOP_CURSORX_COLLEFT &&
				maxRowRight > 0)
			{
				cursorPos.X = SHOP_CURSORX_COLRIGHT;

				maxRow = maxRowRight;
				if (cursorPos.Y > maxRows)
				{
					cursorPos.Y = maxRows;
				}
			}
			else
			{
				cursorPos.X = SHOP_CURSORX_COLLEFT;
			}
		}
	}
	else if (input == KEY_ENTER)
	{
		// Selected item
		const unsigned int index = cursorPos.Y - 4;

		this->game->engine->consoleClear();

		if (this->game->player->gold >= itemList[index].cost)
		{

			this->game->player->itemList.push_back(itemList[index]);

			cout << "You bought a " << itemList[index].name << "." << endl;
			cout << endl;
			cout << "Gold: " << this->game->player->gold << " -> ";
			this->game->player->gold -= itemList[index].cost;
			cout << this->game->player->gold << endl;
		}

		system("pause");
	}
	else if (input == KEY_ESCAPE)
	{
		this->mode = SHOPMODE_MAINMENU;

		cursorPos.X = SHOP_MAINMENU_X;
		cursorPos.Y = Y_BUY;
	}
}

void CShop::printCursor()
{
	this->game->engine->consoleSetPosition(this->cursorPos);
	this->game->engine->consolePrint("*");
}

void CShop::processListInput()
{

}