//📁 File 4: PushNotification.h
#pragma once
#include "INotification.h"
#include <iostream>
class PushNotification : public INotification {
  public:
    void send(const std::string& message) override {
        std::cout << "Sending Push: " << message << "\n";
    }
};