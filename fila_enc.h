#ifndef _FILA_ENC_H_
#define _FILA_ENC_H_

typedef struct nodoLEnc{
   int andar;
   int num_passageiros;
   struct nodoLEnc *prox;
} NodoLEnc;

typedef struct filaEnc{
   struct nodoLEnc *ini;
   struct nodoLEnc *fim;
} FilaEnc;

// Funcao que cria uma fila
FilaEnc* criaFila();

// Funcao que destroi uma fila
void destroiFila(FilaEnc *fila);

// Funcao que insere um elemento na fila
void enfileiraFila(FilaEnc *fila, int andar, int num_passageiros);

// Função que insere um elemento na fila de forma ordenada
int enfileiraFilaOrdenado(FilaEnc *fila, int andar, int num_passageiros);

// Funcao que remove um elemento da fila
int desenfileiraFila(FilaEnc *fila);

// Funcao que determina se uma fila eh vazia
int vaziaFila(FilaEnc *fila);

// Função que exibe fila
void exibeFila(FilaEnc *fila);
#endif
