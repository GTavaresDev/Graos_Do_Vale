#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"
#define max_linhas_length 1024


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
    char line[max_linhas_length];


    char nome[40];
    FILE *file;
    char caminho[100] = "C:\\Program Files\\DadosParaTestesTF-Graos_do_Vale\\";
    char conteudo;

    printf("\n Digite o nome do arquivo: ");
    scanf("%39s", nome);
    char dataStr[10];
    int mes, ano;

    printf("\n Digite a data de recebimento (MM/AAAA): ");
    scanf("%9s", dataStr);

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
        return 1;
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
    


    double peso_bruto_produto;
    int origem, numero_protocolo, num_amostras, tipo_produto;
    if (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d %d %lf %d %d", &origem, &numero_protocolo, &peso_bruto_produto, &num_amostras, &tipo_produto);
    } else {
        fprintf(stderr, "Erro ao ler a primeira linha\n");
        fclose(file);
        return 1;
    }
    double peso_bruto_amostra, umidade;
    int indicador,impurezas;
    for (int i = 0; i < num_amostras; i++) {
        if (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "%d %lf %d %lf", &indicador, &peso_bruto_amostra, &impurezas, &umidade);
        } else {
            fprintf(stderr, "Erro ao ler a linha %d \n", i + 2); 
            break;
        }
    }

    fclose(file);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    double peso_impurezas, percentual_impurezas, peso_limpo;
      printf("\n ");
        printf("\n Origem: %d  Num. de amostras: %d  Data: %d/%d", origem, num_amostras, mes, ano); 
        printf("\n Umidade: %.2lf%% \t Peso Limpo: %.1dT \t Transgenico: %d", umidade, peso_limpo, tipo_produto);
        printf("\n");
    for (int i = 0; i < num_amostras; i++)
    {
    
        peso_impurezas = peso_bruto_produto * (impurezas / 100);
        percentual_impurezas = (peso_impurezas / peso_bruto_produto) * 100;
        peso_limpo = peso_bruto_produto - peso_impurezas;

        if (umidade == 0 || umidade <= 8.5)
        {
            printf("\n Umidade: Faixa 1 \t Quant: %d ", num_amostras);
            printf("\n Ident. da Amostra: ");
            for (int i = 0; i < num_amostras; i++)
            {
                printf(" %d", i + 1);
            }
        }
        else if (umidade >= 8.6 || umidade <= 15)
        {
            printf("\n Umidade: Faixa 2 \t Quant: %d", num_amostras);
            printf("\n Ident. da Amostra: ");
            for (int i = 0; i < num_amostras; i++)
            {
                printf(" %d", i + 1);
            }
        }
        else if (umidade >= 15.1 || umidade <= 25)
        {
            printf("\n Umidade: Faixa 3 \t Quant: %d", num_amostras);
            printf("\n Ident. da Amostra: ");
            for (int i = 0; i < num_amostras; i++)
            {
                printf(" %d", i + 1);
            }
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

int resumo_qtd_mensal()
{
    printf("\n Ola");
  /* Aqui nessa função o usario vai digitar a data de um arquivo que ele já armazenou, que foi guardado em txt no banco 
  de dados, que sera puxado do banco de dados e convertido para exibição */
}

int resumo_geral() {

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