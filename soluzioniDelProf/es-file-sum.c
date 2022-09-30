#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define BUF_LEN 1024
#define PRINT_ERROR fprintf(stderr,				\
			    "%s:%d: Errore #%3d \"%s\"\n",	\
			    __FILE__, __LINE__, errno, strerror(errno));

int main(int argc, char * argv[]) {
	int fd;
	char buf[BUF_LEN] = "Ciao a tutti";
	ssize_t num_bytes, i;
	char c = 0;
	
	/* Prova ad aprire il lettura il file argv[1] */
	if ((fd = open(argv[1], O_RDONLY)) == -1) {
		switch (errno) {
		case 0:
			/* Andata a buon fine: niente da fare */
			break;
		case ENOENT:
			printf("Il file %s non esiste. Verra` creato\n",
			       argv[1]);
			if ((fd = open(argv[1],
				       O_WRONLY | O_CREAT | O_TRUNC,
				       S_IRUSR | S_IWUSR)) == -1) {
				PRINT_ERROR;
			}
			/* Ci scrivo il contenuto di default */
			write(fd, buf, strlen(buf));
			close(fd);
			if ((fd = open(argv[1], O_RDONLY)) == -1) {
				/* Lo abbiamo appena creato. Sarebbe
				 * strano che ci fosse errore */
				PRINT_ERROR;
			}
			break;
		default:
			PRINT_ERROR;
			exit(-1);
		}
	}

	/* 
	 * Prova a leggere fino a BUF_LEN bytes. Se ce ne sono meno,
	 * il numero di byte effettivamente letto e` ritornato dalla
	 * read (e quindi assignato a num_bytes). read(...) ritorna
	 * zero quando siamo a end-of-file (EOF)
	 */
	while (num_bytes = read(fd, buf, BUF_LEN)) {
		/* Scorri il buffer e fai la somma */
		for (i=0; i<num_bytes; i++) {
			c += buf[i];
		}
	}

	/* Chiudi il file descriptor */
	close(fd);
	
	printf("La somma di tutti i byte del file \"%s\" e`\n%d\n",
	       argv[1], c);
}
