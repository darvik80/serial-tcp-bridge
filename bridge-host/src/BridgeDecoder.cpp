//
// Created by Ivan Kishchenko on 10.01.2021.
//

#include "BridgeDecoder.h"

#include <boost/crc.hpp>

BridgeMessage BridgeDecoder::decode(std::istream &inc) {
    BridgeMessage message;
    inc.read((char *) &message.magic, sizeof(uint16_t));
    inc.read((char *) &message.size, sizeof(uint16_t));

    if (!isBridgeMessage(message.magic)) {
        throw std::invalid_argument("Bridge message magic invalid");
    }

    if (message.size) {
        message.data.resize(message.size);
        inc.read((char*)message.data.data(), message.size);
    }

    uint16_t crc16 = 0;
    inc.read((char *) &crc16, sizeof(uint16_t));

    if (message.size) {
        boost::crc_16_type crc16calc;
        crc16calc.process_bytes(message.data.data(), message.size);

        if (crc16 != crc16calc.checksum()) {
            throw std::invalid_argument("Bridge message crc16 invalid");
        }
    } else if (crc16 != 0){
        throw std::invalid_argument("Bridge message invalid");
    }


    return message;
}

bool BridgeDecoder::isBridgeMessage(uint16_t magic) {
    switch (magic) {
        case BRIDGE_MAGIC_SYNC:
        case BRIDGE_MAGIC_STREAM:
            return true;
        default:
            break;

    }
    return false;
}
