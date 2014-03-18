#include "20111593.h"

int main(int argc, char *argv[])
{
	char buffer[81];

	// Open testing file with fopen type 'r', and fopen output file with fopen type 'w'
	ifp = fopen(argv[1], "r");
	ofp = fopen("output.txt", "w");

	// Read one line from file while meet end of file
	while(fgets(buffer, 81, ifp) != NULL){
		// call tokenizing function
		tokenizing(buffer);
	};

	// file close
	fclose(ifp);
	fclose(ofp);

	return 0;
}

void tokenizing(char *buffer)
{
	int i, t=0, decimal_sum = 0;
	bool singlequoteflag = false, commentflag = false, hexaflag = false;
	char imsi_save_word = ' ', decimal[8];
	
	for(i=0 ; buffer[i] != '\0' ; i++){
		// if find '.', set commentflag == true, print '.' and don't print any words after '.' by using commentflag
		if(buffer[i] == '.' && commentflag == false && singlequoteflag == false){
			commentflag = true;
			printchar(buffer[i]);
		}
		// if find space or tab, then print newline. if commentflag == true, then don't execute
		// if C'Hello World' print Hello World one line need to change function by using singlequoteflag
		else if((buffer[i] == ' ' || buffer[i] == '\t' || buffer[i] == '\n') && commentflag == false){
			if(sepaflag == false && singlequoteflag == false){
				sepaflag = true;
				printline();
			}
			else if(singlequoteflag == true)
				printchar(buffer[i]);
		}
		// if find ',', then print newline
		else if(buffer[i] == ',')
			printline();
		// if find ''', then need to classification character or hexadecimal
		else if(buffer[i] == '\''){
			if(singlequoteflag == false){
				singlequoteflag = true;
				printline();
			}
			else
				singlequoteflag = false;
			// classification hexadecimal using imsi_save_word, if hexaflag == true, then print decimal_sum and set hexaflag = false.
			if(imsi_save_word == 'X' && hexaflag == false)
				hexaflag = true;
			else if(hexaflag == true){
				hexaflag = false;
				sscanf(decimal, "%x", &decimal_sum);
				printf("%d", decimal_sum);
				fprintf(ofp, "%d", decimal_sum);
			}
		}
		// if hexaflag == true, then need to convert hexadecimal to decimal
		else if(hexaflag == true && singlequoteflag == true){
			decimal[t] = buffer[i];
			t++;
		}
		else if(commentflag == false){
			sepaflag = false;
			printchar(buffer[i]);
		}
		// save buffer[i] into imsi_save_word for classification character or hexadecimal
		imsi_save_word = buffer[i];
	}

	nextline(commentflag, buffer[i]);
}

void printchar(char buffer)
{
	printf("%c", buffer);
	fprintf(ofp, "%c", buffer);
}

void printline()
{
	printf("\n");
	fprintf(ofp, "\n");
}

void nextline(bool commentflag, char buffer)
{
	// if commentflag == false, need to separate token and new line.
	if(commentflag == false && buffer == '\0')
		sepaflag = true;
	// if commentflag == true need to print newline when meet end of line(when commentflag == true, don't print buffer[i] == '\n')
	if(commentflag == true && buffer == '\0')
		printline();
}
