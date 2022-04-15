# Elevator-manager
Trabalho final da disciplina de Estruturas de Dados I, feito em colaboração com Lucas Caique e Leonardo Lambiase.

# Dependência

+ GSL

Usamos a interface de geração de números pseudo-aleatórios da [GSL](https://www.gnu.org/software/gsl/) para dar conta das chamadas ao elevador sorteando andares e número de passageiros.

# Mudanças

Eu resolvi seguir a idéia do Leonardo e centralizar as chamadas dos elevadores. O que vocês vão ver no código é que a estrutura Elevador agora possui apenas um lista, elevador->destino, ela controla a ordem de visitas do elevador aos andares. Provavelmente nós iremos querer modificar a forma como organizamos ela, mas por enquanto funciona.

As filas 'sobe' e 'desce' agora são criadas diretamente no main. A idéia é que a função que gere as chamadas aleatórias manipule essas filas.

Além disso, o cerébro do código é a função move_elevador. Ela checa se a lista destino está vazia, e se não, altera o estado do elevador e o move. Caso o elevador chegue a algum andar de destino, a função muda o estado do elevador para parado, e exibe um mensagem.

Os código da TAD de Filas é quase o mesmo. Eu adcionei uma função chamada enfileiraFilaOrdenada, que enfileira itens numa fila de forma a manter-la em ordem crescente.

Mais um detalhe, no código atual, o elevador não transporta passageiros, só visita os andares da lista. Provavelmente, a melhor saida é criar uma função que gere um numero aleátorio de passageiros para entrar/sair dos elevadores quando se chega aos andares de destino.


