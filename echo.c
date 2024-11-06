#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 46645

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr;
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

   if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        close(server_fd);
        exit(1);
    }

    listen(server_fd, 1);
    printf("Server listening on %d...\n", PORT);

    while (1) {
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            perror("Connection accept failed");
            continue;
        }

        int bytes_read;
        while ((bytes_read = read(client_fd, buffer, sizeof(buffer))) > 0) {
            write(client_fd, buffer, bytes_read);
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
