#include <unistd.h>
#include <getopt.h>
#include "parse.h"
#include "commands.h"

char* line;						//Contains line of Simple-code
char** words;					//Contains command words, on which line are splitted
char* input_file_name;			
char* output_file_name;
FILE* input;					//Translating Simple-file
FILE* output;					//C-file into which translating is making

void help();
void options(int argc, char** argv);


int main(int argc, char** argv){	
	if(argc == 1){
		file_name_init(&input_file_name, DEFAULT_INPUT_FILE_NAME);
		file_name_init(&output_file_name, DEFAULT_OUTPUT_FILE_NAME);
	}
	else
		options(argc, argv);
	file_channel_init(&input, &output, &input_file_name, &output_file_name);
	file_name_close(&input_file_name);
	file_name_close(&output_file_name);
	buffer_init(&words, &line);
	while(1){
		if(feof(input))		//while not end of file
			break;
		file_channel_get(&input, &line);		
		split(&line, &words);
		if(strcmp(words[0], "import") == 0)
			import(words);
		
		file_channel_put(&output, &words);
		buffer_clear(&words, &line);
	}
	file_channel_close(&input, &output);
	buffer_close(&words, &line);

	system("gcc test.c; ./a.out");	
	return 0;
}



void options(int argc, char** argv){
	bool input_flag = FALSE;
	bool output_flag = FALSE;
	const struct option long_opt[] = {
		{"help", 0, 0, 'h'},
		{"input", 1, 0, 'i'},
		{"output", 1, 0, 'o'},
		{NULL, 0, NULL, 0}
	};
	int opt;
	while((opt = getopt_long(argc, argv, "hi:o:", long_opt, NULL)) != -1){
		switch(opt){
			case 'h': 
				help();
				exit(0);
			case 'i':
				file_name_init(&input_file_name, optarg);
				input_flag = TRUE;
				break;
			case 'o':
				file_name_init(&output_file_name, optarg);
				output_flag = TRUE;
				break;
			case '?':
				exit(-1);
		}
	}
	if(!input_flag)
		file_name_init(&input_file_name, DEFAULT_INPUT_FILE_NAME);
	if(!output_flag)
		file_name_init(&input_file_name, DEFAULT_OUTPUT_FILE_NAME);
}

void help(){
	printf("\nSimple-C Translator 0.0.1 powered by striker2.0\n\n");
	printf("Usage: ./translate [-h] | [[-i] <file> [-o] <file>] Translate given .simple file to .c file\n\n");
	printf("Arguments:\n");
	printf("-h         --help           Show help (this massage) and exit\n");
	printf("-i <file>  --input <file>   Establish input .simple file\n");
	printf("-o <file>  --output <file>  Establish output .c file\n");
	printf("\nEnjoy using!:)\n");
}