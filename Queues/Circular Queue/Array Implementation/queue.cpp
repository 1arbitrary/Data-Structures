#include <iostream>
#include <stdexcept>

template <typename T> struct Queue
{
  static constexpr std::size_t MAX_SIZE = 10;
  T elements[MAX_SIZE];
  std::size_t occupied_indexes = 0;
  int front = -1;
  int rear = -1;

  Queue () = default;

  Queue (const Queue &) = delete;
  Queue &operator= (const Queue &) = delete;

  bool
  is_full () const
  {
    return occupied_indexes == MAX_SIZE;
  }

  bool
  is_empty ()
  {
    return occupied_indexes == 0;
  }

  void
  enqueue (T data)
  {
    if (is_full ())
      {
        throw std::out_of_range ("Attempt To Insert On An Already Filled Queue !");
      }
    if (is_empty ())
      {
        front++;
      }
    elements[++rear] = data;
    occupied_indexes++;
  }

  T
  dequeue ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Dequeue On An Empty Queue !");
      }
    occupied_indexes--;
    return elements[front++];
  }

  T
  get_front () const
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Access The Front Of An Empty Queue !");
      }
    return elements[front];
  }

  void
  print ()
  {
    std::cout << "Queue : ";
    if (is_empty ())
      {
        std::cerr << "Empty Queue !" << '\n';
        return;
      }
    
    int i{ 0 };
    while (i <= rear)
      {
        std::cout << elements[i++] << '\t';
      }
    std::cout << '\n';
  }
};

int
main (void)
{
  return 0;
}
