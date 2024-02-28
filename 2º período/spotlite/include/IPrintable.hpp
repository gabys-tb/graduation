#ifndef IPRINTABLE_H
#define IPRINTABLE_H

#include <iostream>
#include <vector>

// Tipos de objetos que podem ser IPrintable
typedef enum ObjectType {
    ACCOUNT = 0,
    TRACK,
    PLAYLIST,
    ALBUM
} ObjectType;

class IPrintable {
    public:
        virtual ~IPrintable() {};
        virtual std::vector<std::string> getHeader() = 0; 
        virtual std::string getAttribute(std::string key) = 0;
        virtual void setAttribute(std::string key, std::string value) = 0;
        virtual ObjectType getObjectType() = 0;
};

#endif