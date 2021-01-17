#include "parse.h"

int wordcount = 0;			//Contains count of words, in which line are separated


void file_name_init(char** file_name_address, char* filename){
	*file_name_address = (char*) malloc(sizeof(char)*(strlen(filename) + 1));
	if(!(*file_name_address)){
		fprintf(stderr, "MEMORY ERROR DURING FILE_NAME INITIALIZATING: %s\n", filename);
		exit(-1);
	}
	else 
		strcpy(*file_name_address, filename);
}

void file_name_close(char** file_name_address){
	free(*file_name_address);
}

void file_channel_init(FILE** input_address, FILE** output_address, char** input_file_name_address, char** output_file_name_address){
	*input_address = fopen(*input_file_name_address, "r");
	if(!(*input_address)){
		fprintf(stderr, "ERROR DURING OPENING INPUT SIMPLE-FILE %s\n", *input_file_name_address);
		exit(-1);
	}
	*output_address = fopen(*output_file_name_address, "w");
	if(!(*output_address)){
		fprintf(stderr, "ERROR DURING OPENING OUTPUT C-FILE %s\n", *output_file_name_address);
		exit(-1);
	}
}

void file_channel_get(FILE** input_address, char** line_address){
	if(!fgets(*line_address, MAX_LINE_SIZE, *input_address)){
		fprintf(stderr, "ERROR DURING READING FROM INPUT FILE\n");
		exit(-1);
	}
}

void file_channel_put(FILE** output_address, char*** words_address){
	for(int i = 0; i < wordcount-1; i++){
		if(fputs((*words_address)[i], *output_address) == EOF){
			fprintf(stderr, "ERROR DURING WRITING TO OUTPUT FILE\n");
			exit(-1);
		}
		if(fputs(" ", *output_address) == EOF){
			fprintf(stderr, "ERROR DURING WRITING TO OUTPUT FILE\n");
			exit(-1);
		}
	}
	if(fputs((*words_address)[wordcount-1], *output_address) == EOF){
		fprintf(stderr, "ERROR DURING WRITING TO OUTPUT FILE\n");
		exit(-1);
	}
}

void file_channel_close(FILE** input_address, FILE** output_address){
	fclose(*input_address);
	fclose(*output_address);
}

void buffer_init(char*** words_address, char** line_address){
	*words_address = (char**) malloc(MAX_WORD_COUNT * sizeof(char*));
	if(!(*words_address)){
		fprintf(stderr, "MEMORY ERROR DURING COMMAND BUFFER INITIALIZATING: \n");
		exit(-1);
	}
	for(int i = 0; i < MAX_WORD_COUNT; i++){
		(*words_address)[i] = (char*) malloc(MAX_LINE_SIZE * sizeof(char));
		if(!((*words_address)[i])){
			fprintf(stderr, "MEMORY ERROR DURING COMMAND BUFFER INITIALIZATING: \n");
			exit(-1);
		}
	}
	*line_address = (char*) malloc(MAX_LINE_SIZE * sizeof(char));
	if(!(*line_address)){
		fprintf(stderr, "MEMORY ERROR DURING COMMAND BUFFER INITIALIZATING: \n");
		exit(-1);
	}
}

void buffer_clear(char*** words_address, char** line_address){
	for(int i = 0; i < MAX_WORD_COUNT; i++){
		for(int j = 0; j < MAX_LINE_SIZE; j++)
			(*words_address)[i][j] = '\0';
	}
	for(int i = 0; i < MAX_LINE_SIZE; i++)
		(*line_address)[i] = '\0';
}

void buffer_close(char*** words_address, char** line_address){
	for(int i = 0; i < MAX_WORD_COUNT; i++)
		free((*words_address)[i]);
	free(*words_address); 
	free(*line_address);
}

void split(char** line, char*** words){
	wordcount = 0;
	char* word = strtok(*line, " ");
	for(int i = 0; (word != NULL) && (i < MAX_WORD_COUNT); i++){			
		wordcount++;
		strcpy((*words)[i], word);
		word = strtok(NULL, " ");
	}
	if(wordcount == 0){
		strcpy((*words)[0], *line);
		wordcount = 1;
	}
	
}