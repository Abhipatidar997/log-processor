#ifndef LOGPROCESSOR_H
#define LOGPROCESSOR_H

#include <map>
#include <string>
#include <atomic>
#include "ThreadSafeQueue.h"

class LogProcessor {
public:
    LogProcessor(ThreadSafeQueue<std::string>& queue);
    void operator()();

private:
    ThreadSafeQueue<std::string>& logQueue;
    std::map<std::string, int> counts;
};

#endif
