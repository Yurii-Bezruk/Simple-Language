translate: main.o parse.o commands.o
	gcc -o translate main.o parse.o commands.o
	rm *.o *.gch
	./translate --input test.simple --output test2.c
	more test2.c
main.o: main.c
	gcc -c main.c
parse.o: parse.h parse.c
	gcc -c parse.h parse.c
commands.o: commands.h commands.c
	gcc -c commands.h commands.c