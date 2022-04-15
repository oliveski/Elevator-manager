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

int enfileiraFilaOrdenado(FilaEnc *fila, int andar, int num_passageiros) {
    if (vaziaFila(fila))
        enfileiraFila(fila, andar, num_passageiros);
    else {
        NodoLEnc *aux = fila->ini;
        NodoLEnc *novo = (NodoLEnc*)malloc(sizeof(NodoLEnc));
        novo->andar = andar;
        if (aux->prox == NULL) {
            if (aux->andar < andar)
                enfileiraFila(fila, andar, num_passageiros);
            else {
                fila->ini = novo;
                novo->prox = fila->fim;
            }
        } else if (fila->ini->andar > andar) {
            novo->prox = fila->ini;
            fila->ini = novo;
        } else {
            while (aux->prox->andar < andar) {
                if (aux->prox == fila->fim) {
                    enfileiraFila(fila, andar, num_passageiros);
                    return 1;
                }
                aux = aux->prox;
            }
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
    exibeNodoEnc(fila->ini);
    printf("\n");
}
