//
// Created by kamaev on 9/1/26.
//

#ifndef CPP_TEST_USER_H
#define CPP_TEST_USER_H

#include <cstdint>
#include <stdexcept>
#include <string>

#include "../src/lib/types/status_types.h"

class User
{
    uint64_t id;

    std::string name;
    std::string username;
    std::string email;
    std::string password;

    std::string extId;

    Status status;

public:
    explicit User(const size_t size) : id(id + size)
    {
        if (size < 0)
        {
            throw std::out_of_range("size must be non-negative");
        }

        this->status = Status::ACTIVE;
        //TODO: Генерировать extId
    }

    void setName(const std::string& name) { this->name = name; }
    void setUsername(const std::string& username) { this->username = username; }
    void setEmail(const std::string& email) { this->email = email; }
    void setPassword(const std::string& password) { this->password = password; }
    void setStatus(const Status status) { this->status = status; }

    std::string getExtId() { return this->extId; }
    std::string getName() const { return this->name; }
    std::string getUsername() { return this->username; }
    std::string getEmail() { return this->email; }
    Status getStatus() const { return this->status; }

private:
    void generateExtId();

};


#endif //CPP_TEST_USER_H
