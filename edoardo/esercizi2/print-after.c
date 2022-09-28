#include <stdio.h>
//ti ho akkerato
int main()
{
    char s1[81], s2[81];
    int indiceFineRiga;

    fgets(s1, 81, stdin);
    printf("Prima stringa: %s\n", s1);

    fgets(s2, 81, stdin);
    printf("Seconda stringa: %s \n", s2);

    // pulizia

    for (int i = 0; i < 81; i++)
    {
        if (s1[i] < 32 || s1[i] > 126)
        {
            s1[i] = '\0';
            break;
        }
    }

    for (int i = 0; i < 81; i++)
    {
        if (s2[i] < 32 || s2[i] > 126)
        {
            indiceFineRiga = i;
            s2[i] = '\0';
            break;
        }
    }

    // contenitore
    for (int i = 0; '\0' != s1[i]; i++)
    {
        int valoreDiI = 0;
        int lunghezza = 0;
        for (int k = 0; '\0' != s2[k]; k++)
        {
            if (s2[k] != s1[i + valoreDiI])
            {
                break;
            }
            valoreDiI++;
            lunghezza++;
        }
        if (lunghezza == indiceFineRiga)
        {
            printf("trovato: %s \n", &s1[i+lunghezza]);
            break;
        }
    }
    // ancora e ancora

    // lo sto modificando
    return 0;
}
