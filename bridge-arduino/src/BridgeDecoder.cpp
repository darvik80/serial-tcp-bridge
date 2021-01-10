//
// Created by Ivan Kishchenko on 10.01.2021.
//

#include "BridgeDecoder.h"
#include "etl/crc16.h"

int BridgeDecoder::decode(Stream &stream, BridgeMessage &message) {

    while (stream.available()) {
        switch (_state) {
            case DECODE_HEADER: {
                if (stream.available() < sizeof(uint32_t)) {
                    return NOT_ENOUGH_DATA;
                }

                stream.readBytes((char *) &_magic, sizeof(uint16_t));
                stream.readBytes((char *) &_size, sizeof(uint16_t));

                if (_magic != BRIDGE_MAGIC_STREAM && _magic != BRIDGE_MAGIC_SYNC) {
                    _state = DECODE_HEADER;
                    return INVALID_MESSAGE;
                }

                _state = DECODE_BODY;
            }
                break;
            case DECODE_BODY: {
                if (stream.available() < _size + sizeof(uint16_t)) {
                    return NOT_ENOUGH_DATA;
                }
                message.data.resize(_size);
                stream.readBytes((char *) message.data.data(), message.size);
                uint16_t crc16 = 0;
                stream.readBytes((char *) &crc16, sizeof(uint16_t));

                if (_size) {
                    etl::crc16 crc16calc;
                    crc16calc.add(message.data.begin(), message.data.end());

                    if (crc16 != crc16calc.value()) {
                        _state = DECODE_HEADER;
                        return INVALID_MESSAGE;
                    }
                } else if (crc16 != 0) {
                    _state = DECODE_HEADER;
                    return INVALID_MESSAGE;
                }

                message.magic = _magic;
                message.size = _size;
                _state = DECODE_HEADER;
            }
                break;
        }
    }

    return SUCCESS;
}