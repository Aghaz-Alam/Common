//📁 File 1: INotification.h
//🎯 Demonstrates OCP, LSP
#pragma once
#include <string>
class INotification {
 public:
    virtual void send(const std::string& message) = 0;
    virtual ~INotification() = default;
};
/*
✔ Base interface
✔ Derived types must behave correctly (LSP)
✔ Open for extension
*/