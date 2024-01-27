
CC = gcc
CFLAGS = -ggdb -O0 -Wall -Wextra -Wno-unused-value

all : client server

client : client.c

server : server.c | payload_blob.h

%_blob.h : %.S | compile-blob.sh
	./compile-blob.sh $< > $@

.PHONY = clean
clean :
	rm client server *_blob.h 2>/dev/null || true


