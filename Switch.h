//
// Created by Jan on 12.10.2017.
//

#ifndef EMOH_SOCKET_CLIENT_SOCKET_H
#define EMOH_SOCKET_CLIENT_SOCKET_H

#define ACTION_TOGGLE "toggle"
#define ACTION_TURNON "turnOn"
#define ACTION_TURNOFF "turnOff"

#include <RCSwitch.h>
#include "Device.h"

class Switch : public Device
{

private:
    int number;
    void handleMessageArrived(const string topic, const string payload) override;

public:
    Switch(MQTTConnection *connection, string topic, int number);

    void turnOn();
    void turnOff();
    void toggle();
};


#endif //EMOH_SOCKET_CLIENT_SOCKET_H
