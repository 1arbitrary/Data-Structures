#include <iostream>

int
main (void)
{
  std::size_t arr[] = { 5, 1, 9, 2, 6, 3, 8, 4, 7 };
  std::size_t length_arr = sizeof (arr) / sizeof (arr[0]);

  std::size_t i{ 0 };
  while (i < length_arr)
    {
      std::cout << arr[i++] << "\t";
    }
  return 0;
}
