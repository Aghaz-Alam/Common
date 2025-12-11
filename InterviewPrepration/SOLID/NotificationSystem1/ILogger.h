//📁 File 5: ILogger.h
//🎯 Demonstrates ISP
#pragma once
#include <string>
class ILogger {
 public:
    virtual void log(const std::string& msg) = 0;
    virtual ~ILogger() = default;
};
/*
✔ Small and focused
✔ Only log()
*/