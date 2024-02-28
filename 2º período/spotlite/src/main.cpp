#include <iostream>
#include "ArtistMenu.hpp"
#include "LoginScreen.hpp"
#include "UserMenu.hpp"

/**
 * @brief Atualiza o ID atual das Tracks com base no número de Tracks já existentes.
 * 
 */
void updateTrackID() {
    CSVHandler csv;
    Track track;
    
    track.setCurrentId(csv.getTotalLines<Track>());
}

void updateAlbumID() {
    CSVHandler csv;
    Album album;
    
    album.setCurrentId(csv.getTotalLines<Album>());
}

int main() {
    // Carregar uma conta para usar o aplicativo
    Account* currentAccount = loginScreen();

    std::cout << std::endl << GREEN << "Login successful!" << RESET << std::endl;
    
    // Atualizar  o ID atual das Tracks e Albums
    updateTrackID();
    updateAlbumID();

    // Carregar os assets da conta
    try {
        currentAccount->loadAccountAssets();
        
        std::cout << "Done!" << std::endl << std::endl;

    } catch (ValueNotFound &vnf) {
        std::cout << "Nothing to load!" << std::endl << std::endl;
    }

    std::cout << MAGENTA << "Welcome " << currentAccount->getNickname() << "!" << RESET << std::endl << std::endl;
    
    // TODO Com a conta e assets carregados fazer outras coisas
    if (currentAccount->getAccountType() == USER)
        userMenu(currentAccount);
    else
        artistMenu(currentAccount);
    
    // Salva os assets da conta nos CSV's
    currentAccount->saveAccountAssets();

    // Desalocar conta em uso
    delete currentAccount;
    
    return 0;
}