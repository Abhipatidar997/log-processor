#ifndef LOGREADER_H
#define LOGREADER_H

#include <string>
#include "ThreadSafeQueue.h"

class LogReader {
public:
    LogReader(const std::string& file, ThreadSafeQueue<std::string>& queue);
    void operator()();

private:
    std::string filename;
    ThreadSafeQueue<std::string>& logQueue;
};

#endif
