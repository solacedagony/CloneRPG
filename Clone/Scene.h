#ifndef SCENE_H
#define SCENE_H

#include "Engine.h"
#include "Player.h"

class CGame;

class CScene
{
public:
	CScene();
	~CScene();

	CGame *game;
	CEngine *engine;
	CPlayer *player;

	virtual void draw() = 0;
	
private:
	

	
};

#endif