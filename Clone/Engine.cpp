#include <Windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <ctime>

#include "Engine.h"

using std::cout;
using std::endl;

#define GAMETITLE "Clone RPG"
#define FILENAME_LOG "log.txt"

CEngine::CEngine(void)
{
	// Setup window
	this->consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Error check window
	if( this->consoleHandle == INVALID_HANDLE_VALUE )
	{
		DWORD error = GetLastError();

		// Log error here
		cout << "RECEIVED ERROR IN GetStdHandle: " << this->consoleHandle << endl;
	}

	// Setup window parameters
	SetConsoleTitle( GAMETITLE );
	//SetConsoleWindowInfo( this->consoleHandle,  );
	//MoveWindow();
	//COORD *bufferSize = new COORD;
	//bufferSize->X = 5;
	//bufferSize->Y = 5;

	//SetConsoleDisplayMode( this->consoleHandle, CONSOLE_FULLSCREEN_MODE, bufferSize );

	this->logFilename = FILENAME_LOG;

	// Print date and time to log
	string startLog = "Game started at ";
	startLog += this->getDateTime();

	this->Log( startLog );
}

CEngine::~CEngine(void)
{
	this->Log( "" );
	FreeConsole();
}

void CEngine::consolePrint( string text )
{
	COORD pos = { this->currentCursorPosition.X, this->currentCursorPosition.Y };
	consoleSetPosition( pos );
	cout << text;
}

void CEngine::consolePrint( string text, COORD pos )
{
	consoleSetPosition( pos );
	cout << text;
}

void CEngine::consoleSetPosition( COORD pos )
{
	SetConsoleCursorPosition( this->consoleHandle, pos );
}

/* Standard error macro for reporting API errors */ 
 #define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

 void CEngine::consoleClear( )
 {
    COORD coordScreen = { 0, 0 };    /* here's where we'll home the
                                        cursor */ 
    BOOL bSuccess;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */ 
    DWORD dwConSize;                 /* number of character cells in
                                        the current buffer */ 

    /* get the number of character cells in the current buffer */ 

    bSuccess = GetConsoleScreenBufferInfo( this->consoleHandle, &csbi );
    PERR( bSuccess, "GetConsoleScreenBufferInfo" );
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    /* fill the entire screen with blanks */ 

    bSuccess = FillConsoleOutputCharacter( this->consoleHandle, (TCHAR)' ',
       dwConSize, coordScreen, &cCharsWritten );
    PERR( bSuccess, "FillConsoleOutputCharacter" );

    /* get the current text attribute */ 

    bSuccess = GetConsoleScreenBufferInfo( this->consoleHandle, &csbi );
    PERR( bSuccess, "ConsoleScreenBufferInfo" );

    /* now set the buffer's attributes accordingly */ 

    bSuccess = FillConsoleOutputAttribute( this->consoleHandle, csbi.wAttributes,
       dwConSize, coordScreen, &cCharsWritten );
    PERR( bSuccess, "FillConsoleOutputAttribute" );

    /* put the cursor at (0, 0) */ 

    bSuccess = SetConsoleCursorPosition( this->consoleHandle, coordScreen );
    PERR( bSuccess, "SetConsoleCursorPosition" );
    return;
 }

 void CEngine::Log( string text )
 {
	 std::ofstream outFile;
	 outFile.open( logFilename, std::ios::out | std::ios::app );

	 outFile << text << endl;

	 outFile.close();

	 return;
 }

// Stolen from
//http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
string CEngine::getDateTime()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    localtime_s(&tstruct, &now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

void CEngine::consoleSetColor(WORD color)
{
	SetConsoleTextAttribute(this->consoleHandle, color);
}