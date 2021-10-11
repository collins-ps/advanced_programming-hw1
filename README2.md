# MPCS 51100 HW1
**Name**: Phoebe Collins, UCID: 12277438

## References
I did not use any references other than class materials.

## Shortcomings
I did not observe any compilation or run-time errors. The valgrind report for test_list.c and Point.c are clean.

The list implementation assumes that a list is initialised before it is passed to List methods; there is no error checking for this. I did however implement error checking for illegal actions such as removing an element from an empty list, inserting beyond the list's size, and accessing an element beyond the list's size.

## Compiling and running
`make List` and then `./List` 

`make Point` and then `./Point x`, where x is an integer of the number of Points user wants the list to contain.
