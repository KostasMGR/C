/*
Compile command: gcc mutext.c -pthread
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// Αρχικοποίση
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int turn = 1; 

void* print_one(void* arg); // <one>
void* print_two(void* arg); // <two>
void* print_three(void* arg); // <three>


int main(void)
{
    pthread_t t1, t2, t3;

    //Δημιουργεία των threads
    pthread_create(&t1, NULL, print_one, NULL);
    pthread_create(&t2, NULL, print_two, NULL);
    pthread_create(&t3, NULL, print_three, NULL);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}

void* print_one(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&lock); // Κλειδώνει το mutex για την turn

        while(turn!=1)
            pthread_cond_wait(&cond, &lock); // Κρίσιμο σημείο

        printf("<one> "); // Εκτύπωση απαιτούμενου μηνύματος
        fflush(stdout); // Εξασφάλιση άμεσης εκτύπωσης
        sleep(1); // Καθηστέριση ενός δευτερολέπτου
        turn = 2; // Αλλαγή σειράς για εκτέλεση επόμενου thread
        pthread_cond_broadcast(&cond); // Σήμα διακοπής αναμονής
        pthread_mutex_unlock(&lock); // Ξεκλείδωμα mutex
    }
    return NULL;
}

void* print_two(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&lock); // Κλειδώνει το mutex για την turn

        while(turn!=2)
            pthread_cond_wait(&cond, &lock); // Κρίσιμο σημείο

        printf("<two> "); // Εκτύπωση απαιτούμενου μηνύματος
        fflush(stdout); // Εξασφάλιση άμεσης εκτύπωσης
        sleep(1);
        turn = 3; // Αλλαγή σειράς για εκτέλεση επόμενου thread
        pthread_cond_broadcast(&cond); // Σήμα διακοπής αναμονής
        pthread_mutex_unlock(&lock); // Ξεκλείδωμα mutex
    }
    return NULL;
}

void* print_three(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&lock); // Κλειδώνει το mutex για την turn
        while(turn!=3)
            pthread_cond_wait(&cond, &lock); // Κρίσιμο σημείο

        printf("<three> "); // Εκτύπωση απαιτούμενου μηνύματος
        fflush(stdout); // Εξασφάλιση άμεσης εκτύπωσης
        sleep(1);
        turn = 1; // Αλλαγή σειράς για εκτέλεση επόμενου thread
        pthread_cond_broadcast(&cond); // Σήμα διακοπής αναμονής
        pthread_mutex_unlock(&lock); // Ξεκλείδωμα mutex
    }
    return NULL;
}

/*
 * Στο πρόγραμμα χρησιμοποιούνται μεταβλητές συνθήκης (condition variables) σε συνδυασμό με mutex για τον συγχρονισμό
 * των νημάτων.
 * Αιτιολόγηση:
 * Τα νήματα δεν απασχολούν τον CPU ενώ περιμένουν απλά αναστέλλονται μέχρι να λάβουν σήμα.
 * Με σημαφόρους, θα χρειαζόταν 3 διαφορετικοί, με αρχικές τιμές 1, 0, 0. Θα ήταν πιο πολύπλοκη για συνθήκες που
 * αλλάζουν δυναμικά. Άρα, επιλογή μεταβλητών συνθήκης είναι βέλτιστη για προβλήματα με σταθερή σειρά εκτέλεσης και
 * συνθήκες που εξαρτώνται από κοινή κατάσταση.
*/
