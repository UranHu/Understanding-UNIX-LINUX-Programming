/* cp03.c has -i opetion */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644
#define OPTION_I 1>>0

void oops(char *, char const *);
void plain_cp(int, int);

int main(int argc, char const *argv[])
{
	int in_fd, out_fd, n_chars;
	int flag;
	void *buf[BUFFERSIZE];
	flag &= 0x00000000;
	while ((opt = getopt(argc, argv, "i")) != -1){
		switch (opt){
			case 'i':
				flag |= OPTION_I;
				break;
			default:
				fprintf(stderr, "Usage: %s [-i] name\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	if (optind + 1 != argc) {
		fprintf( stderr, "usage: %s source destination\n", *argv[optind]);
		exit(1);
	}

	if ()
		opt_i()l

	return 0;
}

void oops(char *s1, char const *s2){
	fprintf(stderr, "Error: %s", s1);
	perror(s2);
	exit(1);
}

void plain_cp(int sr, int de){
	int in_fd, out_fd;
	if (strcmp(argv[sr], argv[de]) == 0){                                         
		fprintf(stderr, "'%s' and '%s' are the same file\n", argv[sr], argv[de]);
	}
	if ((in_fd = open(argv[sr], O_RDONLY)) == -1)
		oops("Cannot open ", argv[sr]);

	if ((out_fd = creat(argv[de], COPYMODE)) == -1)
		oops("Cannot creat ", argv[de]);

	while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
		if ((write(out_fd, buf, n_chars)) != n_chars)
			oops("write error to ", argv[de]);

	if (close(in_fd) == -1 || close(out_fd) == -1)
		oops("Error closing files", "");
}

void opt_i(int sr, int de){

	plain_cp(sr, de);
}