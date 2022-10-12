#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Si legga da standard input (con fgets+strtol) un array di
// 7 interi. Si stampino prima tutti gli elementi di indice
// dispari e poi quelli di indice pari. Se per esempio
// vengono letti: 11 20 37 45 51 69 75, allora viene
// stampato: 11 37 51 75 20 45 69.

int main()
{
    int var = 2;
    char *inp[var];
    char buf[400]; // just needs to be long
    for (size_t k = 0; k < var; k++)
    {
        fgets(buf, 400, stdin);
        inp[k] = malloc(sizeof(char) * (strlen(buf) + 1));
        strcpy(inp[k], buf);
    }
}