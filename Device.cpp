//
// Created by Jan on 18.10.2017.
//

#include "Device.h"

Device::Device(MQTTConnection *mqttConnection, const string topic) : topic(topic) {
    this->mqttConnection = mqttConnection;

    this->mqttConnection->subscribe(this->topic, this, handleMessageArrived);
}