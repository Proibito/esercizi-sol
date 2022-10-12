#include <stdio.h>

/* Codice che concatena le due stringhe v1 e v2 */
int main()
{
	//	char v1[10] = "Prima,";
	char v1[10] = {
			'P',
			'r',
			'i',
			'm',
			'a',
			',',
			0,
	};
	char v2[10] = " dopo";
	int len1, len2, i;

// https://stackoverflow.com/a/9219752/11642086 const i

	/* Lunghezza delle due stringhe */
	len1 = sizeof(v1);
	len2 = sizeof(v2);

	char v3[len1 + len2];
	/* Stampa delle due stringhe */
	printf("%s\n", v1);
	printf("%s\n", v2);
	/* Copia la seconda stringa alla fine della prima */

	int k = 0;
	i = 0;

	while (v1[i] != '\0')
	{
		v3[i] = v1[i];
		i++;
	}

	while (v2[k] != '\0')
	{
		v3[i] = v2[k];
		k++;
		i++;
	}
	v3[i] = 0;
	printf("%s\n", v3);
	printf("v2: %s\n", v2);
	printf("v1: %p\n", v1);
	printf("v2: %p\n", v2);

	/* Stampa la stringa concatenata */

	// int i = 0, j = 0;
	// printf("\nEnter First String:");
	// gets(v1);
	// printf("\nEnter Second String:");
	// gets(v2);
	// while (str1[i] != '\0')
	// 	i++;
	// while (str2[j] != '\0')
	// {
	// 	str1[i] = str2[j];
	// 	j++;
	// 	i++;
	// }
	// str1[i] = '\0';
}
