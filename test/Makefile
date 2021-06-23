all:	main
main:	main.o weightedGraphlib.o mylib.o
		gcc -g -o main main.o weightedGraphlib.o mylib.o libfdr.a -lm
main.o:	main.c 
	gcc -g -I/ -c main.c -lm
weightedGraphlib.o:	weightedGraphlib.c
	gcc -g -I/ -c weightedGraphlib.c -lm
mylib.o: mylib.c
	gcc -g -I/ -c mylib.c -lm
clean:	
	rm -f *.o *~
