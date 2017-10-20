//
// Created by Jan on 21.10.2017.
//

#include "MQTTException.h"

const char *MQTTException::what() {
    return ("MQTT Error - " + this->message).c_str();
}

MQTTException::MQTTException(string message) : message(message){

}
