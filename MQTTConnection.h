//
// Created by Jan on 18.10.2017.
//

#ifndef EMOH_SOCKET_CLIENT_MQTTCONNECTION_H
#define EMOH_SOCKET_CLIENT_MQTTCONNECTION_H

#include <map>
#include <vector>
#include <include/MQTTClient.h>

#include "Device.h"
#include "mqtt_credentials.h"
#include "MQTTException.h"

using namespace std;

class Device;

class MQTTConnection {

private:
    /**
     * Hash that maps the subscription topics to a dynamic array of pairs, containing a reference to the object
     * and its callback function.
     */
    map<string, vector<pair<Device*, void (Device::*)(const string, const string)>>> callbacks;

    /**
     * Internal function that calls all registered callback functions as soon as a message arrives on the corresponding
     * topic.
     * @param context
     * @param topic
     * @param topicLen
     * @param message
     * @return
     */
    int messageArrived(void *context, char *topic, int topicLen, MQTTClient_message *message);

    /**
     * Internal handler for the case that the connection is lost
     * @param context
     * @param cause
     */
    void static connectionLost(void *context, char *cause);

    int static subscribePlaceholder(void* context, char* topic, int topicLen, MQTTClient_message* msg);

    /**
     * Real connection struct
     */
    MQTTClient client;

public:
    /**
     * Enum that holds the possible persistence options.
     */
    enum Persistence
    {
        DEFAULT = MQTTCLIENT_PERSISTENCE_DEFAULT,
        NONE    = MQTTCLIENT_PERSISTENCE_NONE
    };

    /**
     * Constructs a MQTTConnection object
     * @param address  The hostname of the MQTT Broker
     * @param id The Client ID
     * @param persistence States if and how messages are stored in case of power loss
     */
    MQTTConnection(string address, string id, Persistence persistence = DEFAULT);

    /**
     * Closes the MQTT connection
     */
    ~MQTTConnection();

    /**
     * Let a device subscribe to a new topic.
     * As soon as a message arrives at given topic, the correpsonding callback function is called.
     * @param topic
     * @param context
     * @param callback
     */
    void subscribe(string topic, Device *context, void (Device::*callback)(const string, const string));

    /**
     * Published the given payload on the specified topic.
     * @param topic
     * @param payload
     */
    void publish(string topic, string payload);

    /**
     * Prints the given error on the /emoh/error topic.
     * @param error
     */
    void printError(string error);
};


#endif //EMOH_SOCKET_CLIENT_MQTTCONNECTION_H
