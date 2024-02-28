#include "UserMenu.hpp"

/**
 * @brief Cria uma nova Playlist na conta do Usuário
 * 
 * @param user Usuário que está criando a Playlist
 */
void createPlaylist(User* &user) {
    std::string name, description;

    // Nome
    while (1) {
        while (1) {
            std::cout << std::endl << CYAN << "Choose a name (unique per Playlist):"   << RESET << std::endl;
            std::getline(std::cin, name);

            if (isInvalid(name))
                std::cout << YELLOW << "Character ';' is not allowed!" << RESET << std::endl;
            else break;
        }

        // Verifica se já existe uma Playlist do usuário com esse nome
        try {
            user->selectPlaylist(name);
            std::cout << YELLOW << "You already have a Playlist with this name, please choose another one" << RESET << std::endl;
        } catch (ValueNotFound &vnf){
            break;
        }
    }

    // Descrição
    while (1) {
        std::cout << std::endl << CYAN << "Enter a description (optional)" << RESET << std::endl;
        std::getline(std::cin, description);

        if (isInvalid(description))
            std::cout << YELLOW << "Character ';' is not allowed!" << RESET << std::endl;
        else break;
    }

    // Cria a Playlist
    Playlist* playlist = new Playlist(user->getLogin(), name, description);

    // A adiciona ao usuário
    user->addPlaylist(playlist); 

    std::cout << std::endl << GREEN << "Playlist created successfully!" << RESET << std::endl;
    std::cout << "Show your Playlists by typing 's'" << std::endl;
}

/**
 * @brief Menu de Tracks. Responsável por operações com uma Track selecionada.
 * 
 * @param track Track selecionada.
 */
void userTrackMenu(Track* &track) {
    char data;

    std::cout << std::endl << CYAN << "Track Menu:" << RESET << std::endl;
    std::cout << "Selected Track: '" << track->getTitle() << "' by " << track->getArtistName() << std::endl << std::endl;

    std::cout << "Type 'p' to play" << std::endl;
    std::cout << "Type 's' to show info" << std::endl;
    std::cout << "Type 'h' to show this menu" << std::endl;
    std::cout << "Type 'e' to go back to Track Search Menu" << std::endl << std::endl;

    while (std::cin >> data) { 
        switch (data) {
            // Reproduz a Track
            case 'p':      
                clearInput();          
                track->play();
                    
                break;

            // Mostra as informações da Track
            case 's': 
                clearInput();        
                track->showInfo();
                    
                break;

            // Mostrar o menu
            case 'h':      
                clearInput();

                std::cout << std::endl << CYAN << "Track Menu:" << RESET << std::endl;
                std::cout << "Selected Track: '" << track->getTitle() << "' by " << track->getArtistName() << std::endl << std::endl;

                std::cout << "Type 'p' to play" << std::endl;
                std::cout << "Type 's' to show info" << std::endl;
                std::cout << "Type 'h' to show this menu" << std::endl;
                std::cout << "Type 'e' to go back to Track Search Menu" << std::endl << std::endl;

                break;

            // Voltar ao Menu de busca de Tracks
            case 'e':
                delete track;           
                return;

                break;

            // Qualquer outra opção
            default:  
                clearInput();            
                std::cout << RED << "Invalid option!" RESET << std::endl;

                break;
        }
    }
}

/**
 * @brief Menu de Albums. Responsável por operações com um Album selecionado.
 * 
 * @param album Album selecionado.
 */
