#include <iostream>
#include <conio.h>

#include "Fight.h"
#include "Defines.h"

using std::cout;
using std::endl;

CFight::CFight( CGame *gameArg )
{
	this->game = gameArg;

	this->enemy = new CPlayer;
	
	this->lastNPCDamage = -2;
	this->lastPCDamage = -2;
}


CFight::~CFight()
{
	delete enemy;
}

void CFight::draw()
{
	// Print output
	this->printStats();
	cout << endl;
	this->printPreviousActions();
	cout << endl;
	this->printOptions();
	cout << endl;

	// Get input
	cout << "Input: ";
	char inputChar = _getch();

	// Parse input
	if (inputChar == KEY_1)
	{
		// Melee
		int pcAttack = this->computeAndApplyPCMeleeDamage();
		this->enemy->hpCurrent -= pcAttack;

		this->lastPCDamage = pcAttack;
	}
	else if (inputChar == KEY_2)
	{
		// Magic
		return;
	}
	else if (inputChar == KEY_3)
	{
		// Skill
		return;
	}
	else if (inputChar == KEY_4)
	{
		// Run
		return;
	}
	else
	{
		return;
	}

	// Check for killed enemy
	if (this->enemy->hpCurrent <= 0)
	{
		this->game->engine->consoleClear();
		cout << "You killed the " << this->enemy->name << "!" << endl;
		cout << endl;
		cout << "You gain " << this->enemy->xp << " xp." << endl;
		cout << "Xp: " << this->game->player->xp << "->";
		this->game->player->xp += this->enemy->xp;
		cout << this->game->player->xp << endl;
		cout << endl;

		this->game->player->checkLevel();

		system("pause");
		
		// Enemy is defeated, return to worldmap
		this->game->setScene(SCENE_WORLDMAP);

		// Reset class for next fight
		this->lastPCDamage = -2;
		this->lastNPCDamage = -2;

		return;
	}

	// Enemy response
	int enemyAttack = this->computeAndApplyNPCDamage();
	this->game->player->hpCurrent -= enemyAttack;
	this->lastNPCDamage = enemyAttack;

	// Check for killed player
	if (this->game->player->hpCurrent <= 0)
	{
		this->game->engine->consoleClear();
		cout << "You were killed by the " << this->enemy->name << "!" << endl;

		system("pause");

		// Player lost battle, return to main menu
		this->game->setScene(SCENE_MAINMENU);

		// Reset class for next fight
		this->lastPCDamage = -2;
		this->lastNPCDamage = -2;

		return;
	}
}

void CFight::printStats()
{
	cout << "Player Name: " << this->game->player->name << endl;
	cout << "HP: " << this->game->player->hpCurrent << "/" << this->game->player->hpMax << endl;
	cout << "MP: " << this->game->player->mpCurrent << "/" << this->game->player->mpMax << endl;

	cout << endl;

	cout << "Enemy Name: " << this->enemy->name << endl;
	cout << "HP: " << this->enemy->hpCurrent << "/" << this->enemy->hpMax << endl;
	cout << "MP: " << this->enemy->mpCurrent << "/" << this->enemy->mpMax << endl;
}

void CFight::printPreviousActions()
{
	// Player damage
	if (this->lastPCDamage == -1)
	{
		cout << "Your attack missed the " << this->enemy->name << "." << endl;
	}
	else if ( this->lastPCDamage == 0)
	{
		cout << "Your attack struck the " << this->enemy->name << " but dealt no damage." << endl;
	}
	else if (this->lastPCDamage > 0)
	{
		cout << "Your attack struck the " << this->enemy->name << " for " << this->lastPCDamage << " damage." << endl;
	}
	
	// Enemy damage
	if (this->lastNPCDamage == -1)
	{
		cout << "The " << this->enemy->name << "'s attack missed you." << endl;
	}
	else if (this->lastNPCDamage == 0)
	{
		cout << "The " << this->enemy->name << "'s attack struck you but dealt no damage." << endl;
	}
	else if (this->lastNPCDamage > 0)
	{
		cout << "The " << this->enemy->name << "'s attack struck you and dealt " << this->lastNPCDamage << " damage." << endl;
	}
}

void CFight::printOptions()
{
	cout << "1.) Physical Attack" << endl;
	cout << "2.) Magic Attack" << endl;
	cout << "3.) Skill" << endl;
	cout << "4.) Run" << endl;
}

int CFight::computeAndApplyPCMeleeDamage()
{
	double amountStrMod = 1.5;
	double amountDexMod = .4;
	double amountIntMod = .1;

	int startingPoint = 50.0*(1.0 + (this->game->player->dex / 50.0));
	double variability = double(this->game->randomizer.randomInteger(50, 100)) / 100.0;

	double damage = (((amountStrMod*this->game->player->str) + (amountDexMod*this->game->player->dex) + (amountIntMod*this->game->player->intel)) +
		(this->game->player->weapon.damageBase*this->game->player->weapon.damageMod))*(variability);

	return int(damage);
}

int CFight::computeAndApplyPCMagicDamage()
{
	return 0;
}

int CFight::computeAndApplyPCSkillDamage()
{
	return 0;
}

int CFight::computeAndApplyNPCDamage()
{
	double amountStrMod = 1.5;
	double amountDexMod = .4;
	double amountIntMod = .1;

	int startingPoint = 50.0*(1.0 + (this->game->player->dex / 50.0));
	double variability = double(this->game->randomizer.randomInteger(50, 100)) / 100.0;

	double damage = (((amountStrMod*this->enemy->str) + (amountDexMod*this->enemy->dex) + (amountIntMod*this->enemy->intel)) +
		(this->enemy->weapon.damageBase*this->enemy->weapon.damageMod))*(variability);

	return int(damage);
}

void CFight::setupEnemy( CPlayer *newEnemy )
{
	this->enemy = newEnemy;
}