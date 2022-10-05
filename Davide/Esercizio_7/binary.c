#include<stdio.h>
#include<string.h>

int main()
{
    char stringa_input[100];
    int i;
    fgets(stringa_input, sizeof(stringa_input), stdin);
    int esponente=0;
    while(stringa_input[0]!='\0')
    {
        
        for(i=0;i<strlen(stringa_input);i=i+4)
        {
            stringa_input[i]>>4;
        }
        esponente++;
    }

    return 0;
}