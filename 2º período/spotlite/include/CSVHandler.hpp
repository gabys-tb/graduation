#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H

#include <fstream>

#include "IPrintable.hpp"
#include "Exceptions.hpp"

// Modos do arquivo
#define CSV_IN 0
#define CSV_OUT 1

class CSVHandler {
    private:
        std::fstream csv;
        std::string currentCSVFilePath;
        IPrintable* object = nullptr;
        
        void setMode(const int &mode);
        void checkIfExists();
        void openCSV();
        bool readLine();
        bool readLine(std::vector<std::string> &values);
        std::string join(const std::vector<std::string> &vector);

    public:
        ~CSVHandler();
        void saveToCSV(IPrintable &object);
        template <class OBJ> OBJ* getFirstOf(const std::string &key, const std::string &value);
        template <class OBJ> std::vector<OBJ*> getAllOf(const std::string &key, const std::string &value);
        template <class OBJ> std::vector<OBJ*> getEverything();
        template <class OBJ> void removeAllOf(const std::string &key, const std::string &value);
        template <class OBJ> unsigned int getTotalLines();
};

/**
 * @brief Encontra a primeira ocorrência de "value" no campo "key" no CSV do objeto
 * desejado
 * @tparam OBJ Objeto desejado, pode ser Account, Playlist, Track ou Album
 * @param key Campo em que "value" será procurado
 * @param value Valor a ser procurado
 * @return Um ponteiro para o primeiro objeto com a ocorrência de "value" em "key".
 * Lança a exceção ValueNotFound caso chegue até o fim do CSV sem encontrar "value" em "key"
 */
template <class OBJ> OBJ* CSVHandler::getFirstOf(const std::string &key, const std::string &value) {
    // Salva o objeto para ser usado nos outros métodos
    OBJ obj;
    this->object = &obj;

    openCSV();
    setMode(CSV_IN);

    // Ler o header do CSV e encontrar a posição de "key"
    int keyPos = 0;
    std::vector<std::string> values, header;
    readLine(header);

    for (auto &head : header)
        if (head == key)
            break;
        else
            keyPos++;

    // Escanear todo o CSV até achar a primeira ocorrência de "value" no campo "key"
    while (readLine(values)) {
        // Se encontrou, instancia o objeto com todos os valores
        if (values[keyPos] == value) {
            OBJ* newObj = new OBJ();

            // Instancia o objeto com todos os valores
            for (size_t i = 0; i < header.size(); i++)
                newObj->setAttribute(header[i], values[i]);

            // Retorna o objeto instanciado
            return newObj;
        }
    }

    // Se saiu do loop sem retornar, não encontrou o valor
    throw ValueNotFound();
}

/**
 * @brief Encontra todas as ocorrências de "value" no campo "key" no CSV do objeto
 * desejado
 * @tparam OBJ Objeto desejado, pode ser Account, Playlist, Track ou Album
 * @param key Campo em que "value" será procurado
 * @param value Valor a ser procurado
 * @return Um vetor de ponteiros para todos os objetos com a ocorrência de "value" em "key".
 * Lança a exceção ValueNotFound caso chegue até o fim do CSV sem encontrar "value" em "key"
 */
template <class OBJ> std::vector<OBJ*> CSVHandler::getAllOf(const std::string &key, const std::string &value) {
    // Salva o objeto para ser usado nos outros métodos
    OBJ obj;
    std::vector<OBJ*> objVector;
    this->object = &obj;

    openCSV();
    setMode(CSV_IN);

    // Ler o header do CSV e encontrar a posição de "key"
    int keyPos = 0;
    std::vector<std::string> values, header;
    readLine(header);

    for (auto &head : header)
        if (head == key)
            break;
        else
            keyPos++;

    // Escanear todo o CSV até achar todas as ocorrências de "value" no campo "key"
    while (readLine(values)) {
        // Se encontrou, instancia o objeto com todos os valores
        if (values[keyPos] == value) {
            OBJ* newObj = new OBJ();

            // Instancia o objeto com todos os valores
            for (size_t i = 0; i < header.size(); i++)
                newObj->setAttribute(header[i], values[i]);

            // Adiciona o objeto à lista de objetos encontrados
            objVector.push_back(newObj);
        }
    }

    // Verifica se realmente não achou nenhuma ocorrência para lançar a exceção
    if (objVector.empty())
        throw ValueNotFound();
    else
        return objVector;
}

