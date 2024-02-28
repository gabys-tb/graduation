#include "User.hpp"

/**
 * @brief Destrói o User e libera a memória ocupada por suas Playlists
 * 
 */
User::~User() {
    for (auto &playlist : this->playlists)
        delete playlist;
}

/**
 * @brief Constrói um novo Usuário a partir de uma conta
 * 
 * @param account Conta do Usuário a ser construído
 */
User::User(Account &account) : Account(account) {}

/**
 * @brief Carrega as Playlists do Usuário com suas respectivas Tracks
 * 
 */
void User::loadAccountAssets() {
    CSVHandler csv;

    std::cout << "Loading your Playlists... ";
    
    this->playlists = csv.getAllOf<Playlist>(PLAY_OWNER, getLogin());
}

/**
 * @brief Salva as Playlist do Usuário no CSV
 * 
 */
void User::saveAccountAssets() {
    CSVHandler csv;

    std::cout << "Saving your Playlists... ";

    // Remove as Playlists antigas do Usuário do CSV
    csv.removeAllOf<Playlist>(PLAY_OWNER, getLogin());

    // Salva as novas Playlists do Usuário no CSV
    for (auto &playlist : this->playlists)
        csv.saveToCSV(*playlist);
        
    std::cout << "Done!" << std::endl;
}

/**
 * @brief Adiciona uma Playlist à lista de Playlists do usuário
 * 
 * @param target Playlist a ser adicionada
 */
void User::addPlaylist(Playlist* &target) {
    this->playlists.push_back(target);
}

/**
 * @brief Remove uma Playlist da lista de Playlists do usuário
 * 
 * @param name Nome da Playlist a ser removida
 */
void User::removePlaylist(std::string &name) {
    int index = 0;

    for (auto &playlist : this->playlists) {
        if (playlist->getName() == name) {
            Playlist* temp = playlist;
            this->playlists.erase(this->playlists.begin() + index);
            delete temp;

            return;
        }

        index++;
    }

    // Saiu do for sem deletar a Playlist
    throw ValueNotFound();
}

/**
 * @brief Seleciona uma Playlist com um nome específico. 
 * Lança a exceção ValueNotFound caso não a encontre
 * 
 * @param name Nome da Playlist
 * @return Um ponteiro para a Playlist selecionada
 */
Playlist* User::selectPlaylist(std::string &name) {
    for (auto &playlist : playlists)
        if (playlist->getName() == name)
            return playlist;
    
    // Saiu do for sem retornar a Playlist
    throw ValueNotFound();
}

/**
 * @brief Mostra as Playlists do Usuário
 * 
 */
void User::showPlaylists() {
    std::cout << std::endl << CYAN << "Your Playlists:" << RESET << std::endl << std::endl;

    if (playlists.empty()) 
        std::cout << "You don't have any Playlists :(" << std::endl;

    for (auto &playlist : playlists) {
        std::cout << playlist->getName() << " • " << playlist->sumTotalTracks() << " tracks • ";
        std::cout << playlist->sumTotalTime() << ":00 min" << std::endl;
    }

    std::cout << std::endl;
}