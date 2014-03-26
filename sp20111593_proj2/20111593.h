#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <ctype.h>

void StartSicsim();
char* ResetCommand(char *command);
int CheckingCommand(char *command);
void TokenizingCommand(char *command);
void PrintHelp();
int PrintDir();
void MakeHistory(char *command);
int PrintHistory();
int PrintDump();
void PrintChar(unsigned char c);
void SetMemoryAddress();
int FreeAllMemory();

typedef struct history{
	char *hcommand;
	struct history *hlink;
}history;

history *H_head = NULL, *H_tail;

bool sicsimpower = true;
char VMemory[65536][16];
int m = 0, n = 0;
