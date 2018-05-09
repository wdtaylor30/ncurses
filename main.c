#if 0
William Daniel Taylor
5.7.18
The beginnings of a roguelike RPG...
RESUME AT Part III 5:52
#endif

/* When compiling, use -lncurses and -std=c99 flags */

#include <ncurses.h>
#include <stdlib.h>

//player building
typedef struct Player
{
	int xPos;
	int yPos;
	int hp;
}Player;

//room building
typedef struct Room
{
	int xPos;
	int yPos;
	
	int height;
	int width;

	/*
	//array of pointers to enemies
	Enemies** enemies;
	
	//array of pointers to items
	Items** items;
	*/
}Room;

//environment building
void screenSetup();
Room** mapSetup();
Room* createRoom(int y, int x, int height, int width);
Player* playerSetup();

//user input and movement
void handleInput(int input, Player* user);
void playerMove(int y, int x, Player* user);
void checkPosition(int newY, int newX, Player* user);

/*Main */
int main()
{
	//initialize environment
	screenSetup();
	mapSetup();

	//create player
	Player* user;
	user = playerSetup();

	//main game loop
	int ch;
	while ((ch = getch()) != 'q')
	{
		handleInput(ch, user);
	}
	endwin();

	return 0;
}//end main


void screenSetup()
{
	initscr();
	printw("Press 'q' to exit.");
	noecho();
	refresh();

	return;
}//end method

Room** mapSetup()
{
	Room** rooms;
	rooms = malloc(sizeof(Room) * 6);
	//mvprintw(y, x, "string")

	//top wall
	mvprintw(13, 13, "--------");

	//walkways
	for (int y = 14; y <= 17; y++)
	{
		mvprintw(y, 13, "|......|");
	}//end for

	//bottom wall
	mvprintw(18, 13, "--------");

	//store room information
	rooms[0] = createRoom(13, 13, 6, 8);
}//end method

Room* createRoom (int y, int x, int height, int width)
{
	
}//end method

Player* playerSetup()
{
	Player* newPlayer;
	newPlayer = malloc(sizeof(Player));

	//starting position
	newPlayer->xPos = 14;
	newPlayer->yPos = 14;

	//health
	newPlayer->hp = 100;

	//draw player and move cursor back
	playerMove(14, 14, newPlayer);


	return newPlayer;
}//end method

void handleInput(int input, Player* user)
{
	int newY, newX;
	switch(input)
	{
		//move up
		case 'w':
		case 'W':
			newY = user->yPos - 1;
			newX = user->xPos;
			break;

		//move down
		case 's':
		case 'S':
			newY = user->yPos + 1;
			newX = user->xPos;
			break;

		//move left
		case 'a':
		case 'A':
			newY = user->yPos;
			newX = user->xPos - 1;
			break;

		//move right
		case 'd':
		case 'D':
			newY = user->yPos;
			newX = user->xPos + 1;
			break;

		//default
		default:
			break;
	}//end switch

	checkPosition(newY, newX, user);
}//end method

/* Collision Detection */
void checkPosition(int newY, int newX, Player* user)
{
	int space;
	switch (mvinch(newY, newX))
	{
		//mvinch() finds floor; allow movement
		case '.':
			playerMove(newY, newX, user);
			break;

		//otherwise, do not allow movement
		default:
			move(user->yPos, user->xPos);
			break;
	}//end switch
}//end method

void playerMove(int y, int x, Player* user)
{
	//replace player with floor
	mvprintw(user->yPos, user->xPos, ".");

	//update user positon
	user->yPos = y;
	user->xPos = x;

	//draw player and move cursor back
	mvprintw(user->yPos, user->xPos, "@");
	move(user->yPos, user->xPos);
}//end method
