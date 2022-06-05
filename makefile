all : exec

main.o : main.c 
	gcc -c main.c -o main.o

menu.o : menu.c 
	gcc -c menu.c -o menu.o

username.o : username.c 
	gcc -c username.c -o username.o

book.o : book.c 
	gcc -c book.c -o book.o

exec : main.o menu.o username.o book.o 
	gcc book.o main.o menu.o username.o -o exec

clean :
	rm -f *.o
	rm exec
	
