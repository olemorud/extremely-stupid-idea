
#include "config.h"
#include "die.h"
#include "payload_blob.h" // defines binary_data[]

#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    int new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUF_SIZE] = {0};

    // Creating socket file descriptor
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
        die("socket failed");;

    // Forcefully attaching socket to the port 8080
    int opt = 1;
    int ok = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
            &opt, sizeof opt);
    if (ok == -1) die("setsockopt");;

    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    if (ok == -1) die("bind failed");

    ok = listen(server_fd, 3);
    if (ok == -1) die("listen");

    while (1) {
        ssize_t n;
        new_socket = accept(server_fd, (struct sockaddr*)&address,
                (socklen_t*)&addrlen);
        if (new_socket == -1) die("accept");

        n = read(new_socket, buffer, BUF_SIZE);
        if (n == -1) die("read");

        n = write(new_socket, binary_data, sizeof binary_data);
        if (n == -1) die("write");

        ok = close(new_socket);
        if (ok == -1) die("close");
    }

    return EXIT_SUCCESS;
}

