/*
 Υπολογισμος ημιτονου+συνημιτονου μιας γωνιας με τη σειρα Taylor σε αυτονομες συναρτησεις
 εκτος απο αποτελεσμα οι συναρτησεις θα επιστρεφουν το πληθος των ορων που συμμετειχαν στον υπολογισμο
 να γραφει προγραμμα που να υπολογιζει αν ο υπολογισμος ημιτονου ή συνημιτονου χρειαζεται περισσοτερες επαναληψεις
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// #define PI 3.141592
// #define PRECI 1e-6

double tsin(double x, int *terms);
double tcos(double x, int *terms);

int main()
{
    double deg, rad;
    int cnts=0;
    int cntc=0;
    double apotsin, apotcos;

    if(scanf("%lf", &deg)!=1)
    {
        printf("Λαθος εισοδος");
        return 1;
    }

    rad=deg*(3.1415/180.00);

    apotsin=tsin(rad, &cnts);
    apotcos=tcos(rad, &cntc);

    printf("Ημιτονο: %.6f\n", apotsin);
    printf("Συνημιτονο: %.6f\n", apotcos);

    if(cntc>cnts)
    {
        printf("Ο υπολογισμος του συνημιτονου είχε περισσοτερους όρους: %f\n", apotcos);
    }
    else if (cntc<cnts)
    {
        printf("Ο υπολογισμος του ημιτονου είχε περισσοτερους όρους: %f\n", apotsin);
    }
    else
    {
        printf("Οι υπολογισμοι είχαν ιδιο πληθος ορων\n");
    }

    return 0;
}

double tsin(double x, int *terms)
{
    double term=x;
    double sum=x;
    int n=1;

    while(fabs(term)>1e-6)
    {
        term=-term*x*x/((2*n)*(2*n+1));
        sum+=term;
        n++;
    }
    *terms=n;

    return sum;
}

double tcos(double x, int *terms)
{
    double term=1.0;
    double sum=1.0;
    int n=1;

    while(fabs(term)>1e-6)
    {
        term=-term*x*x/((2*n-1)*(2*n));
        sum+=term;
        n++;
    }
    *terms=n;

    return sum;
}
