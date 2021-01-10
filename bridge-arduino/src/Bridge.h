//
// Created by Ivan Kishchenko on 10.01.2021.
//

#ifndef BRIDGE_ARDUINO_BRIDGE_H
#define BRIDGE_ARDUINO_BRIDGE_H

#include "profile.h"
#include <BridgeMessage.h>
#include <BridgeDecoder.h>
#include <BridgeEncoder.h>

class Bridge {
    enum State {
        IDLE,
        HANDSHAKE,
        CONNECTED,
    };

    State _state{IDLE};
    BridgeEncoder _encoder;
    BridgeDecoder _decoder;

    BridgeMessage _msg;
    Stream& _stream;
public:
    Bridge(Stream& stream) : _stream(stream) {}
    void recv(const etl::function<void, ByteBuffer&> msg);
    int send(ByteBuffer& msg);
};


#endif //BRIDGE_ARDUINO_BRIDGE_H
