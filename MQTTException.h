//
// Created by Jan on 21.10.2017.
//

#ifndef EMOH_SOCKET_CLIENT_MQTTEXCEPTION_H
#define EMOH_SOCKET_CLIENT_MQTTEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class MQTTException : public exception {
private:
    string message;
public:
    MQTTException(string message);

    const char* what() noexcept ;
};


#endif //EMOH_SOCKET_CLIENT_MQTTEXCEPTION_H
