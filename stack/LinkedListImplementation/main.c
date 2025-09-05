#include <stdio.h>
#include <stdlib.h>

struct Node
{
        int data;
        struct Node* next;
};

static void
pushNode (struct Node** head_ptr, int data)
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
printList (struct Node* current)
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
deleteNode (struct Node** current)
{
        struct Node* tempNode = *current;

        puts ("Deleting Node .....");
        *current = (*current)->next;
        free (tempNode);
        tempNode = NULL;
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

        pushNode (&head, 2);
        printList (head);

        pushNode (&head, 3);
        printList (head);

        pushNode (&head, 4);
        printList (head);

        pushNode (&head, 5);
        printList (head);

        pushNode (&head, 6);
        printList (head);

        deleteNode (&head);
        printList (head);

        freeSpace (head);
        return 0;
}
