# Homework 1

Generalize our list of integers to a list of arbitrary type; i.e., a single instance of the List can only store one type, but that type can be anything — list of `int`, `char *`, `Point`, `float`, or anything else. Implement at minimum the same functions that we implemented for the final version of the integer list. Note that this will require adding some additional function pointers to your list type — e.g. `tostr()` (to specify how the given object is printed) and `destroy()` (to specify how to deallocate the memory of the object), possibly among others. You have a lot of latitude to follow your own design ideas. While you are free to look up any aspect of the language or related topics, do not copy a published list implementation — it’s important to think through the exercise on your own. You are free to discuss ideas with other students, or us.

Once the list is complete and tested, use it to replace the array data structure in the Point.c class example. Devise a meaningful performance comparison of an operation that iterates over all elements of the array to one that iterates over all elements of the list. 

# Submission Requirements

Include a README with your name, a list of any references you used, and a discussion of any shortcomings your code may have. You should also include a Makefile and provide instructions for compiling and running your code. Your code must compile using gcc with the following flags: gcc -Wall -ansi -pedantic.  Note that this does not allow support for C99 or C11 language features.
