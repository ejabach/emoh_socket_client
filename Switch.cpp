//
// Created by Jan on 12.10.2017.
//

#include "Switch.h"
#include <iostream>

RCSwitch* Switch::rcSwitch = new RCSwitch();

Switch::Switch(MQTTConnection *connection, string topic, int number) : Device(connection, std::move(topic)), number(number)
{
}

void Switch::handleMessageArrived(const string /* topic */, const string payload)
{
    std::cout << "Received in Socket message handler" << std::endl;
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
    //Switch::rcSwitch->enableTransmit(GPIO_PIN);
    this->mqttConnection->publish("/emoh/debug", "RECEIVED TOGGLE REQUEST");
}

void Switch::turnOn()
{
    Switch::rcSwitch->enableTransmit(GPIO_PIN);
    this->mqttConnection->publish("/emoh/debug", "RECEIVED TURNON REQUEST");
    Switch::rcSwitch->switchOn(SWITCH_GROUP, this->number);
    rcSwitch->disableTransmit();
}

void Switch::turnOff()
{
    Switch::rcSwitch->enableTransmit(GPIO_PIN);
    this->mqttConnection->publish("/emoh/debug", "RECEIVED TURNOFF REQUEST");
    Switch::rcSwitch->switchOff(SWITCH_GROUP, this->number);
    rcSwitch->disableTransmit();
}