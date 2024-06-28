#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  
#include <string.h>  

typedef struct {
    int origem;
    int numero_protocolo;
    float mes;
    float ano;
    int tipo_produto;
    float peso_bruto_produto;
    float peso_limpo;
    float media_guc;
} Registro;

void relatorioMesEspecifico(const char *nome_arquivo, int mes_escolhido) {
    FILE *arquivo;
    Registro reg;
    int encontrou_registros = 0;

    arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    printf("\n\nMês: %d\n", mes_escolhido);
    printf("\nOrigem   Cargas  GU Faixa 1    GU Faixa 2    GU Faixa 3    GU Extra\n");
    printf("-------+--------+------------+------------+------------+------------\n");

    // Lê cada registro do arquivo e imprime apenas os do mês ESCOLHIDO
    while (fread(&reg, sizeof(Registro), 1, arquivo) == 1) {
        if ((int)reg.mes == mes_escolhido) {
            encontrou_registros = 1;

            printf("   %d  ", reg.origem);
            printf("   %d  ", reg.numero_protocolo);

        
            if (reg.media_guc >= 0 && reg.media_guc <= 8.5) {
                printf("              %.2f\n", reg.media_guc);
            } else if (reg.media_guc > 8.5 && reg.media_guc <= 15.0) {
                printf("                  %.2f\n", reg.media_guc);
            } else if (reg.media_guc > 15.0 && reg.media_guc <= 25.0) {
                printf("                      %.2f\n", reg.media_guc);
            } else {
                printf("\n"); 
            }
        }
    }

    // Se não encontrou registros para o mês
    if (!encontrou_registros) {
        printf("Nenhum registro encontrado para o mês %d\n", mes_escolhido);
    }

    // Fecha o arquivo
    fclose(arquivo);
}

// Função para gerar relatórios de todos os meses consecutivos
void gerarRelatorioTodosMeses(const char *nome_arquivo) {
    FILE *arquivo;
    Registro reg;
    int mes;

    // Abre o arquivo para leitura binária
    arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo");
        return;
    }

    for (mes = 1; mes <= 12; ++mes) {
        int encontrou_registros = 0;

        // Imprime cabeçalho do mês
        printf("\n\nMês: %d\n", mes);
        printf("\nOrigem   Cargas  GU Faixa 1    GU Faixa 2    GU Faixa 3    GU Extra\n");
        printf("-------+--------+------------+------------+------------+------------\n");

        // Lê cada registro do arquivo e imprime apenas os do mês atual
        while (fread(&reg, sizeof(Registro), 1, arquivo) == 1) {
            if ((int)reg.mes == mes) {
                encontrou_registros = 1;

                printf("   %d  ", reg.origem);
                printf("   %d  ", reg.numero_protocolo);

                
                if (reg.media_guc >= 0 && reg.media_guc <= 8.5) {
                    printf("              %.2f\n", reg.media_guc);
                } else if (reg.media_guc > 8.5 && reg.media_guc <= 15.0) {
                    printf("                  %.2f\n", reg.media_guc);
                } else if (reg.media_guc > 15.0 && reg.media_guc <= 25.0) {
                    printf("                      %.2f\n", reg.media_guc);
                } else {
                    printf("\n"); 
                }
            }
        }

        // Retorna ao início do arquivo para o próximo mês
        rewind(arquivo);

        // Se não encontrou registros para o mês
        if (!encontrou_registros) {
            printf("Nenhum registro encontrado para o mês %d\n", mes);
        }
    }

    
    fclose(arquivo);
}


void mensal(const char *nome_arquivo) {
    int escolha;

    do {
        printf("\nDigite:\n");
        printf("1. para Gerar relatório de um mês específico\n");
        printf("2. para Gerar relatório de todos os meses (mês a mês)\n");
        printf("3. para Sair\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                int mes_rel;
                printf("\nDigite o número do mês (1 a 12):\n");
                scanf("%d", &mes_rel);
                if (mes_rel >= 1 && mes_rel <= 12) {
                    relatorioMesEspecifico(nome_arquivo, mes_rel);
                } else {
                    printf("Opção Inválida!\n");
                }
                break;
            }
            case 2:
                gerarRelatorioTodosMeses(nome_arquivo);
                break;
            case 3:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção Inválida!\n");
        }
    } while (escolha != 3); 
}

int main() {
    const char *nome_arquivo = "GraosRecebidos-2024.dat"; // Nome do arquivo .dat 

    // Configura o locale para português (Brasil)
    setlocale(LC_ALL, "Portuguese_Brazil");

    // Chamada para ler os registros do arquivo .dat e imprimir de acordo com a opção 
    mensal(nome_arquivo);

    return 0;
}
