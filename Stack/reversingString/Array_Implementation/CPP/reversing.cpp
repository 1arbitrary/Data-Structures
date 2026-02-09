#include <iostream>
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
        elements[++top] = data;
      }
    else
      {
        std::cerr << "Stack is already full !" << "\n";
      }
  }

  T
  pop ()
  {
    if (!isEmpty ())
      {
        return elements[top--];
      }
    else
      {
        std::cerr << "Attempt to pop an empty Stack !" << "\n";
        throw std::out_of_range ("empty list");
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
        T result_arr[MAX_SIZE] = {};
        int i{ 0 };
        while (top > -1)
          {
            T temp = pop ();
            result_arr[i++] = temp;
          }

        int j{ 0 };
        while (j <= i - 1)
          {
            push (result_arr[j++]);
          }
      }
    else
      {
        throw std::out_of_range ("Attempt To Reverse An Empty Stack ");
      }
  }

  void
  print () const
  {
    int i{ 0 };
    std::cout << "Stack : ";
    while (i <= top)
      {
        std::cout << elements[i++] << "\t";
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
