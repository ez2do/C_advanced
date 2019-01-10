#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/fields.h"
#include "libfdr/jrb.h"

typedef struct{
	char name[80];
	long number;
} Entry;

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

int main(){
	IS is1, is2;
	JRB t, tmp;
	char *name = malloc(80 * sizeof(char));
	long number;
	Entry *e = malloc(sizeof(Entry));

	t = make_jrb();

	is1 = new_inputstruct("name.txt");
	is2 = new_inputstruct("number.txt");

	while(get_line(is1) >= 0 && get_line(is2) >= 0){
		strcpy(name, is1->text1);
		name = rtrim(name);
		number = atoi(is2->text1);
		jrb_insert_str(t, strdup(name), new_jval_l(number));
	}

	jrb_traverse(tmp, t){
		printf("%-30s %-2ld\n", tmp->key.s, tmp->val.l);
	}

	jettison_inputstruct(is1);
	jettison_inputstruct(is2);
}

