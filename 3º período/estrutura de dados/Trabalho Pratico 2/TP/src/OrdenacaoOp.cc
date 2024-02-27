#include <getopt.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "Memlog.h" 
#include "MetodosOrdenacao.h"
#include <sys/resource.h>

// variaveis globais para opcoes
int v, k, s, m;
char out_name[100];
char input_name[100];
int regmem;

//imprime os métodos que podem ser utilizados
void menu_metodos(){
  std::cout << "\t\t1- quicksort recursivo\n" ;
  std::cout << "\t\t2- quicksort mediana, informar k \n" ;
  std::cout << "\t\t3- quicksort seleção, informar m\n";
  std::cout << "\t\t4- quicksort não recursivo\n" ;
  std::cout << "\t\t5- quicksort empilha inteligente\n";
  std::cout << "\t\t6- heapsort\n";
  std::cout << "\t\t7- mergesort\n";
}

//imprime as instruções de uso
void uso() {
  fprintf(stderr,"ordenação_op\n");
  fprintf(stderr,"\t-v <int> \t (método a ser executado, opções abaixo)\n");
  menu_metodos();
  fprintf(stderr,"\t-s <int> \t (semente a ser usada)\n");
  fprintf(stderr,"\t-k <int> \t (parâmetro k do quicksort mediana)\n");
  fprintf(stderr,"\t-i <arq> \t (parâmetro m do quicksorentradasáida)\n");
  fprintf(stderr,"\t-o <arq> \t(define nome de arquivo de sáida)\n");
  fprintf(stderr,"\t-l \t\t(registrar acessos a memoria)\n"); 
}

//Lê as opcoes da linha de comando e inicializa variaveis
void parse_args(int argc, char ** argv) {
    // variaveis externas do getopt
    extern char * optarg;

    // variavel auxiliar
    char c;

    // inicializacao variaveis globais para opcoes
    regmem = 0;
    input_name[0] = 0;
    out_name[0] = 0;
    v = 0, s = 0, m = 0, k = 0;

    // getopt - letra indica a opcao, : junto a letra indica parametro
    // no caso de escolher mais de uma operacao, vale a ultima
    while ((c = getopt(argc, argv, "v:s:k:m:i:o:l")) != EOF) {
        switch(c) {
          case 'v':
	          v = std::stoi(optarg);
            break; 
          case 's':
            s = std::stoi(optarg);
            break;
          case 'k':
            k = std::stoi(optarg);
            break;
          case 'm':
            m = std::stoi(optarg);
            break;
          case 'i':
	          strcpy(input_name, optarg); 
            break; 
          case 'o':
	          strcpy(out_name,optarg); 
            break; 
          case 'l': 
	          regmem = 1;
            break;
          default:
            uso();
            exit(1);
        }
    }

    if (!v){
      uso();
      exit(1);
    }

    //verifica se parâmetros obrigatórios foram passados
    else {
      erroAssert((v > 0) && (v < 8), "necessário informar método válido a ser usado");
      if (v == 2) {erroAssert(k > 0, "valor de k inválido");}
      else if(v == 3) {erroAssert(m > 0, "valor de m inválido");}
      erroAssert(strlen(input_name)>0, "necessário informar nome do arquivo de entrada");
      erroAssert(strlen(out_name)>0, "nome de arquivo de saída deve ser definido");
    }
}

//escreve informações sobre o desempenho do quicksort no arquivo de saída
void escreve_info(std::ofstream * file, int tamanho, InfoOrdenacao info, double tempo) {
  *file << "Tamanho do vetor: " << tamanho << "\n";
  *file << "Comparações: " << info.get_comp() << "\n";
  *file << "Cópias: " << info.get_copias() << "\n";
  *file << "Tempo de execução: " << tempo << "\n";
  *file << "\n";
}

//retorna tempo de execução total como base nas structs rusage de entrada
double mede_tempo(struct rusage uso_antes, struct rusage uso_depois){
  double utime, stime;
  
  //mede tempo de usuário
  utime = (double) uso_depois.ru_utime.tv_sec + 1.e-6 * (double) uso_depois.ru_utime.tv_usec
  - (double) uso_antes.ru_utime.tv_sec - 1.e-6 * (double) uso_antes.ru_utime.tv_usec;
          
  //mede tempo de sistema
  stime = (double) uso_depois.ru_stime.tv_sec + 1.e-6 * (double) uso_depois.ru_stime.tv_usec
  - (double) uso_antes.ru_stime.tv_sec - 1.e-6 * (double) uso_antes.ru_stime.tv_usec;
  
  return utime + stime;
}

