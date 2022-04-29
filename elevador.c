#include "elevador.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
        if (elevador->estado == 0)
            printf("Embarque\\Desenbarque de pessoas\nPor favor, espere...\n");
        printf("\n");
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
            desenfileiraFila(elevador->destino);  // galera desce
        }
    }
}

void destroiElevador (Elevador *elevador) {
    destroiFila(elevador->destino);
    free(elevador);
}


int tempoAtenderChamada (Elevador *elevador, int andar, int direcao)
{
    int tempo = 0;

    switch (elevador->estado) {
        case 0: {
            if (vaziaFila(elevador->destino)) {
                if (elevador->andar_atual < andar) {
                    for (int i = elevador->andar_atual; i <= andar; i++)
                        tempo += tempoMovendo;
                    return tempo;
                } else if (elevador->andar_atual > andar) {
                    for (int i = elevador->andar_atual <= andar; i >= andar; i--) {
                        tempo += tempoMovendo;
                    }
                    return tempo;
                } else
                    return 0;
            }
            else {
                if (elevador->andar_atual < elevador->destino->fim->andar) {
                    for (int i = elevador->andar_atual; i <= elevador->destino->fim->andar; i++) {
                        if (buscaNodo(elevador->destino, i) != NULL)
                            tempo += tempoParado;
                        else
                            tempo += tempoMovendo;
                        }
                } else if (elevador->andar_atual > elevador->destino->fim->andar) {
                    for (int i = elevador->andar_atual; i >= elevador->destino->fim->andar; i--) {
                        if (buscaNodo(elevador->destino, i) != NULL)
                            tempo += tempoParado;
                        else
                            tempo += tempoMovendo;
                        }
                    }
                return tempo;
            }
        }
        case 1: {
            if (elevador->andar_atual < andar) {
                for (int i = elevador->andar_atual; i <= andar; i++) {
                    if (buscaNodo(elevador->destino, i) != NULL)
                        tempo += tempoParado;
                    else
                        tempo += tempoMovendo;
                }
                return tempo;
            } else if (elevador->andar_atual > andar) {
                for (int i = elevador->andar_atual; i >= elevador->destino->fim->andar; i--) {
                    if (buscaNodo(elevador->destino, i) != NULL)
                        tempo += tempoParado;
                    else
                        tempo += tempoMovendo;
                    }
                return tempo;
            } else
                return 0;
        }
        case 2: {
            if (elevador->andar_atual < andar) {
                for (int i = elevador->andar_atual; i >= elevador->destino->fim->andar; i--) {
                    if (buscaNodo(elevador->destino, i) != NULL)
                        tempo += tempoParado;
                    else
                        tempo += tempoMovendo;
                }
                return tempo;
            } else if (elevador->andar_atual > andar) {
                for (int i = elevador->andar_atual; i <= andar; i++) {
                    if (buscaNodo(elevador->destino, i) != NULL)
                        tempo += tempoParado;
                    else
                        tempo += tempoMovendo;
                }
                return tempo;
            } else
                return 0;
        }
    }
}

Elevador *elevadorMaisProx(Elevador **elevador, int numElevadores, int andar, int direcao) {
    Elevador *maisProx = elevador[0];
    int menorTempo = tempoAtenderChamada(elevador[0], andar, direcao);
    //puts("done");
    for (int i = 1; i < numElevadores; i++) {
        if (tempoAtenderChamada(elevador[i], andar, direcao) < menorTempo) {
            maisProx = elevador[i];
            menorTempo = tempoAtenderChamada(elevador[i], andar, direcao);
        }
    }
    return maisProx;
}

void gerenciaChamadas (FilaEnc *sobe, FilaEnc *desce, Elevador **elevador, int numElevadores) {
    NodoLEnc *aux;
    while (!vaziaFila(sobe)) {
        aux = sobe->ini;
        Elevador *maisProx = elevadorMaisProx(elevador, numElevadores, aux->andar, 1);

        switch (maisProx->estado) {
            case 0: {
                if (vaziaFila(maisProx->destino))
                    enfileiraFila(maisProx->destino, aux->andar, aux->num_passageiros);

                else if (maisProx->andar_atual < maisProx->destino->ini->andar) // Elevador vai subir
                    enfileiraFilaCrescente(maisProx->destino, aux->andar, aux->num_passageiros);

                else if (maisProx->andar_atual > maisProx->destino->ini->andar) // Elevador vai descer
                    enfileiraFilaDecrescente(maisProx->destino, aux->andar, aux->num_passageiros);

                break;
            }

            case 1: {
                if (vaziaFila(maisProx->destino))
                    enfileiraFila(maisProx->destino, aux->andar, aux->num_passageiros);

                else if (aux->andar < maisProx->andar_atual)
                    enfileiraFilaFinal(maisProx->destino, aux->andar, aux->num_passageiros);

                else if (aux->andar > maisProx->andar_atual)
                    enfileiraFilaCrescente(maisProx->destino, aux->andar, aux->num_passageiros);

                break;
            }

            case 2: {
                if (vaziaFila(maisProx->destino))
                    enfileiraFila(maisProx->destino, aux->andar, aux->num_passageiros);

                else if (aux->andar < maisProx->andar_atual)
                    enfileiraFilaDecrescente(maisProx->destino, aux->andar, aux->num_passageiros);

                else if (aux->andar > maisProx->andar_atual)
                    enfileiraFilaFinal(maisProx->destino, aux->andar, aux->num_passageiros);

                break;
            }
        }
    //    puts("teste");
        desenfileiraFila(sobe);
    }

    while (!vaziaFila(desce)) {
        aux = desce->ini;

        Elevador *maisProx = elevadorMaisProx(elevador, numElevadores, aux->andar, 2);

        switch (maisProx->estado) {
            case 0: {
                if (vaziaFila(maisProx->destino))
                    enfileiraFila(maisProx->destino, aux->andar, aux->num_passageiros);

                else if (maisProx->andar_atual < maisProx->destino->ini->andar) // Elevador vai subir
                    enfileiraFilaCrescente(maisProx->destino, aux->andar, aux->num_passageiros);

                else if (maisProx->andar_atual > maisProx->destino->ini->andar) // Elevador vai descer
                    enfileiraFilaDecrescente(maisProx->destino, aux->andar, aux->num_passageiros);

                break;
            }

            case 1: {
                if (vaziaFila(maisProx->destino))
                    enfileiraFila(maisProx->destino, aux->andar, aux->num_passageiros);

                else if (aux->andar < maisProx->andar_atual)
                    enfileiraFilaFinal(maisProx->destino, aux->andar, aux->num_passageiros);

                else if (aux->andar > maisProx->andar_atual)
                    enfileiraFilaCrescente(maisProx->destino, aux->andar, aux->num_passageiros);

                break;
            }

            case 2: {
                if (vaziaFila(maisProx->destino))
                    enfileiraFila(maisProx->destino, aux->andar, aux->num_passageiros);

                else if (aux->andar < maisProx->andar_atual)
                    enfileiraFilaDecrescente(maisProx->destino, aux->andar, aux->num_passageiros);

                else if (aux->andar > maisProx->andar_atual)
                    enfileiraFilaFinal(maisProx->destino, aux->andar, aux->num_passageiros);

                break;
            }
        }

        desenfileiraFila(desce);
    }
}
