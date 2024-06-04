#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"

int ano_bissexto(int ano) {
    return ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0));
}

int data_valida(int dia, int mes, int ano) {
    if (ano < 1900 || ano > 2100) return 0;
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1) return 0;

    if (mes == 2) {
        if (ano_bissexto(ano)) {
            if (dia > 29) return 0;
        } else {
            if (dia > 28) return 0;
        }
    } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        if (dia > 30) return 0;
    } else {
        if (dia > 31) return 0;
    }

    return 1;
}

int data_nao_futura(int dia, int mes, int ano) {
    time_t t = time(NULL);
    struct tm *dataAtual = localtime(&t);

    int anoAtual = dataAtual->tm_year + 1900;
    int mesAtual = dataAtual->tm_mon + 1;
    int diaAtual = dataAtual->tm_mday;

    if (ano > anoAtual) return 0;
    if (ano == anoAtual && mes > mesAtual) return 0;
    if (ano == anoAtual && mes == mesAtual && dia > diaAtual) return 0;

    return 1;
}

int leitura() {
    char nome[40];
    FILE *file;
    char caminho[100] = "C:\\Program Files\\DadosParaTestesTF-Graos_do_Vale\\";
    char conteudo;

    printf("\n Digite o nome do arquivo: ");
    scanf("%39s", nome);

    strcat(caminho, nome);
    file = fopen(caminho, "r");

    if (file == NULL) {
        perror("\n Erro ao abrir o arquivo");
        return 1;
    }

    while ((conteudo = fgetc(file)) != EOF) {
        putchar(conteudo);
    }


    fclose(file);






    char dataStr[11];
    int dia, mes, ano;

    printf("\n Digite a data de recebimento (DD/MM/AAAA): ");
    scanf("%10s", dataStr);

    if (sscanf(dataStr, "%d/%d/%d", &dia, &mes, &ano) != 3) {
        printf("\n Formato de data invalido.");
        return 1;
    }

    if (data_valida(dia, mes, ano)) {
        if (data_nao_futura(dia, mes, ano)) { 
          printf("\n Data valida e armazenada: %02d/%02d/%04d", dia, mes, ano);         
        } else {
            printf("\n Erro: A data inserida e futura.");
        }
    } else {
        printf("\n Data invalida.");
    }

    return 0;
}

int menu()
{
    int opcao;
    do
    {
        printf("\n Ola usuario, esse e o sistema da empresa Graos Do Vale");
        printf("\n Digite:");
        printf("\n 1. para DETERMINAR");
        printf("\n 2. para ARQUIVAR");
        printf("\n 3. para GERAR RELATORIOS");
        printf("\n 0. para FECHAR O PROGRAMA");
        printf("\n Digite sua opcao: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            determinar();
            break;
        case 2:
            // Chamada para a função "arquivar()"
            break;
        case 3:
            gerar_relatorios();
            break;
        case 0:
            printf("\n Fechando o programa...");
            printf("\n --------------------------------------------------------------------------------------------------------------------------------------------");
            printf("\n Programa desenvolvido pelos alunos:");
            printf("\n Gabriel Tavares dos Santos");
            printf("\n Ivan Alves Pires");
            printf("\n Kaike Andrade Lima");
            printf("\n Mateus de Castro Leao");
            printf("\n Heitor Oliveira Pereira");
            break;
        default:
            printf("\n Opcao invalida! Escolha entre 1, 2, 3 ou 0.");
            break;
        }
    } while (opcao != 0);

    return opcao;
}
int determinar()
{
    leitura();

    double peso_bruto_produto, umidade, impurezas;
    int origem, num_amostras, tipo_produto, cargas, mes, qtd_cargas;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    double peso_impurezas, percentual_impurezas, peso_limpo;
    for (int i = 0; i < cargas; i++)
    {
        printf("\n ");
        printf("\n Peso do bruto bruto KG: %.2lf ", peso_bruto_produto);
        printf("\n Codigo de origem: %d", origem);
        printf("\n Numero de amostras: %d", num_amostras);
        printf("\n Porcentagem de impurezas %%: %.2lf", impurezas);
        printf("\n Tipo de produto: %d", tipo_produto);
        printf("\n Umidade do produto: %.2lf", umidade);
        printf("\n");
        peso_impurezas = peso_bruto_produto * (impurezas / 100);
        percentual_impurezas = (peso_impurezas / peso_bruto_produto) * 100;
        peso_limpo = peso_bruto_produto - peso_impurezas;

        if (umidade == 0 || umidade <= 8.5)
        {
            printf("\n Umidade: Faixa 1 \t Quant: %d", num_amostras);
            for (int i = 0; i < num_amostras; i++)
            {
                printf("\n Ident. da Amostra: %d", i + 1);
            }
        }
        else if (umidade >= 8.6 || umidade <= 15)
        {
            printf("\n Umidade: Faixa 2 \t Quant: %d", num_amostras);
            for (int i = 0; i < num_amostras; i++)
            {
                printf("\n Ident. da Amostra: %d", i + 1);
            }
        }
        else if (umidade >= 15.1 || umidade <= 25)
        {
            printf("\n Umidade: Faixa 3 \t Quant: %d", num_amostras);
            for (int i = 0; i < num_amostras; i++)
            {
                printf("\n Ident. da Amostra: %d", i + 1);
            }
        }
        printf("\n");
    }
}

