#ifndef _ENGINE_H
#define _ENGINE_H

#include <Windows.h>
#include <string>
using std::string;

class CEngine
{
public:
	CEngine(void);
	~CEngine(void);

	void consoleSetPosition( COORD pos );
	void consolePrint( string text );
	void consolePrint( string text, COORD pos );
	void consoleClear( );

	void consoleSetColor(WORD color);

	void Log( string text );
	string getDateTime();

private:
	HANDLE consoleHandle;
	COORD currentCursorPosition;

	string logFilename;
};

#endif