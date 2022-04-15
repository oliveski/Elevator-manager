#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include "elevador.h"
#include "fila_enc.h"

int main() {
    Elevador *elevador;
    FilaEnc *sobe, *desce;

    sobe = criaFila();
    desce = criaFila();
    elevador = criaElevador();

    /***** Chamadas de teste do elevador ******/
    enfileiraFila(elevador->destino, 2, 10);
    enfileiraFila(elevador->destino, 3, 10);
    enfileiraFila(elevador->destino, 6, 10);
    enfileiraFila(elevador->destino, 5, 10);
    enfileiraFila(elevador->destino, 9, 10);
    enfileiraFila(elevador->destino, 7, 10);
    /******************************************/

    while(!vaziaFila(elevador->destino)) {
        exibeElevador(elevador);
        move_elevador(elevador);
        getchar();
    }
    exibeElevador(elevador);

    destroiFila(sobe);
    destroiFila(desce);
    destroiElevador(elevador);
    return 0;
}
