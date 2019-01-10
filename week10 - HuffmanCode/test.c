#include <stdio.h>
#include <stdlib.h>
#include "libfdr/jrb.h"
#include "libfdr/jval.h"
#include "libfdr/dllist.h"
#include "huffmanCode.h"
#include "string.h"

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

int main(){
	char buffer[100] = "aaabbbbcccccdee";
	JRB charFreqTable = makeCharFreqTable(buffer, strlen(buffer));
	JRB ptr;
	jrb_traverse(ptr, charFreqTable){
		printf("%c - %d\n", jval_i(ptr->key), jval_i(ptr->val));
	}
}