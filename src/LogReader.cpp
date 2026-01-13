#include "LogReader.h"
#include <fstream>
#include <unistd.h>
#include <iostream>

LogReader::LogReader(const std::string& file, ThreadSafeQueue<std::string>& queue)
    : filename(file), logQueue(queue) {}

void LogReader::operator()() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: app.log not found\n";
        exit(1);
    }

    std::string line;
    while (true) {
        while (std::getline(file, line)) {
            logQueue.push(line);
        }
        sleep(1);
        file.clear();
    }
}
