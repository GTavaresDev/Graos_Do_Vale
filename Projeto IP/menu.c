#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"
#define MAX_AMOSTRAS 100
#define MAX_INDICADORES 1024

// Definindo o tipo de estrutura utilizada para a ordem de gravação no banco de dados
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

// Que verifica se a data é valida
int data_valida(int mes, int ano) {
    if (ano < 1900 || ano > 2100)
        return 0;
    if (mes < 1 || mes > 12)
        return 0;
    return 1;
}

// Função que verifica se o usario não digitando uma data futura 
int data_nao_futura(int mes, int ano) {
    time_t t = time(NULL);
    struct tm *dataAtual = localtime(&t);

    int anoAtual = dataAtual->tm_year + 1900;
    int mesAtual = dataAtual->tm_mon + 1;

    if (ano > anoAtual)
        return 0;
    if (ano == anoAtual && mes > mesAtual)
        return 0;

    return 1;
}

int menu() {
    int opcao;
    do {
        printf("\n ");
        printf("\n ");
        printf("\n Ola usuario, esse e o sistema da empresa Graos Do Vale");
        printf("\n Digite:");
        printf("\n ");
        printf("\n 1. para Descricao de Carregamento");
        printf("\n 2. para Resumo Quantitativo Mensal");
        printf("\n 3. para Resumo Geral Quantitativo e Qualitativo");
        printf("\n 0. para FECHAR O PROGRAMA");
        printf("\n ");
        printf("\n ");
        printf("\n Digite sua opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                carregamento();
                break;
            case 2:
                resumo_qtd_mensal();
                break;
            case 3:
                resumo_geral();
                break;
            case 0:
                printf("\n Fechando o programa...");
                break;
            default:
                printf("\n Opcao invalida! Escolha entre 1, 2, 3 ou 0.");
                break;
        }
    } while (opcao != 0);

    return opcao;
}

    // Função de carregamento de dados, onde o usario passa o nome do arquivo e a data onde sera armazenado.
int carregamento() {
    char nome_arquivo[40];
    char dataStr[10];
    int mes, ano;

    printf("\n Digite o nome do arquivo: ");
    if (scanf("%39s", nome_arquivo) != 1) {
        printf("\n Erro ao ler o nome do arquivo.");
        return 0;
    }

    printf("\n Digite a data de recebimento (MM/AAAA): ");
    if (scanf("%9s", dataStr) != 1) {
        printf("\n Erro ao ler a data de recebimento.");
        return 0;
    }

    if (sscanf(dataStr, "%d/%d", &mes, &ano) != 2) {
        printf("\n Formato de data invalido.");
        return 0;
    }

    if (!data_valida(mes, ano)) {
        printf("\n Data invalida.");
        return 0;
    }

    if (!data_nao_futura(mes, ano)) {
        printf("\n Erro: A data inserida e futura.");
        return 0;
    }

    FILE *file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        perror("\n Erro ao abrir o arquivo");
        return 0;
    }

    // Declaração das variaveis que serão lidas e jogadas ao banco de dados
    Registro reg;
    int num_amostras;
    float peso_bruto_produto, peso_bruto_amostra, umidade, impurezas;
    float media_guc = 0.0;
    int faixa1_count = 0, faixa2_count = 0, faixa3_count = 0;
    char faixa1_indicadores[MAX_INDICADORES] = "";
    char faixa2_indicadores[MAX_INDICADORES] = "";
    char faixa3_indicadores[MAX_INDICADORES] = "";
    float soma_peso_impurezas = 0.0;

    // Leitura da primeira linha do arquivo
    if (fscanf(file, "%d %d %f %d %d", &reg.origem, &reg.numero_protocolo, &peso_bruto_produto, &num_amostras, &reg.tipo_produto) != 5) {
        fprintf(stderr, "\n Erro ao ler a primeira linha do arquivo");
        fclose(file);
        return 0;
    }

    // Leitura das amostras
    for (int i = 0; i < num_amostras; i++) {
        if (fscanf(file, "%*d %f %f %f", &peso_bruto_amostra, &impurezas, &umidade) != 3) {
            fprintf(stderr, "\n Erro ao ler a amostra %d do arquivo", i + 1);
            fclose(file);
            return 0;
        }

        soma_peso_impurezas += impurezas / 1000.0; 
        media_guc += umidade;

        // Classificação das faixas de umidade
        if (umidade >= 0 && umidade <= 8.5) {
            faixa1_count++;
            strcat(faixa1_indicadores, " ");
            sprintf(faixa1_indicadores + strlen(faixa1_indicadores), "%d", i + 1);
        } else if (umidade > 8.5 && umidade <= 15) {
            faixa2_count++;
            strcat(faixa2_indicadores, " ");
            sprintf(faixa2_indicadores + strlen(faixa2_indicadores), "%d", i + 1);
        } else if (umidade > 15 && umidade <= 25) {
            faixa3_count++;
            strcat(faixa3_indicadores, " ");
            sprintf(faixa3_indicadores + strlen(faixa3_indicadores), "%d", i + 1);
        }
    }

    fclose(file);

    // Cálculo do peso limpo
    float peso_limpo = peso_bruto_produto - soma_peso_impurezas;

    // Resultados
    printf("\n Origem: %d  Num. de amostras: %d  Data: %d/%d", reg.origem, num_amostras, mes, ano);
    printf("\n Umidade: %.1f%% \t Peso Limpo: %.2f T \t Transgenico: %d", media_guc / num_amostras, peso_limpo, reg.tipo_produto);

    if (faixa1_count > 0) {
        printf("\n Umidade: Faixa 1 \t Quant: %d ", faixa1_count);
        printf("\n Ident. das Amostras:%s ", faixa1_indicadores);
    }
    if (faixa2_count > 0) {
        printf("\n Umidade: Faixa 2 \t Quant: %d ", faixa2_count);
        printf("\n Ident. das Amostras:%s ", faixa2_indicadores);
    }
    if (faixa3_count > 0) {
        printf("\n Umidade: Faixa 3 \t Quant: %d ", faixa3_count);
        printf("\n Ident. das Amostras:%s ", faixa3_indicadores);
    }
    printf("\n ");
    printf("\n ");
    printf("\n Programa desenvolvido pelos alunos:");
    printf("\n Gabriel Tavares dos Santos");
    printf("\n Ivan Alves Pires");
    printf("\n Kaike Andrade Lima");
    printf("\n Mateus de Castro Leao");
    printf("\n Heitor Oliveira Pereira");
    printf("\n ");
    printf("\n ");

    // Gravação no arquivo binário
    FILE *arquivo = fopen("GraosRecebidos-2024.dat", "ab");
    if (arquivo == NULL) {
        fprintf(stderr, "\n Erro ao abrir o arquivo para escrita.");
        return 0;
    }

    reg.mes = mes;
    reg.ano = ano;
    reg.peso_bruto_produto = peso_bruto_produto;
    reg.peso_limpo = peso_limpo;
    reg.media_guc = media_guc / num_amostras;

    fwrite(&reg, sizeof(reg), 1, arquivo);

    fclose(arquivo);

    return 1; // Indica que o carregamento foi realizado com sucesso
}

