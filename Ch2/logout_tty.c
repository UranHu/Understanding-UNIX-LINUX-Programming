#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

#define UTSIZE sizeof(struct utmp)

int logout_tty(char *);
void utmp_open(char const *);

static int fd_utmp;

int main(int argc, char const *argv[]){
	utmp_open(argv[1]);
	logout_tty("tty2");
	return 0;
}

int logout_tty(char *line){
	struct utmp rec;
	while (read(fd_utmp, &rec, UTSIZE) == UTSIZE)
		if (strcmp(rec.ut_line, line) == 0){
			rec.ut_type = DEAD_PROCESS;
			if (time(&(rec.ut_time)) != -1)
				if (lseek(fd_utmp, -UTSIZE, SEEK_CUR) != -1)
					if (write(fd_utmp, &rec, UTSIZE) == UTSIZE){
						return 0;
					}
		}

	if (close(fd_utmp) == -1)
		return -1;
	return 0;
}


void utmp_open(char const *filename){
	if ((fd_utmp = open(filename, O_RDWR)) == -1){
		perror(filename);
		exit(1);
	}
}

