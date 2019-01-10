#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/jval.h"
#include "libfdr/dllist.h"
#include "libfdr/fields.h"
#include "huffmanCode.h"

int main(int argc, const char *argv[]){
	FILE    *infile, *outfile;
	char    *buffer;
	long    numbytes;
	char 	filename[100];
	int line1_len, data_size;
	HuffmanTreeArray h;
	int pointer = 0;

	IS is = new_inputstruct(argv[1]);
	if(get_line(is) > 0){
		if(strcmp(is->fields[0], "HM") != 0){
			printf("The file is not marked in HM\n");
			exit(1);
		}
		else{
			int arr_len = is->NF - 2;
			h = createHuffmanTreeArray(arr_len);
			//printf("arr_len: %d - h.size: %d\n", arr_len, h.size);
			for(int i = 0; i < h.size; i++){
				h.node[i] = strtol(is->fields[i + 1], NULL, 10);
			}
			data_size = strtol(is->fields[is->NF - 1], NULL, 10);
			//printf("Array len: %d, data_size: %d\n", arr_len, data_size);
			line1_len = strlen(is->text1);
		}
	}
	 
	/* open an existing file for reading */
	infile = fopen(argv[1], "r");
	outfile = fopen(argv[2], "w");
	 
	/* quit if the file does not exist */
	if(infile == NULL)
	    return 1;
	 
	/* Get the number of bytes */
	fseek(infile, 0L, SEEK_END);
	numbytes = ftell(infile);
	 
	/* reset the file position indicator to 
	the beginning of the file */
	fseek(infile, 0L, SEEK_SET);	
	 
	/* grab sufficient memory for the 
	buffer to hold the text */
	buffer = (char*)calloc(numbytes, sizeof(char));	
	 
	/* memory error */
	if(buffer == NULL)
	    return 1;
	 
	/* copy all the text into the buffer */
	fread(buffer, sizeof(char), numbytes, infile);
	fclose(infile);
	 
	/* confirm we have read the file by
	outputing it to the console */
	//printf("The file content:\n\n%s", buffer);

	//printf("%c - %c - %c - %c\n", h.node[499], h.node[900], h.node[11], h.node[24]);
	for(int i = line1_len; i < strlen(buffer); i++){
		if(buffer[i] == '0')
			pointer = pointer * 2 + 1;
		else
			pointer = pointer * 2 + 2;
		if(h.node[pointer] != -1){
			printf("%c", h.node[pointer]);
			fprintf(outfile, "%c", h.node[pointer]);
			pointer = 0;
		}
	}
	printf("\n");
}
