//
// Created by Ivan Kishchenko on 10.01.2021.
//

#ifndef BRIDGE_ARDUINO_BRIDGEDECODER_H
#define BRIDGE_ARDUINO_BRIDGEDECODER_H

#include "profile.h"
#include <BridgeMessage.h>

enum BridgeErrorCode {
    FAILED = -1,
    SUCCESS,
    INVALID_MESSAGE,
    NOT_ENOUGH_DATA,
};

class BridgeDecoder {
    enum State {
        DECODE_HEADER,
        DECODE_BODY,
    };

    State _state{DECODE_HEADER};
    uint16_t _magic;
    uint16_t _size;
public:
    int decode(Stream &stream, BridgeMessage& message);
};


#endif //BRIDGE_ARDUINO_BRIDGEDECODER_H
