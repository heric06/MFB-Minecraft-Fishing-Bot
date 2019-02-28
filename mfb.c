#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define TOOL	"xdotool"
#define PROGRAM	"Minecraft Fishing Bot - MFB"
#define VERSION "1.04"
#define DROP_HH	235

#define CLICK_L	1
#define CLICK_C	2
#define CLICK_R	3

unsigned int fish();
void help_msg(char* __exe);

int main(int argc, char** argv)
{
	unsigned int i, j = 0;
	unsigned int countdown = 5;
	unsigned int expired = 0;
	unsigned int time = 0;
	
	int opt;
	bool nolim = false;
	bool active = false;
	
	static struct option long_options[] = 
	{
		{"sec",		required_argument,	NULL, 's'},
		{"min",		required_argument, 	NULL, 'm'},
		{"hour",	required_argument,	NULL, 'h'},
		{"nolim",	no_argument,		NULL, 'i'},
		{"help", 	no_argument, 		NULL,  0 },
		{"version", 	no_argument,		NULL, 'v'},
		{NULL, 0, NULL, 0}
	};

	while((opt = getopt_long(argc, argv, "s:m:h:iv", long_options, NULL)) != -1)
	{
		j++;
		switch(opt)
		{
			case 's':
				time += atoi(argv[++j]);
				active = true;
				break;
				
			case 'm':
				time += 60*atoi(argv[++j]);
				active = true;
				break;
				
			case 'h':
				time += 3600*atoi(argv[++j]);
				active = true;
				break;
				
			case 'i':
				nolim = true;
				active = true;
				break;
				
			case 0:
				help_msg(argv[0]);
				break;
				
			case 'v':
				printf("%s %s\n~%d drops/h with maxed out gear\n", PROGRAM, VERSION, DROP_HH);
				break;
				
			default:
				printf("Try \"%s --help\" for more informations.\n", argv[0]);
				return 1;
		}
	}
	
	
	if(active)
	{
		if(!nolim)
			printf("Bot scheduled for %.2d:%.2d:%.2d\n", time/3600, (time/60)%60, time%60);
		
		for(i=countdown; i>0; i--){
			printf("\rStarting bot in %d s ", i);
			fflush(stdout);
			sleep(1);
		}
		printf("\n[fishing]\n");
	
		if(nolim){
			while(true){
				printf("\rActivity: %.2d:%.2d:%.2d", expired/3600, (expired/60)%60, expired%60);
				fflush(stdout);
				expired += fish();
			}
		}
		else
		{
			do{
				printf("\rRemaining: %.2d:%.2d:%.2d", (time-expired)/3600, ((time-expired)/60)%60, (time-expired)%60);
				fflush(stdout);
				expired += fish();
			}
			while(expired < time);
			printf("\n");
		}
	}
	
	return 0;
}

void help_msg(char* __exe)
{
printf("\
Usage: %s [OPTION] [TIME]\n\n\
Options:\n\
 -s <time>\t--sec  <time>\tAdds time seconds\n\
 -m <time>\t--min  <time>\tAdds time minutes\n\
 -h <time>\t--hour <time>\tAdds time hours\n\
 -i\t\t--nolim\t\tNo limit fishing\n\
 -v\t\t--version\tDisplays version\n\
", __exe);
}

unsigned int fish()
{
	char* cmd = malloc(30U*sizeof(char));
	unsigned int expired = 0;
	
	sprintf(cmd, "%s click %d", TOOL, CLICK_R);
	system(cmd);
	expired += 1;
	sleep(1);
	
	sprintf(cmd, "%s mousedown %d", TOOL, CLICK_R);
	system(cmd);
	expired += 1;
	sleep(1);
	
	sprintf(cmd, "%s mouseup %d", TOOL, CLICK_R);
	system(cmd);
	expired += 1;
	sleep(1);
	
	free(cmd);
	return expired;
}
 
