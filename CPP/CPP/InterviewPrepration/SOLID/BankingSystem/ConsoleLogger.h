//📁 ConsoleLogger.h
#pragma once
#include "ILogger.h"
#include <iostream>
class ConsoleLogger : public ILogger {
  public:
    void log(const std::string& msg) override {
        std::cout << "[LOG] " << msg << "\n";
    }
};