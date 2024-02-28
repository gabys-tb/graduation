#include "Album.hpp"

unsigned int Album::count = 0;

/**
 * @brief Atualiza o ID atual dos Albums com base no número de Albums já existentes.
 * Esse valor é dado pelo número de linhas do CSV de Tracks subtraído de 1 para compensar
 * o header do CSV
 * 
 * @param totalLines Número de linhas do CSV de Albums
 */
void Album::setCurrentId(unsigned int totalLines) {
    Album::count = totalLines - 1;
}

/**
 * @brief Constrói um novo objeto Album vazio
 * 
 */
Album::Album() {}

/**
 * @brief Constrói um novo objeto Album
 * 
 * @param title Título do Album
 * @param year Ano do Album
 * @param genre Gênero do Album
 * @param artistName Nome do Artista
 */
Album::Album(std::string owner, std::string title, std::string year, std::string genre, std::string artistName) {
    this->id = Album::count;
    this->owner = owner;
    this->title = title;
    this->year = year;
    this->genre = genre;
    this->artistName = artistName;

    Album::count++;
}

/**
 * @brief Destrói um objeto Album e libera a memória ocupada por suas Tracks
 * 
 */
Album::~Album() {
    for (auto &track : this->tracks)
        delete track;
}

/**
 * @brief Extrai o ID de cada Track presente no Album
 * 
 * @return Uma string com os ID's das Tracks separados por ,
 */
std::string Album::getTracks() {
    std::string buffer;

    for (auto &track : this->tracks)
        buffer += std::to_string(track->getId()) + ",";

    if (buffer.empty() == false)
        buffer.pop_back();          // Remove a última ,

    return buffer;
}

/**
 * @brief Carrega as Tracks do Album a partir de uma string com seus ID's
 * 
 * @param tracksID String com os ID's das Tracks separados por ,
 */
void Album::setTracks(std::string &tracksID) {
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
 * @brief Acessa um atributo do objeto
 * 
 * @param key Nome do atributo a ser acessado
 * @return O atributo no formato std::string
 */
std::string Album::getAttribute(std::string key) {
    if (key == ALB_ID)
        return std::to_string(this->id);
    
    if (key == ALB_OWNER)
        return this->owner;

    if (key == ALB_TITLE)
        return this->title;

    if (key == ALB_YEAR)
        return this->year;
    
    if (key == ALB_GENRE)
        return this->genre;

    if (key == ALB_ARTIST_NAME)
        return this->artistName;

    if (key == ALB_TRACKS)
        return getTracks();
    
    return "";
}

/**
 * @brief Modifica um atributo do objeto
 * 
 * @param key Nome do atributo a ser modificado
 * @param value Valor do atributo no formato std::string
 */
void Album::setAttribute(std::string key, std::string value) {
    if (key == ALB_ID)
        this->id = std::stoi(value);
    
    if (key == ALB_OWNER)
        this->owner = value;

    if (key == ALB_TITLE)
        this->title = value;

    if (key == ALB_YEAR)
        this->year = value;
    
    if (key == ALB_GENRE)
        this->genre = value;

    if (key == ALB_ARTIST_NAME)
        this->artistName = value;

    if (key == ALB_TRACKS)
        setTracks(value);
}

/**
 * @return O header usado no arquivo CSV deste objeto
 */
std::vector<std::string> Album::getHeader() {
    return {ALB_ID, ALB_OWNER, ALB_TITLE, ALB_YEAR, ALB_GENRE, ALB_ARTIST_NAME, ALB_TRACKS}; //ALB_TRACKS = ids das tracks
}

/**
 * @return O tipo deste objeto IPrintable
 */
ObjectType Album::getObjectType() {
    return ALBUM;
}

/**
 * @brief Retorna o id do Album
 * 
 * @return unsigned int Id do Album
 */
unsigned int Album::getId() {return this->id;}

/**
 * @brief Retorna o título do Album
 * 
 * @return std::string Título do Album
 */
std::string Album::getTitle() {return this->title;}

/**
 * @brief Retorna o ano do Album
 * 
 * @return int Ano do Album
 */
std::string Album::getYear() {return this->year;}

/**
 * @brief Retorna o gênero do Album
 * 
 * @return std::string Gênero do Album
 */
std::string Album::getGenre() {return this->genre;}

/**
 * @brief Retorna o nome do Artista do Album
 * 
 * @return std::string Nome do Artista do Album
 */
std::string Album::getArtistName() {return this->artistName;}

/**
 * @brief Adiciona uma Track em um Album
 * 
 * @param target Track que será adicionada
 */
void Album::addTrack(unsigned int &targetID) {
    CSVHandler csv;
    this->tracks.push_back(csv.getFirstOf<Track>(TCK_ID, std::to_string(targetID)));
}

/**
 * @brief Remove uma Track do Album 
 * 
 * @param target Track que será removida
 */
void Album::removeTrack(unsigned int &targetID) {
    if(this->tracks.size() == 1)
        throw AlbumCannotBeEmpty();
    
    for(unsigned int i = 0; i < this->tracks.size(); i++) {
        if(this->tracks[i]->getId() == targetID)
            this->tracks.erase(this->tracks.begin() + i);
    }
}

/**
 * @brief Calcula a duração total do Album
 * 
 * @return int Duração total do Album
 */
int Album::calculateAlbumLength() {
    int sum = 0;
    for(auto &track : this->tracks)
        sum += track->getLength();
    
    return sum;
}

/**
 * @brief Reproduz o Album
 * 
 */
void Album::play() {
    for(auto track : this->tracks)
        track->play();
}

/**
 * @brief Reproduz o Album em ordem alfabética
 * 
 */
void Album::playAlphabeticalOrder() {
    std::vector<Track*> sortedVector = this->tracks;

    sort(sortedVector.begin( ), sortedVector.end( ), [ ](Track* trackA, Track* trackB){
        return trackA->getTitle() < trackB->getTitle();
    });

    for(auto &track : sortedVector)
        track->play();
}

/**
 * @brief Reproduz uma Track específica do album a partir do seu ID.
 * 
 * @param targetID ID da Track.
 */
void Album::playSpecificTrack(unsigned int &targetID) {
    bool found = false;
    
    for(auto &track : this->tracks)
        if(track->getId() == targetID) {
            track->play();
            found = true;
            break;
        }
    
    if(found == false)
        throw TrackNotFound();
}

/**
 * @brief Mostra a lista de Tracks do Album
 * 
 */
void Album::showTracklist() {
    int position = 1;
    for(auto &track : this->tracks) {
        std::cout << MAGENTA << position << ". " << track->getTitle() << " [ID: " << track->getId() << "] - " << track->getLength() << ":00" << RESET << std::endl;
        position++;
    }
}

/**
 * @brief Mostra todas as informações do Album
 * 
 */
void Album::showInfo() {
    std::cout << BLUE << "----------------------------------------------------------------------" << std::endl;
    std::cout << CYAN << "Album ID: " << this->id << std::endl << RESET << this->title << std::endl;
    std::cout << CYAN << this->artistName << " • " << this->year << " • " << this->genre << " • ";
    std::cout << this->tracks.size() << " tracks" << " • " << Album::calculateAlbumLength() << " minutes" << std::endl;
    std::cout << BLUE << "----------------------------------------------------------------------" << std::endl;
    Album::showTracklist();
    std::cout << BLUE << "----------------------------------------------------------------------" << RESET << std::endl;
}