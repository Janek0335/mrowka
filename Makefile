CC:=cc

all: mrowka

mrowka: main.c matrix.c mrowka.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f mrowka
	rm -f *.o

.PHONY: all clean