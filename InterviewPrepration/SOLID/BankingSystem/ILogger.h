//📁 ILogger.h
#pragma once
#include <string>
class ILogger {
  public:
    virtual void log(const std::string& msg) = 0;
    virtual ~ILogger() = default;
};
