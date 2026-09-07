#ifndef CPP_TEST_USER_REPO_H
#define CPP_TEST_USER_REPO_H
#include <vector>

#include "cpp_test/user.h"

class UserRepo
{
   const std::string& filename_;

   public:
   explicit UserRepo(const std::string& filename) : filename_(filename)
   {
      if (filename_.empty())
      {
         throw std::invalid_argument("filename cannot be empty");
      }
   };

   auto getFriends() -> std::optional<std::vector<User>>;
};


#endif //CPP_TEST_USER_REPO_H
