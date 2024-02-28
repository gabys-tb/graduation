#include "LoginScreen.hpp"

/**
 * @brief Limpa quaisquer caracteres restantes no buffer de entrada
 * 
 */
void clearInput() { 
    char c;                                                       
    while ((c = fgetc(stdin)) != '\n' && c != EOF)
        ;
}

/**
 * @brief Verifica se uma string tem caracteres inválidos
 * 
 * @param str String a ser testada
 * @return true se for inválida
 */
bool isInvalid(std::string &str) {
    for (size_t i = 0; i < str.size(); i++)
        if (str[i] == ';')
            return true;

    return false;
}

/**
 * @brief Cria um nova conta e a salva no arquivo CSV de contas
 * 
 */
void createAccount() {
    char data;
    int type;
    std::string temp, nickname, login, password;
    CSVHandler csv;

    // Tipo de conta
    std::cout << CYAN << "Which kind of account do you want to create?" << RESET << std::endl << std::endl;
    std::cout << "Type 'u' for User or 'a' for Artist" << std::endl;
    do {
        std::cin >> data;

        switch (data) {
            case 'u': 
                type = USER;
                break;
            
            case 'a': 
                type = ARTIST;
                break;
            
            default:
                std::cout << RED << "Invalid type!" << RESET << std::endl;       
                break;
        }

        clearInput(); 
    } while (data != 'u' && data != 'a');

    // Apelido
    while (1) {
        std::cout << std::endl << CYAN << "Choose a nickname:" << RESET << std::endl;
        std::getline(std::cin, nickname);

        if (isInvalid(nickname))
            std::cout << YELLOW << "Character ';' is not allowed!" << RESET << std::endl;
        else break;
    }

    // Login
    while (1) {
        while (1) {
            std::cout << std::endl << CYAN << "Choose a login (unique per account):"   << RESET << std::endl;
            std::getline(std::cin, login);

            if (isInvalid(login))
                std::cout << YELLOW << "Character ';' is not allowed!" << RESET << std::endl;
            else break;
        }

        // Verifica se o login já está em uso
        try {
            delete csv.getFirstOf<Account>(ACC_LOGIN, login);

            std::cout << YELLOW << "Login already in use, please choose another one" << RESET << std::endl;
        } catch (ValueNotFound &vnf){
            break;
        }
    }

    // Senha
    while (1) {
        while (1) {
            std::cout << std::endl << CYAN << "Choose a password:" << RESET << std::endl;
            std::getline(std::cin, password);

            if (isInvalid(password))
                std::cout << YELLOW << "Character ';' is not allowed!" << RESET << std::endl;
            else break;
        }

        std::cout << std::endl << CYAN << "Confirm password:"  << RESET << std::endl;
        std::getline(std::cin, temp);

        if (password != temp)
            std::cout << RED << "Password mismatch!" << RESET << std::endl;
        else break;            
    }

    // Criar a conta
    Account account = Account(type, nickname, login, password);

    std::cout << std::endl << GREEN << "Account created successfully!" << RESET << std::endl;
    std::cout << "Sign in by typing 'l'" << std::endl;
}

/**
 * @brief Carrega a conta de um usuário.
 * Lança a exceção AccountDoesNotExist se a conta não existir
 * 
 * @return Um ponteiro para a conta do usuário, já no formato de User ou Artist 
 */
Account* signIn() {
    std::string login, password;
    Account* accountPtr;
    Account account;
    CSVHandler csv;

    // Login
    std::cout << std::endl << CYAN << "Insert your login:" << RESET << std::endl;
    std::getline(std::cin, login);

    // Buscar e instanciar conta se presente no CSV
    try {
        accountPtr = csv.getFirstOf<Account>(ACC_LOGIN, login);
        // Instancia na stack e libera o heap
        account = *accountPtr;
        delete accountPtr;
    } catch (ValueNotFound &vnf) {
        throw AccountDoesNotExist();
    }

    // Senha
    while (1) {
        std::cout << std::endl << CYAN << "Insert your password:" << RESET << std::endl;
        std::getline(std::cin, password);

        if (password != account.getPassword())
            break;
        else
            std::cout << RED << "Incorrect password!" << RESET << std::endl;
    }

    // Retorna a conta específica do usuário
    if (account.getAccountType() == USER)
        return new User(account);
    else
        return new Artist(account);
}

/**
 * @brief Tela inicial, responsável por criar e carregar contas
 * 
 * @return Um ponteiro para a conta que realizar login
 */
Account* loginScreen() {
    std::cout << GREEN << "Welcome to Spotlite!"               << RESET << std::endl << std::endl;
    std::cout << CYAN << "Please sign in or create an account:" << RESET << std::endl << std::endl;

    std::cout << "Type 'l' to sign in"           << std::endl;
    std::cout << "Type 'n' to create an account" << std::endl << std::endl;
    
    char data;  
    bool signedIn = false;
    Account* account = nullptr;

    while ((signedIn == false) && (std::cin >> data)) { 
        try {
            switch (data) {
                // Fazer login com uma conta existente
                case 'l':     
                    clearInput();          
                    account = signIn();
                    signedIn = true;
                    break;

                // Criar uma nova conta
                case 'n':           
                    createAccount();
                    break;

                // Qualquer outra opção
                default:  
                    clearInput();            
                    std::cout << RED << "Invalid option!" RESET << std::endl;
                    break;  
            }
        } catch (AccountDoesNotExist &adne) {
            adne.print();
        }
    }

    return account;
}