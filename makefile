kulkarniAnaghaA1: kulkarniAnaghaA1.o kulkarniAnaghaA1Main.o
	gcc kulkarniAnaghaA1.o kulkarniAnaghaA1Main.c -o kulkarniAnaghaA1 -lm
kulkarniAnaghaA1.o: kulkarniAnaghaA1.c givenA1.h helper.h
	gcc -Wall -std=c99 -c kulkarniAnaghaA1.c -lm
kulkarniAnaghaA1Main.o: kulkarniAnaghaA1Main.c givenA1.h helper.h
	gcc -Wall -std=c99 -c kulkarniAnaghaA1Main.c -lm
clean:
	rm *.o kulkarniAnaghaA1

