#ifndef _ELEVATOR_C_
#define _ELEVATOR_C_

#include "fila_enc.h"

#define MAX_PASSAGEIROS 15

typedef struct {
    int id;	// identificador do elevador
    int estado; /* 0 - Parado
                   1 - Subindo
                   2 - Descendo */
    int andar_atual;
    int num_passageiros;
    FilaEnc *destino;
} Elevador;

// Cria elevador
Elevador *criaElevador();

// Funcao que cria um vetor de elevadores
Elevador** criaElevadores (int numElevadores);

// Funcao que libera o vetor de elevadores
void destroiElevadores (Elevador** elevador, int numElevadores);

// Exibe dados do elevador
void exibeElevador(Elevador *elevador);

// Move elevador na direção de destino->ini, não é eficiente
void move_elevador (Elevador *elevador);

// Funcao que atualiza o numero de pessoas no elevador ao chegar em um destino
void atualizaElevador (Elevador *elevador);

// Destroi elevador
void destroiElevador (Elevador *elevador);

// Retorna o elevador mais proximo de um andar, com a mesma direcao
Elevador *elevadorMaisProx (Elevador **elevadores, int numElevadores, int andar, int direcao);

void gerenciaChamadas (FilaEnc *sobe, FilaEnc *desce, Elevador **elevador, int numElevadores);

int distanciaElevador (Elevador *elevador, int andar);

// Funcao que diz se um elevador vai ficar parado, subir ou descer em seguida
int proximoPassoElevador (Elevador *elevador);

// Funcao que determina quantos passos sao necessarios para um elevador chegar a um andar
int tempoAteAndar (Elevador *elevador, int andar);

/* Elevador *copiaElevador (Elevador *elevador); */

/* int elevadorMovendo (Elevador **elevador, int numElevadores); */

// Funcao que gera chamadas aleatorias para elevadores
void geraChamadas (FilaEnc *fila, int numAndares, int numChamadas);

#endif
