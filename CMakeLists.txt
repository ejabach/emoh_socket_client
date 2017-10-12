cmake_minimum_required(VERSION 3.7)
project(Emoh_Socket_Client)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        libs/mqtt/include/MQTTClient.h
        libs/mqtt/lib/paho-mqtt3a.dll
        libs/mqtt/lib/paho-mqtt3a.exp
        libs/mqtt/lib/paho-mqtt3a.lib
        libs/mqtt/lib/paho-mqtt3a.pdb
        libs/mqtt/lib/paho-mqtt3as.dll
        libs/mqtt/lib/paho-mqtt3as.exp
        libs/mqtt/lib/paho-mqtt3as.lib
        libs/mqtt/lib/paho-mqtt3c.dll
        libs/mqtt/lib/paho-mqtt3c.exp
        libs/mqtt/lib/paho-mqtt3c.lib
        libs/mqtt/lib/paho-mqtt3c.pdb
        libs/mqtt/lib/paho-mqtt3cs.dll
        libs/mqtt/lib/paho-mqtt3cs.exp
        libs/mqtt/lib/paho-mqtt3cs.lib

        main.cpp
        Socket.cpp
        Socket.h
        )

add_executable(Emoh_Socket_Client ${SOURCE_FILES})

include_directories()