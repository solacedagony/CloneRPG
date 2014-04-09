#include <iostream>

#include "Shop.h"

using std::cout;
using std::endl;

CShop::CShop( CGame *gameArg )
{
	this->game = gameArg;
}

CShop::~CShop()
{
}

void CShop::draw()
{
	cout << "Shop keeper" << endl;
	cout << endl;
	
	system("pause");
	this->game->setScene(SCENE_WORLDMAP);

	// Print contents and gold prices
}