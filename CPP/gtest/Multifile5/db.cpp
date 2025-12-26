//db.cpp

#include "db.hpp"

Database::Database() : connected(false) {}

Database::~Database() {}

bool Database::connect() {
    connected = true;
    return connected;
}

bool Database::isConnected() const {
    return connected;
}
