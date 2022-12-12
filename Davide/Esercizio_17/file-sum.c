#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#define MAX_BYTES_SUMMED_EACH_CYCLE 4096


int main(int args, char *argv[])
{
	int fd_1, fd_2, save_errno, sum, read_char, i;
	char string[] = "Ciao a tutti";
	unsigned char byte_read[MAX_BYTES_SUMMED_EACH_CYCLE];

    printf("Inizio programma\n");

	if(args<2)
	{
		dprintf(2, "Not enought arguments\nClosing program");
		return -1;
	}

	fd_1 = open(argv[1], O_RDONLY);
	/*save_errno = errno;
	printf("\n%d\n", errno);*/
	if(errno == ENOENT)
	{
		printf("Il file indicato non esiste. Verra' creato con contenuto \"%s\".\n", string);
		printf("\n-------------------------------\nDETTAGLI:\n%s\n------------------------------\n", strerror(errno));
		fd_2 = open(argv[1], O_WRONLY|O_CREAT, S_IRWXU);
		dprintf(fd_2, "Ciao a tutti");
		close(fd_2);
	}
	else
	{
		printf("File individuato\n");
		close(fd_1);
	}
	

	errno = 0;		/* Reset errno per sapere se con la prossima open ci saranno problemi  */
	/*	LETTURA FILE  E LETTURA VALORI   */
	fd_1 = open(argv[1], O_RDONLY);

	if(errno == ENOENT)		/*Check apertura file nuovo tramite fd_1*/
	{
		dprintf(2, "\n\tAPERTURA FILE NON RIUSCITA\n\tAmico non hai creato il file nel modo giusto.\n");
		return -2;
	}

	sum=0;
	do
	{
		read_char = read(fd_1, byte_read, sizeof(MAX_BYTES_SUMMED_EACH_CYCLE));
		for(i=0;i<read_char;i++)
		{
			sum = sum + (byte_read[i]%256);
		}
	} while(read_char!=0&&read_char!=-1);
	/* 0 per il caso in cui siamo esattamente al fondo del file
	   1 per il caso in cui c'è stato un errore durante la lettura dei byte*/

	printf("La somma dei byte del file e' %d\n", sum);	

	close(fd_1);
	return 0;
}