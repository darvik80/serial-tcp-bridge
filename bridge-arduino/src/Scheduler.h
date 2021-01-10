//
// Created by Ivan Kishchenko on 01.01.2021.
//

#ifndef SERIAL_SCHEDULER_H
#define SERIAL_SCHEDULER_H

#include "profile.h"

enum SchedulerTaskType {
    SCHEDULE_FIXED_DELAY,
    SCHEDULE_FIXED_RATE,
};

class SchedulerTask {
private:
    SchedulerTaskType _type;
    uint64_t _lastTime;
    uint64_t _duration;

    void (*_callback)();
protected:
    virtual void onTask() {
        _callback();
    }
public:
    explicit SchedulerTask(SchedulerTaskType type, uint64_t duration, void (*callback)());

    virtual void execute(uint64_t curTime);
};

class Scheduler {
    etl::vector<SchedulerTask, 10> _tasks;
public:
    Scheduler() = default;

    void scheduleFixedDelay(uint64_t duration, void (*callback)());
    void scheduleFixedRate(uint64_t duration, void (*callback)());
    void schedule(SchedulerTaskType type, uint64_t duration, void (*callback)());

    void setup();
    void loop();
};


#endif //SERIAL_SCHEDULER_H
