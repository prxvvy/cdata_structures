#include <cdata_structures.h>
#include <stdio.h>
#include <stdlib.h>

int
main ()
{
  list_t *p_matrix = list_new ();

  for (int idx = 0; idx < 10; ++idx)
    {
      list_append (p_matrix, &"A"[0], STR);
    }

  list_print_list (p_matrix, 1);

  list_destroy_list (p_matrix);

  return 0;
}
