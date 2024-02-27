#ifndef ESTRUTURAS_H 
#define ESTRUTURAS_H
#include <string>
#include "ListaSignificado.h"

struct Entrada {
    std::string verbete, significado;
};

struct Verbete {
    std::string verbete;
    ListaSignificado lista;
};

#endif