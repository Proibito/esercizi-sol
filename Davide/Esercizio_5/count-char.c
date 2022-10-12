//Caratteri disponibili limitati a max 100
//Dimensione stringa massima = 100

//NOTA: non è stato gestito il caso in cui la stringa sfora dai limiti come richiesto dall'esercizio.

#include<stdio.h>

int main()
{
    char stringa[100];
    
    int i=0, j=0, n_caratteri_raccolti, found;
    char caratteri[100];
    int ripetizioni_caratteri[100];

    FILE* fp = fopen("dati_input.txt", "r");
    printf("Inserisci la stringa:\n");
    fgets(stringa, sizeof(stringa), fp);
    
    n_caratteri_raccolti=0;
    for(i=0;i<stringa[i]!='\0';i++)      //-1 per escludere il carattere del terminatore di stringa
    {
        //stringa[i]
        found=0;
        for(j=0;j<n_caratteri_raccolti&&found==0;j++)
        {
            if(stringa[i]==caratteri[j])
                found=1;
        }

        if(found==0)    //Se non ho trovato il carattere nella lista...
        {
            n_caratteri_raccolti++;
            caratteri[n_caratteri_raccolti-1] = stringa[i];
            ripetizioni_caratteri[n_caratteri_raccolti-1] = 1;
        }
        else            //...ma se invece l'ho trovato...
        {
            j--;        //Ritroviamo la posizione del carattere ripetuto. Il for aveva fatto un giro di troppo.
            ripetizioni_caratteri[j]++;
        }
    }

    //stampa finale
    for(i=0;i<n_caratteri_raccolti;i++)
    {
        printf("%c -- %d\n", caratteri[i], ripetizioni_caratteri[i]);
    }
}