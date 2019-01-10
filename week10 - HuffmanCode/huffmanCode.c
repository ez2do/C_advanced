#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "libfdr/jrb.h"
#include "libfdr/jval.h"
#include "libfdr/dllist.h"
#include "huffmanCode.h"

#define DEFAULT 0

JRB makeCharFreqTable(char *buffer, int size){
	JRB charFreqTable = make_jrb();
	for(int i = 0; i < size; i++){
		JRB node = jrb_find_int(charFreqTable, buffer[i]);
		if(node != NULL)
			node->val = new_jval_i(jval_i(node->val) + 1);
		else
			jrb_insert_int(charFreqTable, buffer[i], new_jval_i(1));
	}
	return charFreqTable;
}

void orderedEnqueue(Dllist queue, Node* u){
	Dllist ptr;
	if(!dll_empty(queue)){
		//insert head
		Node *head = (Node*)jval_v(dll_first(queue)->val);
		if(u->freq < head->freq)
			dll_prepend(queue, new_jval_v(u));
		else{
			dll_traverse(ptr, queue){
				Node *n = (Node*)jval_v(ptr->val);
				if(n->freq > u->freq)
					break;
			}
			dll_insert_b(ptr, new_jval_v(u));
		}
	}
	else
		dll_prepend(queue, new_jval_v(u));
}

Node *makeNode(char data, int freq){
	Node *node = malloc(sizeof(Node));
	node->data = data;
	node->freq = freq;
	node->leftChild = NULL;
	node->rightChild = NULL;
	return node;
}

int queueContain(Dllist queue){
	int total = 0;
	Dllist ptr;
	dll_traverse(ptr, queue){
		total++;
	}
	return total;
}

Node *dequeue(Dllist queue){
	if(dll_empty(queue))
		return NULL;
	else{
		Dllist item = dll_first(queue);
		dll_delete_node(dll_first(queue));
		return (Node*)jval_v(item->val);
	}
}

HuffmanTree *makeHuffmanTree(char *buffer, int size){
	JRB charFreqTable = makeCharFreqTable(buffer, size);
	int total = 0;

	Dllist queue = new_dllist();
	JRB ptr;
	jrb_traverse(ptr, charFreqTable){
		Node *node = makeNode(jval_i(ptr->key), jval_i(ptr->val));
		orderedEnqueue(queue, node);
	}

	while(queueContain(queue) >= 2){
		Node *parent = makeNode(DEFAULT, 0);
		Node *leftNode = dequeue(queue);
		leftNode->direction = LEFT;
		parent->leftChild = leftNode;
		Node *rightNode = dequeue(queue);
		parent->rightChild = rightNode;
		parent->freq = leftNode->freq + rightNode->freq;
		orderedEnqueue(queue, parent);
	}

	return dequeue(queue); //only the root contained in the queue
}

void traverse(Node *root, char *output, int size, JRB huffmanTable){
	char *string;
	if(root->leftChild == NULL && root->rightChild == NULL){
		output[size] = '\0';
		string = strdup(output);
		jrb_insert_int(huffmanTable, root->data, new_jval_s(string));
	}
	else{
		output[size] = '0';
		traverse(root->leftChild, output, size + 1, huffmanTable);
		output[size] = '1';
		traverse(root->rightChild, output, size + 1, huffmanTable);
	}
}

JRB makeHuffmanTable(HuffmanTree *tree){
	char output[1000];
	JRB huffmanTable = make_jrb();
	traverse(tree, output, 0, huffmanTable);
	return huffmanTable;
}

void add2queue(HuffmanTree *tree, Dllist queue){
	if(tree == NULL)
		return;
	else{
		dll_prepend(queue, new_jval_i(tree->data));
		add2queue(tree->leftChild, queue);
		add2queue(tree->rightChild, queue);
	}
}

HuffmanTreeArray createHuffmanTreeArray(int size){
	HuffmanTreeArray h;
	h.size = size;
	h.node = (int*)malloc(sizeof(int) * size);
	return h;
}

void enqueue(Dllist queue, Node *node){
	if(node == NULL)
		node = makeNode(0, 0);
	dll_append(queue, new_jval_v(node));
}

HuffmanTreeArray tree2array(HuffmanTree *tree){
	int degree = countDepth(tree);
	int range = (int)pow((double)2, (double)(degree)) - 1;
	printf("degree: %d, range: %d\n", degree, range);
	HuffmanTreeArray huff = createHuffmanTreeArray(range);
	int *arr = malloc(sizeof(int) * range);
	int total = 0;
	Dllist queue = new_dllist();
	dll_prepend(queue, new_jval_v(tree));
	while(total < range){
		Node *current = (Node*)jval_v(dll_first(queue)->val);
		dll_delete_node(dll_first(queue));

		if(current == NULL || current->data == 0)
			arr[total++] = -1;
		else
			arr[total++] = current->data;

		enqueue(queue, current->leftChild);
		enqueue(queue, current->rightChild);
	}
	huff.node = arr;
	return huff;
}

int max(int a, int b){
	return a > b ? a : b;
}

int countDepth(HuffmanTree *tree){
	if(tree != NULL)
		return 1 + max(countDepth(tree->leftChild), countDepth(tree->rightChild));
	else
		return 0;
}