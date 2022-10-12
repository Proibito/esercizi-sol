#include<stdio.h>
#include<string.h>

int main()
{
    char stringa_input[100], stringa_output[100], stringa_output_invertita[100];
    unsigned i, somma=0, da_sommare, esponente=-1, j, temp;
    printf("Inserisci il numero da convertire: ");
    fgets(stringa_input, sizeof(stringa_input), stdin);
    printf("\nCodifica in base 2\n");

    /*while(stringa_input[0]!='\0')
    {
        somma = somma + stringa_input[0];

        for(i=0;i<strlen(stringa_input);i=i+4)
        {
            stringa_input[i]>>4;
        }
        esponente++;
    }*/

    i=0;
    while(stringa_input[i]!='\0')
    {
        esponente++;
        i++;
    }

    for(i=0;esponente>0;i++)
    {
        da_sommare = stringa_input[i] - '0';
        for(j=esponente-1;j>0;j--)
            da_sommare = da_sommare * 10;
        somma = somma + da_sommare;
        esponente--;
    }

    printf("\nStringa convertita in decimale\nConversione in binario...\n");

    temp = 0x2;
    while(somma!=0)
    {
        printf("%u", somma&0x1);
        //stringa_output[i] = somma&0x1;
        somma = somma >> 1;
    }


    return 0;
}