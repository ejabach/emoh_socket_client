//
// Created by Jan on 18.10.2017.
//

#ifndef EMOH_SOCKET_CLIENT_MQTTCONNECTION_H
#define EMOH_SOCKET_CLIENT_MQTTCONNECTION_H

#include <map>
#include <include/MQTTClient.h>

enum MQTTConnection_Persistence
{
    DEFAULT = MQTTCLIENT_PERSISTENCE_DEFAULT,
    NONE    = MQTTCLIENT_PERSISTENCE_NONE
};

class MQTTConnection {
private:
    std::map callbacks<const char*, void *(const char*)[]>;
    int messageArrived(void *context, char *topic, int topicLen, MQTTClient_message *message);

public:
    /**
     * Constructs a MQTTConnection object
     * @param address  The hostname of the MQTT Broker
     * @param id The Client ID
     * @param persistence States if and how messages are stored in case of power loss
     */
    MQTTConnection(const char* address, const char* id, MQTTConnection_Persistence persistence = DEFAULT);

    void subscribe(const char* topic, void *callback(const char*));
    void publish(const char* topic, const char* payload);
};


#endif //EMOH_SOCKET_CLIENT_MQTTCONNECTION_H
