CC = gcc
CFLAGS = -Wall
LDFLAGS = 
 
 SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
	AOUT = connect4.x
	 
all :	$(AOUT) clean 
connect4.x : $(OBJS)
		$(CC) $(LDFLAGS) -o $@ $^
%.o : %.c
		$(CC) $(CFLAGS) -o $@ -c $<
clean :
		@rm *.o
cleaner : clean
		@rm $(AOUT)
		@rm *.o
doxy :
	doxygen
latex : 
	cd doxygen/latex/
	make
	cd ..
	cd ..
