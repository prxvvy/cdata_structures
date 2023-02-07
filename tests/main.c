#include <cdata_structures.h>
#include <stdio.h>
#include <stdlib.h>

int
main ()
{
  list_t *p_list = list_new ();

  for (int idx = 0; idx < 5; ++idx)
    list_append (p_list, &"ABCDEFGHIJKLMNOPQRSTUVWXYZ"[random () % 26], CHAR);

  list_print_list (p_list, 1);

  printf ("List's length: %d\n", list_get_length_list (p_list));

  node_t *p_removed_node = list_remove_end (p_list);

  node_print_node (p_removed_node);

  free (p_removed_node);

  list_print_list (p_list, 1);

  printf ("List's length: %d\n", list_get_length_list (p_list));

  list_destroy_list (p_list);

  return 0;
}
