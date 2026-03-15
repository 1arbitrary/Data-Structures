#include <iostream>
#include <stdexcept>

template <typename T> struct Deque
{
  static constexpr int MAX_SIZE = 10;
  T elements[MAX_SIZE];
  int front = 0;
  int rear = -1;
  int occupied_indexes = 0;

  bool
  is_full () const
  {
    return occupied_indexes == MAX_SIZE;
  }

  bool
  is_empty () const
  {
    return occupied_indexes == 0;
  }

  void
  enqueue (T data)
  {
    if (is_full ())
      {
        throw std::out_of_range ("Attempt To Enqueue On An Already Filled Deque !");
      }
    rear = (rear + 1) % MAX_SIZE;
    elements[rear] = data;
    occupied_indexes++;
  }

  void
  insert_front (T data)
  {
    if (is_full ())
      {
        throw std::out_of_range ("Attempt To Insert At The Front Of An Already Filled Deque !");
      }

    if (is_empty ())
      {
        elements[front] = data;
        occupied_indexes++;
        return;
      }
    front = (front - 1 + MAX_SIZE) % MAX_SIZE;
    elements[front] = data;
    occupied_indexes++;
  }

  T
  delete_rear ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Delete At The Rear Of An Empty Deque !");
      }

    T element_to_be_deleted = elements[rear];
    rear = (rear - 1 + MAX_SIZE) % MAX_SIZE;
    occupied_indexes--;
    return element_to_be_deleted;
  }

  T
  dequeue ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Dequeue On An Empty Deque !");
      }

    T deleted_element = elements[front];
    front = (front + 1) % MAX_SIZE;
    occupied_indexes--;
    return deleted_element;
  }

  T
  get_front () const
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Access Front Element Of An Empty Deque !");
      }
    return elements[front];
  }

  T
  get_rear () const
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Access Rear Element Of An Empty Deque !");
      }
    return elements[rear];
  }

  void
  print () const
  {
    std::cout << "Deque : ";
    if (is_empty ())
      {
        std::cerr << "Empty Deque !" << '\n';
        return;
      }

    int elements_to_be_printed{ occupied_indexes };
    int i{ front };
    while (elements_to_be_printed != 0)
      {
        std::cout << elements[i] << '\t';
        elements_to_be_printed--;
        i = (i + 1) % MAX_SIZE;
      }
    std::cout << '\n';
  }
};

int
main (void)
{
  Deque<int> d;
  d.enqueue (1000);

  int i = 1;
  while (!d.is_full ())
    {
      d.enqueue (i * 10);
      i++;
    }

  d.print ();

  for (int i = 1; i <= 10; i = i * 2)
    {
      d.dequeue ();
    }

  d.print ();
  d.insert_front (120);
  d.insert_front (130);
  d.insert_front (140);
  d.insert_front (150);
  d.print ();

  while (!d.is_empty ())
    {
      std::cout << "Deleted : " << d.delete_rear () << '\n';
    }

  d.print ();
  return 0;
}
