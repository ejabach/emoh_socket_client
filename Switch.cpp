//
// Created by Jan on 12.10.2017.
//

#include "Switch.h"
#include <iostream>
Switch::Switch(MQTTConnection *connection, string topic, int number) : Device(connection, std::move(topic)), number(number)
{

}

void Switch::handleMessageArrived(const string topic, const string payload)
{
    std::cout << "Received msg on topic" << topic << std::endl;
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
}

void Switch::turnOff()
{
    this->mqttConnection->publish("/emoh/debug", "RECEIVED TURNOFF REQUEST");
}