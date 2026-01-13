#include "LogProcessor.h"
#include <fstream>
#include <iostream>
#include <ctime>

LogProcessor::LogProcessor(ThreadSafeQueue<std::string>& queue)
    : logQueue(queue) {
    counts["INFO"] = 0;
    counts["WARNING"] = 0;
    counts["ERROR"] = 0;
    counts["DEBUG"] = 0;
}

void LogProcessor::operator()() {
    std::ofstream errorFile("error.log", std::ios::app);
    auto lastPrint = time(nullptr);

    while (true) {
        std::string log;
        logQueue.pop(log);

        if (log.find("INFO") != std::string::npos) counts["INFO"]++;
        else if (log.find("WARNING") != std::string::npos) counts["WARNING"]++;
        else if (log.find("ERROR") != std::string::npos) {
            counts["ERROR"]++;
            errorFile << log << std::endl;
        }
        else if (log.find("DEBUG") != std::string::npos) counts["DEBUG"]++;
        else std::cerr << "Invalid log format\n";

        if (time(nullptr) - lastPrint >= 10) {
            std::cout << "----- Log Summary -----\n";
            for (auto& p : counts)
                std::cout << p.first << ": " << p.second << std::endl;
            lastPrint = time(nullptr);
        }
    }
}
