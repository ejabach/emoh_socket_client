//
// Created by Jan on 18.10.2017.
//

#ifndef EMOH_SOCKET_CLIENT_DEVICE_H
#define EMOH_SOCKET_CLIENT_DEVICE_H

#include <map>
#include <string>
#include "MQTTConnection.h"

using namespace std;

class Device {
protected:
    const string topic;
    MQTTConnection *mqttConnection;

    virtual void handleMessageArrived(const string topic, const string payload) = 0;

public:
    Device(MQTTConnection *mqttConnection, const string topic);
};


#endif //EMOH_SOCKET_CLIENT_DEVICE_H
