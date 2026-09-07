//
// Created by kamaev on 9/7/26.
//

#ifndef CPP_TEST_USER_FRIENDS_H
#define CPP_TEST_USER_FRIENDS_H
#include "user.h"

class UserFriends
{
    int id_;
    int user_id_;
    std::vector<User> users_;

public:
    explicit UserFriends(const int user_id) : user_id_(user_id)
    {
        id_ = 0;
    };

    bool addFriend(const User* user);

    [[nodiscard]] int id() const { return id_; }
    [[nodiscard]] int user_id() const { return user_id_; }
    [[nodiscard]] std::vector<User> users() const { return users_; }
};

#endif //CPP_TEST_USER_FRIENDS_H
