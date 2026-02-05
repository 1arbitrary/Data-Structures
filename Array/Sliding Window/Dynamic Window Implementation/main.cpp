#include <iostream>

int
main (void)
{
  std::size_t arr[] = { 2, 1, 5, 2, 3, 2 };
  std::size_t length_arr = sizeof (arr) / sizeof (arr[0]);
  std::size_t S = 7;
  std::size_t left{ 0 };
  std::size_t right{ 0 };
  std::size_t accumulator = 0;
  std::size_t minimum_valid_window_length = length_arr + 1;

  while (right < length_arr)
    {
      // Increase the window size by
      accumulator += arr[right++];
      while (S <= accumulator)
        {
          minimum_valid_window_length = right - left;
          accumulator -= arr[left++];
        }
    }

  std::cout << minimum_valid_window_length;
  return 0;
}
