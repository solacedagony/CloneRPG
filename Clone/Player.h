#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>
#include <string>
#include "Item.h"
#include "Randomizer.h"

using std::string;
using std::vector;

class CPlayer
{
public:
	CPlayer(void);
	~CPlayer(void);

	string name;
	unsigned int level;
	unsigned int xp;

	double hpMax;
	double hpCurrent;
	double mpMax;
	double mpCurrent;

	double str;
	double dex;
	double intel;

	CItem weapon;
	CItem armor;
	
	double amountStrMod;
	double amountDexMod;
	double amountIntMod;

	double magicFireDef;
	double magicEarthDef;
	double magicIceDef;
	double magicWindDef;

	void checkLevel();

	CRandomizer randomizer;
		
private:
	// Inventory
	std::vector<int> items;
	std::vector<int> skills;
	std::vector<int> spells;

	// Xp data
	void initializeXpCurve();
	unsigned int xpRequiredForLevelUp[100];
};

#endif