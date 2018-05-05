#if 0
William Daniel Taylor
4.21.18
#endif

/* hello world using ncurses
   make sure to compile with the -lncurses flag! */

//header file for ncurses
#include <ncurses.h>

int main()
{
	//start curses mode
	initscr();

	//print Hello World
	printw("Hello world!");

	//print to screen
	refresh();

	//wait for user input
	getch();

	//end curses mode
	endwin();

	return 0;
}
