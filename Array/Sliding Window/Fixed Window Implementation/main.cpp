#include <iostream>

int main(void) {
  std::size_t arr[] = {5, 1, 9, 2, 6, 3, 8, 4, 7};
  std::size_t length_arr = sizeof(arr) / sizeof(arr[0]);
  std::size_t window_size = 3;
  std::size_t left = 0;
  std::size_t right = window_size;
  std::size_t accumulator {};
  std::size_t i {0};

  while (i < window_size) {
    accumulator += arr[i++];
  }
  
  while (right < length_arr) {
    accumulator += arr[right++] - arr[left++];
  }

  std::cout << "Sum : " << accumulator;
  return 0;
}
