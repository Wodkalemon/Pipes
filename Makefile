CC = gcc
CFLAGS = -Wall -Wextra -pedantic

SRC=src/
BIN=bin/
LIBDIR=lib/
LIB = -L$(LIBDIR) -lsem
PROG1 = sig_empf1
PROG2 = sig_sender
PROG3 = sig_empf2
PROG4 = sig_empf3
PROG5 = erzeug
PROG6 = verbr
PROG7 = erzeug_nonBlock
PROG8 = semcreate
PROG9 = anonymePipe
PROG10 = semdelete

all:
		make $(PROG1);
		make $(PROG2);
		make $(PROG3);
		make $(PROG4);
		make $(PROG5);
		make $(PROG6);
		make $(PROG7);
		make $(PROG8);
		make $(PROG9);
		make $(PROG10);

$(PROG1): 	$(SRC)$(PROG1).c
			$(CC) $(CFLAGS) -o $(BIN)$@ $(SRC)$(PROG1).c

$(PROG2): 	$(SRC)$(PROG2).c
			$(CC) $(CFLAGS) -o $(BIN)$@ $(SRC)$(PROG2).c

$(PROG3): 	$(SRC)$(PROG3).c
			$(CC) $(CFLAGS) -o $(BIN)$@ $(SRC)$(PROG3).c

$(PROG4): 	$(SRC)$(PROG4).c
			$(CC) $(CFLAGS) -o $(BIN)$@ $(SRC)$(PROG4).c 

$(PROG5): 	$(SRC)$(PROG5).c
			$(CC) $(CFLAGS) -o $(BIN)$@ $(SRC)$(PROG5).c $(LIB)

$(PROG6): 	$(SRC)$(PROG6).c
			$(CC) $(CFLAGS) -o $(BIN)$@ $(SRC)$(PROG6).c

$(PROG7): 	$(SRC)$(PROG7).c
			$(CC) $(CFLAGS) -o $(BIN)$@ $(SRC)$(PROG7).c 

$(PROG8): 	$(SRC)$(PROG8).c
			$(CC) $(CFLAGS) -o $(BIN)$@ $(SRC)$(PROG8).c $(LIB)

$(PROG9): 	$(SRC)$(PROG9).c
			$(CC) $(CFLAGS) -o $(BIN)$@ $(SRC)$(PROG9).c $(LIB)

$(PROG10): 	$(SRC)$(PROG10).c
			$(CC) $(CFLAGS) -o $(BIN)$@ $(SRC)$(PROG10).c $(LIB)

clean:
		rm -f $(PROG1);
		rm -f $(PROG2);
		rm -f $(PROG3);
		rm -f $(PROG4);
		rm -f $(PROG5);
		rm -f $(PROG6);
		rm -f $(PROG7);
		rm -f $(PROG8);
		rm -f $(PROG9);
		rm -f $(PROG10);
