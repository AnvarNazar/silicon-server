//
// Created by anvar on 27/12/19.
//

#ifndef SILICON_SERVER_H
#define SILICON_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "SiliconException.h"
#include "ExceptionCodes.h"

namespace si {
    class Server {
    public:
        Server(int portNo, int64_t bufferSize);

        virtual ~Server();

    private:
        socklen_t _client_address_length{};
        sockaddr_in _server_address{};

        sockaddr_in _client_address{};
        int _server_socket;
        int _client_socket;
        int _port_no;

        int64_t _buffer_size;
    protected:
        char *buffer;
    public:
        void listen();

        virtual char *process_Request() = 0;
    };
}


#endif //SILICON_SERVER_H
