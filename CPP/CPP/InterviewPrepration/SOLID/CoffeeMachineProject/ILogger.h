//File 2: ILogger.h
//Demonstrates ISP
#pragma once
#include <string>
// Small, focused interface (ISP)
class ILogger {
  public:
    virtual void log(const std::string& msg) = 0;
    virtual ~ILogger() = default;
};
/* 
✔ Interface is small → no unused functions
✔ Robots or servers can use same interface without unnecessary features
*/