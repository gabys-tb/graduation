#include "Playlist.hpp"
#include <algorithm>

/**
 * @brief Destrói a Playlist e libera a memória ocupada por suas Tracks
 * 
 */
Playlist::~Playlist() {
    for (auto &track : this->tracks)
        delete track;
}

/**
 * @brief Constrói uma Playlist vazia
 * 
 */
Playlist::Playlist() {}

/**
 * @brief Constrói uma nova Playlist
 * 
 * @param owner Criador e dono da Playlist (login único do usuário)
 * @param name Nome da Playlist
 * @param description Descrição da Playlist
 */
Playlist::Playlist(std::string owner, std::string name, std::string description){
    this->owner = owner;
    this->name = name;
    this->description = description;
    this->tracks.clear();
}

/**
 * @brief Extrai o ID de cada Track presente na Playlist
 * 
 * @return Uma string com os ID's das Tracks separados por ,
 */
std::string Playlist::getTracks() {
    std::string buffer;

    for (auto &track : this->tracks)
        buffer += std::to_string(track->getId()) + ",";

    if (buffer.empty() == false)
        buffer.pop_back();          // Remove a última ,

    return buffer;
}

/**
 * @brief Carrega as Tracks da Playlist a partir de uma string com seus ID's
 * 
 * @param tracksID String com os ID's das Tracks separados por ,
 */
void Playlist::setTracks(std::string &tracksID) {
    CSVHandler csv;
    std::string buffer;
    std::vector<std::string> ids;

    // Se não houver nada para carregar 
    if (tracksID.length() == 0)
        return;

    // Escaneia "tracks" caractere por caractere
    for (size_t i = 0; i <= tracksID.length(); i++) { 
        if (i == tracksID.length() || tracksID[i] == ',') { // Se encontrar um "," ou chegar ao fim de "tracks"
            ids.push_back(buffer);                          // Salva o ID  
            buffer.clear();             
            continue;                                       // Avança para escanear o próximo ID
        }

        buffer += tracksID[i];                       
    }

    // Carrega as Tracks a partir de seus ID's
    for (auto &id : ids) 
        this->tracks.push_back(csv.getFirstOf<Track>(TCK_ID, id));
}

/**
 * @return O header usado no arquivo CSV deste objeto
 */
std::vector<std::string> Playlist::getHeader() {
    return {PLAY_OWNER, PLAY_NAME, PLAY_DESCRIPTION, PLAY_TRACKS};
}

/**
 * @brief Acessa um atributo do objeto
 * 
 * @param key Nome do atributo a ser acessado
 * @return O atributo no formato std::string
 */
std::string Playlist::getAttribute(std::string key) {
    if (key == PLAY_OWNER)
        return this->owner;
    
    if (key == PLAY_NAME)
        return this->name;
    
    if (key == PLAY_DESCRIPTION)
        return this->description;
    
    if (key == PLAY_TRACKS)
        return getTracks();

    return "";
}

/**
 * @brief Modifica um atributo do objeto
 * 
 * @param key Nome do atributo a ser modificado
 * @param value Valor do atributo no formato std::string
 */
void Playlist::setAttribute(std::string key, std::string value) {
    if (key == PLAY_OWNER)
        this->owner = value;
    
    if (key == PLAY_NAME)
        this->name = value;
    
    if (key == PLAY_DESCRIPTION)
        this->description = value;
    
    if (key == PLAY_TRACKS)
        setTracks(value);
}

/**
 * @return O tipo deste objeto IPrintable
 */
ObjectType Playlist::getObjectType() {
    return PLAYLIST;
}

/** 
 * @return O nome da Playlist
 */
std::string Playlist::getName() {
    return this->name;
}

/**
* @brief Retorna a duração total da playlist
*/
int Playlist::sumTotalTime(){
    int total = 0;
    for (auto &track : this->tracks){
        total += track->getLength();
    }
    return total;
}

/**
* @brief Mostra as Tracks da Playlist
*/
void Playlist::showTracks() {
    if (this->tracks.empty())
        std::cout <<  RED << "This Playlist does not have any Tracks :(" << RESET << std::endl;

    for (auto &track : this->tracks)
        track->showInfo();
}

/** 
 * @return A quantidade de Tracks da Playlist
 */
int Playlist::sumTotalTracks() {
    return tracks.size();
}

/**
* @brief Compara duas Tracks
*/
bool compare(Track* t1, Track* t2){
    return t1->getTitle() < t2->getTitle();
}

/**
* @brief Toca as Tracks em ordem alfabética
*/
void Playlist::playAlphabeticalOrdered(){
    std::vector<Track*> tmp = this->tracks; // FUNCIONA?

    std::sort(tmp.begin(), tmp.end(), compare);
    for (auto track : this->tracks){
        track->play();
    }
}

/**
* @brief Toca as Tracks na ordem que foram adicionadas
*/
void Playlist::play(){
    unsigned int tracks = 0;
    for (auto track : this->tracks){
        tracks++;
        track->play();
    }
    if (tracks == 0) std::cout << RED <<"There are no tracks here ;( come back later" << RESET << std::endl;
}

/**
* @brief Toca uma Track específica
* @param name Nome da Track
*/
void Playlist::playSpecific(std::string name){
    //unsigned int index = 0;

    for (auto &track : this->tracks){
        if (track->getTitle() == name){
            track->play();
            return;
        }
    }
    std::cout << RED <<"There are no tracks with this name here ;( come back later" << RESET << std::endl;
}
/**
* @brief Retorna quanto tempo foi gasto ouvindo a Playlist
*/
int Playlist::calculateTimeSpent(){
    // To be done
    return 0;
}

/**
* @brief Adiciona uma track à Playlist
*/
void Playlist::addTrack(unsigned int &targetID){
    CSVHandler csv;
    this->tracks.push_back(csv.getFirstOf<Track>(TCK_ID, std::to_string(targetID)));
}

/**
* @brief Remove uma track da Playlist
*/
void Playlist::removeTrack(unsigned int &targetID){
    unsigned int index = 0;

    for (auto &track : this->tracks) {
        if (track->getId() == targetID) {
            Track* temp = track;
            this->tracks.erase(this->tracks.begin() + index);
            delete temp;

            return;
        }

        index++;
    }

    // Saiu do for sem deletar a Playlist
    throw TrackNotFound();
}