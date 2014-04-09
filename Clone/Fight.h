#ifndef FIGHT_H
#define FIGHT_H

#include "Game.h"

#define DAMAGE_PIERCE	1
#define DAMAGE_BLUNT	2
#define DAMAGE_FIRE		3
#define DAMAGE_EARTH	4
#define DAMAGE_ICE		5
#define DAMAGE_WIND		6

class CFight
{
public:
	CFight( CGame *game );
	~CFight();

	// Draw functions
	void draw();
	void printStats();
	void printPreviousActions();
	void printOptions();

	// Calculate damage functions
	int computeAndApplyPCMeleeDamage();
	int computeAndApplyPCMagicDamage();
	int computeAndApplyPCSkillDamage();
	int computeAndApplyNPCDamage();

	// Enemy configuration functions
	void setupEnemy( CPlayer *player );

private:
	CGame *game;
	CPlayer *enemy;

	// For displaying last damage
	int lastPCDamage;
	int lastNPCDamage;
};

#endif