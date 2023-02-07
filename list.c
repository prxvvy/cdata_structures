#include "cdata_structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int str_includes (char *, char);

static int
str_includes (char *p_str, char char_to_find)
{
  for (int idx = 0; p_str[idx] != 00; ++idx)
    if (p_str[idx] == char_to_find)
      return 1;
  return 0;
}

list_t *
list_new ()
{
  list_t *p_this = calloc (1, sizeof (struct List));
  p_this->p_head = ((void *)0);
  p_this->p_tail = ((void *)0);
  p_this->length = 0;
  return p_this;
}

int
list_get_length_list (list_t *p_list)
{
  return p_list->length;
}

int
list_destroy_list (list_t *p_list)
{
  node_t *p_head = p_list->p_head;

  for (int idx = 0; idx < list_get_length_list (p_list); ++idx)
    {
      node_t *p_node_to_destroy = p_head;
      p_head = p_head->p_next;
      if (p_node_to_destroy->value_type == LIST)
        list_destroy_list ((list_t *)p_node_to_destroy->p_value);
      node_destroy_node (p_node_to_destroy);
    }
  free (p_list);
  p_list = ((void *)0);
  return 1;
}

node_t *
list_prepend (list_t *p_list, void *p_value, value_type_t value_type)
{
  node_t *p_node_new = node_new (p_value, value_type);

  if (!p_node_new)
    return ((void *)0);

  if (!list_get_length_list (p_list))
    {
      p_list->p_head = p_node_new;
      p_list->p_tail = p_node_new;

      p_list->p_head->p_previous = p_list->p_tail;
      p_list->p_tail->p_next = p_list->p_head;

      p_list->length++;
      return p_node_new;
    }

  p_node_new->p_next = p_list->p_head;
  p_list->p_head->p_previous = p_node_new;
  p_list->p_head = p_node_new;
  p_list->p_tail->p_next = p_list->p_head;
  p_list->p_head->p_previous = p_list->p_tail;
  p_list->length++;

  return p_node_new;
}

node_t *
list_append (list_t *p_list, void *p_value, value_type_t value_type)
{
  node_t *p_node_new = node_new (p_value, value_type);

  if (!p_node_new)
    return ((void *)0);

  if (!list_get_length_list (p_list))
    {
      p_list->p_head = p_node_new;
      p_list->p_tail = p_node_new;

      p_list->p_head->p_previous = p_list->p_tail;
      p_list->p_tail->p_next = p_list->p_head;

      p_list->length++;
      return p_node_new;
    }

  p_list->p_tail->p_next = p_node_new;
  p_node_new->p_previous = p_list->p_tail;
  p_list->p_tail = p_node_new;
  p_list->p_head->p_previous = p_list->p_tail;
  p_list->p_tail->p_next = p_list->p_head;
  p_list->length++;

  return p_node_new;
}

node_t *
list_insert (list_t *p_list, void *p_value, value_type_t value_type, int index)
{
  if (index < 0 || index > list_get_length_list (p_list))
    return ((void *)0);

  node_t *p_node_new = ((void *)0);

  if (!list_get_length_list (p_list))
    {
      p_node_new = node_new (p_value, value_type);

      if (!p_node_new)
        return ((void *)0);

      p_list->p_head = p_node_new;
      p_list->p_tail = p_node_new;

      p_list->p_head->p_previous = p_list->p_tail;
      p_list->p_tail->p_next = p_list->p_head;

      p_list->length++;

      return p_node_new;
    }

  if (index == 0)
    return list_prepend (p_list, p_value, value_type);

  node_t *p_head = p_list->p_head;

  index -= 1;

  for (int idx = 0; idx < list_get_length_list (p_list); ++idx)
    {
      if (idx == index)
        break;
      p_head = p_head->p_next;
    }

  if (p_head == p_list->p_tail)
    return list_append (p_list, p_value, value_type);

  p_node_new = node_new (p_value, value_type);

  if (!p_node_new)
    return ((void *)0);

  p_head->p_next->p_previous = p_node_new;
  p_node_new->p_next = p_head->p_next;
  p_head->p_next = p_node_new;
  p_node_new->p_previous = p_head;
  p_list->length++;

  return p_node_new;
}

node_t *
list_get_node (list_t *p_list, int index)
{
  if (index < 0 || index > (list_get_length_list (p_list) - 1))
    return ((void *)0);

  node_t *p_head = p_list->p_head;

  for (int idx = 0; idx < list_get_length_list (p_list); ++idx)
    {
      if (idx == index)
        return p_head;
      p_head = p_head->p_next;
    }

  return ((void *)0);
}

int
list_modify_value (list_t *p_list, void *p_new_value, value_type_t value_type,
                   int index)
{

  node_t *p_gotten_node = list_get_node (p_list, index);

  if (!p_gotten_node)
    return 0;

  p_gotten_node->p_value = p_new_value;
  p_gotten_node->value_type = value_type;

  return 1;
}

