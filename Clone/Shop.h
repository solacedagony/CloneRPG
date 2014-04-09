#ifndef CSHOP_H
#define CSHOP_H

#include "Game.h"

class CShop
{
public:
	CShop( CGame *game );
	~CShop();

	void draw();

private:
	CGame *game;
};

#endif