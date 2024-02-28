#ifndef USER_H
#define USER_H

#include "Account.hpp"
#include "Playlist.hpp"

class User : public Account {
    private:
        std::vector<Playlist*> playlists;

    public:
        ~User();
        User(Account &account);

        virtual void loadAccountAssets() override;
        virtual void saveAccountAssets() override;

        void showPlaylists();
        void addPlaylist(Playlist* &target);
        void removePlaylist(std::string &name);
        Playlist* selectPlaylist(std::string &name);
};

#endif