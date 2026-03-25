/*
Να γραφει προγραμμα το οποιο θα διαβαζει τον χαρτη ενος λαβυρινθου και θα τυπωνει στην οθονη
(space=διαδρομος, '*'=τοιχος). Θα τοποθετει ανθρωπακι ("Α") σε τυχαια θεση του διαδρομου και θα το κινει πανω, κατω,
δεξια, αριστερα συμφωνα με τις εντολες του χρηστη που θα δινονται με τα cursor keys. Θα εκτελουνται εγκυρες κινησεις
(που δεν οδηγουνται σε τοιχο).

Η πρωτη γραμμη του αρχειου θα περιεχει τις διαστασεις του χαρτη (γραμμες, κενο, στηλες). Το προγραμμα τελειωνει μολις
πατηθει το escape. Ο χειρισμος της οθονης και του πληκτρολογιου θα γινουν με χρηση της ncurses
*/
//(hint esc=27 στο ncurses)

// compile command (OS: Linux): gcc C36.c -o C36 -lncurses

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define PLAYER 'A'

void openfile(const char name[], FILE **fp);

int main(int argc, char *argv[])
{
    char map[100][100];
    int rows, cols, x, y;
    int dx=0, dy=0;
    int resp=0;
    srand(time(NULL));

    FILE *fp; //=fopen(argv[1], "r");
    openfile("maze.txt", &fp);
    if(fp==NULL)
    {
        perror("Error file");
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d %d", &rows, &cols);

    while(fgetc(fp)!='\n');

    for(int i=0; i<rows; i++)
    {
        fgets(map[i], 100, fp);
    }
    fclose(fp);

    do
    {
        y=rand()%rows;
        x=rand()%cols;
    }while(map[y][x]=='*');

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    do
    {
        clear();
        //mvaddch(y,x, PLAYER);
        for(int i=0; i<rows; i++)
        {
            /*for(int j=0; j<cols; j++)
            {
                if(i==y && j==x)
                    addch(PLAYER);
                else
                    addch(map[i][j]);
            }
            addch('\n');*/
            mvprintw(i, 0, "%s", map[i]);
        }

        mvaddch(y, x, PLAYER);

        refresh();

        resp=getch();
        int next_x=x;
        int next_y=y;

        switch(resp)
        {
            case KEY_UP:
                next_y--; //if(y>0) y--;
                break;
            case KEY_DOWN:
                next_y++; //if(y<dy-1) y++;
                break;
            case KEY_LEFT:
                next_x--; //if(x>0) x--;
                break;
            case KEY_RIGHT:
                next_x++; //if(x<dx-1) x++;
                break;
        }

        if(next_y>=0 && next_y<rows &&
           next_x>=0 && next_x<cols &&
           map[next_y][next_x]!='*')
        {
            y=next_y;
            x=next_x;
        }
    }while(resp!=27);

    endwin();

    return 0;
}

void openfile(const char name[], FILE **fp)
{
    *fp=fopen(name, "r");
}
