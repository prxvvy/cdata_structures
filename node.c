//
// Created by prxvvy on 04/02/2023
//

#include "cdata_structures.h"
#include <stdio.h>
#include <stdlib.h>

node_t *
node_new (void *p_value, value_type_t value_type)
{
  node_t *p_this = calloc (1, sizeof (struct Node));

  if (!p_this)
    return ((void *)0);

  p_this->p_next = ((void *)0);
  p_this->p_previous = ((void *)0);

  p_this->value_type = value_type;
  p_this->p_value = p_value;

  return p_this;
}

int
node_destroy_node (node_t *p_node)
{
  free (p_node);
  p_node = ((void *)0);
  return 1;
}

void
node_print_node (node_t *p_node)
{
  if (!p_node)
    return;
  printf ("{\n");
  if (p_node->value_type == CHAR)
    {
      printf ("  Type: char,\n");
      printf ("  Value: %c,\n", *(char *)p_node->p_value);
    }
  else if (p_node->value_type == STR)
    {
      printf ("  Type: string,\n");
      printf ("  Value: %s,\n", (char *)p_node->p_value);
    }
  else if (p_node->value_type == INT)
    {
      printf ("  Type: int,\n");
      printf ("  Value: %d,\n", *(int *)p_node->p_value);
    }
  else if (p_node->value_type == LIST)
    {
      printf ("  Type: list,\n");
      list_print_list (p_node->p_value, 0);
      printf (",\n");
    }
  else
    {
      printf ("  Type: unknown,\n");
      printf ("  Value: uknown,\n");
    }
  if (!p_node->p_previous)
    printf ("  Previous pointer: null,\n");
  else
    printf ("  Previous pointer: %p,\n", p_node->p_value);

  if (!p_node->p_next)
    printf ("  Next pointer: null\n");
  else
    printf ("  Next pointer: %p\n", p_node->p_value);

  printf ("}\n");
}
