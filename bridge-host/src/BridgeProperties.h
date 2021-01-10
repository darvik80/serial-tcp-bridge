//
// Created by Ivan Kishchenko on 01.01.2021.
//

#ifndef ROVER_BRIDGEPROPERTIES_H
#define ROVER_BRIDGEPROPERTIES_H


struct BridgeProperties {
    std::string host;
    int port;

    std::string portName;
    int baudRate{57600};
};


#endif //ROVER_BRIDGEPROPERTIES_H
