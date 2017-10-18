#include <iostream>

#include "Switch.h"
#include "MQTTConnection.h
#include "mqtt_credentials.h"

const Switch sockets[] = {
    Switch("/emoh/living_room/sockets", "Living Room", 0001)
};



int main() {
    std::cout << "Starting EMOH Switch Client..." << std::endl;

    MQTTConnection mqtt(MQTT_HOST, MQTT_ID);


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