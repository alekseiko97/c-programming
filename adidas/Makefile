CFLAGS=-Wall -Werror -Iproduct

#add your own other c files here
SHARED=	file_helper.c\
		binary_helper.c
	                         
all: 
	gcc $(CFLAGS) encode.c $(SHARED) -o encode 
	gcc $(CFLAGS) channel.c $(SHARED) -o channel 
	gcc $(CFLAGS) decode.c $(SHARED) -o decode 
clean:
	rm -rf administrationTest $(PN) 

valgrind: 
	valgrind ./$(PN)

.PHONY: clean test valgrind
