#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "IPrintable.hpp"
#include "Track.hpp"
#include "CSVHandler.hpp"

// Headers do CSV para este objeto
#define PLAY_OWNER       "owner"
#define PLAY_NAME        "name"
#define PLAY_DESCRIPTION "description"
#define PLAY_TRACKS      "tracks"

class Playlist : public IPrintable {
    private:
        std::string owner;
        std::string name;
        std::string description;
        std::vector<Track*> tracks;
        std::string getTracks();

        void setTracks(std::string &tracksID);
    
    public:
        ~Playlist();
        Playlist();
        Playlist(std::string owner, std::string name, std::string description);

        virtual std::vector<std::string> getHeader() override;
        virtual std::string getAttribute(std::string key) override;
        virtual void setAttribute(std::string key, std::string value) override;
        virtual ObjectType getObjectType() override;

        std::string getName();
        int sumTotalTime();
        int sumTotalTracks();
        void showTracks();
        void playAlphabeticalOrdered();
        void play();
        void playSpecific(std::string name);
        int calculateTimeSpent();
        void addTrack(unsigned int &trackID);
        void removeTrack(unsigned int &trackID);
};

#endif