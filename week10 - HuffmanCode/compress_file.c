#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/jval.h"
#include "libfdr/dllist.h"
#include "huffmanCode.h"

int main(int argc, const char *argv[]){
	FILE    *infile, *outfile;
	char    *buffer;
	long    numbytes;
	char 	filename[100];
	 
	/* open an existing file for reading */
	printf("%s\n", argv[1]);
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
	printf("The file content:\n\n%s", buffer);

	HuffmanTree *tree = makeHuffmanTree(buffer, strlen(buffer));
	JRB huffmanTable = makeHuffmanTable(tree);
	printf("The Huffman Table:\n");
	JRB ptr;
	int i = 1;
	jrb_traverse(ptr, huffmanTable){
		printf("%d - %c - %s\n", i++, jval_i(ptr->key), jval_s(ptr->val));
	}
	HuffmanTreeArray huffArray;
	huffArray = tree2array(tree);
	fprintf(outfile, "%s ", "HM");
	for(int i = 0; i < huffArray.size; i++){
		fprintf(outfile, "%d ", huffArray.node[i]);
	}
	fprintf(outfile, "%ld", strlen(buffer));
	fprintf(outfile, "\n");

	for(int i = 0; i < strlen(buffer); i++){
		JRB tmp = jrb_find_int(huffmanTable, buffer[i]);
		if(tmp != NULL){
			char *str = strdup(jval_s(tmp->val));
			for(int i = 0; i < strlen(str); i++)
				fprintf(outfile, "%c", str[i]);
		}
	}
	 
	/* free the memory we used for the buffer */
	free(buffer);
}