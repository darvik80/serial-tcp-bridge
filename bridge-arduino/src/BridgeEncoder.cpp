//
// Created by Ivan Kishchenko on 10.01.2021.
//

#include "BridgeEncoder.h"
#include "etl/crc16.h"

void BridgeEncoder::encode(Stream& stream, const BridgeMessage &message) {
    stream.write((const char *) &message.magic, sizeof(uint16_t));
    stream.write((const char *) &message.size, sizeof(uint16_t));

    uint16_t crc16 = 0;
    if (message.size) {
        stream.write((const char *)message.data.data(), message.size);

        etl::crc16 crc16calc;
        crc16calc.add(message.data.begin(), message.data.end());
        crc16 = crc16calc.value();
    }
    stream.write((const char *) &crc16, sizeof(uint16_t));
}