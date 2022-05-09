#include "elevador.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

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
    if (elevador != NULL) {
        printf("Elevador #%d\n", elevador->id);
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
    } else
        printf("Elevador indisponivel.\n");
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
            desenfileiraFila(elevador->destino);
        }
    }
}

void atualizaElevador (Elevador *elevador) {
    if (!vaziaFila(elevador->destino)) {
        int destino = elevador->destino->ini->andar;
        int andar_atual = elevador->andar_atual;
        int num_passageiros = elevador->destino->ini->num_passageiros;

        if (destino == andar_atual) {
            printf("Embarque\\Desembarque...\n");
            elevador->num_passageiros += num_passageiros;
            //desenfileiraFila(elevador->destino);
        }
    }
}

void destroiElevador (Elevador *elevador) {
    destroiFila(elevador->destino);
    free(elevador);
}

int tempoAteAndar (Elevador *elevador, int andar) {
    if (elevador == NULL)
        return -1;
    int tempo = 0;
    Elevador *aux = copiaElevador(elevador);
    enfileiraFila(aux->destino, andar, 0);
    while (!vaziaFila(aux->destino)) {
        //printf("Turno: %d\tAndar: %d\n", tempo,  aux->andar_atual);
        if (aux->andar_atual == andar)
            break;
        move_elevador(aux);
        tempo++;
    }
    destroiElevador(aux);
    //printf("TT: %d\n", tempo);
    return tempo;
}

Elevador *elevadorMaisProx (Elevador **elevador, int numElevadores, int andar, int direcao) {
    int menorTempo = INT_MAX;
    Elevador *maisProx = NULL;

    for (int i = 0; i < numElevadores; i++) {
        if (elevador[i]->estado == 0 && vaziaFila(elevador[i]->destino)) {
            if (tempoAteAndar(elevador[i], andar) < menorTempo) {
                menorTempo = tempoAteAndar(elevador[i], andar);
                maisProx = elevador[i];
            }
        } else if (direcao == 1) {
            if (elevador[i]->andar_atual <= andar) {
                if (elevador[i]->estado == 0) {
                    if (proximoPassoElevador(elevador[i]) == 1) {
                        if (tempoAteAndar(elevador[i], andar) < menorTempo) {
                            menorTempo = tempoAteAndar(elevador[i], andar);
                            maisProx = elevador[i];
                        }
                    }
                } else if (elevador[i]->estado == 1) {
                    if (tempoAteAndar(elevador[i], andar) < menorTempo) {
                        menorTempo = tempoAteAndar(elevador[i], andar);
                        maisProx = elevador[i];
                    }
                }
            }
        } else if (direcao == 2) {
            if (elevador[i]->andar_atual >= andar) {
                if (elevador[i]->estado == 0) {
                    if (proximoPassoElevador(elevador[i]) == 2) {
                        if (tempoAteAndar(elevador[i], andar) < menorTempo) {
                            menorTempo = tempoAteAndar(elevador[i], andar);
                            maisProx = elevador[i];
                        }
                    }
                } else if (elevador[i]->estado == 2) {
                    if (tempoAteAndar(elevador[i], andar) < menorTempo) {
                        menorTempo = tempoAteAndar(elevador[i], andar);
                        maisProx = elevador[i];
                    }
                }
            }
        }
        //printf("Menor tempo: %d\n", menorTempo);
    }
    return maisProx;
}

void gerenciaChamadas (FilaEnc *sobe, FilaEnc *desce, Elevador **elevador, int numElevadores) {
    FilaEnc *espera = criaFila();
    NodoLEnc *aux = sobe->ini;
    while (aux != NULL) {
        Elevador *maisProx = elevadorMaisProx(elevador, numElevadores, aux->andar, 1);
        if (maisProx != NULL) {
            enfileiraFilaCrescente(maisProx->destino, aux->andar, aux->num_passageiros);
        } else {
            enfileiraFila(espera, aux->andar, aux->num_passageiros);
        }
        aux = aux->prox;
        desenfileiraFila(sobe);
    }
    destroiFila(sobe);
    sobe = copiaFila(espera);
    while (!vaziaFila(espera)) // Esvazia espera
        desenfileiraFila(espera);
    //printf("Sobe:  "); exibeFila(sobe);
    //printf("Desce: "); exibeFila(desce);
    aux = desce->ini;
    while (aux != NULL) {
        Elevador *maisProx = elevadorMaisProx(elevador, numElevadores, aux->andar, 2);
        if (maisProx != NULL) {
            enfileiraFilaDecrescente(maisProx->destino, aux->andar, aux->num_passageiros);
        } else {
            enfileiraFila(espera, aux->andar, aux->num_passageiros);
        }
        aux = aux->prox;
        desenfileiraFila(desce);
    }
    destroiFila(desce);
    desce = copiaFila(espera);
    //printf("Sobe:  "); exibeFila(sobe);
    //printf("Desce: "); exibeFila(desce);
    destroiFila(espera);
}

int proximoPassoElevador (Elevador *elevador) {
    if (vaziaFila(elevador->destino) || elevador->andar_atual == elevador->destino->ini->andar)
        return 0;
    else if (elevador->andar_atual < elevador->destino->ini->andar)
        return 1;
    else if (elevador->andar_atual > elevador->destino->ini->andar)
        return 2;
}

Elevador *copiaElevador (Elevador *elevador) {
    Elevador *aux = criaElevador();
    aux->id = elevador->id;
    aux->estado = elevador->estado;
    aux->andar_atual = elevador->andar_atual;
    aux->num_passageiros = elevador->num_passageiros;
    aux->destino = copiaFila(elevador->destino);
    return aux;
}

int elevadorMovendo (Elevador **elevador, int numElevadores) {
    for (int i = 0; i < numElevadores; i++)
        if (elevador[i]->estado || !vaziaFila(elevador[i]->destino))
            return 1;
    return 0;
}

void geraChamadas (FilaEnc *fila, int numAndares, int numChamadas) {
    for (int i = 0; i < numChamadas; i++)
        enfileiraFila(fila, rand()%numAndares + 1, rand()%MAX_PASSAGEIROS + 1);
}
