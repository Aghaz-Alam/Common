//📁 File 7: IMessageValidator.h
//🎯 Demonstrates SRP
#pragma once
#include <string>
class IMessageValidator {
  public:
    virtual bool validate(const std::string &msg) = 0;
    virtual ~IMessageValidator() = default;
};