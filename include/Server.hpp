#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include "Client.hpp"
#include "CHeaders.h"

class Server
{
private:
    std::vector<Client> _clients;
    struct sockaddr_in6 _address;
    int                 _fd;
    int                 _port;
    std::string         _pass;
    char                _buffer[BUFF_SIZE];
public:
    Server();
    Server(char **argv);
    Server(const Server &copy);
    Server &operator=(const Server &copy);
    ~Server();

    void    serverInit(char **argv);

    class InvalidParam : public std::exception
    {
    private:
        std::string _param;
        char*       _errorMessage;
    public:
        InvalidParam(const std::string &param);
        virtual ~InvalidParam() throw();
        virtual const char* what() const throw();
    };
};

#endif