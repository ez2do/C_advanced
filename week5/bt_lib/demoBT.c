#include <stdio.h>
#include "inc/btree.h"

int main(){
	BTA *btfile;
	btinit();
	btfile = btcrt("test_db", 0, FALSE);
	binsky(btfile, "akey", 99);
	btcls(btfile);
	return 0;
}