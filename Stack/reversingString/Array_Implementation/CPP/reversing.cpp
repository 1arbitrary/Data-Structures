#include <iostream>
#include <iterator>
#include <stdexcept>
#define MAX_SIZE 101

template <typename T> struct Stack
{
  int top = -1;
  T elements[MAX_SIZE] = {};

  Stack () = default;

  Stack (const Stack &) = delete;
  Stack &operator= (const Stack &) = delete;

  bool
  isEmpty () const
  {
    return top == -1;
  }

  bool
  isFull () const
  {
    return top == MAX_SIZE - 1;
  }

  void
  push (T data)
  {
    if (!isFull ())
      {
        std::clog << "Adding Element : " << data << "\n";
        elements[++top] = data;
      }
    else
      {
        std::cerr << "Stack is already full !" << "\n";
      }
  }

  void
  pop ()
  {
    if (!isEmpty ())
      {
        std::clog << "Popping element : " << elements[top] << "\n";
        --top;
      }
    else
      {
        std::cerr << "Attempt to pop an empty Stack !" << "\n";
      }
  }

  T
  peek () const
  {
    if (isEmpty ())
      {
        throw std::out_of_range ("Stack is Empty");
      }
    return elements[top];
  }

  void
  reverse ()
  {
    if (!isEmpty ())
      {
	// tbd
      }
    else
      {
        std::cerr << "Trying to reverse an empty stack" << "\n";
      }
  }

  void
  print () const
  {
    int i{ top };
    std::cout << "Stack : ";
    while (i >= 0)
      {
        std::cout << elements[i--] << "\t";
      }
    std::cout << "\n";
  }
};

int
main (void)
{
  Stack<std::string> st;
  st.push ("H");
  st.push ("E");
  st.push ("L");
  st.push ("L");
  st.push ("O");
  st.print ();
  st.reverse ();
  st.print ();
  return 0;
}
