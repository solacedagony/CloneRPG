#ifndef MAINMENU_H
#define MAINMENU_H

class CGame;

class CMainMenu
{
public:
	CMainMenu( CGame *game );
	~CMainMenu();

	void draw();

private:
	CGame *game;
};

#endif