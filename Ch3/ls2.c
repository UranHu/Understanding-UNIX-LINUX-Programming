#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>


void do_ls(char const *);
void do_stat(char const*);
void show_file_info(char const *, struct stat *);
void mode_to_letter(int, char *);
char* uid_to_name(uid_t uid);
char* gid_to_group(gid_t gid);

int main(int argc, char const *argv[])
{
	if (argc == 1){
		do_ls(".");
	}
	else{
		while (--argc){
			printf("%s:\n", *(++argv));
			do_ls(*argv);
		}
	}
	return 0;
}

void do_ls(char const *dir_name){
	DIR *dir;
	struct dirent *dir_entry;
	if ((dir = opendir(dir_name)) == NULL){
		fprintf(stderr, "ls1: cannot open '%s':", dir_name);
		perror("");
		return;
	}
	while ((dir_entry = readdir(dir)) != NULL){
		do_stat(dir_entry->d_name);
	}
	closedir(dir);
}

void do_stat(char const *fname){
	struct stat info;
	if ((stat(fname, &info)) == -1){ //wentichuzaizheli 
		perror("");
		exit(1);
	}
	show_file_info(fname, &info);
}

void show_file_info(char const *fname, struct stat *buf){
	char mode[10];
	mode_to_letter(buf->st_mode, mode);
	printf("%s", mode);
	printf("%2d", buf->st_nlink);
	printf("%-10s", uid_to_name(buf->st_uid));
	printf("%-10s", gid_to_group(buf->st_gid));
	printf("%8ld", buf->st_size);
	printf("%12d ", buf->st_mtim);
	printf("%s\n", fname);
}

void mode_to_letter(int mode, char *str){
	strcpy(str, "----------");

	if (S_ISDIR(mode)) str[0] = 'd';
	if (S_ISCHR(mode)) str[0] = 'c';
	if (S_ISBLK(mode)) str[0] = 'b';

	if (mode & S_IRUSR) str[1] = 'r';
	if (mode & S_IWUSR) str[2] = 'w';
	if (mode & S_IXUSR) str[3] = 'x';	

	if (mode & S_IRGRP) str[4] = 'r';
	if (mode & S_IWGRP) str[5] = 'w';
	if (mode & S_IXGRP) str[6] = 'x';

	if (mode & S_IROTH) str[7] = 'r';
	if (mode & S_IWOTH) str[8] = 'w';
	if (mode & S_IXOTH) str[9] = 'x';
}

char* uid_to_name(uid_t uid){
	struct passwd *buf;
	if((buf = getpwuid(uid)) == NULL){
		perror("");
		exit(1);
	}
	return (buf->pw_name);

}

char* gid_to_group(gid_t gid){
	struct group *buf;
	if ((buf = getgrgid(gid)) == NULL){
		perror("");
		exit(1);
	} 
	return (buf->gr_name);
}