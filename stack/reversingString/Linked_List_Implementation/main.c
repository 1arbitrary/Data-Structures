// This is not a correct implementation of reversing a string using linked list 

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node
{
      int data;
      struct Node *next_node;
};

static bool
is_empty (struct Node *ptr_head)
{
      return (ptr_head == NULL);
}

static void
push (struct Node **ptr_head, int data)
{
      struct Node *current_ptr = malloc (sizeof (struct Node));
      if (*ptr_head != NULL)
            {
                  current_ptr->data = data;
                  current_ptr->next_node = *ptr_head;
                  *ptr_head = current_ptr;
            }
      else
            {
                  current_ptr->data = data;
                  current_ptr->next_node = NULL;
                  *ptr_head = current_ptr;
            }
}

static void
pop (struct Node **ptr_head)
{
      if (!is_empty (*ptr_head))
            {
                  struct Node *free_node = *ptr_head;
                  *ptr_head = (*ptr_head)->next_node;
                  free (free_node);
            }
      else
            {
                  puts ("CRASH INCOMING ! LIST IS TOO SHORT TO BE POPPED");
                  return;
            }
}

static void
print (struct Node *ptr_head)
{
      if (!is_empty (ptr_head))
            {
                  struct Node *current_ptr = ptr_head;
                  while (current_ptr != NULL)
                        {
                              printf ("%d", current_ptr->data);
                              current_ptr = current_ptr->next_node;
                        }
            }
      else
            {
                  puts ("List is empty");
                  return;
            }
}

static void
free_list (struct Node *ptr_head)
{
      if (!is_empty (ptr_head))
            {
                  struct Node *free_node = NULL;
                  while (ptr_head != NULL)
                        {
                              free_node = ptr_head;
                              ptr_head = ptr_head->next_node;
                              free (free_node);
                        }
            }
      else
            {
                  puts ("CRASH INCOMING ! NO NODE TO POP !");
                  return;
            }
}

int
main (void)
{
      struct Node *head = NULL;
      return 0;
}
