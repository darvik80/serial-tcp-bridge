//
// Created by Ivan Kishchenko on 10.01.2021.
//

#include "BridgeEncoder.h"
#include "boost/crc.hpp"

void BridgeEncoder::encode(std::ostream &out, const BridgeMessage &message) {
    out.write((const char *) &message.magic, sizeof(uint16_t));
    out.write((const char *) &message.size, sizeof(uint16_t));

    uint16_t crc16 = 0;
    if (message.size) {
        out.write((const char *)message.data.data(), message.size);

        boost::crc_16_type crc16calc;
        crc16calc.process_bytes((const char *)message.data.data(), message.size);
        crc16 = crc16calc.checksum();
    }
    out.write((const char *) &crc16, sizeof(uint16_t));
}
