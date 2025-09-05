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
        if (head_ptr != NULL)
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
        // declared a new temporary node and i assigned it the current value of head_ptr.
        struct Node* tempNode = *current;
        // In the next line i overwrite the value of current with the value of the next node in the
        // list.

        puts ("Deleting Node .....");
        *current = (*current)->next;
        // Now I simply free the old head
        free (tempNode);
        tempNode = NULL;
}

static void
freeSpace (struct Node* current)
{
        struct Node* temp_var = NULL;
        while (current != NULL)
                {
                        /* So temp_var stores a copy of the address of the current */
                        temp_var = current;
                        current = current->next;
                        /* Freeing even the copy of the address results in freeing the address
                        altogether. */
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
