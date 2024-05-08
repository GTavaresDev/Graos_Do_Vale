#include <stdio.h> 
#include <math.h> 
#include <time.h> 
#include "funcoes.h"

// Preciso encontrar uma forma de voltar para o menu sem que o programa seja fechado antes 
// Função principal
int main() {
    int opcao = menu();
    
    switch (opcao) {
        case 1:
            //determinar();
            break;
        case 2:
            //arquivar();
            break;
        case 3:
            gerar_relatorios();
            break;
        default:
            printf("\n Opcao invalida! Escolha entre 1, 2 ou 3.");
            break;
    }

    return 0;
}


