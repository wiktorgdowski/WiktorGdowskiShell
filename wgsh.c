/* Name: Wiktor Gdowski
   Student Number: c13502327
   Module: Systems Integration
   Assignment: Networking Shell
   Due: Monday 24th October 2016
   GitHub: https://github.com/wiktorgdowski/WiktorGdowskiShell
   */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>
#include <limits.h>
#include <grp.h>

/* Data Structure */
#define TRUE 1
#define STDIN 1
#define BUFFER_MAX_LENGTH 50

/// ==================================================================================================================================

static char buffer[BUFFER_MAX_LENGTH]; // user input buffer
static int bufferChars = 0;
static char userInput = '\0';
static char *commandArgv[5]; // array of strings for given command
static int cmdArgCount = 0; // command word count

/// ==================================================================================================================================

/* 1. Declare Welcome Functions */
void welcomeScreen(); // welcome screen
void shellPrompt(); // display

/* 2. Declare User Input Functions */
void getTextLine(); // get line from user
void populateCommand(); // populate into commandArgv
void destroyCommand(); // clears buffer and commandArgv

/* 3. Declare Shell Functions */
void handleUserCommand(); // handle command
int checkBuiltInCommands(); // check if command is built in

/* 4. Declare External Commands Functions */
void pwd(); // pwd command
void ifconfig(); // ifconfig command

/* 5. Declare Internal Commands Functions */
void internalDate(); // gets date
void userDetails(); // gets user details
void help(); // help command

/// ==================================================================================================================================

 /* 1. Welcome Functions */
void welcomeScreen() // welcome screen
{
	printf("\n");
	printf("\t*** Welcome to my custom Shell %s", getenv("LOGNAME"));
	printf("! ***\n\n");
}

void shellPrompt() // display
{
    printf("wgsh_%s | ", getenv("LOGNAME"));
}

/// ==================================================================================================================================

 /* 2. User Input Functions */
void getTextLine() // get line from user
{
	destroyCommand();
	while ((userInput != '\n') && (bufferChars < BUFFER_MAX_LENGTH))
	{
		buffer[bufferChars++] = userInput;
		userInput = getchar();
	}
	buffer[bufferChars] = 0x00;
	populateCommand();
}

void populateCommand() // populate into commandArgv
{
	char* bufferPointer;
	bufferPointer = strtok(buffer, " ");
	while (bufferPointer != NULL)
	{
		commandArgv[cmdArgCount] = bufferPointer;
		bufferPointer = strtok(NULL, " ");
		cmdArgCount++;
	}
}

void destroyCommand() // clears buffer and commandArgv
{
	while (cmdArgCount != 0) {
		commandArgv[cmdArgCount] = NULL;
		cmdArgCount--;
	}
	bufferChars = 0; // clear buffer
}

/// ==================================================================================================================================

/* 3. Shell Functions */
void handleUserCommand() // handle command
{
	if ((checkBuiltInCommands(commandArgv[0])) == 0)
	{
		printf("\nThis command does not exist. Type in help to view available commands\n\n");
	}
}

int checkBuiltInCommands() // check if command is built in
{
	if (strcmp("pw", commandArgv[0]) == 0)
	{
		pwd();
		return 1;
	}
	if (strcmp("ifc", commandArgv[0]) == 0)
	{
		ifconfig();
		return 1;
	}
	if (strcmp("dt", commandArgv[0]) == 0)
	{
		 internalDate();
		 return 1;
	}
	if (strcmp("ud", commandArgv[0]) == 0)
	{
		userDetails();
		return 1;
	}
	if (strcmp("help", commandArgv[0]) == 0)
	{
		help();
		return 1;
	}
	if (strcmp("exit", commandArgv[0]) == 0)
	{
		printf("\n\t *** You are now logged out! ***\n\n");
		exit(EXIT_SUCCESS);
	}
	return 0;
}

/// ==================================================================================================================================

/* 4. External Commands Functions */
void pwd() // pwd command
{
	printf("\n");
	system("pwd");
	printf("\n");
}

void ifconfig() // ifconfig command
{
	char command[100];
	if (commandArgv[1] == NULL)
	{
		printf("\n");
		system("ifconfig eth0");
		printf("\n");
	}
	else
	{
	    if (commandArgv[1] != NULL)
		{
	       	printf("\n");
			sprintf(command, "ifconfig %s", commandArgv[1]);
			system(command);
			printf("\n");
	    }
	}
}

/// ==================================================================================================================================

/* 5. Internal Commands Functions */
void internalDate() // gets date
{
	printf("\n");
	time_t t;
	struct tm *tmp;
	char buf[64];
	time(&t);
	tmp = localtime(&t);
	strftime(buf, 64, "Time and Date:  %Y%m%d%H%M%S", tmp);
	printf("%s\n", buf);
	printf("\n");
}

void userDetails() // gets user details
{
	printf("\n");
	struct group *gr;
	int ngroups, i;
	gid_t groups[NGROUPS_MAX];
	ngroups = NGROUPS_MAX;
	if ( getgrouplist( getlogin(), getegid(), groups, &ngroups) == -1)
	{
		printf ("Array too small: %d\n", ngroups);
	}
	printf("%d, %s," , geteuid(), getenv("LOGNAME"));
	for (i=0; i < ngroups; i++)
	{
		 gr = getgrgid(groups[i]);
		printf(" %s," ,  gr->gr_name);
	}
	printf(" %s", getcwd(getenv("HOME"), 1024));
	printf("\n");
	printf("\n");
}

void help() // help command
{
	printf("\n");
	printf("pw   - shows the current working directory \n");
	printf("ifc  - show the setting for the first interface \n");
	printf("dt   - show today's date and time \n");
	printf("ud   - show userid, groupid, username and groupname \n");
	printf("exit - exit Shell \n");
	printf("\n");
}

/// ==================================================================================================================================

int main()
{
	welcomeScreen();
	shellPrompt();
	while (TRUE)
	{
		userInput = getchar();
		switch (userInput)
		{
			case '\n':
				shellPrompt();
				break;
			default:
				getTextLine();
				handleUserCommand();
				shellPrompt();
				break;
		}
	}
	printf("\n");
	return 0;
}