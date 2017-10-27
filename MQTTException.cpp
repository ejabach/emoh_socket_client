//
// Created by Jan on 21.10.2017.
//

#include "MQTTException.h"

#include <utility>

const char *MQTTException::what() noexcept
{
    return ("MQTT Error - " + this->message).c_str();
}

MQTTException::MQTTException(string message) : message(std::move(message)){

}
