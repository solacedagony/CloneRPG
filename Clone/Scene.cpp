#include "Scene.h"
#include "Game.h"

CScene::CScene()
{
	if (!this->engine)
	{
		this->engine = new CEngine;
	}
	if (!this->player)
	{
		this->player = new CPlayer;
	}
}

CScene::~CScene()
{
	delete this->engine;
	delete this->player;
}