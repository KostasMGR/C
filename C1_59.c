/*ΘΕΜΑ (C-1-59) "Να γραφεί πρόγραμμα το οποίο θα διαβάζει ένα αρχείο κειμένου, γραμμή γραμμή,
 *και θα γράφει σε νέο αρχείο κειμένου όλες τις γραμμές που αποτελούνται, αποκλειστικά,
 * από πεζούς λατινικούς χαρακτήρες.
 * Τα ονόματα των δύο αρχείων δίνονται, παραμετρικά, στην γραμμή εντολών."*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//void openfile(const char name[], const char mode[], FILE **fp);
bool lower(const char *str);

int main(int argc, char *argv[])
{

    char line[1024];

    if(argc!=3)
    {
        printf("Χρήση: %s <αρχείο_εισόδου> <αρχείο_εξόδου>\n", argv[0]);
        exit(1);
    }

    FILE *fin=fopen(argv[1], "r");
    if(fin==NULL)
    {
        perror("Σφαλμα κατα το ανοιγμα του αρχειου εισοδου\n");
        exit(1);
    }

    FILE *fout=fopen(argv[2], "w");
    if(fout==NULL)
    {
        perror("Σφαλμα κατα το ανοιγμα του αρχειου εξοδου\n");
        fclose(fin);
        exit(1);
    }


    while(fgets(line,sizeof(line), fin)!=NULL)
    {
        if(lower(line))
        {
            fputs(line, fout);
        }
    }

    fclose(fin);
    fclose(fout);

    return 0;
}

bool lower(const char *str)
{
    int i=0;
    bool itis=false;

    while(str[i]!='\0'&&str[i]!='\n'&&str[i]!='\r')
    {
        if (!islower((unsigned char)str[i])) //str<'a'||str[i]>'z'
        {
            return false;
        }
        itis=true;
        i++;
    }
    return itis;
}
