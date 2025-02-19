#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <pwd.h>

int main()
{
	struct utsname sysinfo;
	uname(&sysinfo);

	struct passwd *pw = getpwuid(getuid());

	printf("\033[1;32mCustomFetch\033[0m\n");
	printf("User: %s\n", pw->pw_name);
	printf("OS: %s %s \n", sysinfo.sysname, sysinfo.release);
	printf("Kernel: %s\n", sysinfo.version);
	printf("Machine: %s\n", sysinfo.machine);

	return 0;
}
