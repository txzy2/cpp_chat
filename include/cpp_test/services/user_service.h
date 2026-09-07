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

    void addFriend(uint64_t userId, const User& friend_) const;
    std::vector<User> getFriends(uint64_t userId) const;
    bool areFriends(uint64_t userId, uint64_t friendId) const;
};

#endif // CPP_TEST_USER_SERVICE_H
