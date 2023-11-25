#include <iostream>
#include "CHeaders.h"
#include "Numeric_Replies.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

// socket, close, setsockopt, getsockname,
// getprotobyname, gethostbyname, getaddrinfo,
// freeaddrinfo, bind, connect, listen, accept, htons,
// htonl, ntohs, ntohl, inet_addr, inet_ntoa, send,
// recv, signal, sigaction, lseek, fstat, kqueue, 
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << USAGE << std::endl;
        return 1;
    }

    // Extract the port number from command line arguments
    int port = std::stoi(argv[1]);
    // Create socket address structure
    struct sockaddr_in6 server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin6_family = AF_INET6;
    server_address.sin6_addr = in6addr_any;  // Listen on all available interfaces
    server_address.sin6_port = htons(port);

    // Create a socket that supports both IPv4 and IPv6
    int fd_server = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP);

    if (fd_server == -1)
    {
        // Handle error
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Bind the socket to the specified address and port
    if (bind(fd_server, (struct sockaddr*)&server_address, sizeof(server_address)) == -1)
    {
        // Handle error
        std::cerr << "Error binding socket" << std::endl;
        close(fd_server);
        return 1;
    }

    // Listen on the socket
    if (listen(fd_server, 10) == -1)
    {
        // Handle error
        std::cerr << "Error listening on socket" << std::endl;
        close(fd_server);
        return 1;
    }

    // The socket is now ready for incoming connections...
    while (true)
    {
        // Accept an incoming connection
        struct sockaddr_in6 client_address;
        socklen_t client_address_len = sizeof(client_address);
        int fd_client = accept(fd_server, (struct sockaddr*)&client_address, &client_address_len);

        if (fd_client == -1)
        {
            // Handle error
            std::cerr << "Error accepting connection" << std::endl;
            close(fd_server);
            return 1;
        }

        // Send a message to the client
        const char* message = "Hello Client!\n";
        int bytes_sent = send(fd_client, message, strlen(message), 0);

        if (bytes_sent == -1)
        {
            // Handle error
            std::cerr << "Error sending message to client" << std::endl;
            close(fd_server);
            close(fd_client);
            return 1;
        }

        // Receive a message from the client
        char buffer[80];
        int bytes_received = recv(fd_client, buffer, 80, 0);

        if (bytes_received == -1)
        {
            // Handle error
            std::cerr << "Error receiving message from client" << std::endl;
            close(fd_server);
            close(fd_client);
            return 1;
        }

        // Make sure the message is null terminated
        buffer[bytes_received] = '\0';
        std::cout << "Received: " << buffer << std::endl;

        // Close the connection
        close(fd_client);
    }
    return 0;
}
