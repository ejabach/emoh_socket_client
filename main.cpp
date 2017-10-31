#include <iostream>

#include "Switch.h"
#include "defines.h"

using namespace std;

int main() {
    cout << "Starting EMOH Switch Client..." << endl;

    MQTTConnection *connection = nullptr;
    try {
        printf("Trying to connect to MQTT Broker:\n\tHOST:%s\n\tID:%s\n", MQTT_HOST, MQTT_ID);
        connection = new MQTTConnection(MQTT_HOST, MQTT_ID);
    }
    catch (MQTTException exception)
    {
        cout << "Error connection to MQTT: " + string(exception.what()) << endl;
        return 0;
    }
    cout << "Connected successfully!" << endl;

    Switch switches[] = { Switch(connection, SWITCH_TOPIC, 1) };

    cout << "Registered Switches: " << endl;
    for (Switch s : switches)
    {
        cout << s.getTopic() << endl;
    }

    connection->publish("/emoh/debug", "Testing publish...");

    cout << "Waiting for incoming requests..." << endl;
    cout << "Quit by pressing 'q' or 'Q'" << endl;
    int quit = getchar();
    while (! (quit == 'q' || quit == 'Q'))
    {
        quit = getchar();
    }

    return 0;
}