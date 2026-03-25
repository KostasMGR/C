/*Να γραφτει προγραμμα που θα τοποθετει σε δυναμικα δεσμευμενο πινακα τις εφαπτομενες ολων των γωνιων 0-360
με βημα την μια μοιρα. Όπου δεν ειναι δυνατος ο υπολογισμος θα τοποθετειται η τιμη -999,99
οχι math.h, οχι τυπωμα πινακα*/

#include <stdio.h>
#include <stdlib.h>

double apots(double x);
double apotc(double x);


int main(int argc, char *argv[])
{

    double rad, hmitono, sinimitono;
    int deg;

    double *efapt=(double*)malloc(361*sizeof(double));

    if(efapt==NULL)
    {
        printf("ERROR MEMORY ALLOCATION");
        return 1;
    }

    for(deg=0; deg<=360; deg++)
    {
        if(deg==90 || deg==270)
        {
            efapt[deg]=-999.99;
        }
        else
        {
            rad=deg*3.1415/180.00;

            hmitono=apots(rad);
            sinimitono=apotc(rad);

            efapt[deg]=hmitono/sinimitono;
        }
    }

    free(efapt);

    return 0;
}

double apots(double x)
{
    double term=x;
    double sum=x;
    int n=1;

    for(int i=0; i<360; i++)
    {
        term=-term*x*x/((2*n)*(2*n+1));
        sum+=term;
        n++;
    }
    return sum;
}

double apotc(double x)
{
    double term=1.0;
    double sum=1.0;
    int n=1;

    for(int i=0; i<360; i++)
    {
        term=-term*x*x/((2*n-1)*(2*n));
        sum+=term;
        n++;
    }
    return sum;
}
