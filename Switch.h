//
// Created by Jan on 12.10.2017.
//

#ifndef EMOH_SOCKET_CLIENT_SOCKET_H
#define EMOH_SOCKET_CLIENT_SOCKET_H

#define ACTION_TOGGLE "toggle"
#define ACTION_TURNON "turnOn"
#define ACTION_TURNOFF "turnOff"

#include "libs/rcSwitch/RCSwitch.h"
#include "Device.h"

class Switch : public Device{

private:
    const char* name;
    const char* topic;
    int number;

public:
    Switch(const char *name, const char *path, int number);



    const char* getName();
    const char* getTopic();
    const int getNumber();

    void turnOn();
    void turnOff();
    void toggle();
};


#endif //EMOH_SOCKET_CLIENT_SOCKET_H
