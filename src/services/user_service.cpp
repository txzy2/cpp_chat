#include "../../include/cpp_test/services/user_service.h"

void UserService::addFriend(const uint64_t userId, const User& friend_) const
{
    if (userId == friend_.getId())
    {
        throw std::logic_error("Cannot add yourself as friend");
    }

    auto friends = userRepo_->loadFriends(userId);
    for (const auto& f : friends)
    {
        if (f.getId() == friend_.getId())
        {
            throw std::logic_error("Already friends");
        }
    }

    friends.push_back(friend_);
    userRepo_->saveFriends(userId, friends);
}

std::vector<User> UserService::getFriends(const uint64_t userId) const
{
    return userRepo_->loadFriends(userId);
}

bool UserService::areFriends(const uint64_t userId, const uint64_t friendId) const
{
    return userRepo_->areFriends(userId, friendId);
}
