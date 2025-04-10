#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

// Read text from socket and print it out. Continue until socket closes.
// Return nonzero if the client sent a quit message, zero otherwise.
int server(int client_socket) {
    while (1) {
        int length;
        char* text;
        
        // Read the length of the text message from the socket.
        // If read returns 0, it means the client closed the connection.
        if (read(client_socket, &length, sizeof(length)) == 0)
            return 0;

        // Allocate a buffer to hold the text.
        text = (char*) malloc(length);

        // Read the text itself and print it.
        read(client_socket, text, length);
        printf("%s\n", text);

        // If the client sent the message "quit", we're done.
        if (strcmp(text, "quit") == 0)
            return 1;

        // Free the buffer.
        free(text);

        }
    return 0;
}

int main(int argc, char* const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <socket_name>\n", argv[0]);
        return 1;
    }
    
    const char* const socket_name = argv[1];
    int socket_fd;
    struct sockaddr_un name;
    int client_sent_quit_message;

    // Create the socket.
    socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("socket");
        return 1;
    }

    // Indicate that this is a server.
    name.sun_family = AF_LOCAL;
    strncpy(name.sun_path, socket_name, sizeof(name.sun_path) - 1);
    if (bind(socket_fd, (struct sockaddr*)&name, sizeof(name)) < 0) {
        perror("bind");
        return 1;
    }

    // Listen for connections.
    listen(socket_fd, 5);

    // Repeatedly accept connections, spinning off one server() to deal with
    // each client. Continue until a client sends a "quit" message.
    do {
        struct sockaddr_un client_name;
        socklen_t client_name_len = sizeof(client_name);
        int client_socket_fd;

        /// If the client sent the message "quit", we're done.
        if (strcmp(text, "quit") == 0)
            return 1;
/ Accept a connection.
        client_socket_fd = accept(socket_fd, (struct sockaddr*)&client_name, &client_name_len);
        if (client_socket_fd < 0) {
            perror("accept");
            continue;
        }

        // Handle the connection.
        client_sent_quit_message = server(client_socket_fd);

        // Close our end of the connection.
        close(client_socket_fd);
    } while (!client_sent_quit_message);

    // Remove the socket file.
    unlink(socket_name);

    return 0;
}

