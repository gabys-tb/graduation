#ifndef USER_MENU_H
#define USER_MENU_H

#include "LoginScreen.hpp"
#include "Track.hpp"
#include "Playlist.hpp"
#include "Album.hpp"

//Definição das opções de busca
#define TITLE       "title"
#define GENRE       "genre"
#define ARTIST_NAME  "artista"

void createPlaylist(User* &user);
void playlistMenu(Playlist* &playlist);
void userTrackMenu(Track* &track);
void userAlbumMenu(Album* &album);
void trackSearchMenu();
void albumSearchMenu();
void searchTrack(std::string &target, std::string targetOption);
void searchAlbum(std::string &target, std::string targetOption);
void userMenu(Account* &currentAccount);

#endif