// Função que le os dados do arquivo em binario
int lerArquivoBinario(Registro registros[], int *num_registros) {
    FILE *arquivo = fopen("GraosRecebidos-2024.dat", "rb");
    if (arquivo == NULL) {
        fprintf(stderr, "\n Erro ao abrir o arquivo.");
        return 1;
    }

    *num_registros = 0;
    while (fread(&registros[*num_registros], sizeof(Registro), 1, arquivo) == 1) {
        (*num_registros)++;
    }

    fclose(arquivo);
    return 0;
}

int resumo_qtd_mensal() {
    Registro registros[10]; // Máximo 10 registros serão lidos
    int num_registros;

    if (lerArquivoBinario(registros, &num_registros) != 0) {
        return 1; // Retorna 1 em caso de erro ao ler o arquivo binário
    }
    printf("\n ");
    printf("\n ");
    printf("\n --------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n UFG-BSI-IP (COOPERATIVA AGRICOLA GRAO_DO_VALE V1.0)");
    printf("\n ANO: 2024 <RESUMO QUANTITATIVO MENSAL>");
    printf("\n --------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n");

    for (int i = 0; i < num_registros; i++) {
        Registro *reg = &registros[i];
        printf("\n Origem: %d  Protocolo: %d  Data: %.0f/%.0f", reg->origem, reg->numero_protocolo, reg->mes, reg->ano);
        printf("\n Umidade Media: %.1f%% \t Peso Limpo: %.2f T \t Transgenico: %d", reg->media_guc, reg->peso_limpo, reg->tipo_produto);
        printf("\n --------------------------------------------------------------------------------------------------------------------------------------------");
    }

    printf("\n");
    return 0; // Retorna 0 indicando que a função foi executada sem erros
}


int resumo_geral()
{
}

/* printf("\n --------------------------------------------------------------------------------------------------------------------------------------------");
printf("\n UFG-BSI-IP (COPERATIVA AGRICOLA GRAO_DO_VALE V1.0)");
printf("\n ANO: 2024 <GERAR RELATORIOS>");
printf("\n --------------------------------------------------------------------------------------------------------------------------------------------");
printf("\n Origem: %d \t Num. de amostras: %d \t Data: %02d/%02d/%04d ", origem, num_amostras, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
printf("\n Umidade: %.1lf%% \t Peso Limpo: %.1lf \t Transgenico: %d \t Percentual de Impurezas: %.1lf", umidade, peso_limpo, tipo_produto, percentual_impurezas);
// Preciso criar uma função para mostrar a data que o relatorio foi armazenado
printf("\n");
printf("\n Mes: %d", mes);
printf("\n Qts cargas chegaram nesse mes: %d", qtd_cargas);
printf("\n Origem \t Cargas \t GU Faixa 1 \t GU Faixa 2 \t GU Faixa 3 \t GU Extra ");
// Retira esses xxxx substituir pelas variaveis do array
printf("\n ----------+----------------+----------------+---------------+---------------+-----------------+---------------------------------------------");
printf("\n    %d \t\t    %d \t\t    xxxx \t   xxxx \t  xxxx \t\t   xxxx ", origem, qtd_cargas);
printf("\n ----------+----------------+----------------+---------------+---------------+-----------------+---------------------------------------------");
printf("\n                                                                                                                                             ");
printf("\n        \t        \t Faixa 1                  (umid.)        Faixa 2                (umid.)      Faixa 3           (umid.) ");
printf("\n        \t Peso   \t Peso                      Tipo          Peso                    Tipo        Peso               Tipo    ");
printf("\n Origem \t Total  \t Limpo        Trans        Nao           Limpo      Trans        Nao         Limpo     Trans    Nao     ");
printf("\n ----------+----------------+--------------+-----------+------------+------------+-----------------------------------------------------------");
printf("\n    %d \t\t    %d \t\t  xxxx \t\txxxx \t   xxxx \t  xxxx", origem, qtd_cargas);

printf("\n --------------------------------------------------------------------------------------------------------------------------------------------");
printf("\n");
printf("\n");
printf("\n");
printf("\n");
printf("\n");
printf("\n");
*/