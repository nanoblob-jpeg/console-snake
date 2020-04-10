#include <iostream>

//for the keypresses
#include <conio.h>

#ifndef WINDOWS
#define WINDOWS
//for multithreading
#include "mingw.thread.h"
#include <windows.h>
#endif
//the following line is necessary for the
//  GetConsoleWindow() function to work!
//it basically says that you are running this
//  program on Windows 2000 or higher
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

//game header file
#include "game.h"


int main (void)
{
	HWND console = GetConsoleWindow();
  	RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    //window resized to 40(80 space, width)x35(35 lines, height)
    //MoveWindow(window_handle, x, y, width, height, redraw_window);
    short width{720}, height{600};
    MoveWindow(console, r.left, r.top, width, height, TRUE);

    //start game in it's own thread
	std::thread gameThread(runGame);


	gameThread.join();

	std::cout << "Thanks for playing";

	//closing the console window
	HWND wnd=GetConsoleWindow();
	PostMessage(wnd, WM_CLOSE, 0, 0);
	system("color 07");
	exit(0);
	return 0;
}