#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define bool short
#define TRUE 1
#define FALSE 0

#define DEFAULT_INPUT_FILE_NAME "test.txt" 
#define DEFAULT_OUTPUT_FILE_NAME "test.c"

#define MAX_WORD_COUNT 20
#define MAX_LINE_SIZE 50

void file_name_init(char** file_name_address, char* filename);
void file_name_close(char** file_name_address);

void file_channel_init(FILE** input_address, FILE** output_address, char** input_file_name_address, char** output_file_name_address);
void file_channel_get(FILE** input_address, char** line_address);
void file_channel_put(FILE** output_address, char*** words_address);
void file_channel_close(FILE** input_address, FILE** output_address);

void buffer_init(char*** words_address, char** line_address);
void buffer_clear(char*** words_address, char** line_address);
void buffer_close(char*** words_address, char** line_address);

void split(char** line, char*** words);