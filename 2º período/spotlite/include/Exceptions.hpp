#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>

#include "TerminalColors.hpp"

class AccountDoesNotExist {
    public:
        void print();
};

class TrackNotFound {};

class ValueNotFound {};

class NoMatchingResults {};

class AlbumCannotBeEmpty {};
#endif