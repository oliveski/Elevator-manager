#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "elevador.h"
#include "fila_enc.h"


Elevador** criaElevadores (int numElevadores);
void destroiElevadores (Elevador** elevador, int numElevadores);

int main() {
    int op;
    int numElevadores = 1;
    int numAndares = 15;
    FilaEnc *sobe, *desce;
    Elevador **elevador = NULL;

    sobe = criaFila();
    desce = criaFila();

    srand(time(NULL));

    do {
        printf("=============== ELEVATOR MANAGER ===============\n");
        printf("1. Configurar variaveis: \n");
        printf("2. Iniciar Simulacao: \n");
        printf("3. Sair\n");
        printf("Opcao: ");
        scanf(" %d", &op);

        switch (op) {
            case 1: {
                if (elevador != NULL)
                    for (int i = 0; i < numElevadores; i++)
                        destroiElevador(elevador[i]);
                printf("Numero de elevadores: " ); scanf(" %d", &numElevadores);
                printf("Numero de andares: "); scanf(" %d", &numAndares);
                elevador = (Elevador**)malloc(numElevadores*sizeof(Elevador));

                //inicia elevadores
                for (int i = 0; i < numElevadores; i++) {
                    elevador[i] = criaElevador();
                    elevador[i]->id = i+1;
                }
                geraChamadas(sobe, numAndares, 2);
                geraChamadas(desce, numAndares, 2);
                break;
            }

            case 2: {
                int turno = 0;
                printf("\nIniciando Simulacao...\n\n");
                printf("Chamadas: \n");
                printf("Sobe:  "); exibeFila(sobe);
                printf("Desce: "); exibeFila(desce);
                gerenciaChamadas(sobe, desce, elevador, numElevadores);

                do {
                    printf("\nTurno: %d\n", turno++);
                    gerenciaChamadas(sobe, desce, elevador, numElevadores);
                    for (int i = 0; i < numElevadores; i++) {
                        exibeElevador(elevador[i]);
                        move_elevador(elevador[i]);
                    }
                    printf("Chamadas: \n");
                    printf("Sobe:  "); exibeFila(sobe);
                    printf("Desce: "); exibeFila(desce);
                    scanf(" %c", &op);
                } while (op == '\n');
                break;
            }
            case 3: {
                destroiFila(sobe);
                destroiFila(desce);

                // destroi elevador
                for (int i = 0; i < numElevadores; i++)
                    destroiElevador(elevador[i]);
                printf("Saindo...\n");
                break;
            }
            default:
                printf("Opcao invalida.\n");
        }
        puts("");
    } while (op != 3);
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
