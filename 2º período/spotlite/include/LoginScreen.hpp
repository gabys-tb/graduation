#ifndef LOGIN_SCREEN_H
#define LOGIN_SCREEN_H

#include <iostream>

#include "TerminalColors.hpp"
#include "Exceptions.hpp"
#include "CSVHandler.hpp"
#include "User.hpp"
#include "Artist.hpp"

void clearInput();
bool isInvalid(std::string &str);
void createAccount();
Account* signIn();
Account* loginScreen();

#endif