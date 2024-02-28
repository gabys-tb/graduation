#include <getopt.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "Memlog.h" 
#include "DicionarioArvore.h"
#include "DicionarioHash.h"

// variaveis globais para opcoes
char op[4];
char nome_entrada[100];
char nome_saida[100];
int regmem;

//imprime as instruções de uso
void uso() {
  fprintf(stderr,"\t-i <arq> \t (define nome do arquivo de entrada)\n");
  fprintf(stderr,"\t-o <arq> \t(define nome do arquivo de sáida)\n");
  fprintf(stderr,"\t-t <string> \t(informa a implementação a ser utilizada: hash ou arv)\n");
  fprintf(stderr,"\t-l \t\t(registrar acessos a memoria)\n"); 
}

//lê as opcoes da linha de comando e inicializa variaveis
void parse_args(int argc, char ** argv) {
    // variaveis externas do getopt
    extern char * optarg;

    // variavel auxiliar
    char c;

    // inicializacao variaveis globais para opcoes
    regmem = 0;
    nome_entrada[0] = 0;
    nome_saida[0] = 0;
    op[0] = 0;

    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while ((c = getopt(argc, argv, "i:o:t:l")) != EOF) {
        switch(c) {
          case 'i':
	          strcpy(nome_entrada, optarg); 
            break; 
          case 'o':
	          strcpy(nome_saida, optarg); 
            break; 
          case 't':
	          strcpy(op, optarg); 
            break; 
          case 'l': 
	          regmem = 1;
            break;
          default:
            uso();
            exit(1);
        }
    }
    //verifica se parâmetros obrigatórios foram passados
    erroAssert(nome_entrada[0] != 0, "necessário informar arquivo de entrada");
    erroAssert(nome_saida[0] != 0, "necessário informar arquivo de entrada");
    erroAssert(op[0] != 0, "necessário informar a implementação a ser utilizada");
}

//conta linhas do arquivo
int conta_linhas(char *nome_entrada) {
    int count = 0;
    std::string aux;

    //abre arquivo
    std::ifstream arq (nome_entrada);  
    if(arq.is_open()){
        while(arq.peek()!=EOF) {
            //conta o número de linhas
            getline(arq, aux);
            count++;
        }   
        //fecha arquivo
        arq.close();
    }
    return count;
}

//Separa as informações das linhas de adicionar
void separa_linha(std::string linha, std::string vet[3]) {
    //índice do final do verbete
    int fim = 0;

    //flag para indicar significado vazio
    int flag = 0;

    //guarda índice do começo do significado na linha
    int comeco_sig;

    //guarda tipo de verbete (a,n ou v)
    vet[0] =  linha.substr(0, 1);

    //itera pela linha
    for(int i = 0; i < (int)linha.length(); i++){
      if(linha[i] == ']') {fim = i-1;}   
    }

    //salva o verbete
    vet[1] = linha.substr(3, fim-2);

    //adiciona tipo ao final do verbete
    vet[1].append(" (");
    vet[1].append(vet[0]);
    vet[1].append(")");

    //verifica se significado é vazio
    if(linha[fim+2] == '\0'){flag = 1;}
    for(int i = fim+2; i < (int)linha.length()-1; i++){
      if(linha[i] != ' ' ) {flag = 0;}   
    }
    
    //salva significado
    comeco_sig = fim+3;
    if (!flag){vet[2] = linha.substr(comeco_sig, (int)linha.length() - comeco_sig);}
    else {vet[2] = "";}
    
    return;
}


//programa principal
int main(int argc, char ** argv) {
    int num_linhas;
    char log[10] = "log.out";

    // avaliar linha de comando
    parse_args(argc, argv);

    //abertura do arquivo de entrada para leitura
    std::ifstream arq_entrada(nome_entrada);

    //abertura de arquivo de saida para escrita
    std::ofstream arq_saida(nome_saida);
     
    //inicia registro de acesso
    iniciaMemLog(log);

    //ativar ou nao o registro de acesso
    if (regmem){ 
      ativaMemLog();
    }
    else{
      desativaMemLog();
    }

    //define maximo de entradas
    num_linhas = conta_linhas(nome_entrada);
    printf("podem ser adicionados no dicionário no máximo %d verbetes\n", num_linhas);

    //verifica estrutura a ser usada
    if(strcmp(op, "arv") == 0){
      DicionarioArvore * arv = new DicionarioArvore;
      Entrada p; std::string linha; std::string vet[3];
      
      defineFaseMemLog(0);
      //lê arquivo linha a linha
      for(int i = 0; i<num_linhas; i++){
          getline(arq_entrada, linha);
          //separa linha em substrings
          separa_linha(linha, vet);

          p.verbete = vet[1];
          p.significado = vet[2];

          //insere verbete 
          arv->insere(p);
      }
      defineFaseMemLog(1);
      arv->escreve(&arq_saida);

      defineFaseMemLog(2);
      arv->atualiza();
      
      defineFaseMemLog(3);
      arv->escreve(&arq_saida);

      delete arv;

      //fecha arquivos
      arq_entrada.close();
      arq_saida.close();
    }
    else if(strcmp(op, "hash") == 0){
      DicionarioHash hash = DicionarioHash(num_linhas);
      
      Entrada p; std::string linha; std::string vet[3];
      
      defineFaseMemLog(0);
      
      //lê arquivo linha a linha
      for(int i = 0; i<num_linhas; i++){
        getline(arq_entrada, linha);
        separa_linha(linha, vet);

        p.verbete = vet[1];
        p.significado = vet[2];

        //insere verbete
        hash.insere(p);
      }

      defineFaseMemLog(1);
      //escreve dicionário completo
      hash.escreve(&arq_saida);

      defineFaseMemLog(2);
      //tira verbetes com significado
      hash.remove_verbetes();

      defineFaseMemLog(3);
      //escreve verbetes sem significado
      hash.escreve(&arq_saida);

      //fecha arquivos
      arq_entrada.close();
      arq_saida.close();
    }
      
    finalizaMemLog();
    
    return 0;
}

