CC = gcc
CFLAGS =-g -O0 -Wall -Werror
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXE =  codeurViterbi decodeurViterbi decodeurViterbiNoDigital

all: $(EXE)

%.o : %.c
	$(CC) $(CFLAGS) -c $<

codeurViterbi : codeurViterbi.o
	$(CC) $(CFLAGS) -o $@ $^

decodeurViterbi : decodeurViterbi.o
	$(CC) $(CFLAGS) -o $@ $^

decodeurViterbiNoDigital : decodeurViterbiNoDigital.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY : clean

clean:
	rm -f $(EXE) $(OBJ)
