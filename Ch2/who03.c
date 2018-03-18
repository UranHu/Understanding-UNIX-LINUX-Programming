#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <stdlib.h>
#include <time.h>

#define SHOWHOST
#define NRECS 16
#define UTSIZE sizeof(struct utmp)

void show_info(struct utmp *);
void show_time(time_t);
int next_utmp(int);
int load_utmp(int);

static struct utmp buf[NRECS];
static int cur_num;
static int nur_utmp;

int main(int argc, char const *argv[])
{
	int fd;
	if ((fd = open(UTMP_FILE, O_RDONLY)) == -1){
		perror(UTMP_FILE);
		exit(1);
	}
	cur_num = nur_utmp = 0;
	while (next_utmp(fd)){
		show_info(&buf[cur_num - 1]);
	}
	close(fd);

	return 0;
}

void show_info(struct utmp *utbufp){
	if (utbufp->ut_type != USER_PROCESS)
		return;
	printf("%-8.8s ", utbufp->ut_user);
	printf("%-8.8s ", utbufp->ut_line);
	show_time(utbufp->ut_time);
	#ifdef SHOWHOST
		printf("(%s)\n", utbufp->ut_host);
	#endif
}

void show_time(time_t timeval){
	struct tm *lt  = gmtime(&timeval);
	char* cp = ctime(&timeval);
	printf("%8d-%.2d-%d %.2d:%d ", lt->tm_year + 1900, lt->tm_mon + 1, lt->tm_mday, lt->tm_hour, lt->tm_min );
}

int next_utmp(int fd){
	if (cur_num == nur_utmp)
		if (load_utmp(fd) == -1)
			return 0;
	++cur_num;
	return 1;

}

int load_utmp(int fd){
	int assize;
	cur_num = 0;
	if (assize = read(fd, &buf, UTSIZE * NRECS)){
		nur_utmp = assize / UTSIZE;
		return nur_utmp;
	} 
	return -1;
}