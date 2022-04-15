#include "elevador.h"
#include "fila_enc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função que cria elevador;
Elevador *criaElevador () {
    Elevador *elevador = (Elevador*)malloc(sizeof(Elevador));
    elevador->estado = 0;	// começa parado
    elevador->andar_atual = 1;	// no primeiro andar
    elevador->num_passageiros = 0; // e sem passageiros
    elevador->destino = criaFila();
    return elevador;
}

void exibeElevador(Elevador *elevador) {
    printf("Estado: %d ", elevador->estado);
    if (elevador->estado == 0)
        printf("(parado)\n");
    else if (elevador->estado == 1)
        printf("(subindo)\n");
    else
        printf("(descendo)\n");
    printf("Andar atual: %d\n", elevador->andar_atual);
    printf("Numero de Passageiros: %d\n", elevador->num_passageiros);
    printf("Fila: ");
    exibeFila(elevador->destino);
    if (elevador->estado == 0)
        printf("Embarque\\Desenbarque de pessoas\nPor favor, espere...\n");
    printf("\n");
}


void move_elevador (Elevador *elevador) {
    if (!vaziaFila(elevador->destino)) {
        if (elevador->andar_atual < elevador->destino->ini->andar) {
            elevador->estado = 1;	// elevador sobe
            elevador->andar_atual++;	// subo 1 andar
        } else if (elevador->andar_atual > elevador->destino->ini->andar) {
            elevador->estado = 2;	// elevador desce
            elevador->andar_atual--;	// desco um andar
        } else {
            elevador->estado = 0;	// to aqui ja
            desenfileiraFila(elevador->destino);  // galera desce
        }
    }
}

void destroiElevador (Elevador *elevador) {
    destroiFila(elevador->destino);
    free(elevador);
}
