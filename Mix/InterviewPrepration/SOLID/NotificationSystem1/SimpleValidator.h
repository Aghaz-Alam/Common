//📁 File 8: SimpleValidator.h
#pragma once
#include "IMessageValidator.h"
class SimpleValidator : public IMessageValidator {
  public:
    bool validate(const std::string& msg) override {
        return !msg.empty();  // only checks non-empty
    }
};
//✔ This class ONLY validates → SRP
