//📁 File 9: NotificationService.h
//🎯 Demonstrates DIP + SRP
#pragma once
#include "INotification.h"
#include "ILogger.h"
#include "IMessageValidator.h"
#include <string>
class NotificationService {
 private:
    INotification& notifier;      // DIP
    ILogger& logger;              // DIP
    IMessageValidator& validator; // DIP

 public:
    NotificationService(INotification& n,
                        ILogger& l,
                        IMessageValidator& v)
        : notifier(n), logger(l), validator(v) {}

    void notify(const std::string& msg) {
        if (!validator.validate(msg)) {
            logger.log("Invalid message!");
            return;
        }

        logger.log("Sending notification...");
        notifier.send(msg);
        logger.log("Notification sent successfully!");
    }
};
/*
✔ Depends on abstractions (DIP)
✔ Performs one job — sending notification (SRP)
*/