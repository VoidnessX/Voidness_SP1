#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void tokenizing(char *s);
void nextline(bool flag, char s);
void printchar(char s);
void printline();

FILE *ifp, *ofp;
bool sepaflag = false;
