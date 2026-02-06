#include <iostream>

int
main (void)
{
  std::size_t arr[] = { 4, 2, 1, 7, 8, 1, 2, 8, 10 };
  std::size_t length_arr = sizeof (arr) / sizeof (arr[0]);
  std::size_t target = 8;
  std::size_t left{ 0 };
  std::size_t right{ 0 };
  std::size_t smallest_valid_window{ length_arr + 1 };
  std::size_t accumulator{ 0 };

  while (right < length_arr)
    {
      // so the window should naturally grow
      accumulator += arr[right++];
      // and should only shrink if the accumulator >= target and should keep on
      // doing that unless target > accumulator
      while (target <= accumulator)
        {
          // if smallest valid window is greater than current window length
          // then update it with current window length
          if (smallest_valid_window > (right - left))
            {
              // this should be captured before shrinking otherwise the proper
              // window in which accumulator == target won't be captured.
              smallest_valid_window = right - left;
            }
          // then shrink
          accumulator -= arr[left++];
        }
    }

  if (smallest_valid_window == (length_arr + 1))
    std::cout << "Unable to find a smallest valid window." << "\n";
  else
    std::cout << "The smallest valid window : " << smallest_valid_window
              << "\n";

  return 0;
}
