#include "Playlist.hpp"
#include "doctest.h"
#include <string>


TEST_CASE("Playlist - Teste 01 - Remover Track de uma Playlist"){
    CSVHandler csv;

    Track track;
    track.setCurrentId(csv.getTotalLines<Track>());

    Track testTrack = Track("title", 3, "0000", "genre", "artist");
    unsigned int id = testTrack.getId();

    Playlist play;
    play.addTrack(id);
    play.removeTrack(id);

    //Tentativa de remover uma Track que já foi removida
    CHECK_THROWS_AS(play.removeTrack(id), TrackNotFound);

    csv.removeAllOf<Track>(TCK_ID, std::to_string(id));
}


TEST_CASE("Playlist - Teste 02 - Total de tracks"){
    CSVHandler csv;
    
    Track track;
    track.setCurrentId(csv.getTotalLines<Track>());

    Track testTrack = Track("title", 3, "0000", "genre", "artist");
    unsigned int id = testTrack.getId();
    
    Playlist play;
    play.addTrack(id);

    unsigned int total = play.sumTotalTracks();

    //Adicionada apenas uma Track
    CHECK_EQ(total, 1);

    csv.removeAllOf<Track>(TCK_ID, std::to_string(id));
}

TEST_CASE("Playlist - Teste 03 - Tempo total da playlist"){
    CSVHandler csv;
    
    Track track;
    track.setCurrentId(csv.getTotalLines<Track>());

    Track testTrack0 = Track("title", 3, "0000", "genre", "artist");
    unsigned int id0 = testTrack0.getId();

    Track testTrack1 = Track("title", 3, "0000", "genre", "artist");
    unsigned int id1 = testTrack1.getId();

    Playlist play;
    play.addTrack(id0);
    play.addTrack(id1);

    unsigned int total = play.sumTotalTime();

    //Duas Tracks de 3 minutos adicionadas
    CHECK_EQ(total, 6);  // TEMPO DE DUAS MÚSICAS DE ID 1

    csv.removeAllOf<Track>(TCK_ID, std::to_string(id0));
    csv.removeAllOf<Track>(TCK_ID, std::to_string(id1));
}

TEST_CASE("Playlist - Teste 04 - Adicionar uma Playlist do arquivo CSV"){
    CSVHandler csv;

    Track track;
    track.setCurrentId(csv.getTotalLines<Track>());

    Track testTrack = Track("title", 3, "0000", "genre", "artist");
    unsigned int id = testTrack.getId();

    Playlist testPlay = Playlist("testOwner", "name", "description");
    testPlay.addTrack(id);
    csv.saveToCSV(testPlay);

    Playlist* writtenPlaylist = csv.getFirstOf<Playlist>(PLAY_OWNER, "testOwner");

    //Uma Track de 3 minutos adicionada
    CHECK(writtenPlaylist->sumTotalTime() == 3);

    delete writtenPlaylist;

    csv.removeAllOf<Track>(TCK_ID, std::to_string(id));
    csv.removeAllOf<Playlist>(PLAY_OWNER, "testOwner");
}