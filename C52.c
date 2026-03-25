/*Να γραφεί συνάρτηση η οποία θα λύνει τη δευτεροβάθμια εξίσωση. Η συνάρτηση θα επιστρέφει
 * εκτός από τις ρίζες ένα κωδικό με την ακόλουθη σημασία:

    1: Η εξίσωση είναι αδύνατη στο R.

    2: Η εξίσωση έχει διπλή ρίζα.

    3: Η εξίσωση έχει δύο ρίζες.

Να γραφεί πρόγραμμα το οποίο θα διαβάζει έναν αριθμό Ν και θα δημιουργεί Ν τυχαίες τριάδες συντελεστών
στο διάστημα [-10.0 ... 10.0] (με ένα δεκαδικό ψηφίο) και θα τυπώνει το πλήθος των εξισώσεων με διπλή ρίζα.*/

// compile command (OS: Linux): gcc C52.c -lm

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int solve(double a, double b, double c, double *x1, double *x2);

int main(int argc, char* argv[])
{
    int N, cnt=0;
    double a, b, c, r1, r2;
    int apot;

    srand(time(NULL));
    /*printf("Δωσε το Ν\n");
    scanf("%d", &N);
    if (N <= 0)
    {
        printf("Το N πρέπει να είναι θετικός αριθμός!\n");
        return 1;
    }*/
    //if(scanf("%d", &N)!=1||N<=0) return 1;

    do // θα του αρεσει περισσοτερο σαν ελεγχος εγκυροτητας
    {
        printf("Δωσε το Ν\n");
        scanf("%d", &N);
    }while(N<=0);

    for(int i=0; i<N; i++)
    {
        do
        {
            a=(rand()%201-100)/10.0;
        }while(a==0.0);

        b=(rand()%201-100)/10.0;
        c=(rand()%201-100)/10.0;

        apot=solve(a, b, c, &r1, &r2);

        if(apot==2)
            cnt++;
    }

    printf("Πληθος: %d\n", cnt);

    return 0;
}

int solve(double a, double b, double c, double *x1, double *x2)
{
    double diakr;
    diakr=b*b-4*a*c;
    if(diakr<0)
    {
        return 1;
    }
    else if(diakr==0)
    {
        *x1=-b/(2*a);
        *x2=*x1;
        return 2;
    }
    else
    {
        *x1 = (-b + sqrt(diakr)) / (2 * a);
        *x2 = (-b - sqrt(diakr)) / (2 * a);

        return 3;
    }
}
