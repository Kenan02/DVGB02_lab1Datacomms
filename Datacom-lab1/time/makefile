CC=gcc
CFLAGS=-g -Og

all: client server

client: client.c
	$(CC) -o client client.c $(CFLAGS)


server: server.c
	$(CC) -o server server.c $(CFLAGS)

clean:
	rm server
	rm client