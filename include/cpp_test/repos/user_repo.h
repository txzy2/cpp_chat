#ifndef CPP_TEST_USER_REPO_H
#define CPP_TEST_USER_REPO_H

#include <string>
#include <vector>

#include "cpp_test/user.h"

class UserRepo
{
    std::string filename_;

public:
    explicit UserRepo(std::string filename) : filename_(std::move(filename)) {}

    void saveFriends(uint64_t userId, const std::vector<User>& friends);
    std::vector<User> loadFriends(uint64_t userId) const;
    bool areFriends(uint64_t userId, uint64_t friendId) const;

private:
    static std::string userToString(const User& user);
    static User stringToUser(const std::string& str);
};

#endif // CPP_TEST_USER_REPO_H
