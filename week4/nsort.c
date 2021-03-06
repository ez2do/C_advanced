#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/jrb.h"
#include "libfdr/fields.h"

int main()
{
  JRB b;
  JRB bn;
  IS is;

  is = new_inputstruct(NULL);
  b = make_jrb();

  while (get_line(is) >= 0) {
    (void) jrb_insert_int(b, atoi(is->text1), new_jval_s(strdup(is->text1)));
  }

  jrb_traverse(bn, b) {
    printf("%d - %s", jval_i(bn->key), jval_s(bn->val));
  }
}