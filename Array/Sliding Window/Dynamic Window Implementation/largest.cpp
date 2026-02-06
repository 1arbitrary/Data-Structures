#include <iostream>

int
main (void)
{
  std::size_t arr[] = { 4, 2, 1, 7, 8, 1, 2, 8, 10 };
  std::size_t accumulator{ 0 };
  std::size_t length_arr = sizeof (arr) / sizeof (arr[0]);
  std::size_t target = 8;
  std::size_t largest_valid_window{ 0 };
  std::size_t left{ 0 };
  std::size_t right{ 0 };

  while (right < length_arr)
    {
      accumulator += arr[right++];
      while (accumulator > target)
        {
          accumulator -= arr[left++];
        }
      if (largest_valid_window < (right - left))
        {
          largest_valid_window = right - left;
        }
    }

  if (largest_valid_window == 0)
    std::cout << "No valid window was found" << "\n";
  else
    std::cout << "The largest valid window which was found : "
              << largest_valid_window << "\n";

  return 0;
}
