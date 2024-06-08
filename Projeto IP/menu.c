#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"

int data_valida( int mes, int ano) {
    if (ano < 1900 || ano > 2100) return 0;
    if (mes < 1 || mes > 12) return 0;
    return 1;
}

int data_nao_futura( int mes, int ano) {
    time_t t = time(NULL);
    struct tm *dataAtual = localtime(&t);

    int anoAtual = dataAtual->tm_year + 1900;
    int mesAtual = dataAtual->tm_mon + 1;

    if (ano > anoAtual) return 0;
    if (ano == anoAtual && mes > mesAtual) return 0;

    return 1;
}

int menu()
{
    int opcao;
    do
    {   
        printf("\n");
        printf("\n");
        printf("\n Ola usuario, esse e o sistema da empresa Graos Do Vale");
        printf("\n Digite:");
        printf("\n 1. para Descricao de Carregamento");
        printf("\n 2. para Resumo Quantitativo Mensal");
        printf("\n 3. para Resumo Geral Quantitativo e Qualitativo");
        printf("\n");
        printf("\n");
        printf("\n 0. para FECHAR O PROGRAMA");
        printf("\n Digite sua opcao: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
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
        // Voltar o rodape para o final de cada relatorio.
            printf("\n Fechando o programa...");
            printf("\n --------------------------------------------------------------------------------------------------------------------------------------------");
            break;
        default:
            printf("\n Opcao invalida! Escolha entre 1, 2, 3 ou 0.");
            break;
        }
    } while (opcao != 0);

    return opcao;
}
int carregamento()
{
    char nome[40];
    FILE *file;
    char caminho[100] = "C:\\Program Files\\DadosParaTestesTF-Graos_do_Vale\\";
    char conteudo;

    printf("\n Digite o nome do arquivo: ");
    scanf("%39s", nome);
    char dataStr[8];
    int mes, ano;

    printf("\n Digite a data de recebimento (MM/AAAA): ");
    scanf("%7s", dataStr);

    if (sscanf(dataStr, "%d/%d", &mes, &ano) != 2) {
        printf("\n Formato de data invalido.");
        return 1;
    }

    if (data_valida( mes, ano)) {
        if (data_nao_futura( mes, ano)) {       
        } else {
            printf("\n Erro: A data inserida e futura.");
        }
    } else {
        printf("\n Data invalida.");
    }

    strcat(caminho, nome);
    file = fopen(caminho, "r");

    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    while ((conteudo = fgetc(file)) != EOF) {
    }

    rewind(file);
    

    double peso_bruto_produto, umidade, impurezas;
    int origem, num_amostras, tipo_produto, cargas, variavel, qtd_cargas;
    if (fscanf(file, "%d %lf %lf %lf %d %d %d %d %d", &cargas, &peso_bruto_produto, &umidade, &impurezas, &num_amostras, &tipo_produto, &origem, &variavel, &qtd_cargas) != 9) {
        fprintf(stderr, "\n Erro ao ler os dados do arquivo");
        fclose(file);
        return 1;
    }

    fclose(file);
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
        printf("\n");
            printf("\n Programa desenvolvido pelos alunos:");
            printf("\n Gabriel Tavares dos Santos");
            printf("\n Ivan Alves Pires");
            printf("\n Kaike Andrade Lima");
            printf("\n Mateus de Castro Leao");
            printf("\n Heitor Oliveira Pereira");
    }
}

int resumo_qtd_mensal()
{
 
}

int resumo_geral() {

}