int gerar_relatorios()
{
   char nome[40];
    FILE *file;
    char caminho[100] = "C:\\Program Files\\DadosParaTestesTF-Graos_do_Vale\\";
    char conteudo;

    printf("\n Digite o nome do arquivo: ");
    scanf("%39s", nome);


    // Falta criar um  printf sobre gerar relatorios de qual ano ou mes.

    strcat(caminho, nome);
    file = fopen(caminho, "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    while ((conteudo = fgetc(file)) != EOF) {
        putchar(conteudo);
    }

    rewind(file);

    // A partir da segunda linha ele vai repetir variaveis, um array resove ao inves de reescrever todas as variaveis.
    double peso_bruto_produto, umidade, impurezas;
    int origem, num_amostras, tipo_produto, cargas, mes, qtd_cargas;

    if (fscanf(file, "%d %lf %lf %lf %d %d %d %d %d", &cargas, &peso_bruto_produto, &umidade, &impurezas, &num_amostras, &tipo_produto, &origem, &mes, &qtd_cargas) != 9) {
        fprintf(stderr, "\n Erro ao ler os dados do arquivo");
        fclose(file);
        return 1;
    }

    fclose(file);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("\n Quantidade de cargas: %d", cargas);
    int vetor[cargas];

    double peso_impurezas, percentual_impurezas, peso_limpo;

    for (int i = 0; i < cargas; i++) {
        printf("\n");
        printf("\n Peso bruto do produto KG: %.2lf", peso_bruto_produto);
        printf("\n Codigo de origem: %d", origem);
        printf("\n Numero de amostras: %d", num_amostras);
        printf("\n Porcentagem de impurezas %%: %.2lf", impurezas);
        printf("\n Tipo de produto: %d", tipo_produto);
        printf("\n Umidade do produto: %.2lf", umidade);
        printf("\n");

        peso_impurezas = peso_bruto_produto * (impurezas / 100);
        percentual_impurezas = (peso_impurezas / peso_bruto_produto) * 100;
        peso_limpo = peso_bruto_produto - peso_impurezas;

        if (umidade <= 8.5) {
            printf("\nUmidade: Faixa 1 \t Quantidade: %d", num_amostras);
        } else if (umidade <= 15) {
            printf("\nUmidade: Faixa 2 \t Quantidade: %d", num_amostras);
        } else if (umidade <= 25) {
            printf("\nUmidade: Faixa 3 \t Quantidade: %d", num_amostras);
        }

        for (int j = 0; j < num_amostras; j++) {
            printf("\nIdent. da Amostra: %d", j + 1);
        }
        printf("\n");
    
    }

    printf("\n --------------------------------------------------------------------------------------------------------------------------------------------");
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
}
