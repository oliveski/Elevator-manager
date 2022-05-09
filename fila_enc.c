#include "fila_enc.h"
#include <stdio.h>
#include <stdlib.h>

// Funcao que cria uma fila
FilaEnc* criaFila(){
   FilaEnc *fila = (FilaEnc*)malloc(sizeof(FilaEnc));
   fila->ini = NULL;
   fila->fim = NULL;
   return fila;
}

// Funcao que destroi uma fila
void destroiFila(FilaEnc *fila){
   NodoLEnc *aux = fila->ini;
   while(aux != NULL){
       NodoLEnc *tmp = aux->prox;
       free(aux); // Cuidar ordem do free
       aux = tmp;
   }
   free(fila);
}

// Funcao que insere um elemento na fila
void enfileiraFila(FilaEnc *fila, int andar, int num_passageiros){
   NodoLEnc *novo = (NodoLEnc*)malloc(sizeof(NodoLEnc));
   novo->andar = andar;
   novo->prox = NULL;
   novo->num_passageiros = num_passageiros;
   if (fila->fim != NULL)
      fila->fim->prox = novo;
   else
      fila->ini = novo;
   fila->fim = novo;
}

void enfileiraFilaCrescente(FilaEnc *fila, int andar, int num_passageiros) {
    if (vaziaFila(fila))
        enfileiraFila(fila, andar, num_passageiros);
        else {
            NodoLEnc *novo = (NodoLEnc*)malloc(sizeof(NodoLEnc));
            novo->andar = andar;
            novo->num_passageiros = num_passageiros;
            if (fila->ini->andar > andar) {
                NodoLEnc *aux = fila->ini;
                fila->ini = novo;
                novo->prox = aux;
            } else if (fila->fim->andar < andar) {
                fila->fim->prox = novo;
                fila->fim = novo;
                novo->prox = NULL;
            } else {
                NodoLEnc *aux = fila->ini;
                while (aux->prox->andar < andar)
                    aux = aux->prox;
                novo->prox = aux->prox;
                aux->prox = novo;
            }
        }
}

void enfileiraFilaDecrescente(FilaEnc *fila, int andar, int num_passageiros) {
    if (vaziaFila(fila))
        enfileiraFila(fila, andar, num_passageiros);
    else {
        NodoLEnc *novo = (NodoLEnc*)malloc(sizeof(NodoLEnc));
        novo->andar = andar;
        novo->num_passageiros = num_passageiros;
        if (fila->ini->andar < andar) {
            NodoLEnc *aux = fila->ini;
            fila->ini = novo;
            novo->prox = aux;
        } else if (andar < fila->fim->andar) {
            fila->fim->prox = novo;
            fila->fim = novo;
        } else {
            NodoLEnc *aux = fila->ini;
            while (aux->prox->andar > andar)
                aux = aux->prox;
            novo->prox = aux->prox;
            aux->prox = novo;
        }
    }
}

// Funcao que remove um elemento da fila
int desenfileiraFila(FilaEnc *fila){
   NodoLEnc *aux = fila->ini;
   int num_passageiros = aux->num_passageiros;
   fila->ini = aux->prox;
   if (fila->ini == NULL)
      fila->fim = NULL;
   free(aux);
   return num_passageiros;
}

// Funcao que determina se uma fila eh vazia
int vaziaFila(FilaEnc *fila){
   return (fila->ini == NULL);
}

NodoLEnc* exibeNodoEnc(NodoLEnc *raiz) {
    if (raiz == NULL)
        return raiz;
    printf("%d (%d) | ", raiz->andar, raiz->num_passageiros);
    exibeNodoEnc(raiz->prox);
}

void exibeFila(FilaEnc *fila) {
    if (vaziaFila(fila))
        printf("Fila vazia.");
    else
        exibeNodoEnc(fila->ini);
    printf("\n");
}

NodoLEnc *buscaNodo (FilaEnc *fila, int andar) {
    NodoLEnc *aux = fila->ini;
    while (aux != NULL) {
        if (aux->andar == andar)
            return aux;
        aux = aux->prox;
    }
    return NULL;
}

NodoLEnc *copiaNodos (NodoLEnc *nodo) {
    if (nodo == NULL)
        return NULL;
    NodoLEnc *copia = (NodoLEnc*)malloc(sizeof(NodoLEnc));
    copia->andar = nodo->andar;
    copia->num_passageiros = nodo->num_passageiros;
    copia->prox = copiaNodos(nodo->prox);
    return copia;
}

FilaEnc *copiaFila(FilaEnc *fila) {
    if (fila == NULL)
        return NULL;
    FilaEnc *copia = criaFila();
    if(!vaziaFila(fila)) {
        copia->ini = copiaNodos(fila->ini);
        NodoLEnc *aux = copia->ini;
        while(aux->prox != NULL)
            aux = aux->prox;
        copia->fim = aux;
    }
    return copia;
}
