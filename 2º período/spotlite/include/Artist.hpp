#ifndef ARTIST_H
#define ARTIST_H

#include "Account.hpp"
#include "Album.hpp"


class Artist : public Account {
    private:
        std::vector<Album*> albums;

    public:
        ~Artist();
        Artist(Account& account);        
        
        virtual void loadAccountAssets() override;
        virtual void saveAccountAssets() override;
        
        void addAlbum(Album* newAlbum);
        Album* selectAlbum(std::string albumName);
        void showAlbums();
};

#endif