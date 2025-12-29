//📁 File 3: SMSNotification.h
#pragma once
#include "INotification.h"
#include <iostream>
class SMSNotification : public INotification {
  public:
    void send(const std::string& message) override {
        std::cout << "Sending SMS: " << message << "\n";
    }
};