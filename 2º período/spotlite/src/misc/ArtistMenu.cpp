#include "ArtistMenu.hpp"


/**
 * @brief Cria um novo álbum na conta do Artista
 * 
 * @param artist Artista que está criando o álbum
 */

void createAlbum(Artist* &artist) {
    std::string title, year, genre;

    // Título
    while (1) {
        while (1) {
            std::cout << std::endl << CYAN << "Choose a title (unique per Album):"   << RESET << std::endl;
            std::getline(std::cin, title);

            if (isInvalid(title))
                std::cout << YELLOW << "Character ';' is not allowed!" << RESET << std::endl;
            else break;
        }

        // Verifica se já existe um álbum do usuário com esse título
        try {
            artist->selectAlbum(title);
            std::cout << YELLOW << "You already have an album with this title, please choose another one" << RESET << std::endl;
        } catch (ValueNotFound &vnf){
            break;
        }
    }

    // Ano de lançamento
    while (1) {
        std::cout << std::endl << CYAN << "Enter the album's year of release" << RESET << std::endl;
        std::getline(std::cin, year);

        if (isInvalid(year)) {
            std::cout << YELLOW << "Character ';' is not allowed!" << RESET << std::endl;
        }
        else if (stoi(year) < 1948 || stoi(year) > 2022){
            std::cout << YELLOW << "Insert a valid value!" << RESET << std::endl;
            continue;
        }
        else {
            break;
        }
    }

    //Gênero musical
    while (1) {
        std::cout << std::endl << CYAN << "Enter the album's genre" << RESET << std::endl;
        std::getline(std::cin, genre);

        if (isInvalid(genre)){
            std::cout << YELLOW << "Character ';' is not allowed!" << RESET << std::endl;
            continue;
        }
        else {break;}
    }

    // Cria o álbum
    Album* album = new Album(artist->getLogin(), title, year, genre, artist->getNickname());

    // O adiciona ao usuário
    artist->addAlbum(album); 

    std::cout << std::endl << GREEN << "Album created successfully!" << RESET << std::endl;
    std::cout << "Show your albums by typing 's'" << std::endl;
}



/**
 * @brief Menu do Álbum, responsável por gerenciar as Tracks da Album
 * 
 * @param album Álbum que se deseja gerenciar
 */


void albumMenu(Album* &album) {
    char data;
    unsigned int trackId;

    std::cout << std::endl << CYAN << "Album Menu:" << RESET << std::endl;
    std::cout << "Selected Album: " << album->getTitle() << std::endl << std::endl;

    std::cout << "Type 's' to show this Album's Tracks" << std::endl;
    std::cout << "Type 'y' to show your available tracks" << std::endl;
    std::cout << "Type 'a' to add a Track to this Album" << std::endl;
    std::cout << "Type 'h' to show this menu" << std::endl;
    std::cout << "Type 'e' to go back to Artist Menu" << std::endl << std::endl;

    // Menu do Album
    while (std::cin >> data) { 
        try {
            switch (data) {
                // Mostrar as Tracks do Álbum
                case 's':      
                    clearInput();     
                    album->showTracklist();
                    
                    break;

                // Mostra todas as tracks do próprio artista
                case 'y':
                    clearInput();
                    

                    break;

                // Adicionar Track ao Álbum
                case 'a': 
                    clearInput();   
                    std::cout << std::endl << CYAN << "Insert Track's ID:" << RESET << std::endl;
                    std::cin >> trackId;  

                    album->addTrack(trackId);   
                    std::cout << std::endl << GREEN << "Track added successfully!" << RESET << std::endl;
                    
                    break;

                // Mostrar o menu
                case 'h':      
                    clearInput();

                    std::cout << std::endl << CYAN << "Album Menu:" << RESET << std::endl;
                    std::cout << "Selected Album: " << album->getTitle() << std::endl << std::endl;

                    std::cout << "Type 's' to show this Album's Tracks" << std::endl;
                    std::cout << "Type 'y' to show your available tracks" << std::endl;
                    std::cout << "Type 'a' to add a Track to this Album" << std::endl;
                    std::cout << "Type 'h' to show this menu" << std::endl;
                    std::cout << "Type 'e' to go back to Artist Menu" << std::endl << std::endl;

                    break;

                // Voltar ao Menu do usuário
                case 'e':           
                    return;

                    break;

                // Qualquer outra opção
                default:  
                    clearInput();            
                    std::cout << RED << "Invalid option!" << RESET << std::endl;

                    break;  
            }
        } catch (ValueNotFound &vnf) {
            std::cout << YELLOW << "This Track doesn't exist on Spotlite" << RESET << std::endl;
        } catch (TrackNotFound &tnf) {
            std::cout << YELLOW << "This Track doesn't exist on this Album" << RESET << std::endl;
        }
    }
} 

/**
 * @brief Adiciona track ao repertório do artista
 * 
 * @param artist que está adicionando a track
 */

