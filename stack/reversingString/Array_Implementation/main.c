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
                  if (data != '\n')
                        {
                              current_structure->top++;
                              current_structure->character_array[current_structure->top] = data;
                        }
            }
}

static bool
is_empty (stack *current_structure)
{
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
                  strcpy (foo_array, current_structure->character_array);

                  int i = current_structure->top;
                  current_structure->top = -1;

                  while (i >= 0)
                        {
                              Push (current_structure, foo_array[i]);
                              i--;
                        }
                  current_structure->character_array[current_structure->top + 1] = '\0';
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
      printf ("Reversed String : %s\n", current_structure->character_array);
}

static void
init (void)
{
      stack current_structure = { .top = -1 };
      char input_array[MAX_SIZE] = {};

      puts ("Input a String: ");
      fgets (input_array, MAX_SIZE, stdin);

      int input_size = strnlen (input_array, MAX_SIZE);
      int i = 0;

      while (i < input_size)
            {
                  Push (&current_structure, input_array[i]);
                  i++;
            }
      reversing_string (&current_structure);
      Print (&current_structure);
}

int
main (void)
{
      init ();
      return 0;
}
