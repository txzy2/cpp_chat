#include "cpp_test/user_friends.h"

bool UserFriends::addFriend(const User* user)
{
    if (user == nullptr) { return false; }
    if (user_id_ == user->getId()) { return false; }

    users_.push_back(*user);
    return true;
}