void createTrack(Artist* &artist) {
    std::string title, length, year, genre;

    // Nome da música
    while (1) {
        std::cout << std::endl << CYAN << "Enter the track's name:" << RESET << std::endl;
        std::getline(std::cin, title);

        if (isInvalid(title))
            std::cout << YELLOW << "Character ';' is not allowed!" << RESET << std::endl;
        else break;
    }

    // Duração
    while (1) {
        std::cout << std::endl << CYAN << "Enter the track's length (in minutes)" << RESET << std::endl;
        std::getline(std::cin, length);

        try {
            if (stoi(length) < 1 || isInvalid(length)){
                std::cout << YELLOW << "Insert a valid value!" << RESET << std::endl;
                continue;
            }
        } catch (std::invalid_argument &e) {
            std::cout << YELLOW << "Insert a valid value!" << RESET << std::endl;
            continue;
        }
        break;
    }

    // Ano de lançamento
    while (1) {
        std::cout << std::endl << CYAN << "Enter the track's year of release" << RESET << std::endl;
        std::getline(std::cin, year);

        if (isInvalid(year)) {
            std::cout << YELLOW << "Character ';' is not allowed!" << RESET << std::endl;
        }
        else if (stoi(year) < 1948 || stoi(year) > 2022){
            std::cout << YELLOW << "Insert a valid value!" << RESET << std::endl;
            continue;
        }
        else {
            break;
        }
    }

    //Gênero musical
    while (1) {
        std::cout << std::endl << CYAN << "Enter the track's genre" << RESET << std::endl;
        std::getline(std::cin, genre);

        if (isInvalid(genre)){
            std::cout << YELLOW << "Character ';' is not allowed!" << RESET << std::endl;
            continue;
        }
        else {break;}
    }

    // Cria a track
    Track(title, stoi(length), year, genre, artist->getNickname());

    std::cout << std::endl << GREEN << "Track added successfully!" << RESET << std::endl;
}

/**
 * @brief Artista seleciona se quer trabalhar com ábum ou track
 * 
 * @return valor indicador de álbum ou track 
 */

int chooseOption(){
    std::cout << "Type 'a' for album or 't' for Track" << std::endl;
    
    char data;

    while (std::cin >> data) {
        switch (data) {
        // Seleciona álbum
        case 'a':
            clearInput();
            return 0;

        // Seleciona track
        case 't':
            clearInput();
            return 1;

        // Qualquer outro caractere
        default:  
            clearInput();            
            std::cout << RED << "Invalid option! Please try again" RESET << std::endl;
            std::cout << "Type 'a' for album or 't' for track" << std::endl;
            break;  
        }
    }
    return 0;
}



/**
 * @brief Menu do Artista, responsável por gerenciar os álbuns e single tracks
 * 
 * @param currentAccount Conta atual usando o aplicativo
 */

void artistMenu(Account* &currentAccount) {
    // Muda o ponteiro de Account para Artist
    Artist* artist = dynamic_cast<Artist*>(currentAccount);

    char data;
    
    Album* album;
    std::string albumName, trackName;

    std::cout << CYAN << "Artist Menu:" << RESET << std::endl << std::endl;

    std::cout << "Type 'c' to create a Track or an Album"   << std::endl;
    std::cout << "Type 's' to show your Tracks or Albums" << std::endl;
    std::cout << "Type 'q' to select an Album to edit" << std::endl;
    std::cout << "Type 'h' to show this menu" << std::endl;
    std::cout << "Type 'e' to log out" << std::endl << std::endl;

    // Menu do Artista
    while (std::cin >> data) { 
        try {
            switch (data) {
                // Criar um álbum ou track
                case 'c':    
                    clearInput(); 
                    
                    if(chooseOption() == ALBUM){
                        createAlbum(artist); 
                        std::cout << "Type 'q' + 'album's name' to add tracks to your album" << std::endl;
                    }
                    else{
                        createTrack(artist);
                    }
                            
                    break;
    

                // Mostrar álbuns ou tracks existentes
                case 's':      
                    clearInput();  

                    if (chooseOption() == ALBUM){
                        artist->showAlbums();
                    }  
                    else{
                        std::string artisticName = artist->getNickname();
                        try{
                            trackSearchMenu();
                        }
                        catch(NoMatchingResults){
                            std::cout << "You don't have any added tracks yet!" << std::endl;
                        }
                    }

                    break;
                
                // Selecionar álbum
                case 'q':      
                    clearInput();   
                    std::cout << std::endl << CYAN << "Type the album's name:" << RESET << std::endl;
                    std::getline(std::cin, albumName);

                    album = artist->selectAlbum(albumName);
                    albumMenu(album);

                    break;

                // Mostrar o menu
                case 'h':      
                    clearInput();

                    std::cout << CYAN << "Artist Menu:" << RESET << std::endl << std::endl;

                    std::cout << "Type 'c' to create a Track or an Album"   << std::endl;
                    std::cout << "Type 's' to show your Tracks or Albums" << std::endl;
                    std::cout << "Type 'q' to select an Album to edit" << std::endl;
                    std::cout << "Type 'h' to show this menu" << std::endl;
                    std::cout << "Type 'e' to log out" << std::endl << std::endl;

                    break;

                // Log out
                case 'e':           
                    return;

                    break;

                // Qualquer outra opção
                default:  
                    clearInput();            
                    std::cout << RED << "Invalid option!" RESET << std::endl;

                    break;  
            }
        } catch (ValueNotFound &vnf) {
            std::cout << YELLOW << "This Album doesn't exist on your Account" << RESET << std::endl;
        }
    }
}


