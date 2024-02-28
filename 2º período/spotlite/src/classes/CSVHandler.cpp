#include "CSVHandler.hpp"

/**
 * @brief Destrutor, fecha o arquivo CSV se este foi aberto
 * 
 */
CSVHandler::~CSVHandler() {
    if (this->csv.is_open())
        this->csv.close();
}

/**
 * @brief Configura o arquivo CSV para leitura ou escrita. Para saída, esta será no modo append
 * 
 * @param mode Modo desejado: CSV_IN para leitura, CSV_OUT para escrita
 */
void CSVHandler::setMode(const int &mode) {
    if (this->csv.is_open())
        this->csv.close();

    if (mode == CSV_IN)
        this->csv.open(currentCSVFilePath, std::fstream::in);
    else
        this->csv.open(currentCSVFilePath, std::fstream::out | std::fstream::app);
}

/**
 * @brief Une as strings de um vetor em apenas uma string separada por ";"
 * 
 * @param vector Vetor com as strings a serem unidas
 * @return String com os atributos separados por ";"
 */
std::string CSVHandler::join(const std::vector<std::string> &vector) {
    std::string buffer;

    for (auto &header : vector)
        buffer += header + ";";
    
    if (buffer.empty() == false)
        buffer.pop_back();          // Remove o último ;

    return buffer;
}

/**
 * @brief Verifica se o arquivo CSV existe, o cria caso não exista
 * 
 */
void CSVHandler::checkIfExists() {
    // Verifica se o arquivo existe ao tentar abrir para ler
    this->csv.open(currentCSVFilePath, std::fstream::in);
    bool failedFirstOpen = this->csv.fail();
    
    // Se existe, fecha antes de abrir de novo
    if (this->csv.is_open())
        this->csv.close();

    // Abre no modo de saída append. Se o CSV não existir, ele é criado
    this->csv.open(currentCSVFilePath, std::fstream::out | std::fstream::app);

    // Se na primeira abertura houve falha, o arquivo não existia e foi criado, logo, inicializa o header CSV
    if (failedFirstOpen == true)
        this->csv << join(this->object->getHeader()) << std::endl;
}
    
/**
 * @brief Abre um CSV correspondente ao tipo de objeto que se deseja salvar.
 * Por padrão, abre no modo de saída append. Se o CSV não existir, ele é criado
 * @param object Objeto a ser salvo
 */
void CSVHandler::openCSV() {
    // Reinicia o estado do CSV
    if (this->csv.is_open())
        this->csv.close();

    // Abre o CSV correspondente
    switch (this->object->getObjectType()) {
        case ACCOUNT:
            this->currentCSVFilePath = "./data/accountData.csv";
            break;

        case TRACK:
            this->currentCSVFilePath = "./data/trackData.csv";
            break;

        case PLAYLIST:
            this->currentCSVFilePath = "./data/playlistData.csv";
            break;

        case ALBUM:
            this->currentCSVFilePath = "./data/albumData.csv";
            break;
    }

    // Abre o CSV, o cria se não existir
    checkIfExists();    

    // TODO Adicionar exceções de falha de abertura do arquivo
}

/**
 * @brief Salva as informações de um objeto IPrintable no arquivo CSV correspondente
 * 
 * @param object Objeto que se deseja salvar informações
 */
void CSVHandler::saveToCSV(IPrintable &object) {
    // Salva o objeto para ser usado nos outros métodos
    this->object = &object;
    openCSV();

    // Extrai as informações do objeto
    std::vector<std::string> info;
    for (auto &header : this->object->getHeader())
        info.push_back(this->object->getAttribute(header));
    
    this->csv << join(info) << std::endl;
}

/**
 * @brief Lê uma linha do CSV, avançando a posição de leitura a cada vez
 * 
 * @param values Vetor de strings que guardará os valores lidos, já separados
 * @return true ao ler a linha com sucesso, false se chegar ao final do arquivo
 */
bool CSVHandler::readLine(std::vector<std::string> &values) {
    values.clear();
    std::string buffer, line;

    // Retorna false se chegar ao fim do CSV
    if (!(getline(this->csv, line)))
        return false;

    // Escaneia "line" caractere por caractere
    for (size_t i = 0; i <= line.length(); i++) { 
        if (i == line.length() || line[i] == ';') { // Se encontrar um ";" ou chegar ao fim de "line
            values.push_back(buffer);               // Salva a palavra escaneada
            buffer.clear();                 
            continue;                               // Avança para escanear a próxima palavra
        }

        buffer += line[i];                          // Monta a palavra caractere por caractere
    }

    return true;
}

/**
 * @brief Lê uma linha do CSV, avançando a posição de leitura a cada vez.
 * Não guarda os valores, apenas lê a linha.
 * 
 * @return true ao ler a linha com sucesso, false se chegar ao final do arquivo
 */
bool CSVHandler::readLine() {
    std::string line;

    // Retorna false se chegar ao fim do CSV
    if (!(getline(this->csv, line)))
        return false;

    // Retorna true se leu a linha com sucesso
    return true;
}