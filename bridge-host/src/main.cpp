#include <iostream>

#include "BridgeProperties.h"
#include "Bridge.h"

int main(int argc, char* argv[]) {
    boost::asio::io_service main;
    boost::asio::signal_set signals(main, SIGINT, SIGTERM, SIGQUIT);
    signals.async_wait([](const boost::system::error_code &error, int signalNumber) {
        if (!error) {
            // A signal occurred.
            std::cout << "Handle: " << signalNumber;
        }
    });

    BridgeProperties props{"ya.ru", 80, "/dev/cu.usbserial-1410", 57600};

    Bridge bridge(props);
    bridge.start();

    main.run();

    bridge.stop();

    return 0;
}