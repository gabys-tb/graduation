#include "CSVHandler.hpp"
#include "Account.hpp"
#include "Album.hpp"
#include "Playlist.hpp"
#include "Track.hpp"

#include "doctest.h"

TEST_CASE("CSVHandler - Teste 01 - Adicionar uma nova Account") {
  CSVHandler csv;

  int type = 0;
  std::string nickname = "Nickname", login = "Login", password = "Password";

  Account account = Account(type, nickname, login, password);

  Account* writtenAccount = csv.getFirstOf<Account>(ACC_PASSWORD, "Password");

  CHECK_EQ(writtenAccount->getAccountType(), 0);
  CHECK_EQ(writtenAccount->getNickname(), "Nickname");
  CHECK_EQ(writtenAccount->getLogin(), "Login");
  CHECK_EQ(writtenAccount->getPassword(), "Password");

  delete writtenAccount;
}

TEST_CASE("CSVHandler - Teste 02 - Adicionar uma nova Track") {
  CSVHandler csv;

  Track track;
  track.setCurrentId(csv.getTotalLines<Track>());

  int length = 3;
  std::string title = "Title", year = "Year", genre = "Genre", artistName = "ArtistName";

  Track track1 = Track(title, length, year, genre, artistName);

  Track* writtenTrack = csv.getFirstOf<Track>(TCK_ARTIST_NAME, "ArtistName");

  CHECK_EQ(writtenTrack->getId(), 0);
  CHECK_EQ(writtenTrack->getTitle(), "Title");
  CHECK_EQ(writtenTrack->getLength(), 3);
  CHECK_EQ(writtenTrack->getYear(), "Year");
  CHECK_EQ(writtenTrack->getGenre(), "Genre");
  CHECK_EQ(writtenTrack->getArtistName(), "ArtistName");

  delete writtenTrack;
}

TEST_CASE("CSVHandler - Teste 03 - Adicionar uma nova Playlist") {
  CSVHandler csv;

  std::string owner = "Owner", name = "Name", description = "Description";

  Playlist playlist = Playlist(owner, name, description);
  csv.saveToCSV(playlist);

  Playlist* writtenPlaylist = csv.getFirstOf<Playlist>(PLAY_NAME, "Name");

  CHECK_EQ(writtenPlaylist->getName(), "Name");

  delete writtenPlaylist;
}

TEST_CASE("CSVHandler - Teste 04 - Adicionar um novo Album") {
  CSVHandler csv;

  Album album;
  album.setCurrentId(csv.getTotalLines<Album>());

  std::string owner = "Owner", title = "Title", year = "Year", genre = "Genre", artistName = "ArtistName";

  Album testAlbum = Album(owner, title, year, genre, artistName);
  csv.saveToCSV(testAlbum);

  Album* writtenAlbum = csv.getFirstOf<Album>(ALB_OWNER, "Owner");

  CHECK_EQ(writtenAlbum->getTitle(), "Title");
  CHECK_EQ(writtenAlbum->getYear(), "Year");
  CHECK_EQ(writtenAlbum->getGenre(), "Genre");

  delete writtenAlbum;
}

TEST_CASE("CSVHandler - Teste 05 - Contar quantidade de linhas") {
  CSVHandler csv;

  int length = 3;
  std::string title = "Title2", year = "Year", genre = "Genre", artistName = "ArtistName";

  Track track2 = Track(title, length, year, genre, artistName);
  Track track3 = Track(title, length, year, genre, artistName);
  Track track4 = Track(title, length, year, genre, artistName);

  unsigned int lines = csv.getTotalLines<Track>();

  // Header + 4 Tracks = 5 linhas
  CHECK_EQ(lines, 5);
}

TEST_CASE("CSVHandler - Teste 06 - Get vários objetos") {
  CSVHandler csv;

  std::vector<Track*> writtenTracks = csv.getAllOf<Track>(TCK_TITLE, "Title2");

  CHECK_EQ(writtenTracks[0]->getTitle(), "Title2");
  CHECK_EQ(writtenTracks[1]->getTitle(), "Title2");
  CHECK_EQ(writtenTracks[2]->getTitle(), "Title2");

  for (auto &track : writtenTracks)
    delete track;
}

TEST_CASE("CSVHandler - Teste 07 - Get todos objetos") {
  CSVHandler csv;

  std::vector<Track*> writtenTracks = csv.getEverything<Track>();

  CHECK_EQ(writtenTracks[0]->getTitle(), "Title");
  CHECK_EQ(writtenTracks[1]->getTitle(), "Title2");
  CHECK_EQ(writtenTracks[2]->getTitle(), "Title2");
  CHECK_EQ(writtenTracks[3]->getTitle(), "Title2");

  for (auto &track : writtenTracks)
    delete track;
}

TEST_CASE("CSVHandler - Teste 08 - Remover objetos do CSV") {
  CSVHandler csv;

  csv.removeAllOf<Track>(TCK_YEAR, "Year");

  unsigned int lines = csv.getTotalLines<Track>();

  // Somente header
  CHECK_EQ(lines, 1);
}

TEST_CASE("CSVHandler - Teste 09 - Remover objetos do CSV que não existem") {
  CSVHandler csv;

  csv.removeAllOf<Track>(TCK_YEAR, "Year");

  unsigned int lines = csv.getTotalLines<Track>();

  // Somente header
  CHECK_EQ(lines, 1);
}

TEST_CASE("CSVHandler - Teste 10 - Get objeto que não existe") {
  CSVHandler csv;
  
  CHECK_THROWS_AS(csv.getFirstOf<Account>(ACC_NICKNAME, "nfquiwgqlwuifqwcnfmiu"), ValueNotFound);
}


TEST_CASE("CSVHandler - Teste 11 - Get vários objetos que não existem") {
  CSVHandler csv;

  CHECK_THROWS_AS(csv.getAllOf<Playlist>(PLAY_NAME, "wjifwqyifquwhfyic"), ValueNotFound);
}


TEST_CASE("CSVHandler - Teste 12 - Get todos objetos que não existem") {
  CSVHandler csv;
  
  CHECK_THROWS_AS(csv.getEverything<Track>(), ValueNotFound);
}