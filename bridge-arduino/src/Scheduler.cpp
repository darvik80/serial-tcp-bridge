//
// Created by Ivan Kishchenko on 01.01.2021.
//

#include "Scheduler.h"

SchedulerTask::SchedulerTask(SchedulerTaskType type, uint64_t duration, void (*callback)())
        : _type(type), _duration(duration), _callback(callback) {}

void SchedulerTask::execute(uint64_t curTime) {
    if (_type == SCHEDULE_FIXED_DELAY) {
        uint64_t diff = curTime - _lastTime;
        if (diff >= _duration) {
            _lastTime = curTime;
            onTask();
        }
    } else if (_type == SCHEDULE_FIXED_RATE) {
        uint64_t diff = curTime - _lastTime;
        if (diff >= _duration) {
            _lastTime += diff;
            onTask();
        }
    }

}

void Scheduler::setup() {
}

void Scheduler::loop() {
    uint64_t curTime = millis();
    for (auto& task : _tasks) {
        task.execute(curTime);
    }
}

void Scheduler::scheduleFixedDelay(uint64_t duration, void (*callback)()) {
    schedule(SCHEDULE_FIXED_DELAY, duration, callback);
}

void Scheduler::scheduleFixedRate(uint64_t duration, void (*callback)()) {
    schedule(SCHEDULE_FIXED_RATE, duration, callback);
}

void Scheduler::schedule(SchedulerTaskType type, uint64_t duration, void (*callback)()) {
    _tasks.emplace_back(type, duration, callback);
}

