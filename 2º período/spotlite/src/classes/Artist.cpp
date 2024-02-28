#include "Artist.hpp"

/**
 * @brief Destrói o Artist e libera a memória ocupada por seus Albums
 * 
 */
Artist::~Artist() {
    for (auto &album : this->albums)
        delete album;
}

/**
 * @brief Constrói um novo Artista a partir de uma conta
 * 
 * @param account Conta do Artista a ser construída
 */
Artist::Artist(Account &account): Account(account) {}

/**
 * @brief Carrega os Albums do Artista com suas respectivas Tracks
 * 
 */
void Artist::loadAccountAssets() {
    CSVHandler csv;

    std::cout << "Loading your Albums... ";

    this->albums = csv.getAllOf<Album>(ALB_OWNER, getLogin());
}

/**
 * @brief Salva os Albums do Artista no CSV
 * 
 */
void Artist::saveAccountAssets() {
    CSVHandler csv;

    std::cout << "Saving your Albums... ";

    // Remove os Albums antigos do Artista do CSV
    csv.removeAllOf<Album>(ALB_OWNER, getLogin());

    // Salva os novos Albums do Artista no CSV
    for (auto &album : this->albums)
        csv.saveToCSV(*album);
        
    std::cout << "Done!" << std::endl;
}

/**
 * @brief Adiciona um álbum no repositório do artista
 *
 */

void Artist::addAlbum(Album* newAlbum){
    albums.push_back(newAlbum);
}

/**
 * @brief Procura um álbum específico do artista
 * @return Retorna o álbum encontrado
 */

Album* Artist::selectAlbum(std::string albumName){
    for(unsigned int i = 0; i < albums.size();i++){
        if(albums[i]->getTitle() == albumName){
            return albums[i];
        }
    }
    //saiu do for sem achar album
    throw ValueNotFound();
}


/**
 * @brief Mostra os álbuns do artista
 * 
 */

void Artist::showAlbums() {
    std::cout << std::endl << CYAN << "Your Albums:" << RESET << std::endl << std::endl;

    if (albums.empty()) 
        std::cout << "You don't have any Albums :(" << std::endl;

    for (auto &album : albums) {
        std::cout << album->getTitle() << " • ";
        std::cout << album->calculateAlbumLength() << ":00 min" << std::endl;
    }

    std::cout << std::endl;
}


