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
		//gets(command);
		fgets(command, sizeof(command), stdin);
		CheckingCommand(command);
		fflush(stdin);
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
int CheckingCommand(char *command)
{
	char *token_command1 = NULL, *token_command2 = NULL, *token_command3 = NULL, *token_command4 = NULL;
	char separator[] = " ,\t\n";
	
	token_command1 = strtok(command, separator);
	if(token_command1 != NULL)
		token_command2 = strtok(NULL, separator);
	if(token_command2 != NULL)
		token_command3 = strtok(NULL, separator);
	if(token_command3 != NULL)
		token_command4 = strtok(NULL, separator);

	if((strcmp(token_command1, "help") == 0 || strcmp(token_command1, "h") == 0) && (token_command2 == NULL)){
		PrintHelp();
		MakeHistory(token_command1);
	}
	else if((strcmp(token_command1, "dir") == 0 || strcmp(token_command1, "d") == 0) && (token_command2 == NULL)){
		PrintDir();
		MakeHistory(token_command1);
	}
	else if((strcmp(token_command1, "quit") == 0 || strcmp(token_command1, "q") == 0) && (token_command2 == NULL))
		sicsimpower = false;
	else if((strcmp(token_command1, "history") == 0 || strcmp(token_command1, "hi") == 0) && (token_command2 == NULL)){
		PrintHistory();
		MakeHistory(token_command1);
	}
	else if((strcmp(token_command1, "dump") == 0 || strcmp(token_command1, "du") == 0) && (strcmp(token_command2, "start"))){
		m = 0;
		n = 0;
		PrintDump();
		MakeHistory(command);
	}
	else
		printf("Wrong command\n");

	
	printf("%s\n", token_command1);
	printf("%s\n", token_command2);
	printf("%s\n\n\n", command);
	
	return 0;
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

//TODO - MAKE FUNCTION IN THIS AREA

/* Function name : PrintDump()
 *
 */
int PrintDump()
{
	int cnt = 0, firstn = n;

	for( ; ; m++){
		// print memory address
		printf("%05lx  ", &VMemory[m][0]-&VMemory[0][0]);

		// print data of memory
		for( ; ; n++){
			if(n == 15){
				printf("%02x ", VMemory[m][n]);
				n = 0;
				cnt++;
				break;
			}
			else{
				printf("%02x ", VMemory[m][n]);
				cnt++;
			}

			if(cnt == 160)
				break;
		}

		// print ASCII code
		printf("; ");
		for( ; ; firstn++){
			if(firstn == 15){
				PrintChar(VMemory[m][firstn]);
				printf("\n");
				firstn = 0;
				break;
			}
			else{
				PrintChar(VMemory[m][firstn]);
			}
		}

		if(cnt == 160)
			break;
	}

	SetMemoryAddress();

	return 0;
}

void PrintChar(unsigned char c)
{
	if(isprint(c))
		printf("%c", c);
	else
		printf(".");
}

void SetMemoryAddress()
{
	if(n == 15){
		n = 0;
		m = m+1;
	}
	else
		n = n+1;
}







// END OF PROGRAM
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
