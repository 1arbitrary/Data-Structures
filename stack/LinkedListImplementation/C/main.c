#include <stdio.h>
#include <stdlib.h>

struct Node
{
  int data;
  struct Node* next;
};

static void
push (struct Node** head_ptr, int data)
{
  struct Node* current = malloc (sizeof (struct Node));
  if (*head_ptr != NULL)
    {
      current->data = data;
      current->next = *head_ptr;
      *head_ptr = current;
    }
  else
    {
      current->data = data;
      current->next = NULL;
      *head_ptr = current;
    }
}

static void
print (struct Node* current)
{
  printf ("List : ");
  while (current != NULL)
    {
      printf ("%d ", current->data);
      current = current->next;
    }
  puts ("");
}

static void
pop (struct Node** current)
{
  struct Node* tempNode = *current;
  if (tempNode != NULL)
    {
      puts ("Deleting Node .....");
      *current = (*current)->next;
      free (tempNode);
    }
  else
    {
      puts ("HEAD NODE DOESN'T EXIST !");
    }
}

static void
freeSpace (struct Node* current)
{
  struct Node* temp_var = NULL;
  while (current != NULL)
    {
      temp_var = current;
      current = current->next;
      free (temp_var);
    }
}

int
main (void)
{
  struct Node* head = NULL;

  push (&head, 2);
  print (head);

  push (&head, 3);
  print (head);

  push (&head, 4);
  print (head);

  push (&head, 5);
  print (head);

  push (&head, 6);
  print (head);

  pop (&head);
  print (head);

  freeSpace (head);
  return 0;
}
