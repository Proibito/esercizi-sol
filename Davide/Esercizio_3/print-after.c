#include<stdio.h>
#include<string.h>

int main()
{
    char s1[81];
    char s2[81];
    int i=0, i2=0, j=0;

    fgets(s1, sizeof(s1), stdin);
    fgets(s2, sizeof(s2), stdin);

    while((int)s1[i]>=32&&(int)s1[i]<=126)
    {
        i++;
    }
    s1[i]='\0';

    while((int)s2[i]>=32&&(int)s2[i]<=126)
    {
        i++;
    }
    s2[i]='\0';

    for(i2=0;s1[i2]!='\0'||j==strlen(s2)-1;i2++)
    {
        i=i2;
        j=0;
        while(s1[i]==s2[j])
        {
            printf("\nTrovati %c e %c uguali", s1[i], s2[j]);
            i++, j++;
        }
        if(j==strlen(s2)-1)           //devo mettere il +1?
            break;
    }
    printf("\n%s", &s1[i2+j]);

    printf("\n");
    return 0;
}