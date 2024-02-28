#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct Ponto{
    int x, y, n;
}Ponto;

int menor_multiplo_de_4(int x){
    int quociente = x/4;
    return quociente*4;
}

void calcula_ponto(Ponto *p){
   
    int ponto_ref;
    ponto_ref = menor_multiplo_de_4(p->n);
    
    int dif = p->n-ponto_ref;

    switch (dif){
    case 0:
        p->x = ponto_ref/2;
        p->y = 0;
        break;
    
    case 1:
        p->x = -1;
        p->y = ponto_ref/2 + 1;
        break;

    case 2:
        p->x = -ponto_ref/2 - 2;
        p->y = 0;
        break;

   case 3:
        p->x = 0;
        p->y = -ponto_ref/2 - 2;
        break;
    }
    return;
}

void main(){
    Ponto *ponto;
    scanf("%d", &(ponto->n));
    
    ponto->x=0;
    ponto->y=0;

    calcula_ponto(ponto);
    printf("%d %d", ponto->x, ponto->y);
    
    return;
}

