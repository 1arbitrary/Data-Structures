// Trace the working of this C program ---------------------------------
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 50

typedef struct
{
      int top;
      char character_array[MAX_SIZE];
} stack;

static bool
is_full (stack *current_structure)
{
      // To check the space left in the array. Should return `false` ideally.
      return (current_structure->top >= (MAX_SIZE - 1));
}

static void
Push (stack *current_structure, char data)
{
      if (is_full (current_structure))
            {
                  puts ("List is full ! CRASH INCOMING");
                  return;
            }
      else
            {
                  // Increment top before inserting so that there is no data loss.
                  current_structure->top++;
                  current_structure->character_array[current_structure->top] = data;
            }
}

static bool
is_empty (stack *current_structure)
{
      // This is just to check if i'm popping an empty array otherwise this isn't really useful.
      return (current_structure->top < 0);
}

static void
Pop (stack *current_structure)
{
      if (!(is_empty (current_structure)))
            {
                  current_structure->top--;
                  return;
            }
      else
            {
                  puts ("List is too short ! UNABLE TO POP");
                  return;
            }
}

static void
reversing_string (stack *current_structure)
{
      if (!is_empty (current_structure))
            {
                  char foo_array[MAX_SIZE] = {};

                  // The reason because i've set the size_t n to top + 1 is because it would also
                  // require a null terminating character
                  memcpy (foo_array, current_structure->character_array,
                          current_structure->top + 1);

                  int i = current_structure->top;
                  current_structure->top = -1;

                  while (i >= 0)
                        {
                              Push (current_structure, foo_array[i]);
                              i--;
                        }
            }
      else
            {
                  puts ("List Is Too Short, Nothing To Reverse");
                  return;
            }
}

void
Print (stack *current_structure)
{
      printf ("%s", current_structure->character_array);
}

static void
init (void)
{
      // Initializing a local struct variable;
      stack current_structure = { .top = -1 };

      // A sample array to store input
      char input_array[MAX_SIZE] = {};

      puts ("Input a String: ");

      // To store input and not ignore spaces; unlike `scanf`.
      fgets (input_array, MAX_SIZE, stdin);

      int i = 0;
      // Loop to iterate through the stored input array and push the elements one by one from the
      // beginning.
      while (input_array[i] != '\0')
            {
                  // To push only the elements which are non '\n' characters
                  if (input_array[i] != '\n')
                        {
                              Push (&current_structure, input_array[i]);
                              i++;
                        }
                  else
                        {
                              // Remember to increment the value of `i` before writing continue,
                              // otherwise it will be stuck in an infinte loop.
                              i++;
                              continue;
                        }
            }
      // Calling the reversing string function
      reversing_string (&current_structure);
      Print (&current_structure);
}

int
main (void)
{
      init ();
      return 0;
}
