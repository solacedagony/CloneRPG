#include <Windows.h>
#include <iostream>

#include "Player.h"

using std::cout;
using std::endl;

CPlayer::CPlayer(void)
{
	initializeXpCurve();

	this->name = "";
	this->xp = 0;
	this->hpCurrent = 0;
	this->hpMax = 0;
	this->mpCurrent = 0;
	this->mpMax = 0;
	this->str = 0;
	this->dex = 0;
	this->intel = 0;
	this->level = 1;
}


CPlayer::~CPlayer(void)
{
}

void CPlayer::checkLevel()
{
	if (this->level == 0)
	{
		return;
	}

	bool levelCheck = true;
	while (levelCheck)
	{
		if (this->xp >= this->xpRequiredForLevelUp[this->level])
		{
			cout << "You gained a level!" << endl;
			cout << "" << endl;
			
			// Calculate new level
			cout << "Level: " << this->level << "->";
			this->level += 1;
			cout << this->level << endl;

			// Calculate HP
			cout << "HP: " << this->hpMax << "->";
			this->hpMax = this->hpMax*1.1;
			this->hpCurrent = this->hpMax;
			cout << this->hpMax << endl;

			// Calculate MP
			cout << "MP: " << this->mpMax << "->";
			this->mpMax = this->mpMax*1.1;
			this->mpCurrent = this->mpMax;
			cout << this->mpMax << endl;

			// Calculate strength
			cout << "Str: " << this->str << "->";
			this->str = this->str*1.1;
			cout << this->str << endl;

			// Calculate dexterity
			cout << "Dex: " << this->dex << "->";
			this->dex = this->dex*1.1;
			cout << this->dex << endl;

			// Calculate intelligence
			cout << "Int: " << this->intel << "->";
			this->intel = this->intel*1.1;
			cout << this->intel << endl;
		}
		else
		{
			levelCheck = false;
		}
	}
}

void CPlayer::initializeXpCurve()
{
	this->xpRequiredForLevelUp[1] = 10;
	this->xpRequiredForLevelUp[2] = 25;

	for (unsigned int i = 3; i < 99; i++)
	{
		if (i < 5)
		{
			xpRequiredForLevelUp[i] = xpRequiredForLevelUp[i - 1] + 10;
		}
		else
		{
			xpRequiredForLevelUp[i] = xpRequiredForLevelUp[i - 1] + xpRequiredForLevelUp[i - 3];
		}
	}	
}