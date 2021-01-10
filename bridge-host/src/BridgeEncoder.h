//
// Created by Ivan Kishchenko on 10.01.2021.
//

#ifndef ROVER_BRIDGEENCODER_H
#define ROVER_BRIDGEENCODER_H

#include <ostream>
#include <BridgeMessage.h>

class BridgeEncoder {
public:
    virtual void encode(std::ostream &out, const BridgeMessage& message);
};


#endif //ROVER_BRIDGEENCODER_H
