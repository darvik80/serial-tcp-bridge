//
// Created by Ivan Kishchenko on 10.01.2021.
//

#ifndef ROVER_BRIDGEDECODER_H
#define ROVER_BRIDGEDECODER_H

#include <istream>
#include <BridgeMessage.h>

class BridgeDecoder {
    static bool isBridgeMessage(uint16_t magic);
public:
    BridgeMessage decode(std::istream &inc);
};


#endif //ROVER_BRIDGEDECODER_H
