//
// Created by Ivan Kishchenko on 01.01.2021.
//

#undef min
#undef max

#define BRIDGE_ARDUINO

#define ETL_NO_STL
#define ETL_NOT_USING_STL       1
#define ETL_NO_HUGE_VAL_SUPPORT 1
#define ETL_NO_CPP_NAN_SUPPORT  1
#undef ETL_CPP11_SUPPORTED
#define ETL_CPP11_SUPPORTED     1

#include <etl/string.h>
#include <etl/vector.h>
#include <etl/function.h>
#include <etl/scheduler.h>

#include <Arduino.h>

