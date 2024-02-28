#ifndef TRACK_H
#define TRACK_H

#include "IPrintable.hpp"
#include "TerminalColors.hpp"

// Headers do CSV para este objeto
#define TCK_ID          "id"
#define TCK_TITLE       "title"
#define TCK_LENGTH      "length"
#define TCK_YEAR        "year"
#define TCK_GENRE       "genre"
#define TCK_ARTIST_NAME "artistName"

class Track : public IPrintable {
    private:
        static unsigned int count;
        unsigned int id;
        std::string title;
        int length; //Considerando a duração de cada música como um numero inteiro (em minutos)
        std::string year;
        std::string genre;
        std::string artistName;

    public:
        Track();
        Track(std::string title, int length, std::string year, std::string genre, std::string artistName);
        ~Track();

        virtual std::vector<std::string> getHeader() override; 
        virtual std::string getAttribute(std::string key) override;
        virtual void setAttribute(std::string key, std::string value) override;       
        virtual ObjectType getObjectType() override;

        std::string getTitle();
        unsigned int getId();
        void setCurrentId(unsigned int totalLines);
        int getLength();
        std::string getYear();
        std::string getGenre();
        std::string getArtistName();
        void play();
        void showInfo();
};

#endif