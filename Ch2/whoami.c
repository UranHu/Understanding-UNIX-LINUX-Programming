#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main(int argc, char const *argv[])
{
	uid_t uid;
	struct passwd *user;
	if (argc == 1){
		uid = geteuid();
		user = getpwuid(uid);
		printf("%s\n", user->pw_name);
	}
	return 0;
}