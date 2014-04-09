#include "Item.h"
#include "Defines.h"

CItem::CItem()
{
	this->name = "Unnamed Item";
	this->type = ITEM_WEAPON;
	this->cost = 1;
	this->weight = 1;

	// Weapon type variables
	this->damageBase = 0;
	this->damageMod = 0;
	this->accuracy = 0;

	// Armor type variables
	this->armor = 0;

	// Item type variables
	this->hpRestore = 0;
	this->mpRestore = 0;

	this->healsPoison = false;
	this->healsParalysis = false;

	this->bringsBackToLife = false;
	this->percentHpAfterLife = 0;
}

CItem::~CItem()
{
}

