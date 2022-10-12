#include <stdio.h>

int main()
{
    char input[100] = {0};
    fgets(input, 100, stdin);
    int lunghezzaStringa = 0;

    for (int i = 0; i < 100; i++)
    {
        // printf(" %d", input[i]);
        if (input[i] == 10)
        {
            lunghezzaStringa = i;
            break;
        }
    }

    printf("\nlunghezza string %d\n", lunghezzaStringa);
    char caratteriLetti[lunghezzaStringa];
    for (int i = 0; i < lunghezzaStringa; i++)
    {
        int continua = 0;
        int contati = 0;
        for (int k = 0; k < lunghezzaStringa; k++)
        {
            if (caratteriLetti[k] == input[i])
            {
                continua = 1;
            }
        }
        if (continua)
        {
            continue;
        }
        else
        {
            int trovato = 0;
            for (int f = 0; f < lunghezzaStringa; f++)
            {
                if (input[i] == input[f])
                {
                    trovato++;
                }
            }
            printf("%d - %c \n", trovato, input[i]);
            caratteriLetti[i] = input[i];
        }
    }
    return 0;
}