//
// Created by Ivan Kishchenko on 10.01.2021.
//

#ifndef BRIDGE_ARDUINO_BRIDGETYPES_H
#define BRIDGE_ARDUINO_BRIDGETYPES_H

#ifdef BRIDGE_ARDUINO

#include "profile.h"
#include <etl/vector.h>

typedef etl::vector<uint8_t, 256> ByteBuffer;
#else
#include <vector>
typedef std::vector<uint8_t> ByteBuffer;
#endif


class BridgeTypes {

};


#endif //BRIDGE_ARDUINO_BRIDGETYPES_H
