#include <stdio.h>
#define LEFT 0
#define RIGHT 1

typedef struct Node{
	char data;
	int freq;
	int direction; //0 for left, 1 for right
	struct Node *leftChild, *rightChild;
}Node;

typedef Node HuffmanTree;

typedef struct{
	int size;
	int *node;
}HuffmanTreeArray;

JRB makeCharFreqTable(char *buffer, int size);
HuffmanTree *makeHuffmanTree(char *buffer, int size);
JRB makeHuffmanTable(HuffmanTree *tree);
HuffmanTreeArray createHuffmanTreeArray(int size);
HuffmanTreeArray tree2array(HuffmanTree *tree);
int countDepth(HuffmanTree *tree);