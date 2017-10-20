#include <iostream>

#include "Switch.h"
#include "MQTTConnection.h

int main() {
    std::cout << "Starting EMOH Switch Client..." << std::endl;




    for (Switch socket : sockets)
    {
        std::cout << "Socket " << socket.getName() << std::endl;
        std::cout << "\tSubscribing to topics:'" << std::endl;
        for (auto topic : socket.getSubscriptions())
        {
            std::cout << '\t\t\'' << topic.first << '\'' << std::endl;
            mqtt.subscribe(topic.first, topic.second);
        }
    }

    return 0;
}