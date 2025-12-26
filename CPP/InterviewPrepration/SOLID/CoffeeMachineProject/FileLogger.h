//File 4: FileLogger.h
// file logger:
#pragma once
#include "ILogger.h"
#include <fstream>
class FileLogger : public ILogger {
  public:
    void log(const std::string& msg) override {
        std::ofstream file("log.txt", std::ios::app);
        file << "[File] " << msg << "\n";
    }
};
