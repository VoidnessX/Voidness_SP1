#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

void StartSicsim();
char* ResetCommand(char *command);
void CheckingCommand(char *command);
void PrintHelp();
int PrintDir();
void MakeHistory(char *command);
int PrintHistory();
int FreeAllMemory();

typedef struct history{
	char *hcommand;
	struct history *hlink;
}history;

history *H_head = NULL, *H_tail;
bool sicsimpower = true;
