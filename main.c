#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>
#include <sys/sysinfo.h>

void get_screen_resolution(char *resolution, size_t size)
{
	FILE *pipe = popen("xrandr | grep '*' | awk '{print $1}'", "r");
	if (pipe)
	{
		fgets(resolution, size, pipe);
		resolution[strcspn(resolution, "\n")] = 0;
		pclose(pipe);
	}
	else
	{
		snprintf(resolution, size, "Uknown");
	}
}

void get_gpu_info(char *gpu, size_t size)
{
	FILE *pipe = popen("lspci | grep -i 'VGA' | cut -d':' -f3", "r");
	if (pipe)
	{
		fgets(gpu, size, pipe);
		gpu[strcspn(gpu, "\n")] = 0;
		pclose(pipe);
	}
	else
	{
		snprintf(gpu, size, "Unknown");
	}
}

void print_ascii_logo()
{
	printf("\033[1;36m");
	printf("      /\\_/\\  \n");
	printf("     ( o.o )  \n");
	printf("      > ^ <   Neofetch Clone\n");
	printf("\033[0m");
}

int main()
{
	struct utsname sysinfo;
	uname(&sysinfo);

	struct passwd *pw = getpwuid(getuid());
	struct sysinfo sys_info;

	char resolution[32];
	char gpu[128];

	get_screen_resolution(resolution, sizeof(resolution));
	get_gpu_info(gpu, sizeof(gpu));

	long total_RAM = sys_info.totalram / 1024 / 1024;
	long free_RAM = sys_info.freeram / 1024 / 1024;

	print_ascii_logo();

	printf("\033[1;32mUser:    \033[0m%s\n", pw->pw_name);
	printf("\033[1;32mOS:      \033[0m%s %s\n", sysinfo.sysname, sysinfo.release);
	printf("\033[1;32mKernel:  \033[0m%s\n", sysinfo.version);
	printf("\033[1;32mMachine: \033[0m%s\n", sysinfo.machine);
	printf("\033[1;32mUptime:  \033[0m%ld min\n", sys_info.uptime / 60);
	printf("\033[1;32mRAM:     \033[0m%ldMB / %ldMB\n", total_RAM - free_RAM, total_RAM);
	printf("\033[1;32mScreen:  \033[0m%s\n", resolution);
	printf("\033[1;32mGPU:     \033[0m%s\n", gpu);

	return 0;
}
