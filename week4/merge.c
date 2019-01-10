#include <stdio.h>
#include <stdlib.h>
#include "libfdr/fields.h"

int main(){
	IS is1, is2;
	FILE *fout = fopen("info.txt", "w");
	is1 = new_inputstruct("name.txt");
	is2 = new_inputstruct("number.txt");

	if (is1 == NULL) {
    perror("name.txt");
    exit(1);
  	}

  	if (is2 == NULL) {
    perror("number.txt");
    exit(1);
  	}

	while(get_line(is1) >= 0 && get_line(is2) >= 0){
		printf("%s%s\n", is1->text1, is2->text2);
		fprintf(fout, "%s%s", is1->text1, is2->text1);
	}
	jettison_inputstruct(is1);
	jettison_inputstruct(is2);
}