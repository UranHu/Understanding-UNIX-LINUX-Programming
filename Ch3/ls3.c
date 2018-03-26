#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <string.h>

#define MAXFNUM 128

void do_ls(char const *, char *l[]);
void sort_by_fname(char *f[], int, int);
int row_num(int, char *f[]);
int sum_max_len(int, char *f[]);

static int cur = 0;

int main(int argc, char const *argv[])
{
	int width;
	char *fname_list[MAXFNUM];
	char *s[] = {"china", "frech", "america", "british"};
	struct winsize wsize;
	if (argc == 1){
		do_ls(".", fname_list);
	}
	else{
		while (--argc){
			do_ls(argv[argc], fname_list);
		}
	}
	sort_by_fname(fname_list, 0, cur - 1);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &wsize);
	width = wsize.ws_col;
	int row = row_num(width, fname_list);
	for (int i = 0; i < row; ++i){
		for (int j = 0 ; j <= cur / row; ++j){
			if (row * j + i < cur)
				printf("%-ms ", fname_list[row * j + i]);
		}
	printf("\n");
	}
			
	return 0;
}

void do_ls(char const *dir_name, char *fname_list[]){
	DIR *dir;
	struct dirent *dir_entry;
	if ((dir = opendir(dir_name)) == NULL){
		fprintf(stderr, "ls1: cannot open '%s':", dir_name);
		perror("");
		return;
	}
	while ((dir_entry = readdir(dir)) != NULL){
		if (dir_entry->d_reclen != 16){
		fname_list[cur] = dir_entry->d_name;
		++cur;
	}
	}
}

void sort_by_fname(char *fname_list[], int left, int right){
	int i = left, j = right;
	char *key;
	char *temp;
	key = fname_list[j];
	if (i >= j)
		return;
	while (i < j){
		while (i < j && strcmp(fname_list[i], key) <= 0){
			++i;
		}
		while (i < j && strcmp(key, fname_list[j]) <= 0){
			--j;
		}
		temp = fname_list[i];
		fname_list[i] = fname_list[j];
		fname_list[j] = temp;
	}
	temp = fname_list[right];
	fname_list[right] = fname_list[j];
	fname_list[j] = temp;
	sort_by_fname(fname_list, left, j - 1);
	sort_by_fname(fname_list, j + 1, right);
}

int row_num(int width, char *fname_list[]){
	int row = 0, sml = 0, result;
	while (row < cur - 1){
		++row;
		sml = sum_max_len(row, fname_list);
		if (sml < width)
			return row;
	}
	return cur - 1;
}

int sum_max_len(int row, char *fname_list[]){
	int sum = 0;
	for (int i = 0; i <= cur / row; ++i)
	{
		int max = 0;
		for (int j = i * row; j < (i + 1) * row; ++j)
			if (j < cur && max < strlen(fname_list[j]))
				max = strlen(fname_list[j]);
		sum += max;
	}
	return sum + cur / row * 2;
}