void userAlbumMenu(Album* &album) {
    char data;
    unsigned int id;

    std::cout << std::endl << CYAN << "Album Menu:" << RESET << std::endl;
    std::cout << "Selected Album: '" << album->getTitle() << "' by " << album->getArtistName() << std::endl << std::endl;

    std::cout << "Type 'p' to play" << std::endl;
    std::cout << "Type 'o' to play in alphabetical order" << std::endl;
    std::cout << "Type 't' to play a specific Track" << std::endl;
    std::cout << "Type 's' to show info" << std::endl;
    std::cout << "Type 'h' to show this menu" << std::endl;
    std::cout << "Type 'e' to go back to Album Search Menu" << std::endl << std::endl;

    while (std::cin >> data) {
        try { 
            switch (data) {
                // Reproduz o Album
                case 'p':      
                    clearInput();          
                    album->play();
                        
                    break;
                    
                // Reproduz o Album em ordem alfabética
                case 'o':       
                    clearInput();
                    album->playAlphabeticalOrder();
                        
                    break;

                // Reproduz uma Track específica do Album
                case 't':       
                    clearInput();
                    std::cout << std::endl << CYAN << "Insert Track's ID:" << RESET << std::endl;
                    std::cin >> id;

                    album->playSpecificTrack(id);
                        
                    break;

                // Mostra as informações do Album
                case 's': 
                    clearInput();        
                    album->showInfo();
                        
                    break;

                // Mostrar o menu
                case 'h':      
                    clearInput();

                    std::cout << std::endl << CYAN << "Album Menu:" << RESET << std::endl;
                    std::cout << "Selected Album: '" << album->getTitle() << "' by " << album->getArtistName() << std::endl << std::endl;

                    std::cout << "Type 'p' to play" << std::endl;
                    std::cout << "Type 'o' to play in alphabetical order" << std::endl;
                    std::cout << "Type 's' to show info" << std::endl;
                    std::cout << "Type 'h' to show this menu" << std::endl;
                    std::cout << "Type 'e' to go back to Album Search Menu" << std::endl << std::endl;

                    break;

                // Voltar ao Menu de busca de Albums
                case 'e':
                    delete album;           
                    return;

                    break;

                // Qualquer outra opção
                default:  
                    clearInput();            
                    std::cout << RED << "Invalid option!" RESET << std::endl;

                    break;
            }
        } catch(TrackNotFound &tnf) {
            std::cout << YELLOW << "This Track is not on the album" << RESET << std::endl << std::endl;
        }
    }
}

/**
 * @brief Procura e mostra Tracks presentes no Spotlite por título, gênero ou artista
 * 
 * @param target String contendo a informação que se deseja procurar
 * @param targetOption Tipo de informação procurada (título, gênero ou artista)
 */
void searchTrack(std::string &target, std::string targetOption) {
    std::cout << std::endl << GREEN << "Searching Tracks..." << RESET << std::endl;
    
    int resultsCounter = 0;

    std::for_each(target.begin(), target.end(), [](char & c) {c = ::tolower(c);});
    
    CSVHandler csv;
    std::vector<Track*> allTracks = csv.getEverything<Track>();
    
    for (auto &track : allTracks) {
        std::string result;
        
        if (targetOption == TITLE)
            result = track->getTitle();
        if (targetOption == GENRE)
            result = track->getGenre();
        if (targetOption == ARTIST_NAME)
            result = track->getArtistName();

        std::for_each(result.begin(), result.end(), [](char & c) {c = ::tolower(c);});

        if(result.find(target) != std::string::npos) {
            track->showInfo();
            resultsCounter ++;
        }
    }

    for (auto &track : allTracks)
        delete track;

    if (resultsCounter == 0)
        throw NoMatchingResults();
    
    std::cout << GREEN << "Total of " << resultsCounter << " matching results!" << RESET << std::endl << std::endl;
}

/**
 * @brief Procura e mostra Albums presentes no Spotlite por título, gênero ou artista
 * 
 * @param target String contendo a informação que se deseja procurar
 * @param targetOption Tipo de informação procurada (título, gênero ou artista)
 */
void searchAlbum(std::string &target, std::string targetOption) {
    std::cout << std::endl << GREEN << "Searching Albums..." << RESET << std::endl;

    int resultsCounter = 0;

    std::for_each(target.begin(), target.end(), [](char & c) {c = ::tolower(c);});
    
    CSVHandler csv;
    std::vector<Album*> allAlbums = csv.getEverything<Album>();
    
    for (auto &album : allAlbums) {
        std::string result;
        
        if(targetOption == TITLE)
            result = album->getTitle();
        if(targetOption == GENRE)
            result = album->getGenre();
        if(targetOption == ARTIST_NAME)
            result = album->getArtistName();

        std::for_each(result.begin(), result.end(), [](char & c) {c = ::tolower(c);});

        if(result.find(target) != std::string::npos) {
            album->showInfo();
            resultsCounter ++;
        }
    }
    
    for (auto &album : allAlbums)
        delete album;

    if (resultsCounter == 0)
        throw NoMatchingResults();
    
    std::cout << GREEN << "Total of " << resultsCounter << " matching results!" << RESET << std::endl << std::endl;
}


