#include "Account.hpp"

/**
 * @brief Constrói um novo objeto Account vazio
 * 
 */
Account::Account() {}

/**
 * @brief Constrói um novo objeto Account
 * 
 * @param accountType Tipo da conta
 * @param nickname Apelido
 * @param login Login
 * @param password Senha
 */
Account::Account(int &accountType, std::string &nickname, std::string &login, std::string &password) {
    this->accountType = accountType;
    this->nickname = nickname;
    this->login = login;
    this->password = password;

    CSVHandler csv;
    csv.saveToCSV(*this);
}

/**
 * @return O header usado no arquivo CSV deste objeto
 */
std::vector<std::string> Account::getHeader() {
    return {ACC_TYPE, ACC_NICKNAME, ACC_LOGIN, ACC_PASSWORD};
}

/**
 * @brief Acessa um atributo do objeto
 * 
 * @param key Nome do atributo a ser acessado
 * @return O atributo no formato std::string
 */
std::string Account::getAttribute(std::string key) {
    if (key == ACC_TYPE)
        return std::to_string(this->accountType);
    
    if (key == ACC_NICKNAME)
        return this->nickname;
    
    if (key == ACC_LOGIN)
        return this->login;
    
    if (key == ACC_PASSWORD)
        return this->password;

    return "";
}

/**
 * @brief Modifica um atributo do objeto
 * 
 * @param key Nome do atributo a ser modificado
 * @param value Valor do atributo no formato std::string
 */
void Account::setAttribute(std::string key, std::string value) {
    if (key == ACC_TYPE)
        this->accountType = std::stoi(value);
    
    if (key == ACC_NICKNAME)
        this->nickname = value;
    
    if (key == ACC_LOGIN)
        this->login = value;
    
    if (key == ACC_PASSWORD)
        this->password = value;
}

/**
 * @return O tipo deste objeto IPrintable
 */
ObjectType Account::getObjectType() {
    return ACCOUNT;
}

/**
 * @return O tipo da conta 
 */
int Account::getAccountType() {
    return this->accountType;
}

/**
 * @return O apelido da conta 
 */
std::string Account::getNickname() {
    return this->nickname;
}

/**
 * @return O login (username) da conta 
 */
std::string Account::getLogin() {
    return this->login;
}

/**
 * @return A senha da conta 
 */
std::string Account::getPassword() {
    return this->password;
}