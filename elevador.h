#ifndef _ELEVATOR_C_
#define _ELEVATOR_C_

#include "fila_enc.h"

#define tempoParado  15
#define tempoMovendo 5

typedef struct {
    int id;
    int estado; /* 0 - Parado
                   1 - Subindo
                   2 - Descendo */
    int andar_atual;
    int num_passageiros;
    FilaEnc *destino;
} Elevador;

// Cria elevador
Elevador *criaElevador();

// Exibe dados do elevador
void exibeElevador(Elevador *elevador);

// Move elevador na direção de destino->ini, não é eficiente
void move_elevador (Elevador *elevador);

// Destroi elevador
void destroiElevador (Elevador *elevador);

// Retorna o elevador mais proximo de um andar, com a mesma direcao
Elevador *elevadorMaisProx (Elevador **elevadores, int numElevadores, int andar, int direcao);

int tempoAtenderChamada (Elevador *elevador, int andar, int direcao);

void gerenciaChamadas (FilaEnc *sobe, FilaEnc *desce, Elevador **elevador, int numElevadores);

#endif
