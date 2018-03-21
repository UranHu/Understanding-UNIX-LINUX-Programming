/* cp03.c has -i option */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644
#define OPTION_I 1>>0

void oops(char *, char const *);
void plain_cp(char const *, char const *);
void opt_i(char const *, char const *);
int overwrite_ans(char *);
int is_same_file(char const *, char const *);

int main(int argc, char const **argv)
{
	int in_fd, out_fd, n_chars;
	int flag;
	char opt;
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

	if (optind + 2 != argc) {
		fprintf( stderr, "usage: %s source destination\n", *(argv + optind));
		exit(1);
	}

	if (flag == 0x00000001)
		opt_i(*(argv + optind), *(argv + optind + 1));
	else 
		plain_cp(*(argv + optind), *(argv + optind + 1));
	return 0;
}

void oops(char *s1, char const *s2){
	fprintf(stderr, "Error: %s", s1);
	perror(s2);
	exit(1);
}

void plain_cp(char const *sr, char const *de){
	int in_fd, out_fd;
	void *buf[BUFFERSIZE];
	int n_chars;
	if (is_same_file(sr, de)){                                         
		fprintf(stderr, "'%s' and '%s' are the same file\n", sr, de);
		exit(1);
	}
	if ((in_fd = open(sr, O_RDONLY)) == -1)
		oops("Cannot open ", sr);

	if ((out_fd = creat(de, COPYMODE)) == -1)
		oops("Cannot creat ", de);

	while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
		if ((write(out_fd, buf, n_chars)) != n_chars)
			oops("write error to ", de);

	if (close(in_fd) == -1 || close(out_fd) == -1)
		oops("Error closing files", "");
}

void opt_i(char const *sr_name, char const *de_name){
	if (access(de_name, F_OK) != 0){
		plain_cp(sr_name, de_name);
	}
	else{
		char ans[3];
		printf("overwrite '%s'?", de_name);
		scanf("%s", ans);
		if (overwrite_ans(ans))
			plain_cp(sr_name, de_name);
		else 
			return;
	}
}

int overwrite_ans(char *ans){
	int p = 0;
	while (ans[p++] != '\0')
		*(ans + p - 1) = toupper(*(ans + p - 1));

	if (!strcmp("YES", ans) || !strcmp("Y", ans))
		return 1;
	return 0;
}

int is_same_file(char const *sr_name, char const *de_name){
	struct stat sr_statbuf, de_statbuf;
	if (stat(sr_name, &sr_statbuf) == -1){
		perror(sr_name);
		exit(1);
	}
	if (stat(de_name, &de_statbuf) == -1){
		perror(de_name);
		exit(1);
	}
	if ((sr_statbuf.st_ino == de_statbuf.st_ino) && (sr_statbuf.st_rdev == de_statbuf.st_rdev)) 
		return 1;
	return 0;
}