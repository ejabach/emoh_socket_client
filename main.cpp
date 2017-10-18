#include <iostream>
#include <include/MQTTClientPersistence.h>
#include <include/MQTTClient.h>

#include "Socket.h"
#include "mqtt_connection.h"


#define NUMBER_OF_SOCKETS 1
#define

const Socket sockets[NUMBER_OF_SOCKETS] = {
    Socket("/emoh/living_room/sockets", "Living Room", 0001)
};



int main() {
    std::cout << "Starting EMOH Socket Client...\n" << std::endl;

    MQTTClient client;
    MQTTClient_connectOptions options = MQTTClient_connectOptions_initializer;

    MQTTClient_create(&client, MQTT_HOST, MQTT_ID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    for (int i = 0; i < NUMBER_OF_SOCKETS; i++)
    {
        Socket curr = sockets[i];
        std::cout << "\t(" << i << ") " << curr.getName() << "\n" << std::endl;


    }

    return 0;
}