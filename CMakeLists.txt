cmake_minimum_required(VERSION 3.7)
project(Emoh_Socket_Client)

set(CMAKE_CXX_STANDARD 14)

set(WIRING_PI libs/wiringPi)
set(MQTT libs/mqtt)
set(RC_SWITCH libs/rcSwitch)

include_directories(${WIRING_PI} ${MQTT} ${RC_SWITCH})

set(EXECUTABLES
        main.cpp
        Socket.cpp
        Socket.h
        )

set(LIBRARIES
        ${WIRING_PI}/wiringPi.h
        ${WIRING_PI}/wiringPi.c

        ${MQTT}/include/MQTTClient.h
        ${MQTT}/lib/paho-mqtt3a.dll
        ${MQTT}/lib/paho-mqtt3a.exp
        ${MQTT}/lib/paho-mqtt3a.lib
        ${MQTT}/lib/paho-mqtt3a.pdb
        ${MQTT}/lib/paho-mqtt3as.dll
        ${MQTT}/lib/paho-mqtt3as.exp
        ${MQTT}/lib/paho-mqtt3as.lib
        ${MQTT}/lib/paho-mqtt3c.dll
        ${MQTT}/lib/paho-mqtt3c.exp
        ${MQTT}/lib/paho-mqtt3c.lib
        ${MQTT}/lib/paho-mqtt3c.pdb
        ${MQTT}/lib/paho-mqtt3cs.dll
        ${MQTT}/lib/paho-mqtt3cs.exp
        ${MQTT}/lib/paho-mqtt3cs.lib

        ${RC_SWITCH}/RCSwitch.cpp
        ${RC_SWITCH}/RCSwitch.h
        )

add_executable(emoh ${EXECUTABLES})
add_library(libs ${LIBRARIES})

#target_link_libraries(emoh ${WIRING_PI} ${MQTT} ${RC_SWITCH})