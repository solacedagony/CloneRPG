#ifndef ITEM_H
#define ITEM_H

#include <string>

using std::string;

class CItem
{
public:
	CItem();
	~CItem();

	// Variables for all items
	string name;
	unsigned int type;
	unsigned int cost;
	unsigned int weight;

	// Weapon type variables
	unsigned int damageBase;
	unsigned int damageMod;
	unsigned int accuracy;

	// Armor type variables
	unsigned int armor;
	
	// Item type variables
	unsigned int hpRestore;
	unsigned int mpRestore;

	bool healsPoison;
	bool healsParalysis;

	bool bringsBackToLife;
	unsigned int percentHpAfterLife;

private:
};

#endif