#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/jval.h"
#include "libfdr/dllist.h"
#include "huffmanCode.h"

int countNode(HuffmanTree *tree){
	if(tree == NULL)
		return 0;
	else
		return 1 + countNode(tree->leftChild) + countNode(tree->rightChild);
}

int main(){
	char text[1000] = "ahihi do ngok, sao toi lai pro tke nay =))))";
	HuffmanTree *tree = makeHuffmanTree(text, strlen(text));
	JRB huffmanTable = makeHuffmanTable(tree);
	printf("The Huffman Table:\n");
	JRB ptr;
	jrb_traverse(ptr, huffmanTable){
		printf("%c - %s\n", jval_i(ptr->key), jval_s(ptr->val));
	}
	/*JRB charFreq = makeCharFreqTable(text, strlen(text));
	JRB t;
	jrb_traverse(t, charFreq){
		printf("%c - %d\n", jval_i(t->key), jval_i(t->val));
	}*/
	HuffmanTreeArray huffArray;
	huffArray = tree2array(tree);
	printf("size: %d\n", huffArray.size);
	printf("Count: %d\n", countNode(tree));
	for(int i = 0; i < huffArray.size; i++){
		if(huffArray.node[i] != -1)
			printf("%d - %c\n", i, huffArray.node[i]);
	}
}