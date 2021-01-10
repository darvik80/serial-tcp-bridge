//
// Created by Ivan Kishchenko on 10.01.2021.
//

#ifndef BRIDGEMESSAGE_H
#define BRIDGEMESSAGE_H

#include "BridgeTypes.h"

#define BRIDGE_MAGIC_SYNC 0x4577
#define BRIDGE_MAGIC_STREAM 0x4578

struct BridgeMessage {
    uint16_t magic;
    uint16_t size;
    ByteBuffer data;
};

#endif //BRIDGEMESSAGE_H
