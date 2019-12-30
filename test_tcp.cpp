

#include <netinet/in.h>
#include <netdb.h>
#include <cstdio>
#include <cstdlib>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

void error(const char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char **argv) {
    int csocket, portno, n;
    struct sockaddr_in server_address;
    struct hostent *server;

    char buffer[512];
    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    csocket = socket(AF_INET, SOCK_STREAM, 0);
    if (csocket < 0) {
        error("ERROR opening port");
    }
    server = gethostbyname(argv[1]);
    if (server == nullptr) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &server_address.sin_addr.s_addr,
          server->h_length);
    server_address.sin_port = htons(portno);
    if (connect(csocket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        error("ERROR connecting");
    }
    printf("Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    n = write(csocket, buffer, strlen(buffer));
    if (n < 0) {
        error("ERROR writing to socket");
    }
    bzero(buffer, 256);
    n = read(csocket, buffer, 255);
    if (n < 0) {
        error("ERROR reading from socket");
    }
    printf("%s\n", buffer);
    close(csocket);
    return 0;
}