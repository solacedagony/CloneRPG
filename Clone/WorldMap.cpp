#include <iostream>
#include <conio.h>
#include <iomanip>
#include <string>

#include "WorldMap.h"
#include "Defines.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

CWorldMap::CWorldMap( CGame *gameArg )
{
	this->game = gameArg;

	this->loadMap();

	this->playerPosition.X = 5;
	this->playerPosition.Y = 2;
}

CWorldMap::~CWorldMap()
{
}

void CWorldMap::draw()
{
	// Print outside border
	this->printBorder();

	// Print selection menu
	this->printMenu();

	// Print map
	this->printMap();

	// Print hero "H"
#define HERO_X 25
#define HERO_Y 10
	COORD heroPos = { HERO_X, HERO_Y };
	this->game->engine->consolePrint("H", heroPos);

#define INPUTPOS_X 0
#define INPUTPOS_Y 22

	COORD inputPos = { INPUTPOS_X, INPUTPOS_Y };
	this->game->engine->consoleSetPosition(inputPos);
	cout << "Enter a command: ";
	char input;

	// Parse keyboard input
	input = _getch();

	if (input == KEY_UPARROW ||
		input == KEY_DOWNARROW ||
		input == KEY_LEFTARROW ||
		input == KEY_RIGHTARROW)
	{
		// Set initial position
		int posX = this->playerPosition.X;
		int posY = this->playerPosition.Y;

		// Modify position for keypress
		if (input == KEY_UPARROW)
		{
			posY -= 1;
		}
		else if (input == KEY_DOWNARROW)
		{
			posY += 1;
		}
		else if (input == KEY_LEFTARROW)
		{
			posX -= 1;
		}
		else if (input == KEY_RIGHTARROW)
		{
			posX += 1;
		}

		// Check for collision
		if (!this->checkCollision(posX, posY))
		{
			// If no collision, set new position
			this->playerPosition.X = posX;
			this->playerPosition.Y = posY;

			// Randomize possible fight
			int randomInt = this->game->player->randomizer.randomInteger(0, 99);
			this->game->engine->Log(to_string((long long)randomInt));

			if (randomInt < FIGHT_CHANCE)
			{
				// Switch to fight mode
				this->game->setScene( SCENE_FIGHT );

				// Setup new enemy
				CPlayer *newEnemy = new CPlayer;
				newEnemy->name = "Goblin";
				newEnemy->hpCurrent = 50;
				newEnemy->hpMax = 50;
				newEnemy->mpCurrent = 0;
				newEnemy->mpMax = 0;
				newEnemy->str = 1;
				newEnemy->dex = 1;
				newEnemy->intel = 1;
				newEnemy->xp = 5;
				newEnemy->weapon.damageBase = 1;
				newEnemy->weapon.damageMod = 1;

				this->game->setEnemy(newEnemy);
			}
		}
	}
	else if (input == KEY_ESCAPE)
	{
		this->game->setExit();
	}
	else if (tolower(input) == KEY_CHARSTATS)
	{
		this->printCharStats();
	}
	else if (tolower(input) == KEY_INTERACT)
	{
		checkForInteraction();
	}
	else if (tolower(input) == KEY_INVENTORY)
	{
	}

	return;
}

void CWorldMap::loadMap()
{
	std::vector<std::string> mapLine;

	// Easy way to convert map into variable
	mapLine.push_back("########################################################################################################################");
	mapLine.push_back("#****************************************************************************_*****************************************#");
	mapLine.push_back("#****     ****************               ***************************        / \\                      ******************#");
	mapLine.push_back("#****      **********       **********            *********************     |W|                       *****************#");
	mapLine.push_back("#******                 ****************                                                               ****************#");
	mapLine.push_back("#*****************************************        *********************                                  **************#");
	mapLine.push_back("#***********************************************************************                         **********************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("#**********************************************************************************************************************#");
	mapLine.push_back("########################################################################################################################");

	// Write map to variable
	for (unsigned int i = 0; i < mapLine.size(); i++)
	{
		this->map.push_back(mapLine[i]);
	}

	// Set region
	Region startingForest;
	startingForest.name = "Mysterious Forest";
	startingForest.topleft.X = 0;
	startingForest.topleft.Y = 0;
	startingForest.bottomright.X = 51;
	startingForest.bottomright.Y = 8;
	this->region.push_back(startingForest);

	Region forestTown;
	forestTown.name = "Forest Town";
	forestTown.topleft.X = 68;
	forestTown.topleft.Y = 0;
	forestTown.bottomright.X = 130;
	forestTown.bottomright.Y = 10;
	this->region.push_back(forestTown);

	CPlayer goblin;
	goblin.name = "Goblin";
	goblin.hpCurrent = 50;
	goblin.hpMax = 50;
	goblin.mpCurrent = 0;
	goblin.mpMax = 0;
	goblin.weapon.damageBase = 2;
	goblin.weapon.damageMod = 1;
	this->game->monsters.push_back(goblin);

	CPlayer troll;
	troll.name = "Troll";
	troll.hpCurrent = 20;
	troll.hpMax = 20;
	troll.mpCurrent = 0;
	troll.mpMax = 0;
	troll.weapon.damageBase = 6;
	troll.weapon.damageMod = 5;
	this->game->monsters.push_back(troll);

	return;
}

void CWorldMap::printBorder()
{
#define MAP_WIDTH 51
#define MAP_HEIGHT 20

	// Clear screen
	this->game->engine->consoleClear();

	// Print first line
	COORD pos = { 0, 0 };
	this->game->engine->consoleSetPosition(pos);
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		cout << "#";
	}

	// Print last line
	pos.Y = MAP_HEIGHT;
	this->game->engine->consoleSetPosition(pos);
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		cout << "#";
	}

	// Print middle borders
	for (int i = 1; i < MAP_HEIGHT; i++)
	{
		pos.X = 0;
		pos.Y = i;
		this->game->engine->consolePrint("#", pos);

		pos.X = MAP_WIDTH - 1;
		this->game->engine->consolePrint("#", pos);
	}

	return;
}

