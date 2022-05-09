#include "fila_enc.h"
#include "elevador.h"
#include <stdio.h>
#include <stdlib.h>

Elevador** criaElevadores (int numElevadores);
void destroiElevadores (Elevador** elevador, int numElevadores);

void main(){
    int numElevadores = 1;
    int numAndares = 5;

    Elevador** elevador = criaElevadores(numElevadores);

    FilaEnc *sobe, *desce;

    sobe = criaFila();
    desce = criaFila();


    geraChamadas(sobe, numAndares, 2);
    geraChamadas(desce, numAndares, 2);
    exibeFila(sobe);
    exibeFila(desce);
    puts("");
    gerenciaChamadas(sobe, desce, elevador, numElevadores);
    while (elevadorMovendo(elevador, numElevadores)) {
        for (int i = 0; i < numElevadores; i++) {
            exibeElevador(elevador[i]);
            move_elevador(elevador[i]);
            atualizaElevador(elevador[i]);
            puts("");
        }
        gerenciaChamadas(sobe, desce, elevador, numElevadores);
        printf("Chamadas:\n");
        printf("Sobe:  "); exibeFila(sobe);
        printf("Desce: "); exibeFila(desce);
        puts("");
    }

    destroiElevadores(elevador, numElevadores);
    destroiFila(sobe);
    destroiFila(desce);

}

Elevador** criaElevadores (int numElevadores) {
    Elevador **elevador = (Elevador**)malloc(numElevadores*sizeof(Elevador));
    for (int i = 0; i < numElevadores; i++) {
        elevador[i] = criaElevador();
        elevador[i]->id = i+1;
    }
    return elevador;
}

void destroiElevadores (Elevador** elevador, int numElevadores) {
    for (int i = 0; i < numElevadores; i++)
        destroiElevador(elevador[i]);
}
