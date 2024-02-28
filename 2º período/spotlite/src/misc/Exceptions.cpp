#include "Exceptions.hpp"

/**
 * @brief Imprime na tela o que o usuário deve fazer caso a conta em questão não exista
 * 
 */
void AccountDoesNotExist::print() {
    std::cout << YELLOW << "This account does not exist!" << RESET << std::endl;
    std::cout << "Please try again by typing 'l' or create a new account by typing 'n'" << std::endl;
}
