//
// Created by anvar on 27/12/19.
//

#include <strings.h>
#include <cerrno>
#include <unistd.h>

#include "Server.h"

namespace sc {

    Server::Server(int portNo, int64_t bufferSize) : _port_no(portNo = 6868), _buffer_size(bufferSize = 1024 * 24) {
        _server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (_server_socket < 0) {
            throw SiliconException((char *) "failed to create linux socket", EXCEPTION_SOCKET_CREATION_FAILED);
        }
        bzero((char *) &_server_address, sizeof(_server_address));
        _server_address.sin_family = AF_INET;
        _server_address.sin_addr.s_addr = INADDR_ANY;
        _server_address.sin_port = htons(_port_no);

        if (bind(_server_socket, reinterpret_cast<const sockaddr *>(&_server_address), sizeof(_server_address)) < 0) {
            throw SiliconException("failed to bind socket", EXCEPTION_SOCKET_BINDING_FAILED);
        }
        buffer = new char[_buffer_size];
    }

    void Server::listen(void (*process_data)(char *)) {
        if (::listen(_server_socket, 5) < 0) {
            if (errno == EADDRINUSE) {
                throw SiliconException("port is already in use", EXCEPTION_PORT_NO_IN_USE);
            } else {
                throw SiliconException("failed to listen on socket", EXCEPTION_SOCKET_LISTEN_FAILED);
            }
        }
        _client_address_length = sizeof(_client_address);
        _client_socket = accept(_server_socket, reinterpret_cast<sockaddr *>(&_client_address),
                                &_client_address_length);
        if (_client_socket < 0) {
            throw SiliconException("accept connection from socket failed", EXCEPTION_SOCKET_ACCEPT_FAILED);
        }

        int socket_read = 0;
        do {
            socket_read = read(_client_socket, buffer, _buffer_size);
            process_data(buffer);
        } while (socket_read == 0);

        if (socket_read < 0) {
            throw SiliconException("failed read from client", EXCEPTION_SOCKET_READ_FAILED);
        }
    }

    Server::~Server() {
        delete[] buffer;
    }
}
