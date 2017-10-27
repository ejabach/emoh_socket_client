//
// Created by Jan on 12.10.2017.
//

#include "Switch.h"

Switch::Switch(MQTTConnection *connection, string topic, string number) : Device(connection, std::move(topic)), number(std::move(number))
{
    if (this->rcSwitch == nullptr)
    {
        this->rcSwitch = new RCSwitch();
        this->rcSwitch->enableTransmit(GPIO_PIN);
    }

    this->mqttConnection->subscribe(topic, this, (void (Device::*)(const string, const string))Switch::handleMessageArrived);
}

void Switch::handleMessageArrived(const string topic, const string payload)
{
    if (payload == ACTION_TOGGLE)
    {
        this->toggle();
    }
    else if (payload == ACTION_TURNON)
    {
        this->turnOn();
    }
    else if (payload == ACTION_TURNOFF)
    {
        this->turnOff();
    }
    else
    {
        this->mqttConnection->printError("Undefined action: " + payload);
    }
}

void Switch::toggle()
{
    this->mqttConnection->publish("/emoh/debug", "RECEIVED TOGGLE REQUEST");
}

void Switch::turnOn()
{
    this->mqttConnection->publish("/emoh/debug", "RECEIVED TURNON REQUEST");
    this->rcSwitch->switchOn(SWITCH_GROUP, this->number);
}

void Switch::turnOff()
{
    this->mqttConnection->publish("/emoh/debug", "RECEIVED TURNOFF REQUEST");
    this->rcSwitch->switchOff(SWITCH_GROUP, this->number);
}