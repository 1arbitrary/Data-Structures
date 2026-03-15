# Dynamic Array Implementation

* The array resizes whenever the number of stored elements reaches the current maximum capacity.
* Resizing is handled using a `resize()` function.
* In this implementation, memory is dynamically allocated because static arrays have a fixed size and cannot be resized.
* The dynamic array structure maintains a pointer to the dynamically allocated array.
* When resizing, a new array is allocated with twice the capacity of the previous array.
* Elements from the old array are copied into the new array.
* The old array is then deallocated, and the pointer maintained by the structure is updated to point to the newly resized array.
