//
// Created by Jan on 18.10.2017.
//

#include <include/MQTTClient.h>
#include "MQTTConnection.h"

void MQTTConnection::printError(const string message) {
    this->publish("/emoh/error/", message);
}

void MQTTConnection::subscribe(const string topic, Device *context, void (*callback)(const string, const string)) {
    if (! this->callbacks[topic])
    {
        this->callbacks[topic] = pair(context, callback);
    }
    else
    {
        this->callbacks[topic] += pair(context, callback);
    }
}

void MQTTConnection::publish(string topic, string payload) {

}

MQTTConnection::MQTTConnection(string address, string id, MQTTConnection::Persistence persistence)
{
    this->client = MQTTClient();

    MQTTClient_connectOptions options = MQTTClient_connectOptions_initializer

    int persistence_transl = MQTTCLIENT_PERSISTENCE_NONE;
    if (persistence == Persistence::DEFAULT)
    {
        persistence_transl = MQTTCLIENT_PERSISTENCE_DEFAULT;
    }

    MQTTClient_create(&this->client, MQTT_HOST, MQTT_ID,
                      persistence_transl, NULL);
    options.keepAliveInterval = 20;
    options.cleansession = 1;

    MQTTClient_setCallbacks(client, this, connectionLost, messageArrived, NULL);

    if (MQTTClient_connect(this->client, &options) != MQTTCLIENT_SUCCESS)
    {
        throw MQTTException("Couldn't establish connection.");
    }
}

MQTTConnection::~MQTTConnection() {
    MQTTClient_disconnect(this->client, 100000);
    MQTTClient_destroy(&this->client);
}

int MQTTConnection::messageArrived(void *context, char *topic, int topicLen, MQTTClient_message *message) {
    string topicStr = string(topic);
    auto keySearch = this->callbacks.find(topicStr);
    if (keySearch != this->callbacks.end())
    {
        Device *device = keySearch->second->first;
        auto callback = keySearch->second->second;
        device->(callback)(topic, message->payload);
    }
    else
    {
        throw MQTTException("No subscription found for topic "+topicStr);
    }
    return 1;
}

void MQTTConnection::connectionLost(void *context, char *cause) {
    throw MQTTException("Connection loss, cause: " + string(cause));
}
