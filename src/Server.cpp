#include "Server.hpp"

void    Server::serverInit(char **argv)
{
    
}

Server::Server(char **argv)
{

}

Server::~Server()
{

}

Server::InvalidParam::InvalidParam(const std::string &param) : _param(param)
{
    _errorMessage = new char[100];
    strcpy(_errorMessage, "Error: bad input => ");
    strcat(_errorMessage, param.c_str());
}

Server::InvalidParam::~InvalidParam() throw()
{
    delete [] _errorMessage;
}

const char* Server::InvalidParam::what() const throw()
{
    return (_errorMessage);
}