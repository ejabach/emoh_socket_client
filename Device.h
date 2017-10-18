//
// Created by Jan on 18.10.2017.
//

#ifndef EMOH_SOCKET_CLIENT_DEVICE_H
#define EMOH_SOCKET_CLIENT_DEVICE_H

#include <map>

class Device {
private:
    virtual std::map<const char*, void *(const char*)> subscriptions;
public:
    virtual std::map<const char*, void *(const char*)> getSubscriptions();
};


#endif //EMOH_SOCKET_CLIENT_DEVICE_H
