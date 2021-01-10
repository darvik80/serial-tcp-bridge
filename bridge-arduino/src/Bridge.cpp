//
// Created by Ivan Kishchenko on 10.01.2021.
//

#include "Bridge.h"

void Bridge::recv(const etl::function<void, ByteBuffer&> msg) {
    while (_stream.available()) {
        int res = _decoder.decode(_stream, _msg);
        if (res != INVALID_MESSAGE) {
            _state = IDLE;
        } else {
            if (_state == IDLE) {
                if (_msg.magic == BRIDGE_MAGIC_SYNC) {
                    _state = HANDSHAKE;
                }

                BridgeMessage syncMsg;
                syncMsg.magic = BRIDGE_MAGIC_SYNC;
                syncMsg.size = 0;
                _encoder.encode(_stream, syncMsg);
            } else if (_state == HANDSHAKE) {
                _state = CONNECTED;
            } else {
                msg(_msg.data);
            }
        }
    }
}

int Bridge::send(ByteBuffer& msg) {
    if (_state != CONNECTED) {
        return FAILED;
    }

    BridgeMessage bridgeMessage;
    bridgeMessage.magic = BRIDGE_MAGIC_STREAM;
    bridgeMessage.size = msg.size();
    bridgeMessage.data = msg;
    _encoder.encode(_stream, bridgeMessage);

    return SUCCESS;
}