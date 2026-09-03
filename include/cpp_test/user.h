//
// Created by kamaev on 9/1/26.
//

#ifndef CPP_TEST_USER_H
#define CPP_TEST_USER_H

#include <string>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "status_types.h"

class User
{
    uint64_t id_;

    std::string name_;
    std::string username_;
    std::string email_;
    std::string password_;

    boost::uuids::uuid extId_;

    Status status_;

    static uint64_t nextId_;

public:
    explicit User() : id_(++nextId_), status_(ACTIVE)
    {
        extId_ = boost::uuids::random_generator()();
    }

    void setName(const std::string& name) { name_ = name; }
    void setUsername(const std::string& username) { username_ = username; }
    void setEmail(const std::string& email) { email_ = email; }
    void setPassword(const std::string& password) { password_ = password; }
    void setStatus(const Status status) { status_ = status; }

    [[nodiscard]] uint64_t getId() const { return id_; }
    [[nodiscard]] boost::uuids::uuid getExtId() const { return extId_; }
    [[nodiscard]] std::string getName() const { return name_; }
    [[nodiscard]] std::string getUsername() const { return username_; }
    [[nodiscard]] std::string getEmail() const { return email_; }
    [[nodiscard]] Status getStatus() const { return status_; }

private:
    void generateExtId();
};


#endif //CPP_TEST_USER_H
