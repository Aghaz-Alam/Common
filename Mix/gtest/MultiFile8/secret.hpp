//secret.hpp

#ifndef SECRET_HPP
#define SECRET_HPP

#include <gtest/gtest_prod.h>

class Secret {
private:
    int hidden(int x);

    FRIEND_TEST(SecretTest, HiddenLogic);
};

#endif
