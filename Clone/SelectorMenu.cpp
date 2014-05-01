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
		printShopHeader();
		printKeys();

		// Print cursor
		printCursor();

		// Constants for menu printing
		const int maxRows = 15;
		const int yOffset = 4;
		const int column1 = 4;
		const int column2 = 25;

		COORD writePos;
		writePos.X = column1;
		writePos.Y = yOffset;

		// Calculate Y offset
		unsigned int endingItem = 0;
		if (itemList.size() < maxRows)
		{
			endingItem = itemList.size();
		}
		else
		{
			endingItem = maxRows;
		}

		// Print list
		for (int i = 0; i < endingItem; i++)
		{
			writePos.X = column1;
			writePos.Y = i + yOffset;
			this->game->engine->consoleSetPosition(writePos);
			this->game->engine->consolePrint(itemList[i+this->menuOffset].name);

			writePos.X = column2;
			this->game->engine->consoleSetPosition(writePos);
			this->game->engine->consolePrint(std::to_string((long long)itemList[i + this->menuOffset].cost));
		}

		// Print cursor
		this->printCursor();

		// Grab input
		char input = _getch();

		// Parse input
		if (input == KEY_DOWNARROW)
		{
			if (cursorPos.Y >= (maxRows+yOffset-1) &&
				(this->menuOffset+maxRows) < itemList.size())
			{
				// Increment offset down for menu
				this->menuOffset++;
			}
			else if ((cursorPos.Y - yOffset + 1) < maxRows)
			{
				this->cursorPos.Y += 1;
			}
		}
		else if (input == KEY_UPARROW)
		{
			if (cursorPos.Y <= yOffset &&
				this->menuOffset > 0)
			{
				this->menuOffset--;
			}
			else if (cursorPos.Y > yOffset)
			{
				cursorPos.Y--;
			}
		}
		else if (input == KEY_ENTER)
		{
			// Selected item
			const unsigned int index = cursorPos.Y - yOffset + this->menuOffset;

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
			this->menuComplete = true;
		}
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
	writePos.X = 1;
	writePos.Y = 1;
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