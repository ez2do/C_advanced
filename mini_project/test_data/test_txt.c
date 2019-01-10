#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/fields.h"

int main(){
	IS is = new_inputstruct("station_info.txt");
	while(get_line(is) >= 0){
		printf("%s - %s\n", is->fields[0], is->fields[1]);
	}
	jettison_inputstruct(is);
}