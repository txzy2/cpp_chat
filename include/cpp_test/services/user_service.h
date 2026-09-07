#ifndef CPP_TEST_USER_SERVICE_H
#define CPP_TEST_USER_SERVICE_H

#include "../repos/user_repo.h"
#include "cpp_test/user.h"

class UserService
{
    UserRepo* user_repo_;

    public:
    explicit UserService(UserRepo* repo) : user_repo_(repo) {};

    void setFriend(User* user);

    [[nodiscard]] auto getFriends() const -> std::vector<User>
    {
        const auto friends = user_repo_->getFriends();
        if (friends->empty())
        {
            throw std::runtime_error("No friends in user repo");
        }

        return friends.value();
    };

};

#endif //CPP_TEST_USER_SERVICE_H
