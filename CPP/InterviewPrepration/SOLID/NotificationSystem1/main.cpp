//📁 File 10: main.cpp
#include "EmailNotification.h"
#include "SMSNotification.h"
#include "PushNotification.h"
#include "ConsoleLogger.h"
#include "SimpleValidator.h"
#include "NotificationService.h"

int main() {
    ConsoleLogger logger;
    SimpleValidator validator;

    EmailNotification email;
    SMSNotification sms;
    PushNotification push;

    NotificationService service1(email, logger, validator);
    NotificationService service2(sms, logger, validator);
    NotificationService service3(push, logger, validator);

    service1.notify("Hello from Email!");
    service2.notify("Hello from SMS!");
    service3.notify("Hello from Push!");

    return 0;
}
/*
🖥️ Program Output
[Log] Sending notification...
Sending Email: Hello from Email!
[Log] Notification sent successfully!
[Log] Sending notification...
Sending SMS: Hello from SMS!
[Log] Notification sent successfully!
[Log] Sending notification...
Sending Push: Hello from Push!
[Log] Notification sent successfully!
*/


//g++ -std=c++17 main.cpp -o solid