/**
 * @brief Menu de busca de Tracks. Responsável pelas operações de busca e seleção de Tracks.
 * 
 */
void trackSearchMenu() {
    char data;
    unsigned int id;
    CSVHandler csv;
    Track* track;
    std::string target;

    std::cout << std::endl << CYAN << "Track Search Menu:" << RESET << std::endl << std::endl;

    std::cout << "Type 't' to search Tracks by title" << std::endl;
    std::cout << "Type 'g' to search Tracks by genre" << std::endl;
    std::cout << "Type 'a' to search Tracks by artist" << std::endl;
    std::cout << "Type 'q' to select a Track" << std::endl;
    std::cout << "Type 'h' to show this menu" << std::endl;
    std::cout << "Type 'e' to go back to User Menu" << std::endl << std::endl;

    while (std::cin >> data) {
        try { 
            switch (data) {
                // Procura Tracks por nome
                case 't':      
                    clearInput();          
                    std::cout << std::endl << CYAN << "Insert title:" << RESET << std::endl;
                    std::getline(std::cin, target);

                    searchTrack(target, TITLE);
                        
                    break;
                    
                // Procura Tracks por gênero
                case 'g':       
                    clearInput();
                    std::cout << std::endl << CYAN << "Insert genre:" << RESET << std::endl;
                    std::getline(std::cin, target);

                    searchTrack(target, GENRE);  
                        
                    break;

                // Procura Tracks por artista
                case 'a': 
                    clearInput();        
                    std::cout << std::endl << CYAN << "Insert artist:" << RESET << std::endl;
                    std::getline(std::cin, target);

                    searchTrack(target, ARTIST_NAME);   
                        
                    break;

                // Seleciona uma Track
                case 'q':      
                    clearInput();
                    std::cout << std::endl << CYAN << "Insert Track's ID:" << RESET << std::endl;
                    std::cin >> id;

                    track = csv.getFirstOf<Track>(TCK_ID, std::to_string(id));

                    userTrackMenu(track);

                    break;

                // Mostrar o menu
                case 'h':      
                    clearInput();

                    std::cout << std::endl << CYAN << "Track Search Menu:" << RESET << std::endl << std::endl;

                    std::cout << "Type 't' to search Tracks by title" << std::endl;
                    std::cout << "Type 'g' to search Tracks by genre" << std::endl;
                    std::cout << "Type 'a' to search Tracks by artist" << std::endl;
                    std::cout << "Type 'q' to select a Track" << std::endl;
                    std::cout << "Type 'h' to show this menu" << std::endl;
                    std::cout << "Type 'e' to go back to User Menu" << std::endl << std::endl;

                    break;

                // Voltar ao Menu do usuário
                case 'e':           
                    return;

                    break;

                // Qualquer outra opção
                default:  
                    clearInput();            
                    std::cout << RED << "Invalid option!" RESET << std::endl;

                    break;
            }
        } catch(NoMatchingResults &nmr) {
            std::cout << YELLOW << "No matching results! Try again." << RESET << std::endl << std::endl;
        } catch(ValueNotFound &vnf) {
            std::cout << YELLOW << "This Track doesn't exist on Spotlite" << RESET << std::endl << std::endl;
        }
    }
}

/**
 * @brief Menu de busca de Albums. Responsável pelas operações de busca e seleção de Albums.
 * 
 */
