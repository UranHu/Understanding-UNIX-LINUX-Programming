#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 512
#define LINE 10
void readline(int, char *);
void reverse(char *, char *);
int main(int argc, char const *argv[])
{
	int fd;
	int nur_line = 0;
	char buf[LINE][MAXLINE];
	if ((fd = open(argv[1], O_RDONLY)) == -1){
		perror(argv[1]);
		exit(1);
	}
	if ((lseek(fd, 0 ,SEEK_END)) == -1){
		perror(argv[1]);
		exit(1);
	}
	while (nur_line < LINE){
		readline(fd, buf[nur_line]);
		++nur_line;
	}
	for (int i = nur_line; i >= 0 ; --i)
	{
		fprintf(stdout, "%s", buf[i]);
	}


}

void readline(int fd, char *buf_line){
	int pos = 0;
	char temp[MAXLINE];
	while (lseek(fd, -1, SEEK_CUR)){
		if (read(fd, temp + pos, 1) == -1){
			perror("");
			exit(1);
		}
		if (*(temp + pos) == '\n'){
			lseek(fd, -1, SEEK_CUR);
			reverse(temp, buf_line);
			return;
		}
		++pos;
		lseek(fd, -1, SEEK_CUR);
	}
}

void reverse(char *str1, char *str2){
	int str1_len;
	int i = 0;
	while (*(str1 + i) != '\n'){
		++i;
	}
	for (int j = 0; j < i; ++j)
	{
		*(str2 + j) = *(str1 + i - 1 - j);
	}
	*(str2 + i) = '\n';
	*(str2 + i + 1) = '\0';
}