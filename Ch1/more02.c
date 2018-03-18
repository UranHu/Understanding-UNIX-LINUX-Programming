#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512

int see_more(FILE *);
void do_more(FILE *);

int main(int argc, char const *argv[])
{
	FILE *fp;
	if (argc == 1)
		do_more(stdin);   
	else
		while (--argc)
			if ((fp = fopen(*++argv, "r")) != NULL) {
				do_more(fp);
				fclose(fp);
			}
			else
				exit(1);
	return 0;
}

int see_more(FILE *cmd) {
	int c;
	printf("\033[7m more? \033[m");
	while ((c = getc(cmd)) != EOF){
		switch (c){
			case 'q':
				return 0;
				break;
			case ' ':
				return PAGELEN;
				break;
			case '\n':
				return 1;
				break;
			default:
				;
		}
	}
	return 0;
}

void do_more(FILE *fp){
	char line[LINELEN];
	int num_of_lines = 0;
	int reply;
	FILE *fp_tty;
	if ((fp_tty = fopen("/dev/tty", "r")) == NULL)
		exit(1);
	while (fgets(line, LINELEN, fp)){
		if (num_of_lines == PAGELEN){
			reply = see_more(fp_tty);
			if (reply == 0)
				break;
			num_of_lines -= reply;
		}
		if (fputs(line, stdout) == EOF)
			exit(1);
		++num_of_lines;
	}
}