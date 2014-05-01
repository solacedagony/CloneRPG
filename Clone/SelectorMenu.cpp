#include <iostream>
#include <conio.h>

#include "SelectorMenu.h"
#include "Defines.h"

using std::cout;
using std::endl;

CSelectorMenu::CSelectorMenu( CGame *gameArg )
{
	this->game = gameArg;
}

CSelectorMenu::~CSelectorMenu()
{
}

void CSelectorMenu::reset()
{
	this->menuOffset = 0;
	this->cursorPos.X = 2;
	this->cursorPos.Y = 4;
	this->menuComplete = false;
}

void CSelectorMenu::printShopList( string shopArg, vector< CItem > itemList)
{
	// Reset all menu settings
	this->reset();
	this->name = shopArg;

	// Menu interaction
	while (!this->menuComplete)
	{
		// Clear all writing
		this->game->engine->consoleClear();

		// Print static text
		this->printShopHeader();
		this->printKeys();

		// Print cursor
		this->printCursor();

		// Print list
		this->printList( itemList );

		// Print cursor
		this->printCursor();

		// Grab input
		char input = _getch();

		// Parse input
		parseInputShop(input, itemList);
	}
}

void CSelectorMenu::printPlayerList()
{
	// Reset all menu settings
	this->reset();
	this->name = this->game->player->name;

	// Menu interaction
	while (!this->menuComplete)
	{
		// Clear all writing
		this->game->engine->consoleClear();

		// Print static text
		this->printShopHeader();
		this->printKeys();

		// Print cursor
		this->printCursor();

		// Print list
		this->printList(this->game->player->itemList);

		// Print cursor
		this->printCursor();

		// Grab input
		char input = _getch();

		// Parse input
		parseInputPlayer(input, this->game->player->itemList);
	}
}

void CSelectorMenu::printCursor()
{
	this->game->engine->consoleSetPosition(this->cursorPos);
	this->game->engine->consolePrint("*");
}

void CSelectorMenu::printShopHeader()
{
	COORD writePos;
	writePos.X = 0;
	writePos.Y = 0;
	this->game->engine->consoleSetPosition(writePos);
	this->game->engine->consolePrint(this->name + "'s Shop");

	unsigned int nameX = 4;
	unsigned int costX = 25;
	
	writePos.X = 5;
	writePos.Y = 4;

	// Setup number of list columns
	COORD itemHeader1;
	itemHeader1.X = nameX;
	itemHeader1.Y = 2;
	this->game->engine->consoleSetPosition(itemHeader1);
	this->game->engine->consolePrint("Item");

	itemHeader1.Y += 1;
	this->game->engine->consoleSetPosition(itemHeader1);
	this->game->engine->consolePrint("==========================");

	COORD costHeader1;
	costHeader1.X = costX;
	costHeader1.Y = 2;
	this->game->engine->consoleSetPosition(costHeader1);
	this->game->engine->consolePrint("Price");	
}

void CSelectorMenu::printKeys()
{
	COORD menu;
	menu.X = 40;
	menu.Y = 2;
	this->game->engine->consoleSetPosition(menu);
	this->game->engine->consolePrint("Escape - Exit menu");

	menu.Y += 1;
	this->game->engine->consoleSetPosition(menu);
	this->game->engine->consolePrint("Enter - Select item");

	menu.Y += 1;
	this->game->engine->consoleSetPosition(menu);
	this->game->engine->consolePrint("Up Arrow - Scroll up");

	menu.Y += 1;
	this->game->engine->consoleSetPosition(menu);
	this->game->engine->consolePrint("Down Arrow - Scroll down");

}