//Programa principal para execucao de métodos de ordenação em vetores de registros
int main(int argc, char ** argv) {
    int n, num_linhas;
    InfoOrdenacao info;
    Registro *vetor; 
    char log[10] = "log.out";

    //declaração de variáveis de tempo
    //int rc;
    double tempo_total; 
    struct rusage uso_antes, uso_depois; 
    
    // avaliar linha de comando
    parse_args(argc,argv);

    //abertura do arquivo de entrada para leitura
    std::ifstream arq_entrada(input_name);

    //abertura de arquivo de saida para escrita
    std::ofstream arq_saida(out_name);
    
     
    //inicia registro de acesso
    iniciaMemLog(log);

    //ativar ou nao o registro de acesso
    if (regmem){ 
      ativaMemLog();
    }
    else{
      desativaMemLog();
    }

    //setando a semente de acordo com parametro s passado pelo terminal   
    srand(s);

    //leitura do arquivo de entrada
    arq_entrada >> num_linhas;

    for(int i=0; i<num_linhas; i++){
        //lê tamanho do vetor
        arq_entrada >> n;

        //alocacao de memória para vetor
        vetor = new Registro[n];

        //zerando as variável de tempo
        tempo_total = 0; 
      
        //loop que cria no total cinco vetores de tamanho N
        for(int l=0; l<5; l++) {
          
          //atribuição de valores pseudoaleatorios às chaves 
          for(int j=0; j<n; j++) {vetor[j].chave = rand();}      

          /*execução da versao específica de quicksort 
          passada como parâmetro v */
          switch(v){
              case 1:
                  defineFaseMemLog(0);
                  //salva informações de processamento antes de executar o sort
                  getrusage(RUSAGE_SELF, &uso_antes);  
                  info.quick_sort_recursivo(vetor, n);
                  //salva informações de processamento depois de executar o sort
                  getrusage(RUSAGE_SELF, &uso_depois);
                  break;
              case 2:
                  defineFaseMemLog(0);
                  getrusage(RUSAGE_SELF, &uso_antes); 
                  erroAssert(k < n, "valor de k inválido");
                  info.quick_sort_mediana(vetor, n, k);
                  getrusage(RUSAGE_SELF, &uso_depois);
                  break;
              case 3:
                  defineFaseMemLog(0);
                  getrusage(RUSAGE_SELF, &uso_antes); 
                  erroAssert(m < n, "valor de m inválido");
                  info.quick_sort_selecao(vetor, n, m);
                  getrusage(RUSAGE_SELF, &uso_depois);
                  break;
              case 4:
                  defineFaseMemLog(0);
                  getrusage(RUSAGE_SELF, &uso_antes); 
                  info.quick_sort_nao_recursivo(vetor, n);
                  getrusage(RUSAGE_SELF, &uso_depois);
                  break;
              case 5:
                  defineFaseMemLog(0);
                  getrusage(RUSAGE_SELF, &uso_antes); 
                  info.quick_sort_empilha_inteligente(vetor, n);
                  getrusage(RUSAGE_SELF, &uso_depois);
                  break;
              case 6:
                  getrusage(RUSAGE_SELF, &uso_antes); 
                  info.heap_sort(vetor, n);
                  getrusage(RUSAGE_SELF, &uso_depois);
                  break;
              case 7:
                  getrusage(RUSAGE_SELF, &uso_antes); 
                  info.merge_sort(vetor, 0, n-1);
                  getrusage(RUSAGE_SELF, &uso_depois);
                  break;
          }
          //salva tempo total de cada vez que algoritmo é chamado
          tempo_total = mede_tempo(uso_antes, uso_depois);

          //escreve informações sobre quicksort no arquivo de saída
          escreve_info(&arq_saida, n, info, tempo_total);

          //reseta o número de comparações e cópias
          info.reset();
        }
      
        //desaloca memória do vetor
        delete [] vetor;
    }
  
    //fecha arquivos
    arq_entrada.close();
    arq_saida.close();

    finalizaMemLog();
    
    return 0;
}

