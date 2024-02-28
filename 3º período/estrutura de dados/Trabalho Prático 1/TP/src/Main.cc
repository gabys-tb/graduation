#include <stdlib.h>
#include <fstream>
#include "Sistema.h"
#include "Memlog.h"

int main (int argc, char **argv){
    std::string aux, mensagem;
    CelulaUsuario* celula;
    int id, pri;
    Email email;

    char log[10] = "log.out";

    if (argv[1] == NULL){
        std::cout << "Arquivo não informado." << std::endl;
        abort();
    }

    iniciaMemLog(log);
    desativaMemLog();

    std::ifstream file(argv[1]);

    Sistema sistema;
    
    file >> aux;
    while (!file.eof()) {
        if (aux == "CADASTRA"){
            file >> id;
            sistema.adicionar_usuario(id);
        }
        else if(aux == "CONSULTA"){
            file >> id;
            sistema.acessar_inbox(id);
        }
        else if (aux == "ENTREGA"){
            file >> id >> pri;
            celula = sistema.pesquisar_id(id);

            if (celula != NULL){ 
                file >> aux;
                mensagem.clear();
                while (aux != "FIM"){
                    mensagem += aux + " ";
                    file >> aux;
                }
                email.set_pri(pri);
                email.set_texto(mensagem);
                sistema.entregar_mensagem(celula, email);
            }
            else {
                sistema.imprimir_erro(id);
            }
        }
        else if (aux == "REMOVE") {
            file >> id;
            sistema.remover_usuario(id);
        }
        
        file >> aux;
    }
    
    return finalizaMemLog();

}