void
list_print_list (list_t *p_list, int new_line)
{

  if (!list_get_length_list (p_list))
    {

      if (new_line)
        printf ("[]\n");
      else
        printf ("[]");

      return;
    }

  printf ("[");

  for (int idx = 0; idx < list_get_length_list (p_list); ++idx)
    {
      node_t *p_node = list_get_node (p_list, idx);

      if (p_node->value_type == STR)
        {
          if (idx == list_get_length_list (p_list) - 1)
            printf ("%s", (char *)p_node->p_value);
          else
            printf ("%s, ", (char *)p_node->p_value);
        }
      else if (p_node->value_type == CHAR)
        {
          if (idx == list_get_length_list (p_list) - 1)
            printf ("%c", *(char *)p_node->p_value);
          else
            printf ("%c, ", *(char *)p_node->p_value);
        }
      else if (p_node->value_type == INT)
        {
          if (idx == list_get_length_list (p_list) - 1)
            printf ("%d", *(int *)p_node->p_value);
          else
            printf ("%d, ", *(int *)p_node->p_value);
        }
      else if (p_node->value_type == LIST)
        {
          if (idx == list_get_length_list (p_list) - 1)
            list_print_list (p_list, 0);
          else
            list_print_list (p_list, 0);
        }
      else
        {
          if (idx == list_get_length_list (p_list) - 1)
            printf ("UNKNOWN");
          else
            printf ("UNKNOWN, ");
        }
    }

  if (new_line)
    printf ("]\n");
  else
    printf ("]");
}

node_t *
list_remove_beginning (list_t *p_list)
{
  if (!list_get_length_list (p_list))
    return ((void *)0);

  node_t *p_node_to_remove = ((void *)0);

  if (list_get_length_list (p_list) == 1)
    {
      p_node_to_remove = p_list->p_head;

      p_list->p_head = ((void *)0);
      p_list->p_tail = ((void *)0);

      p_node_to_remove->p_next = ((void *)0);
      p_node_to_remove->p_previous = ((void *)0);

      p_list->length--;
      return p_node_to_remove;
    }

  p_node_to_remove = p_list->p_head;

  p_list->p_head = p_list->p_head->p_next;
  p_list->p_head->p_previous = p_list->p_tail;
  p_list->p_tail->p_next = p_list->p_head;

  p_node_to_remove->p_next = ((void *)0);
  p_node_to_remove->p_previous = ((void *)0);

  p_list->length--;

  return p_node_to_remove;
}

node_t *
list_remove_end (list_t *p_list)
{
  if (!list_get_length_list (p_list))
    return ((void *)0);

  node_t *p_node_to_remove = ((void *)0);

  if (list_get_length_list (p_list) == 1)
    {
      p_node_to_remove = p_list->p_head;

      p_list->p_head = ((void *)0);
      p_list->p_tail = ((void *)0);

      p_node_to_remove->p_next = ((void *)0);
      p_node_to_remove->p_previous = ((void *)0);

      p_list->length--;

      return p_node_to_remove;
    }

  p_node_to_remove = p_list->p_tail;

  p_list->p_tail = p_list->p_tail->p_previous;
  p_list->p_tail->p_next = p_list->p_head;
  p_list->p_head->p_previous = p_list->p_tail;

  p_node_to_remove->p_next = ((void *)0);
  p_node_to_remove->p_previous = ((void *)0);

  p_list->length--;

  return p_node_to_remove;
}

list_t *
list_split_string (char *p_str, char sep)
{
  if (!p_str || !strlen (p_str))
    return ((void *)0);
  if (sep == 00)
    return ((void *)0);

  if (!str_includes (p_str, sep))
    return ((void *)0);

  char *p_text_element = calloc (1, sizeof (char));
  if (!p_text_element)
    return ((void *)0);

  size_t p_text_element_len = strlen (p_text_element);

  list_t *p_strs = list_new ();

  for (int idx = 0; p_str[idx] != 00; ++idx)
    {
      if (p_str[idx] == sep)
        {
          if (strlen (p_text_element))
            {
              list_append (p_strs, p_text_element, STR);
              p_text_element = ((void *)0);
              p_text_element_len = 0;
            }
          continue;
        }
      char *p_realloc_res = realloc (p_text_element, p_text_element_len + 2);
      if (!p_realloc_res)
        {
          free (p_text_element);
          p_text_element = ((void *)0);
          break;
        }
      p_text_element = p_realloc_res;
      p_text_element[p_text_element_len++] = p_str[idx];
      p_text_element[p_text_element_len] = 00;
    }

  if (p_text_element)
    if (strlen (p_text_element))
      list_append (p_strs, p_text_element, STR);

  return p_strs;
}
