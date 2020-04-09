#include <iostream>

//for the keypresses
#include <conio.h>

//for multithreading
#include "mingw.thread.h"

//the following line is necessary for the
//  GetConsoleWindow() function to work!
//it basically says that you are running this
//  program on Windows 2000 or higher
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

//windows API
#include <windows.h>

//game header file
#include "game.h"


//variables for color changing
HANDLE hStdout; 
CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 


int main (void)
{
	std::thread gameThread(runGame);

	gameThread.join();

	std::cout << "Thanks for playing";

	//closing the console window
	HWND wnd=GetConsoleWindow();
	PostMessage(wnd, WM_CLOSE, 0, 0);
	exit(0);
	return 0;
}




//resizing the window
/*
  HWND console = GetConsoleWindow();
  RECT r;
  GetWindowRect(console, &r); //stores the console's current dimensions

  //MoveWindow(window_handle, x, y, width, height, redraw_window);
  MoveWindow(console, r.left, r.top, 800, 600, TRUE);
  Sleep(1000);
  MoveWindow(console, r.left, r.top, r.right - r.left, r.bottom - r.top, TRUE);
 */

//changing the color
/*
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout,  BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "test  ";

    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
 */