void albumSearchMenu() {
    char data;
    unsigned int id;
    CSVHandler csv;
    Album* album;
    std::string target;

    std::cout << std::endl << CYAN << "Album Search Menu:" << RESET << std::endl << std::endl;

    std::cout << "Type 't' to search Albums by title" << std::endl;
    std::cout << "Type 'g' to search Albums by genre" << std::endl;
    std::cout << "Type 'a' to search Albums by artist" << std::endl;
    std::cout << "Type 'q' to select an Album" << std::endl;
    std::cout << "Type 'h' to show this menu" << std::endl;
    std::cout << "Type 'e' to go back to User Menu" << std::endl << std::endl;

    while (std::cin >> data) { 
        try {
            switch (data) {
                // Procura Albums por nome
                case 't':      
                    clearInput();          
                    std::cout << std::endl << CYAN << "Insert title:" << RESET << std::endl;
                    std::getline(std::cin, target);

                    searchAlbum(target, TITLE);
                        
                    break;
                    
                // Procura Albums por gênero
                case 'g':       
                    clearInput();
                    std::cout << std::endl << CYAN << "Insert genre:" << RESET << std::endl;
                    std::getline(std::cin, target);

                    searchAlbum(target, GENRE);  
                        
                    break;

                // Procura Albums por artista
                case 'a': 
                    clearInput();        
                    std::cout << std::endl << CYAN << "Insert artist:" << RESET << std::endl;
                    std::getline(std::cin, target);

                    searchAlbum(target, ARTIST_NAME);   
                        
                    break;

                // Seleciona um Album
                case 'q':      
                    clearInput();
                    std::cout << std::endl << CYAN << "Insert Album's ID:" << RESET << std::endl;
                    std::cin >> id;

                    album = csv.getFirstOf<Album>(TCK_ID, std::to_string(id));

                    userAlbumMenu(album);

                    break;

                // Mostrar o menu
                case 'h':      
                    clearInput();

                    std::cout << std::endl << CYAN << "Album Search Menu:" << RESET << std::endl << std::endl;

                    std::cout << "Type 't' to search Albums by title" << std::endl;
                    std::cout << "Type 'g' to search Albums by genre" << std::endl;
                    std::cout << "Type 'a' to search Albums by artist" << std::endl;
                    std::cout << "Type 'q' to select an Album" << std::endl;
                    std::cout << "Type 'h' to show this menu" << std::endl;
                    std::cout << "Type 'e' to go back to User Menu" << std::endl << std::endl;

                    break;

                // Voltar ao Menu do usuário
                case 'e':           
                    return;

                    break;

                // Qualquer outra opção
                default:  
                    clearInput();            
                    std::cout << RED << "Invalid option!" RESET << std::endl;

                    break;
            }
        } catch(NoMatchingResults &nmr) {
            std::cout << YELLOW << "No matching results! Try again." << RESET << std::endl << std::endl;
        } catch(ValueNotFound &vnf) {
            std::cout << YELLOW << "This Album doesn't exist on Spotlite" << RESET << std::endl << std::endl;
        }
    }
}

/**
 * @brief Menu da Playlist, responsável por gerenciar as Tracks da Playlist
 * 
 * @param playlist Playlist que se deseja gerenciar
 */
