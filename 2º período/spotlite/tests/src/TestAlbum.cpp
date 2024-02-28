#include"Album.hpp"

#include "doctest.h"

TEST_CASE("Album - Teste 01 - Criar um novo Album") {
  CSVHandler csv;

  Album album;
  album.setCurrentId(csv.getTotalLines<Album>());

  Album testAlbum = Album("owner", "title", "0000", "genre", "artist");
  csv.saveToCSV(testAlbum);

  CHECK(testAlbum.getTitle() == "title");
  CHECK(testAlbum.getId() == csv.getTotalLines<Album>() - 2);
  CHECK(testAlbum.getYear() == "0000");
  CHECK(testAlbum.getGenre() == "genre");
  CHECK(testAlbum.getArtistName() == "artist");
}

TEST_CASE("Album - Teste 02 - Reproduzir uma Track específica que não existe no Album") {
  Album album;

  unsigned int invalidId = 1;

  //Tentar reproduzir uma faixa inexistente
  CHECK_THROWS_AS(album.playSpecificTrack(invalidId), TrackNotFound);
  
}

TEST_CASE("Album - Teste 03 - Calcular duração do Album") {
  CSVHandler csv;

  Track track;
  track.setCurrentId(csv.getTotalLines<Track>());

  Track testTrack = Track("title", 3, "0000", "genre", "artist");
  unsigned int id = testTrack.getId();

  Album album;
  album.addTrack(id);

  //Uma Track de 3 minutos adicionada
  CHECK(album.calculateAlbumLength() == 3);

  csv.removeAllOf<Track>(TCK_ID, std::to_string(id));
}

TEST_CASE("Album - Teste 04 - Adicionar um album do arquivo CSV") {
  CSVHandler csv;

  Track track;
  track.setCurrentId(csv.getTotalLines<Track>());

  Album album;
  album.setCurrentId(csv.getTotalLines<Album>());

  Track testTrack = Track("title", 3, "0000", "genre", "artist");
  unsigned int id = testTrack.getId();

  Album testAlbum = Album("testOwner", "title", "0000", "genre", "artist");
  testAlbum.addTrack(id);
  csv.saveToCSV(testAlbum);

  Album* writtenAlbum = csv.getFirstOf<Album>(ALB_OWNER, "testOwner");

  //Uma Track de 3 minutos adicionada
  CHECK(writtenAlbum->calculateAlbumLength() == 3);

  delete writtenAlbum;

  csv.removeAllOf<Track>(TCK_ID, std::to_string(id));
  csv.removeAllOf<Album>(ALB_OWNER, "testOwner");
}
