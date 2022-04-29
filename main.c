#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include "elevador.h"
#include "fila_enc.h"

int main() {
    FilaEnc *sobe, *desce;

    sobe = criaFila();
    desce = criaFila();
    int numElevadores = 2;
    Elevador **elevador = (Elevador**)malloc(numElevadores*sizeof(Elevador));

    //inicia elevador
    for (int i = 0; i < numElevadores; i++) {
        elevador[i] = criaElevador();
        //enfileiraFila(elevador[i]->destino, 0, 0);
        elevador[i]->id = i+1;
    }

    //enfileiraFila(sobe, 1, 0);
    enfileiraFila(sobe, 2, 0);
    //enfileiraFila(sobe, 1, 0);
    //enfileiraFila(sobe, 5, 0);
    //enfileiraFila(sobe, 6, 0);
    //enfileiraFila(desce, 2, 0);
    //enfileiraFila(desce, 3, 0);
    //enfileiraFila(desce, 6, 0);
    //enfileiraFila(desce, 7, 0);

    /*Elevador *maisProx;
    NodoLEnc *aux = sobe->ini;
    while(aux != NULL) {
        maisProx = elevadorMaisProx(elevador, numElevadores, aux->andar, 1);
        printf("Elevador mais prox de %d: #%d\n", aux->andar, maisProx->id);
        enfileiraFilaCrescente(maisProx->destino, aux->andar, aux->num_passageiros);
        aux = aux->prox;
    }*/
    gerenciaChamadas(sobe, desce, elevador, numElevadores);
    puts("");
    for (int i = 0; i < numElevadores; i++) {
        exibeElevador(elevador[i]);
    }




    destroiFila(sobe);
    destroiFila(desce);

    // destroi elevador
    for (int i = 0; i < numElevadores; i++)
        destroiElevador(elevador[i]);
    return 0;
}
