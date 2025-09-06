#include <stdio.h>

static void
print_string_recursively (char *current_arr)
{
      if ((*current_arr) != '\0')
            {
                  printf ("%c", *(current_arr));
                  print_string_recursively ((current_arr + 1));
            }
}

static void
reverse_string_recursively (char *current_array)
{
      if ((*current_array) != '\0')
            {
                  reverse_string_recursively (current_array + 1);
		  printf("%c", *current_array);
            }
}

int
main (void)
{
      char helloArr[] = "Hello";
      int size = sizeof (helloArr) / sizeof (helloArr[0]);

      print_string_recursively (helloArr);
      puts ("");

      reverse_string_recursively (helloArr);
      puts ("");
      
      return 0;
}
