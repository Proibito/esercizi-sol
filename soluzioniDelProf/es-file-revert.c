#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


/*
 * Per  permettere la  gestione dei  file attraverso  file descriptors
 * oppure  attraverso  stream  (a  seconda che  la  macro  USE_FD  sia
 * definita o meno),  si sceglie di definire un certo  numero di macro
 * che permettano  di fare le  operazioni sui file. La  definizione di
 * tali  macro cambiera`  a seconda  della definizione  di USE_FD.  Il
 * codice  del  programma, infine,  provvedera`  ad  accedere ai  file
 * esclusivamente attraverso tali macro.
 *
 * Le macro definite sono le seguenti:
 * 
 * FILE_OPEN_READ_SUCCESS(name)  apre  il  file "name"  in  lettura  e
 * ritorna non-zero in caso di successo
 *
 * FILE_OPEN_WRITE_SUCCESS(name) apre  il file  "name" in  scrittura e
 * ritorna non-zero in caso di successo
 *
 * FILE_INPUT_SEEK_END  posiziona il  "file poisition  indicator" alla
 * fine del file di input
 *
 * FILE_INPUT_ONE_CHAR_BACK arretra  di uno  la posizione del  file di
 * input e  ritorna -1 se  questo non  e` possibile (perche'  siamo ad
 * inizio file)
 *
 * FILE_READ_ONE_CHAR(c) legge un  byte dal file di input  e lo scrive
 * sulla variabile c che e` di tipo char
 *
 * FILE_WRITE_ONE_CHAR(c) scrive il byte nella variabile c sul file di
 * output
 *
 * FILE_CLOSE chiude tutti i file
 */
#ifdef USE_FD

int in_fd, out_fd; /* Variabili globali per comodita` */
#define FILE_OPEN_READ_SUCCESS(name)		\
	((in_fd = open(name, O_RDONLY)) != -1)
#define FILE_OPEN_WRITE_SUCCESS(name)			\
	((out_fd = open(name,				\
			O_WRONLY | O_CREAT | O_TRUNC,	\
			S_IRUSR | S_IWUSR)) != -1)
#define FILE_INPUT_SEEK_END lseek(in_fd, 0, SEEK_END);
#define FILE_INPUT_ONE_CHAR_BACK		\
	lseek(in_fd, -1, SEEK_CUR)
#define FILE_READ_ONE_CHAR(c)			\
	read(in_fd, &(c), 1);
#define FILE_WRITE_ONE_CHAR(c)			\
	write(out_fd, &(c), 1);
#define FILE_CLOSE				\
	close(in_fd);				\
	close(out_fd);
	
#else  /* USE_FD non e` definita*/

FILE * in, * out; /* Variabili globali per comodita` */
#define FILE_OPEN_READ_SUCCESS(name)		\
	((in = fopen(name, "r")) != NULL)
#define FILE_OPEN_WRITE_SUCCESS(name)		\
	((out = fopen(name, "w")) != NULL)
#define FILE_INPUT_SEEK_END fseek(in, 0, SEEK_END);
#define FILE_INPUT_ONE_CHAR_BACK		\
	fseek(in, -1, SEEK_CUR)
#define FILE_READ_ONE_CHAR(c)			\
	c = fgetc(in);
#define FILE_WRITE_ONE_CHAR(c)			\
	fputc(c, out);
#define FILE_CLOSE				\
	fclose(in);				\
	fclose(out);

#endif /* USE_FD */


int main(int argc, char * argv[]) {
	char c;
	ssize_t num_bytes;
	
	/* 
	 * Il primo  argomento letto a  riga di comando argv[1]  e` il
	 * nome del file da cui leggere
	 */
	if (!FILE_OPEN_READ_SUCCESS(argv[1])) {
		fprintf(stderr, "Error %d (%s) when opening file \"%s\"\n",
			errno,
			strerror(errno),
			argv[1]);
		exit(EXIT_FAILURE);
	}

	/* 
	 * Il secondo argomento letto a  riga di comando argv[2] e` il
	 * nome del file su cui scrivere
	 */
	if (!FILE_OPEN_WRITE_SUCCESS(argv[2])) {
		fprintf(stderr, "Error %d (%s) when opening file \"%s\"\n",
			errno,
			strerror(errno),
			argv[2]);
		exit(EXIT_FAILURE);
	}

	/* 
	 * Si posiziona il  file position indicator del  file di input
	 * alla fine
	 */
	FILE_INPUT_SEEK_END;
	while (FILE_INPUT_ONE_CHAR_BACK != -1) {
		FILE_READ_ONE_CHAR(c);
		/* Sposta indietro di una posizione dopo la lettura */
		FILE_INPUT_ONE_CHAR_BACK;
		FILE_WRITE_ONE_CHAR(c);
	}
	FILE_CLOSE;
}