void CWorldMap::printMenu()
{
#define MENU_OFFSET 54

	COORD gameNameAndVersionPos = { MENU_OFFSET, 0 };
	COORD menuEntriesPos = { MENU_OFFSET, gameNameAndVersionPos.Y + 3 };
	COORD playerPositionPosX = { MENU_OFFSET, menuEntriesPos.Y + 5 };
	COORD playerPositionPosY = { MENU_OFFSET, (playerPositionPosX.Y + 1) };
	COORD regionPos = { MENU_OFFSET, playerPositionPosY.Y + 2 };

	// Menu options
	std::vector<std::string> menuEntries;
	menuEntries.push_back("A Interact");
	menuEntries.push_back("C Char Stats"); 
	menuEntries.push_back("I Inventory");

	// Print menu entries
	for (unsigned int i = 0; i < menuEntries.size(); i++)
	{
		this->game->engine->consolePrint(menuEntries[i], menuEntriesPos);
		menuEntriesPos.Y++;
	}

	// Setup game name and version
	string gameNameAndVersion = this->game->getGameName() + string(" v") + std::to_string((long long)game->getMajorVersion() ) + string(".") + std::to_string((long long)game->getMinorVersion() );
	this->game->engine->consolePrint(gameNameAndVersion, gameNameAndVersionPos);

	// Print player position and region
	COORD playerPos;
	playerPos.X = this->playerPosition.X;
	playerPos.Y = this->playerPosition.Y;

	string playerPosX = "Char position X: " + std::to_string((long long)playerPos.X);
	string playerPosY = "Char position Y: " + std::to_string((long long)playerPos.Y);
	this->game->engine->consolePrint(playerPosX, playerPositionPosX);
	this->game->engine->consolePrint(playerPosY, playerPositionPosY);

	string currentRegion = "Region: " + returnRegion();
	this->game->engine->consolePrint(currentRegion, regionPos);

	return;
}