/**
 * @brief Encontra todos os objetos OBJ no CSV correspondente
 * @tparam OBJ Objeto desejado, pode ser Account, Playlist, Track ou Album
 * @return Um vetor de ponteiros para todos os objetos OBJ no CSV correspondente.
 * Lança a exceção ValueNotFound caso chegue até o fim do CSV sem encontrar nenhum objeto (CSV vazio)
 */
template <class OBJ> std::vector<OBJ*> CSVHandler::getEverything() {
    // Salva o objeto para ser usado nos outros métodos
    OBJ obj;
    std::vector<OBJ*> objVector;
    this->object = &obj;

    openCSV();
    setMode(CSV_IN);
    
    // Ler o header do CSV
    std::vector<std::string> values, header;
    readLine(header);

    // Escanear todo o CSV até achar todos os objetos
    while (readLine(values)) {
        OBJ* newObj = new OBJ();

        // Instancia o objeto com todos os valores
        for (size_t i = 0; i < header.size(); i++)
            newObj->setAttribute(header[i], values[i]);

        // Adiciona o objeto à lista de objetos encontrados
        objVector.push_back(newObj);
    }

    // Verifica se realmente não achou nenhuma ocorrência para lançar a exceção
    if (objVector.empty())
        throw ValueNotFound();
    else
        return objVector;
}

/**
 * @brief Remove todas as ocorrências de OBJ com "value" no campo "key" no CSV do objeto
 * desejado. Não lança nenhuma exceção e não muda o arquivo CSV se não for necessário
 * @tparam OBJ Objeto desejado, pode ser Account, Playlist, Track ou Album
 * @param key Campo em que "value" será procurado
 * @param value Valor a ser procurado
 */
template <class OBJ> void CSVHandler::removeAllOf(const std::string &key, const std::string &value) {
    // Salva o objeto para ser usado nos outros métodos
    OBJ obj;
    std::vector<OBJ*> objVector;
    this->object = &obj;

    openCSV();
    setMode(CSV_IN);

    // Ler o header do CSV e encontrar a posição de "key"
    int keyPos = 0;
    bool found = false;
    std::vector<std::string> values, header;
    readLine(header);
    
    for (auto &head : header)
        if (head == key)
            break;
        else
            keyPos++;

    // Escanear todo o CSV até achar todas as ocorrências de "value" no campo "key"
    while (readLine(values)) {
        // NÃO instancia as que encontrar
        if (values[keyPos] != value) {
            OBJ* newObj = new OBJ();

            // Instancia o objeto com todos os valores
            for (size_t i = 0; i < header.size(); i++)
                newObj->setAttribute(header[i], values[i]);

            // Adiciona o objeto à lista de objetos encontrados
            objVector.push_back(newObj);
        } else {
            found = true;
        }
    }  

    // Se não achou nenhuma ocorrência, não há necessidade de mudar o arquivo CSV
    if (found == false) {
        for (auto &obj : objVector) 
            delete obj;
    
        return;
    }

    // Excluir o CSV antigo
    std::remove(this->currentCSVFilePath.c_str());

    // Cria um novo CSV e salva somente os OBJ que não foram removidos
    openCSV();

    for (auto &obj : objVector) {
        saveToCSV(*obj);
        delete obj;
    }
}

/**
 * @brief Encontra o total de linhas no CSV do objeto correspondente
 * @tparam OBJ Objeto desejado, pode ser Account, Playlist, Track ou Album
 * @return O total de linhas (incluindo o header)
 */
template <class OBJ> unsigned int CSVHandler::getTotalLines() {
    // Salva o objeto para ser usado nos outros métodos
    OBJ obj;
    this->object = &obj;

    openCSV();
    setMode(CSV_IN);

    unsigned int totalLines = 0;

    // Escanear todo o CSV até ler todas as linhas
    while (readLine())
        totalLines++;

    return totalLines;
}

#endif