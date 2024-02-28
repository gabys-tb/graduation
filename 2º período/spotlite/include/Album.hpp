#ifndef ALBUM_H
#define ALBUM_H

#include <algorithm>

#include "IPrintable.hpp"
#include "Track.hpp"
#include "CSVHandler.hpp"

// Headers do CSV para este objeto
#define ALB_ID          "id"
#define ALB_OWNER       "owner"
#define ALB_TITLE       "title"
#define ALB_YEAR        "year"
#define ALB_GENRE       "genre"
#define ALB_ARTIST_NAME "artistName"
#define ALB_TRACKS      "tracks"

class Album : public IPrintable {
    private:
        static unsigned int count;
        unsigned int id;
        std::string owner;
        std::string title;
        std::string year;
        std::string genre;
        std::string artistName;
        std::vector<Track*> tracks;

        std::string getTracks();
        void setTracks(std::string &tracksID);

    public:
        Album();
        Album(std::string owner, std::string title, std::string year, std::string genre, std::string artistName);
        ~Album();

        virtual std::vector<std::string> getHeader() override; 
        virtual std::string getAttribute(std::string key) override;
        virtual void setAttribute(std::string key, std::string value) override;
        virtual ObjectType getObjectType() override;
        
        unsigned int getId();
        void setCurrentId(unsigned int totalLines);
        std::string getTitle();
        std::string getYear();
        std::string getGenre();
        std::string getArtistName();
        void addTrack(unsigned int &targetID);
        void removeTrack(unsigned int &targetID);
        int calculateAlbumLength();
        void play();
        void playAlphabeticalOrder();
        void playSpecificTrack(unsigned int &targetID);
        void showTracklist();
        void showInfo();
};

#endif