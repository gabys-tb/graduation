#include "Track.hpp"
#include "CSVHandler.hpp"

unsigned int Track::count = 0;

/**
 * @brief Atualiza o ID atual das Tracks com base no número de Tracks já existentes.
 * Esse valor é dado pelo número de linhas do CSV de Tracks subtraído de 1 para compensar
 * o header do CSV
 * 
 * @param totalLines Número de linhas do CSV de Tracks
 */
void Track::setCurrentId(unsigned int totalLines) {
    Track::count = totalLines - 1;
}

/**
 * @brief Constrói um novo objeto Track vazio
 * 
 */
Track::Track() {}

/**
 * @brief Constrói um novo objeto Track
 * 
 * @param title Título
 * @param length Duração
 * @param year Ano
 * @param genre Gênero
 * @param artistName Nome do Artista
 */
Track::Track(std::string title, int length, std::string year, std::string genre, std::string artistName) {
    this->title = title;
    this->id = Track::count;
    this->length = length;
    this->year = year;
    this->genre = genre;
    this->artistName = artistName;

    CSVHandler csv;
    csv.saveToCSV(*this);

    Track::count++;
}

/**
 * @brief Destrói um objeto Track
 * 
 */
Track::~Track() {}

/**
 * @brief Acessa um atributo do objeto
 * 
 * @param key Nome do atributo a ser acessado
 * @return O atributo no formato std::string
 */
std::string Track::getAttribute(std::string key) {
    if (key == TCK_TITLE)
        return this->title;

    if (key == TCK_ID)
        return std::to_string(this->id);
    
    if (key == TCK_LENGTH)
        return std::to_string(this->length);

    if (key == TCK_YEAR)
        return this->year;
    
    if (key == TCK_GENRE)
        return this->genre;

    if (key == TCK_ARTIST_NAME)
        return this->artistName;

    return "";
}

/**
 * @brief Modifica um atributo do objeto
 * 
 * @param key Nome do atributo a ser modificado
 * @param value Valor do atributo no formato std::string
 */
void Track::setAttribute(std::string key, std::string value) {
    if (key == TCK_TITLE)
        this->title = value;

    if (key == TCK_ID)
        this->id = std::stoi(value);
    
    if (key == TCK_LENGTH)
        this->length = std::stoi(value);

    if (key == TCK_YEAR)
        this->year = value;
    
    if (key == TCK_GENRE)
        this->genre = value;

    if (key == TCK_ARTIST_NAME)
        this->artistName = value;
}

/**
 * @return O header usado no arquivo CSV deste objeto
 */
std::vector<std::string> Track::getHeader() {
    return {TCK_ID, TCK_TITLE, TCK_LENGTH, TCK_YEAR, TCK_GENRE, TCK_ARTIST_NAME};
}

/**
 * @return O tipo deste objeto IPrintable
 */
ObjectType Track::getObjectType() {
    return TRACK;
}

/**
 * @brief Retorna o título da Track
 * 
 * @return std::string Título da Track
 */
std::string Track::getTitle() {return this->title;}

/**
 * @brief Retorna o id da Track
 * 
 * @return unsigned int Id da Track
 */
unsigned int Track::getId() {return this->id;}

/**
 * @brief Retorna a duração da Track
 * 
 * @return int Duração da Track
 */
int Track::getLength() {return this->length;}

/**
 * @brief Retorna o ano da Track
 * 
 * @return int Ano da Track
 */
std::string Track::getYear() {return this->year;}

/**
 * @brief Retorna o gênero da Track
 * 
 * @return std::string Gênero da Track
 */
std::string Track::getGenre() {return this->genre;}

/**
 * @brief Retorna o nome do Artista da Track
 * 
 * @return std::string Nome do artista da Track
 */
std::string Track::getArtistName() {return this->artistName;}

/**
 * @brief Reproduz a Track
 * 
 */
void Track::play() {
    std::cout << BLUE << "----------------------------------------------------------------------" << std::endl;
    std::cout << GREEN << "Playing '" << this->title << "' by " << this->artistName << "... ♪ ♫ ♪" << std::endl;
    std::cout << BLUE << "----------------------------------------------------------------------" << RESET << std::endl;
}

/**
 * @brief Mostra todas as informações da Track
 * 
 */
void Track::showInfo() {
    std::cout << BLUE << "----------------------------------------------------------------------" << std::endl;
    std::cout << CYAN << "Track ID: " << this->id << std::endl << RESET << this->title << std::endl;
    std::cout << CYAN << this->artistName << " • " << this->year << " • " << this->genre << " • " << this->length << ":00" << std::endl;
    std::cout << BLUE << "----------------------------------------------------------------------" << RESET << std::endl;
}