void playlistMenu(Playlist* &playlist) {
    char data;
    unsigned int trackId;

    std::cout << std::endl << CYAN << "Playlist Menu:" << RESET << std::endl;
    std::cout << "Selected Playlist: " << playlist->getName() << std::endl << std::endl;

    std::cout << "Type 's' to show this Playlist's Tracks" << std::endl;
    std::cout << "Type 'a' to add a Track to this Playlist" << std::endl;
    std::cout << "Type 'r' to remove a Track from this Playlist" << std::endl;
    std::cout << "Type 'h' to show this menu" << std::endl;
    std::cout << "Type 'e' to go back to User Menu" << std::endl << std::endl;

    // Menu da Playlist
    while (std::cin >> data) { 
        try {
            switch (data) {
                // Mostrar as Tracks da Playlist
                case 's':      
                    clearInput();     
                    playlist->showTracks();
                    
                    break;

                // Adicionar Track ou Album à Playlist
                case 'a': 
                    clearInput();   
                    std::cout << std::endl << CYAN << "Insert Track's ID:" << RESET << std::endl;
                    std::cin >> trackId;  

                    playlist->addTrack(trackId);   
                    std::cout << std::endl << GREEN << "Track added successfully!" << RESET << std::endl;
                    
                    break;

                // Remover Track da Playlist
                case 'r':      
                    clearInput();   
                    std::cout << std::endl << CYAN << "Insert Track's ID:" << RESET << std::endl;
                    std::cin >> trackId;

                    playlist->removeTrack(trackId);
                    std::cout << std::endl << GREEN << "Track deleted successfully!" << RESET << std::endl;
                    break;

                // Mostrar o menu
                case 'h':      
                    clearInput();

                    std::cout << std::endl << CYAN << "Playlist Menu:" << RESET << std::endl;
                    std::cout << "Selected Playlist: " << playlist->getName() << std::endl << std::endl;

                    std::cout << "Type 's' to show this Playlist's Tracks" << std::endl;
                    std::cout << "Type 'a' to add a Track to this Playlist" << std::endl;
                    std::cout << "Type 'r' to remove a Track from this Playlist" << std::endl;
                    std::cout << "Type 'h' to show this menu" << std::endl;
                    std::cout << "Type 'e' to go back to User Menu" << std::endl << std::endl;

                    break;

                // Voltar ao Menu do usuário
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
            std::cout << YELLOW << "This Track doesn't exist on Spotlite" << RESET << std::endl;
        } catch (TrackNotFound &tnf) {
            std::cout << YELLOW << "This Track doesn't exist on this Playlist" << RESET << std::endl;
        }
    }
}

/**
 * @brief Menu do Usuário, responsável por gerenciar as Playlists e tocar Tracks
 * 
 * @param currentAccount Conta atual usando o aplicativo
 */
void userMenu(Account* &currentAccount) {
    // Muda o ponteiro de Account para User
    User* user = dynamic_cast<User*>(currentAccount);

    char data;
    Playlist* playlist;
    std::string playName;
    std::string target;

    std::cout << CYAN << "User Menu:" << RESET << std::endl << std::endl;

    std::cout << "Type 'c' to create a Playlist"   << std::endl;
    std::cout << "Type 'd' to delete a Playlist"   << std::endl;
    std::cout << "Type 's' to show your Playlists" << std::endl;
    std::cout << "Type 'q' to select a Playlist" << std::endl;
    std::cout << "Type 't' to search Tracks" << std::endl;
    std::cout << "Type 'a' to search Albums" << std::endl;
    std::cout << "Type 'h' to show this menu" << std::endl;
    std::cout << "Type 'e' to log out" << std::endl << std::endl;

    // Menu do Usuário
    while (std::cin >> data) { 
        try {
            switch (data) {
                // Criar uma Playlist
                case 'c':    
                    clearInput(); 
                    createPlaylist(user);         
                    
                    break;
    
                // Deletar uma Playlist
                case 'd':      
                    clearInput();     
                    std::cout << std::endl << CYAN << "Insert Playlist's name:" << RESET << std::endl;
                    std::getline(std::cin, playName);

                    user->removePlaylist(playName);
                    std::cout << std::endl << GREEN << "Playlist deleted successfully!" << RESET << std::endl;

                    break;

                // Mostrar as Playlist existentes
                case 's':      
                    clearInput();     
                    user->showPlaylists();

                    break;
                
                // Selecionar Playlist
                case 'q':      
                    clearInput();   
                    std::cout << std::endl << CYAN << "Insert Playlist's name:" << RESET << std::endl;
                    std::getline(std::cin, playName);

                    playlist = user->selectPlaylist(playName);
                    playlistMenu(playlist);

                    break;
                
                //Procurar Tracks
                case 't':
                    clearInput();

                    trackSearchMenu();

                    break;

                //Procurar Tracks
                case 'a':
                    clearInput();

                    albumSearchMenu();

                    break;

                // Mostrar o menu
                case 'h':      
                    clearInput();

                    std::cout << CYAN << "User Menu:" << RESET << std::endl << std::endl;

                    std::cout << "Type 'c' to create a Playlist"   << std::endl;
                    std::cout << "Type 'd' to delete a Playlist"   << std::endl;
                    std::cout << "Type 's' to show your Playlists" << std::endl;
                    std::cout << "Type 'q' to select a Playlist" << std::endl;
                    std::cout << "Type 't' to search Tracks" << std::endl;
                    std::cout << "Type 'a' to search Albums" << std::endl;
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
            std::cout << YELLOW << "This Playlist doesn't exist on your Account" << RESET << std::endl;
        }
    }
}