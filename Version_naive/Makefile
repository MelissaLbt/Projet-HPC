.SUFFIXES:.c .o
 
CC = gcc
 
SRCS = sd_naive.c \
       morpho_naive.c
 
OBJS = $(SRCS:.c=.o)
EXEC = main
 
start: $(OBJS)
	$(CC) -o $(EXEC) $(OBJS)
 
.c.o:
	$(CC) -Wall -g -o $@ -c $<
 
.PHONY: clean

clean:
	rm -f $(OBJS)
