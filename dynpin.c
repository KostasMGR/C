/*ΝΑ ΦΤΙΑΧΤΕΙ ΠΡΟΓΡΑΜΜΑ ΣΤΗ C  ΟΠΟΥ ΘΑ ΔΗΜΙΟΥΡΓΕΙ ΔΥΝΑΜΙΚΟ ΠΙΝΑΚΑ ΜΕ ΤΟΥΣ Ν ΜΙΚΡΟΤΕΡΟΥΣ ΠΡΩΤΟΥΣ ΑΡΙΘΜΟΥ.
ΘΑ ΧΡΗΣΙΜΟΠΟΙΕΙ ΜΙΑ ΣΥΝΑΡΤΗΣΗ ΓΙΑ ΤΟ ΓΕΜΙΣΜΑ ΤΟΥ ΠΙΝΑΚΑ ΚΑΙ ΑΛΛΗ ΜΙΑ ΣΥΝΑΡΤΗΣΗ ΠΟΥ ΘΑ ΕΛΕΓΧΕΙ
ΑΝ Ο ΑΡΙΘΜΟΣ ΕΙΝΑΙ ΠΡΩΤΟΣ*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void fill(int *pin, int N);
bool prime(int num);

int main()
{
    int N;
    printf("Δωσε πληθος πρωτων αριθμων Ν\n");
    if(scanf("%d", &N)!=1 || N<=0)
    {
        printf("Το Ν πρεπει να ειναι θετικο\n");
        return 1;
    }

    int *pin=(int*)malloc(N*sizeof(int));
    if(pin==NULL)
    {
        printf("Σφαλμα κατα την δεσμευση μνημης\n"); //perror("Σφαλμα κατα την δεσμευση μνημης\n");
        return 1;
    }

    fill(pin, N);

    printf("Οι %d πρωτοι αριθμοι ειναι:\n", N);
    for(int i=0; i<N; i++)
    {
        printf("%d", pin[i]);
    }
    printf("\n");

    free(pin);

    return 0;
}

bool prime(int num)
{
    if(num<2)
    {
        return false;
    }
    for(int i=2; i*i<=num; i++)
    {
        if(num%i==0)
        {
            return false;
        }
    }
    return true;
}

void fill(int *pin, int N)
{
    int cnt=0;
    int cand=2;

    while(cnt<N)
    {
        if(prime(cand))
        {
            pin[cnt]=cand;
            cnt++;
        }
        cand++;
    }
}