void CSelectorMenu::printList(vector<CItem>itemList)
{
	COORD writePos;
	writePos.X = MENU_COLUMN1_Y;
	writePos.Y = MENU_YOFFSET;

	if (itemList.size() > 0)
	{
		// Calculate Y offset
		unsigned int endingItem = 0;
		if (itemList.size() < MENU_MAXROWS)
		{
			endingItem = itemList.size();
		}
		else
		{
			endingItem = MENU_MAXROWS;
		}

		// Print list
		for (int i = 0; i < endingItem; i++)
		{
			writePos.X = MENU_COLUMN1_Y;
			writePos.Y = i + MENU_YOFFSET;
			this->game->engine->consoleSetPosition(writePos);
			this->game->engine->consolePrint(itemList[i + this->menuOffset].name);

			writePos.X = MENU_COLUMN2_Y;
			this->game->engine->consoleSetPosition(writePos);
			this->game->engine->consolePrint(std::to_string((long long)itemList[i + this->menuOffset].cost));
		}
	}
	else
	{
		this->game->engine->consoleSetPosition(writePos);
		this->game->engine->consolePrint("You have no items!");
	}
}

void CSelectorMenu::parseInputPlayer(char input, vector<CItem> itemList)
{
	if (input == KEY_DOWNARROW)
	{
		if (cursorPos.Y >= (MENU_MAXROWS + MENU_YOFFSET - 1) &&
			(this->menuOffset + MENU_MAXROWS) < itemList.size())
		{
			// Increment offset down for menu
			this->menuOffset++;
		}
		else if ((cursorPos.Y - MENU_YOFFSET + 1) < MENU_MAXROWS &&
				 (cursorPos.Y - MENU_YOFFSET + 1) < itemList.size())
		{
			this->cursorPos.Y += 1;
		}
	}
	else if (input == KEY_UPARROW)
	{
		if (cursorPos.Y <= MENU_YOFFSET &&
			this->menuOffset > 0)
		{
			this->menuOffset--;
		}
		else if (cursorPos.Y > MENU_YOFFSET)
		{
			cursorPos.Y--;
		}
	}
	else if (input == KEY_ENTER)
	{
		this->game->engine->consoleClear();

		if (itemList.size() > 0)
		{
			// Selected item
			unsigned int index = cursorPos.Y - MENU_YOFFSET + this->menuOffset;	

			unsigned int shopCost = (int)(.80 * (float)itemList[index].cost);
			cout << "You sold a " << itemList[index].name << "." << endl;
			cout << endl;
			cout << "Gold: " << this->game->player->gold << " -> ";
			this->game->player->gold += shopCost;
			cout << this->game->player->gold << endl;

			this->game->player->itemList.erase(this->game->player->itemList.begin() + index);
		}
		else
		{
			cout << "You have no items to sell!" << endl;
		}

		system("pause");
	}
	else if (input == KEY_ESCAPE)
	{
		this->menuComplete = true;
	}
}

void CSelectorMenu::parseInputShop(char input, vector<CItem> itemList)
{
	if (input == KEY_DOWNARROW)
	{
		if (cursorPos.Y >= (MENU_MAXROWS + MENU_YOFFSET - 1) &&
			(this->menuOffset + MENU_MAXROWS) < itemList.size())
		{
			// Increment offset down for menu
			this->menuOffset++;
		}
		else if ((cursorPos.Y - MENU_YOFFSET + 1) < MENU_MAXROWS &&
				 (cursorPos.Y - MENU_YOFFSET + 1) < itemList.size())
		{
			this->cursorPos.Y += 1;
		}
	}
	else if (input == KEY_UPARROW)
	{
		if (cursorPos.Y <= MENU_YOFFSET &&
			this->menuOffset > 0)
		{
			this->menuOffset--;
		}
		else if (cursorPos.Y > MENU_YOFFSET)
		{
			cursorPos.Y--;
		}
	}
	else if (input == KEY_ENTER)
	{
		// Selected item
		const unsigned int index = cursorPos.Y - MENU_YOFFSET + this->menuOffset;

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
		else
		{
			cout << "You don't have enough money for that!" << endl;
		}

		system("pause");
	}
	else if (input == KEY_ESCAPE)
	{
		this->menuComplete = true;
	}
}