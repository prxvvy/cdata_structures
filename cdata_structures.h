#ifndef CDATA_STRUCTURES_H
#define CDATA_STRUCTURES_H

typedef enum ValueType
{
  CHAR,
  STR,
  INT,
  LIST
} value_type_t;

typedef struct Node
{
  struct Node *p_next;
  struct Node *p_previous;
  void *p_value;
  value_type_t value_type;
} node_t;

typedef struct List
{
  node_t *p_head;
  node_t *p_tail;
  int length;
} list_t;

node_t *node_new (void *, value_type_t);

int node_destroy_node (node_t *);

void node_print_node (node_t *);

list_t *list_new ();

void list_print_list (list_t *, int);

int list_get_length_list (list_t *);

node_t *list_prepend (list_t *, void *, value_type_t);

node_t *list_append (list_t *, void *, value_type_t);

node_t *list_insert (list_t *, void *, value_type_t, int);

int list_destroy_list (list_t *);

node_t *list_get_node (list_t *, int);

int list_modify_value (list_t *, void *, value_type_t, int);

node_t *list_remove_beginning (list_t *);

node_t *list_remove_end (list_t *);

list_t *list_split_string (char *, char);

#endif // CDATA_STRUCTURES_H
