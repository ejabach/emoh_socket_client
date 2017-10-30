//
// Created by Jan on 18.10.2017.
//

#include <include/MQTTClient.h>
#include "MQTTConnection.h"


int MQTTConnection::subscribePlaceholder(void* context, char* topic, int topicLen, MQTTClient_message* msg)
{
    return static_cast<MQTTConnection*>(context)->messageArrived(context, topic, topicLen, msg);
}

void MQTTConnection::printError(const string message) {
    this->publish("/emoh/error/", message);
}

void MQTTConnection::subscribe(const string topic, Device *context, void (Device::*callback)(const string, const string)) {
    auto find = this->callbacks.find(topic);
    if (find == this->callbacks.end())
    {
        this->callbacks[topic] = vector<pair <Device*, void (Device::*)(const string, const string)>>();
    }
    this->callbacks[topic].emplace_back(pair <Device*, void (Device::*)(const string, const string)>(context, callback));
}

void MQTTConnection::publish(string topic, string payload) {
    cout << "Trying to publish message to topic: " << topic << endl;
    MQTTClient_message message = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token; // for QoS >= 1

    size_t payloadLen = payload.length();
    char *payloadPtr = (char*)malloc(payloadLen);

    if (*payloadPtr != nullptr)
    {
        payload.copy(payloadPtr, payloadLen);
        message.payload = payloadPtr;
        message.payloadlen = payloadLen;
        message.qos = 0; // TODO: Change soon
        message.retained = 0; // ?
        MQTTClient_publishMessage(this->client, topic.c_str(), &message, &token);
    }
}

void MQTTConnection::connectionLost(void *context, char *cause) {
    throw MQTTException("Connection loss, cause: " + string(cause));
}

MQTTConnection::MQTTConnection(string address, string id, MQTTConnection::Persistence persistence)
{
    this->client = MQTTClient();

    MQTTClient_connectOptions options = MQTTClient_connectOptions_initializer;

    int persistence_transl = MQTTCLIENT_PERSISTENCE_NONE;
    if (persistence == Persistence::DEFAULT)
    {
        persistence_transl = MQTTCLIENT_PERSISTENCE_DEFAULT;
    }

    MQTTClient_create(&this->client, address.c_str(), id.c_str(),
                      persistence_transl, nullptr);
    options.keepAliveInterval = 20;
    options.cleansession = 1;

    MQTTClient_setCallbacks(client, this, connectionLost, subscribePlaceholder, nullptr);

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
    std::cout << "Received message on topic" << topicStr <<std::endl;
    if (message->payload == nullptr)
    {
        throw MQTTException("Invalid payload");
    }
    string payload = string((char*)message->payload);
    auto keySearch = this->callbacks.find(topicStr);
    if (keySearch != this->callbacks.end())
    {
        vector<pair<Device*, void (Device::*)(const string, const string)>> vec = keySearch->second;
        Device *device = nullptr;
        for (pair <Device*, void (Device::*)(const string, const string)> p : vec)
        {
            device = p.first;
            auto callback = p.second;
            (device->*callback)(topic, payload);
        }
    }
    else
    {
        throw MQTTException("No subscription found for topic "+topicStr);
    }

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topic);

    return 1;
}
