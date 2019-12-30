#include <iostream>
#include "Server.h"

class Application : public si::Server {
public:
    Application(int portNo, int64_t bufferSize) : Server(portNo, bufferSize) {

    }

private:
    char *process_Request() override {
        printf("%s\n", buffer);
        return buffer;
    }
};

int main() {
    Application *server;
    try {
        server = new Application(6868, 2014 * 2);
        server->listen();
    } catch (si::SiliconException &exception) {
        std::cout << exception.what() << std::endl;
    };
    return 0;
}
