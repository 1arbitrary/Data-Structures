#include <iostream>
#include <stdexcept>

template <typename T> struct StaticArray {
  static constexpr int MAX_SIZE = 10;
  T elements[MAX_SIZE];
  int occupied_indexes = 0;

  bool is_full() const { return occupied_indexes == MAX_SIZE; }
  bool is_empty() const { return occupied_indexes == 0; }

  void insert(T data) {
    if (is_full()) {
      throw std::out_of_range("Attempt To Insert On A Filled Array !");
    }
    elements[occupied_indexes++] = data;
  }

  T remove() {
    if (is_empty()) {
      throw std::out_of_range("Attempt To Delete On An Empty Array !");
    }
    return elements[--occupied_indexes];
  }

  bool search(T data) {
    int i = 0;
    while (i < occupied_indexes) {
      if (elements[i] == data) {
        return true;
      } else {
        i++;
      }
    }
    return false;
  }

  void print() const {
    std::cout << "Array : ";
    if (is_empty()) {
      std::cerr << "Empty Static Array" << '\n';
      return;
    }

    int i = 0;
    int elements_to_be_printed = occupied_indexes;
    while (elements_to_be_printed != 0) {
      std::cout << elements[i++] << '\t';
      elements_to_be_printed--;
    }
    std::cout << '\n';
  }
};

int main(void) {
  StaticArray<int> arr;
  for (int i = 1; i <= 10; i++) {
    arr.insert(i * 10);
  }
  arr.print();

  arr.remove();
  arr.remove();

  std::cout << "Check : " << std::boolalpha << arr.search(50) << '\n';
  std::cout << "Check : " << std::boolalpha << arr.search(999) << '\n';
  arr.print();
  return 0;
}
