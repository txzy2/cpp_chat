#ifndef CPP_TEST_USER_SERVICE_H
#define CPP_TEST_USER_SERVICE_H

#include <vector>

#include "../repos/user_repo.h"
#include "cpp_test/user.h"

class UserService
{
    UserRepo* userRepo_;

public:
    explicit UserService(UserRepo* repo) : userRepo_(repo) {}

    void addFriend(uint64_t userId, const User& friend_);
    std::vector<User> getFriends(uint64_t userId);
    bool areFriends(uint64_t userId, uint64_t friendId);
};

#endif // CPP_TEST_USER_SERVICE_H
