List: test_list.c IList.c IList.h
	gcc -Wall -ansi -pedantic -o List test_list.c IList.c -I.
Point: Point.c IList.c IList.h
	gcc -Wall -ansi -pedantic -o Point Point.c IList.c -lm -I.