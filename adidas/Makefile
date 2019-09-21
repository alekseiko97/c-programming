PN=encode

CFLAGS=-Wall -Werror -Iproduct

#add your own other c files here
SHARED=	file_helper.c
	                         
all: 
	gcc $(CFLAGS) $(PN).c $(SHARED) -o $(PN) 

clean:
	rm -rf administrationTest $(PN) 

valgrind: 
	valgrind ./$(PN)



.PHONY: clean test valgrind
