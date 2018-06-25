#if 0
William Daniel Taylor
6.23.18
Random walk example in C using ncurses.
#endif

//!Make sure to compile using -lncurses and -std=c99

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct Walker
{
    int x;
    int y;
}Walker;

//screen setup
void screenSetup()
{
    initscr();
    printw("Ctrl + C to exit.");
    noecho();
    refresh();
}//end method

void display(int y, int x)
{
    //print step and refresh
    mvprintw(y, x, "*");
    refresh();

    //delay
    usleep(20000);
}//end method

void generateStep(Walker* w, int numSteps)
{
    //initialize randomizer
    srand(time(NULL));

    for(int i = 1; i <= numSteps; i++)
    {
        //create random between 0 and 3
        int step = rand() % 4;
        
        //decide step
        switch(step)
        {
            case 0:
                w->x = w->x + 1;
                break;
            case 1:
                w->x = w->x - 1;
                break;
            case 2:
                w->y = w->y + 1;
                break;
            case 3:
                w->y = w->y - 1;
                break;
            default:
                break;
        }//end switch

        //draw step
        display(w->y, w->x);
    }//end for
}//end method

int main()
{
    screenSetup();

    Walker* walker;
    walker = malloc(sizeof(Walker));

    //starting coordinates
    walker->x = 50;
    walker->y = 20;

    generateStep(walker, 10000);
    refresh();
    
    getch();
    endwin();

    return 0;
}//end method