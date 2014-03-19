#include "20111593.h"

int main()
{
	StartSicsim();
	FreeAllMemory();

	return 0;
}

/* Function name : StartSicsim()
 * Start SIC Machine. when sicsimpower = true, machine listening user's command.
 * using ResetCommand() function, clear the char array which is used to store command.
 * when command input, using CheckingCommand() function to classificate the command.
 */
void StartSicsim()
{
	char *command;

	while(sicsimpower){
		command = ResetCommand(command);
		printf("sicsim> ");
		scanf("%s", command);
		CheckingCommand(command);
	}
}

/* Function name : ResetCommand(char *command)
 * if command is NULL, then dynamic allocation using calloc for command.
 * if command isn't NULL, then free command and calloc command again.
 */
char* ResetCommand(char *command)
{
	if(command == NULL)
		command = (char*)calloc(50, sizeof(char));
	else{
		free(command);
		command = (char*)calloc(50, sizeof(char));
	}

	return command;
}

//TODO - Need to comment
void CheckingCommand(char *command)
{
	if(strcmp(command, "help") == 0 || strcmp(command, "h") == 0){
		PrintHelp();
		MakeHistory(command);
	}
	else if(strcmp(command, "dir") == 0 || strcmp(command, "d") == 0){
		PrintDir();
		MakeHistory(command);
	}
	else if(strcmp(command, "quit") == 0 || strcmp(command, "q") == 0)
		sicsimpower = false;
	else if(strcmp(command, "history") == 0 || strcmp(command, "hi") == 0){
		PrintHistory();
		MakeHistory(command);
	}

	else
		printf("Wrong command\n");
}

/* Function name : PrintHelp()
 * Print command list
 */
void PrintHelp()
{
	printf("---------- Command List ----------\n");
	printf(" h[elp]\n");
	printf(" d[ir]\n");
	printf(" q[uit]\n");
	printf(" hi[story]\n");
	printf(" du[mp] [start, end]\n");
	printf(" e[dit] address, value\n");
	printf(" f[ill] start, end, value\n");
	printf(" reset\n");
	printf(" opcode mnemonic\n");
	printf(" mnemonic opcode\n");
	printf(" opcode list\n");
	printf(" mnemonic list\n");
}


/* Function name : PrintDir()
 * Print file list where the program execute.
 * if file type is directory, print like 'dir1/'
 * if file is runnable, print like '*.out*'
 */
int PrintDir()
{
	DIR *dp;
	struct dirent *ep;
	struct stat statbuf;
	
	dp = opendir("./");
	if(dp != NULL){
		while((ep = readdir(dp)) != NULL){
			stat(ep->d_name, &statbuf);
			if(S_ISDIR(statbuf.st_mode))
				printf("%s/\n", ep->d_name);
			else if(statbuf.st_mode == 33261)
				printf("%s*\n", ep->d_name);
			else
				printf("%s\n", ep->d_name);
		}
		closedir(dp);
	}
	else{
		perror("Couldn't open directory\n");
		return EXIT_FAILURE;
	}

	return 0;
}

/* Function name : MakeHistory()
 * when call MakeHistory() with command, save the command by using single linked list.
 */
void MakeHistory(char *command)
{
	if(H_head == NULL){
		H_head = (history*)malloc(sizeof(history));
		H_head->hlink = NULL;
		H_head->hcommand = (char*)calloc(50, sizeof(char));
		strcpy(H_head->hcommand, command);
		H_tail = H_head;
	}
	else{
		H_tail->hlink = (history*)malloc(sizeof(history));
		H_tail = H_tail->hlink;
		H_tail->hcommand = (char*)calloc(50, sizeof(char));
		strcpy(H_tail->hcommand, command);
		H_tail->hlink = NULL;
	}
}

/* Function name : PrintHistory()
 * print the user's command starting first command to last command(printing commands are valid command) by using history linked list.
 */
int PrintHistory()
{
	int i = 1;
	history *tmp = H_head;

	while(tmp){
		printf("%d	%s\n", i, tmp->hcommand);
		tmp = tmp->hlink;
		i++;
	}

	return 0;
}

//TODO - Maybe need more free function
int FreeAllMemory()
{
	history *tmp, *cur = H_head;

	while(cur){
		tmp = cur->hlink;
		free(cur->hcommand);
		free(cur);
		cur = tmp;
	}

	return 0;
}
