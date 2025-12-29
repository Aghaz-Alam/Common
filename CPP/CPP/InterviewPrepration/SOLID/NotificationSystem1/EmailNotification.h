//📁 File 2: EmailNotification.h
#pragma once
#include "INotification.h"
#include <iostream>
class EmailNotification : public INotification {
 public:
    void send(const std::string& message) override {
        std::cout << "Sending Email: " << message << "\n";
    }
};