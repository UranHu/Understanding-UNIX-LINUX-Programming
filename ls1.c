#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void do_ls(char const *);

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
		printf("%s\n", dir_entry->d_name);
	}
}