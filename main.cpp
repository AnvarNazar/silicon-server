#include <iostream>
#include "Server.h"

void process_data(char *buffer);

int main() {
    sc::Server server(6868, 1024 * 8);

    try {
        server.listen(process_data);
    } catch (sc::SiliconException &exception) {
        std::cout << exception.what() << std::endl;
    }

    return 0;
}

void process_data(char *buffer) {
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n%s", buffer);
}

