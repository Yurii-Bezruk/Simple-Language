#include "commands.h"

void import(char** words){
	strcpy(words[0], "#include"); 
	char* lib = (char*) malloc(sizeof(char)*(strlen(words[1]) + 4));
	strcpy(lib, "<");
	strcat(lib, words[1]);
	lib[strlen(lib) - 1] = '\0';
	strcat(lib, ".h>\n");
	strcpy(words[1], lib);
	free(lib);
}