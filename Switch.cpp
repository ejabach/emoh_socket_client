//
// Created by Jan on 12.10.2017.
//

#include "Switch.h"
#include <iostream>

RCSwitch Switch::rcSwitch = RCSwitch();

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
    //Switch::rcSwitch->disableTransmit();
}

void Switch::turnOn()
{
    Switch::rcSwitch.enableTransmit(GPIO_PIN);
    this->mqttConnection->publish("/emoh/debug", "RECEIVED TURNON REQUEST");
    cout << "Trying to turn on switch with group " << SWITCH_GROUP << " and number " << this->number << endl;
    Switch::rcSwitch.switchOn(const_cast<char *>(SWITCH_GROUP), this->number);
    //Switch::rcSwitch->disableTransmit();
}

void Switch::turnOff()
{
    Switch::rcSwitch.enableTransmit(GPIO_PIN);
    this->mqttConnection->publish("/emoh/debug", "RECEIVED TURNOFF REQUEST");
    Switch::rcSwitch.switchOff(SWITCH_GROUP, this->number);
    //Switch::rcSwitch->disableTransmit();
}