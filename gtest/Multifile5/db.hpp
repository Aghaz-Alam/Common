//db.hpp

#ifndef DB_HPP
#define DB_HPP

class Database {
public:
    Database();
    ~Database();
    bool connect();
    bool isConnected() const;

private:
    bool connected;
};

#endif
