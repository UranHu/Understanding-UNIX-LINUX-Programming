#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <cstdlib>
#include <time.h>

#define SHOWHOST

using namespace std;
void show_info(struct utmp *);
void show_time(time_t);


int main(int argc, char const *argv[])
{
	int fd;
	struct  utmp current_record;
	size_t reclen = sizeof(current_record);
	if ((fd = open(UTMP_FILE, O_RDONLY)) == -1){
		perror(UTMP_FILE);
		exit(1);
	}

	while (read(fd, &current_record, reclen) == reclen){
		show_info(&current_record);
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