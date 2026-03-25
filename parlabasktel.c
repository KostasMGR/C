/*
 * compile command: mpicc parlabasktel.c -o parlabasktel
 * executable command: mpiexec -np 4 ./parlabasktel
*/

#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv)
{
    int my_rank; //ID τρέχουσας διεργασίας
    int p, k; // p: συνολικό πλήθος διεργασιών, k: μετρητής
    int source, target;
    int tag_menu=10; //input επιλογής
    int tag_n = 20; // μέγεθος πίνακα
    int tag_data = 30; // απεσταλμένα κομμάτια πίνακα
    int tag_res1 = 40; // αποτελέσματα για μέση τιμή και μέγιστη τιμή
    int tag_params = 50; //στέλνει πίσω το τελικο μ και m
    int tag_res2 = 60; // αποτελέσματα για διασπορά και διανυσμα δ

    int done=0; //μεταβλητη για ατερμων βρογχο
    int choise; //επιλογη απο menu

    int plithos, num; // n = συνολικό πλήθος, num = τοπικό πλήθος

    double data[100]; // Ο κεντρικός πίνακας X (Process 0)
    double data_loc[100]; // Ο τοπικός πίνακας X (Workers)
    double delta_fin[100]; // Ο τελικός πίνακας δ (Process 0)
    double delta_loc[100]; // Ο τοπικός πίνακας δ (Workers)

    double tot_sum;
    double variance;

    MPI_Status status;

    MPI_Init(&argc, &argv); // Αρχικοποίηση MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // αποθήκευση του ID της τρέχουσας διεργασίας στο my_rank
    MPI_Comm_size(MPI_COMM_WORLD, &p); // αποθήκευση πόσες διεργασίες ξεκίνησαν συνολικά

    while(!done) // Ατέρμων βρόγχος
    {
        if(my_rank==0) // Αν είναι o master
        {
            // Μενού έναρξης
            printf("\n=================================\n");
            printf("Menu\n");
            printf("1. Εισαγωγή τιμών και υπολογισμός\n");
            printf("2. Έξοδος\n");
            printf("Πληκτρολογίστε την επιλογή σας: \n");
            fflush(stdout); // Καθαρισμός buffer για άμεση εμφάνηση
            scanf("%d", &choise);
            printf("\n");

            if(choise==2) // Επιλογή 2 = τερματισμός
            {
                printf("Bye\n");
                done=1;
            }

            for(target=1; target<p; target++)
                MPI_Send(&done, 1, MPI_INT, target, tag_menu, MPI_COMM_WORLD); // Αποστολή μεταβλητής done για την συνέχεια ή τον τερματισμό

        }

        else
        {
                MPI_Recv(&done, 1, MPI_INT, 0, tag_menu, MPI_COMM_WORLD, &status); // Παραλαβή της done για συνέχεια ή τερματισμό

        }

        if(done) break; // Διακοπή βρόγχου αν done=1

        if (my_rank == 0) // Αν είναι o master
        {
            printf("Δώσε το πλήθος των αριθμών:\n");
            scanf("%d", &plithos);
            printf("Δώσε τους %d αριθμούς:\n", plithos);
            for (k=0; k<plithos; k++)
                scanf("%le", &data[k]);

            for (target = 1; target < p; target++)
                MPI_Send(&plithos, 1, MPI_INT, target, tag_n, MPI_COMM_WORLD); // Αποστολή πλήθους στους workers

            num = plithos/p; // πόσες τιμές αντιστοιχεί στον κάθε worker
            k=num; // δεικτης ξεκινά εκεί που τελειώνει o master

            for (target = 1; target < p; target++)
            {
                MPI_Send(&data[k], num, MPI_DOUBLE, target, tag_data, MPI_COMM_WORLD); // στέλνει το κομμάτι
                k+=num; // μετακινεί τον δείκτη στον επόμενο
            }

            for (k=0; k<num; k++)
                data_loc[k]=data[k]; // κομμάτι αρχικής διεργασίας
        }

        else
        {
            MPI_Recv(&plithos, 1, MPI_INT, 0, tag_n, MPI_COMM_WORLD, &status); // λήψη κομματίου
            num = plithos/p; // υπολογισμός μεγέθους
            MPI_Recv(&data_loc[0], num, MPI_DOUBLE, 0, tag_data, MPI_COMM_WORLD, &status); // λήψη τοπικού πίνακα
        }

        double loc_sum=0.0; // τοπικό άθροισμα
        double loc_max=data_loc[0]; // τοπικό μέγιστο

        for(k=0; k<num; k++)
        {
            loc_sum+=data_loc[k]; // Ερώτημα α

            if(data_loc[k]>loc_max)
                loc_max=data_loc[k]; // Ερώτημα β
        }

        double global_m=0.0; // τελική μέση τιμή
        double global_max=0.0; // τελικό μέγιστο

        if(my_rank!=0) // οι workers στελνουν
        {
            double results[2]={loc_sum, loc_max}; // πίνακας με τις τελικες τιμές
            MPI_Send(results, 2, MPI_DOUBLE, 0, tag_res1, MPI_COMM_WORLD); // Αποστολή στον master
        }

        else // ο master παραλαμβάνει
        {
            tot_sum=loc_sum; // συνολικό άθροισμα
            global_max=loc_max; // ολικό μέγιστο

            double temp_res[2]; // προσωρινός πίνακας λήψης

            for(source=1; source<p; source++)
            {
                MPI_Recv(temp_res, 2, MPI_DOUBLE, source, tag_res1, MPI_COMM_WORLD, &status); // λήψη πακέτων
                tot_sum+=temp_res[0]; // πρόσθεση για το ολικό άθροισμα
                if(temp_res[1]>global_max) // εύρεση ολικού μεγίστου
                    global_max=temp_res[1];
            }

            global_m=tot_sum/plithos; // υπολογισμός μέσης τιμής (ερώτημα α)

            // Εκτύπωση αποτελεσμάτων για τα ερωτήματα α και β
            printf("\n");
            printf("(α) Μέση Τιμή (μ): %.2f\n", global_m);
            printf("(β) Μέγιστη Τιμή (m): %.2f\n", global_max);

        }

        double params[2]; // πίνακας για μ και m

        if(my_rank==0) // o master
        {
            params[0]=global_m; // τοποθετεί μ
            params[1]=global_max; // τοποθετεί m
            for(target=1; target<p; target++)
            {
                MPI_Send(params, 2, MPI_DOUBLE, target, tag_params, MPI_COMM_WORLD); // στέλνει στους workers τα πακέτα των τιμών μ και m που τους αναλογεί
            }
        }
        else // οι workers
        {
            MPI_Recv(params, 2, MPI_DOUBLE, 0, tag_params, MPI_COMM_WORLD, &status); // λήψη από workers
            global_m=params[0]; // ανάκτηση μ
            global_max=params[1]; // ανάκτηση m
        }

        double local_var_sum=0.0; // τοπικό άθροισμα διασποράς

        for(k=0; k<num; k++)
        {
            local_var_sum+=(data_loc[k]-global_m)*(data_loc[k]-global_m); // (xi-μ)^2 Ερώτημα γ

            delta_loc[k]=(data_loc[k]-global_max)*(data_loc[k]-global_max); // (xi-m)^2 Ερώτημα δ
        }

        if(my_rank!=0) // οι workers στέλνουν
        {
            MPI_Send(&local_var_sum, 1, MPI_DOUBLE, 0, tag_res2, MPI_COMM_WORLD); // το τελικό άθροισμα της διασποράς στον πίνακα
            MPI_Send(delta_loc, num, MPI_DOUBLE, 0, tag_res2+1, MPI_COMM_WORLD); // το νέο διάνυσμα στην επόμενη θέση
        }

        else // ο master παραλαμβάνει
        {
            double total_var = local_var_sum; // ολική διασπορά
            for(k=0; k<num; k++)
                delta_fin[k]=delta_loc[k]; // ολικό δ

            int idx=num; // δείκτης λήψης
            for(source=1; source<p; source++)
            {
                double temp;
                MPI_Recv(&temp, 1, MPI_DOUBLE, source, tag_res2, MPI_COMM_WORLD, &status); // λήψη διασποράς
                total_var+=temp; // άθροιση

                MPI_Recv(&delta_fin[idx], num, MPI_DOUBLE, source, tag_res2+1, MPI_COMM_WORLD, &status); // λήψη διανύσματος
                idx+=num; //μετακίνηση δείκτη
            }

            variance=total_var/plithos; // υπολογισμός ολικής διασποράς

            // Εκτύπωση αποτελεσμάτων για τα ερωτήματα γ και δ
            printf("(γ) Διασπορά (var): %.2f\n", variance);
            printf("(δ) Διάνυσμα δ: ");
            for(k=0; k<plithos; k++)
                printf("%1f", delta_fin[k]);
        }

        MPI_Barrier(MPI_COMM_WORLD); // Συγχρονισμός μενού
    }

    MPI_Finalize(); // Κλείσιμο MPI περιβάλλοντος
    return 0;
}
