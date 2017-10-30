cmake_minimum_required(VERSION 3.6)
project(CPP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    include/MQTTAsync.h
    include/MQTTClient.h
    include/MQTTClientPersistence.h
    lib/paho-mqtt3a.dll
    lib/paho-mqtt3a.exp
    lib/paho-mqtt3a.lib
    lib/paho-mqtt3a.pdb
    lib/paho-mqtt3as.dll
    lib/paho-mqtt3as.exp
    lib/paho-mqtt3as.lib
    lib/paho-mqtt3c.dll
    lib/paho-mqtt3c.exp
    lib/paho-mqtt3c.lib
    lib/paho-mqtt3c.pdb
    lib/paho-mqtt3cs.dll
    lib/paho-mqtt3cs.exp
    lib/paho-mqtt3cs.lib)

add_executable(CPP ${SOURCE_FILES})