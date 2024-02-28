#ifndef ARTIST_MENU_H
#define ARTIST_MENU_H

#include "LoginScreen.hpp"
#include "Track.hpp"
#include "Album.hpp"
#include "Artist.hpp"
#include "UserMenu.hpp"

#define ALBUM 0
#define TRACK 1

void createAlbum(Artist* &artist);
void createTrack(Artist* &artist);
void albumMenu(Album* &album);
int chooseOption();
void artistMenu(Account* &currentAccount);
#endif