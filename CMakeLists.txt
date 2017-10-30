cmake_minimum_required(VERSION 3.6)
project(Emoh_Socket_Client)

set(CMAKE_CXX_STANDARD 14)

set(MQTT libs/mqtt)
set(RC_SWITCH libs/rcSwitch)

include_directories(${MQTT} ${RC_SWITCH})

set(EXECUTABLES
        main.cpp
        Switch.cpp
        Switch.h
        defines.h
        mqtt_credentials.h
        MQTTConnection.cpp
        MQTTConnection.h
        Device.cpp
        Device.h
        MQTTException.cpp
        MQTTException.h
        )

set(LIBRARIES
        #${WIRING_PI}/wiringPi.h
        #${WIRING_PI}/wiringPi.c

        ${RC_SWITCH}/RCSwitch.cpp
        ${RC_SWITCH}/RCSwitch.h
        )

link_directories(
        libs/mqtt
        libs/rcSwitch
        )

add_executable(emoh ${EXECUTABLES})
add_library(libs ${LIBRARIES})

target_link_libraries(emoh
        wiringPi

        MQTTClient.h
        MQTTClientPersistence.h
        paho-mqtt3a.dll
        paho-mqtt3a.exp
        paho-mqtt3a.lib
        paho-mqtt3a.pdb
        paho-mqtt3as.dll
        paho-mqtt3as.exp
        paho-mqtt3as.lib
        paho-mqtt3c.dll
        paho-mqtt3c.exp
        paho-mqtt3c.lib
        paho-mqtt3c.pdb
        paho-mqtt3cs.dll
        paho-mqtt3cs.exp
        paho-mqtt3cs.lib)