void CWorldMap::printMap()
{
#define MAP_OFFSET_X 25
#define MAP_OFFSET_Y 11
	int posX = this->playerPosition.X;
	int posY = this->playerPosition.Y;

	//string log = "Player pos: ";
	//log += std::to_string( (long long)(posX) ) + "/" + std::to_string( (long long)(posY) );
	//engine->Log( log );

	// Print map
	int xDiff = posX - MAP_OFFSET_X + 1;
	int yDiff = posY - MAP_OFFSET_Y + 1;

	//log = "Diff: " + std::to_string( (long long)xDiff ) + "/" + std::to_string( (long long)yDiff );
	//engine->Log( log );

	//log = "Y: " + std::to_string( (long long)(posY - MAP_OFFSET_Y) ) + "/" + std::to_string( (long long)(posY + MAP_OFFSET_Y) ) + "    X: " + std::to_string( (long long)(posX - MAP_OFFSET_X) ) + "/" + std::to_string( (long long)(posX + MAP_OFFSET_X) );
	//engine->Log( log );

	// TODO: Need to fix printing
	WORD currentColor = 0;
	for (signed int y = (posY - MAP_OFFSET_Y + 2); y < (posY + MAP_OFFSET_Y - 1); y++)
	{
		for (signed int x = (posX - MAP_OFFSET_X + 2); x < (posX + MAP_OFFSET_X); x++)
		{
			//string logData = "x: (";
			//logData += std::to_string( (long long)x ) + ") y: (" + std::to_string( (long long)y ) + ") char: (";			

			if (x >= 0 && y >= 0 &&
				y < this->map.size() && x < this->map[0].size())
			{
				//logData += this->player->map[y][x];

				COORD pos = { x - xDiff + 1, y - yDiff };
				string newChar(1, this->map[y][x]);
				if (newChar == "#")
				{
					if (currentColor != (BLACK_BG | BRIGHTWHITE_FG))
					{
						currentColor = BLACK_BG | BRIGHTWHITE_FG;
						this->game->engine->consoleSetColor(currentColor);
					}
				}
				else if (newChar == "M")
				{
					if (currentColor != (YELLOW_BG | GREEN_FG))
					{
						currentColor = YELLOW_BG | GREEN_FG;
						this->game->engine->consoleSetColor(currentColor);
					}
				}
				else if (newChar == "~")
				{
					if (currentColor != (BLUE_BG | LIGHTBLUE_FG))
					{
						currentColor = BLUE_BG | LIGHTBLUE_FG;
						this->game->engine->consoleSetColor(currentColor);
					}
				}
				else
				{
					if (currentColor != (BLACK_BG | WHITE_FG) )
					{
						currentColor = BLACK_BG | WHITE_FG;
						this->game->engine->consoleSetColor(currentColor);
					}
				}

				// Print character
				this->game->engine->consolePrint(newChar, pos);
			}

			//logData += ")";
			//engine->Log( logData );
		}
	}

	//log = "x: " + std::to_string( (long long)x ) + " y: " + std::to_string( (long long)y );
	//engine->Log( log );

	return;
}

bool CWorldMap::checkCollision(int posX, int posY)
{
	// If the tile is any of these types, it can be moved onto
	vector<char> walkable;
	walkable.push_back(' ');

	// Positions are switched because map variable is indexed backwards
	for (unsigned int i = 0; i < walkable.size(); i++)
	{
		if (this->map[posY][posX] == walkable[i])
		{
			// Can walk on this, no collision
			return false;
		}
	}

	// Collision detected
	return true;
}

void CWorldMap::printCharStats()
{
	this->game->engine->consoleClear();

	cout << "Name: " << this->game->player->name << endl;
	cout << "=====================================================" << endl;
	cout << "HP: " << this->game->player->hpCurrent << "/" << this->game->player->hpMax << endl;
	cout << "MP: " << this->game->player->mpCurrent << "/" << this->game->player->mpMax << endl;
	cout << endl;
	cout << "Strength:\t" << std::setw(3) << this->game->player->str << endl;
	cout << "Dexterity:\t" << std::setw(3) << this->game->player->dex << endl;
	cout << "Intelligence:\t" << std::setw(3) << this->game->player->intel << endl;
	cout << endl;
	cout << "Weapons: " << endl;
	cout << "Armor: " << endl;
	cout << endl;

	system("pause");
}

void CWorldMap::checkForInteraction()
{
	// Save 
	COORD pos;
	pos.X = this->playerPosition.X;
	pos.Y = this->playerPosition.Y;

	// Find characters
	char leftChar = this->map[pos.Y][pos.X - 1];
	char rightChar = this->map[pos.Y][pos.X + 1];
	char upChar = this->map[pos.Y-1][pos.X];
	char downChar = this->map[pos.Y+1][pos.X];

	// Make vector of all interactable chars
	vector<char> interactChars;
	interactChars.push_back( INTERACT_WEAPON );
	interactChars.push_back( INTERACT_ARMOR );
	interactChars.push_back( INTERACT_ITEMS );

	// Compare each character to vector
	for (int i = 0; i < interactChars.size(); i++)
	{
		if (interactChars[i] == leftChar ||
			interactChars[i] == rightChar ||
			interactChars[i] == upChar ||
			interactChars[i] == downChar)
		{
			// Enter shop
			this->game->setScene(SCENE_SHOP);

			return;
		}
	}
}

string CWorldMap::returnRegion()
{
	// Go through all regions and find current one
	for (unsigned int i = 0; i < this->region.size(); i++)
	{
		// Get region coords
		int topLeftX = this->region[i].topleft.X;
		int topLeftY = this->region[i].topleft.Y;
		int botRightX = this->region[i].bottomright.X;
		int botRightY = this->region[i].bottomright.Y;

		// Find if player is in this region
		if (this->playerPosition.X >= topLeftX &&
			this->playerPosition.X <= botRightX &&
			this->playerPosition.Y <= botRightY &&
			this->playerPosition.Y >= topLeftY)
		{
			return this->region[i].name;
		}
	}

	return string("None");
}