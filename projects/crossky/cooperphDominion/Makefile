CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

cardtest1.out: cardtest1.c dominion.c rngs.c
	echo “Results of running cardtest1.out:” > cardtest1.out
	gcc -o cardtest1 cardtest1.c dominion.c rngs.c $(CFLAGS)
	cardtest1 >> cardtest1.out
	gcov -b -f dominion.c >> cardtest1.out

cardtest2.out: cardtest2.c dominion.c rngs.c
	echo “Results of running cardtest2.out:” > cardtest2.out
	gcc -o cardtest2 cardtest2.c dominion.c rngs.c $(CFLAGS)
	cardtest2 >> cardtest2.out
	gcov -b -f dominion.c >> cardtest2.out

randomtestcard1.out: randomtestcard1.c dominion.c rngs.c
	echo “Results of running randomtestcard1.out:” > randomtestcard1.out
	gcc -o randomtestcard1 randomtestcard1.c dominion.c rngs.c $(CFLAGS)
	randomtestcard1 >> randomtestcard1.out
	gcov -b -f dominion.c >> randomtestcard1.out
	
randomtestadventurer.out: randomtestadventurer.c dominion.c rngs.c
	echo “Results of running randomtestadventurer.out:” > randomtestadventurer.out
	gcc -o randomtestadventurer randomtestadventurer.c dominion.c rngs.c $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	gcov -b -f dominion.c >> randomtestadventurer.out 

all: randomtestcard1.out randomtestadventurer.out cardtest1.out cardtest2.out

clean:
	rm -f *.o playdom player cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 randomtestcard1 randomtestcard2 randomtestadventurer *.gcov *.gcda *.gcno *.so *.out
