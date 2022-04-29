#ifndef _FILA_ENC_H_
#define _FILA_ENC_H_

typedef struct nodoLEnc {
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

// Função que insere um elemento na fila de forma crescente
void enfileiraFilaCrescente(FilaEnc *fila, int andar, int num_passageiros);

// Função que insere um elemento na fila de forma decrescente
void enfileiraFilaDecrescente(FilaEnc *fila, int andar, int num_passageiros);

// Função que insere um nodo no fim da fila
void enfileiraFilaFinal(FilaEnc *fila,int andar, int num_passageiros);

// Funcao que remove um elemento da fila
int desenfileiraFila(FilaEnc *fila);

// Funcao que determina se uma fila eh vazia
int vaziaFila(FilaEnc *fila);

// Função que exibe fila
void exibeFila(FilaEnc *fila);

// Função que busca nodo; retorna o endereço do nodo, se ele existir na fila, returna NULL caso contrário
NodoLEnc *buscaNodo (FilaEnc *fila, int andar);
#endif
