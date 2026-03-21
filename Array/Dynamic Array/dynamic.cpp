#include <iostream>
#include <stdexcept>

template <typename T> struct DynamicArray
{
  std::size_t arr_size = 10;
  T *elements = new T[arr_size];
  std::size_t occupied_indexes = 0;

  DynamicArray () = default;
  ~DynamicArray ()
  {
    delete[] elements;
  }

  DynamicArray (const DynamicArray &) = delete;
  DynamicArray &operator= (const DynamicArray &) = delete;

  bool
  is_full () const
  {
    return occupied_indexes == arr_size;
  }
  bool
  is_empty () const
  {
    return occupied_indexes == 0;
  }

  void
  resize ()
  {
    arr_size *= 2;
    T *new_array = new T[arr_size];
    std::copy (elements, elements + occupied_indexes, new_array);
    delete[] elements;
    elements = new_array;
  }

  void
  insert (T data)
  {
    if (is_full ())
      {
        resize ();
      }
    elements[occupied_indexes++] = data;
  }

  T
  remove ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Delete On An Empty Array !");
      }
    return elements[--occupied_indexes];
  }

  bool
  search (T data)
  {
    std::size_t i = 0;
    while (i < occupied_indexes)
      {
        if (elements[i] == data)
          {
            return true;
          }
        else
          {
            i++;
          }
      }
    return false;
  }

  void
  print () const
  {
    std::cout << "Array : ";
    if (is_empty ())
      {
        std::cerr << "Empty Dynamic Array" << '\n';
        return;
      }

    std::size_t i = 0;
    std::size_t elements_to_be_printed = occupied_indexes;
    while (elements_to_be_printed != 0)
      {
        std::cout << elements[i++] << '\t';
        elements_to_be_printed--;
      }
    std::cout << '\n';
  }
};

int
main (void)
{
  DynamicArray<int> arr;
  for (std::size_t i = 1; i <= 10; i++)
    {
      arr.insert (i * 10);
    }
  arr.print ();

  arr.remove ();
  arr.remove ();

  std::cout << "Check : " << std::boolalpha << arr.search (50) << '\n';
  std::cout << "Check : " << std::boolalpha << arr.search (999) << '\n';
  arr.print ();

  arr.insert (293);
  arr.insert (7777);
  arr.print ();

  arr.insert (2883);
  arr.insert (9999);
  arr.print ();
  return 0;
}
