//
// Created by Ivan Kishchenko on 10.01.2021.
//

#ifndef BRIDGE_ARDUINO_BRIDGEENCODER_H
#define BRIDGE_ARDUINO_BRIDGEENCODER_H

#include "profile.h"
#include <BridgeMessage.h>

class BridgeEncoder {
public:
    void encode(Stream& stream, const BridgeMessage& message);
};


#endif //BRIDGE_ARDUINO_BRIDGEENCODER_H
