LIN (Local Interconnect Network)
--------------------------------------------------------
What is it?
->A low-cost, low-speed protocol for non-critical body electronics.

How used?
->Master ECU sends frame → slaves respond.

Where used?
✔ Power windows
✔ Mirror control
✔ Seat sensors
✔ Door lock systems

Why needed?
->Very cheap hardware
->Works where CAN is unnecessary

Pros
->Very low cost
->Simple architecture

Cons
->Slow (20 Kbps)
->Single master only
->Not suitable for real-time safety

//LIN Example (Simulation)
#include <iostream>
using namespace std;
string lin_request(string cmd) {
    if (cmd == "READ_TEMPERATURE")
        return "22*C";
    return "UNKNOWN";
}
int main() {
    cout << "LIN Response: " << lin_request("READ_TEMPERATURE") << endl;
}
/*
Output
LIN Response: 22*C
*/