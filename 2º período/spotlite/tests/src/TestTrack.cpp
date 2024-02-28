#include "Track.hpp"
#include "CSVHandler.hpp"

#include "doctest.h"

TEST_CASE("Track - Teste 01 - Criar uma nova Track") {
  CSVHandler csv;

  Track track;
  track.setCurrentId(csv.getTotalLines<Track>());

  Track testTrack = Track("title", 3, "0000", "genre", "artist");

  CHECK(testTrack.getTitle() == "title");
  CHECK(testTrack.getId() == csv.getTotalLines<Track>() - 2);
  CHECK(testTrack.getLength() == 3);
  CHECK(testTrack.getYear() == "0000");
  CHECK(testTrack.getGenre() == "genre");
  CHECK(testTrack.getArtistName() == "artist");

  csv.removeAllOf<Track>(TCK_ID, std::to_string(testTrack.getId()));
}
