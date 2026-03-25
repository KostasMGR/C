/*Να γραφτει προγραμμα C με ncurses οπου: θα αρχικοποιει την οθονη και θα αποκρυπτει τον κερσορα
 θα τοποθετει χαρακτηρα @ στο κεντρο της οθονης
 θα επιτρεπει στον χρηστη να μετακινει τον παικτη με τα βελακια
 θα διασφαλιζεται οτι δεν θα βγαινει εκτος οριο παραθυρου
 θα τερματιζει με το Q*/

// compile: gcc ncursestry.c -o ncursestry -lncurses

#include <stdio.h>
#include <ncurses.h>
#include <time.h>

#define PLAYER 'A'

int main()
{
    //srand=(time(NULL));
    int resp;
    int x,y;
    int maxx, maxy;

    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    getmaxyx(stdscr, maxy,maxx);

    y=maxy/2;
    x=maxx/2;

    do
    {
        clear();
        mvaddch(y,x, PLAYER);
        refresh();

        resp=getch();

        switch(resp)
        {
            case KEY_UP:
                if(y>0) y--;
                break;
            case KEY_DOWN:
                if(y<maxy-1) y++;
                break;
            case KEY_LEFT:
                if(x>0) x--;
                break;
            case KEY_RIGHT:
                if(x<maxx-1) x++;
                break;
        }
    }while(resp!='q' && resp !='Q');
    endwin();
    return 0;
}
