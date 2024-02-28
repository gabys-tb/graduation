#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "IPrintable.hpp"
#include "CSVHandler.hpp"

// Headers do CSV para este objeto
#define ACC_TYPE     "accountType"
#define ACC_NICKNAME "nickname"
#define ACC_LOGIN    "login"
#define ACC_PASSWORD "password"

// Tipos de conta
#define USER 0
#define ARTIST 1

class Account : public IPrintable {
    private:
        int accountType;
        std::string nickname;
        std::string login;
        std::string password;

    public:
        Account();
        Account(int &accountType, std::string &nickname, std::string &login, std::string &password);

        virtual std::vector<std::string> getHeader() override;
        virtual std::string getAttribute(std::string key) override;
        virtual void setAttribute(std::string key, std::string value) override;
        virtual ObjectType getObjectType() override;
        
        virtual void loadAccountAssets() {};
        virtual void saveAccountAssets() {};

        int getAccountType();
        std::string getNickname();
        std::string getLogin();
        std::string getPassword();
};

#endif