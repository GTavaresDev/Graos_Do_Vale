#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"
#define max_linhas_length 1024

int data_valida(int mes, int ano)
{
    if (ano < 1900 || ano > 2100)
        return 0;
    if (mes < 1 || mes > 12)
        return 0;
    return 1;
}

int data_nao_futura(int mes, int ano)
{
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
    char caminho[100] = "";
    char conteudo;

    printf("\n Digite o nome do arquivo: ");
    scanf("%39s", nome);
    char dataStr[10];
    int mes, ano;

    printf("\n Digite a data de recebimento (MM/AAAA): ");
    scanf("%9s", dataStr);
    // Preciso criar uma verificação se aquele mes já não possui outro arquivo 
    if (sscanf(dataStr, "%d/%d", &mes, &ano) != 2)
    {
        printf("\n Formato de data invalido.");
        return 1;
    }

    if (data_valida(mes, ano))
    {
        if (data_nao_futura(mes, ano))
        {
        }
        else
        {
            printf("\n Erro: A data inserida e futura.");
        }
    }
    else
    {
        printf("\n Data invalida.");
        return 1;
    }

    strcat(caminho, nome);
    // Leitura do arquivo .txt
    file = fopen(caminho, "r");

    if (file == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    while ((conteudo = fgetc(file)) != EOF)
    {
    }

    rewind(file);
    // Leitura da primeira linha do arquivo 
    double peso_bruto_produto;
    int origem, numero_protocolo, num_amostras, tipo_produto;
    if (fgets(line, sizeof(line), file) != NULL)
    {
        sscanf(line, "%d %d %lf %d %d", &origem, &numero_protocolo, &peso_bruto_produto, &num_amostras, &tipo_produto);
    }
    else
    {
        fprintf(stderr, "\n Erro ao ler a primeira linha");
        fclose(file);
        return 1;
    }

    double peso_bruto_amostra, umidade, impurezas;
    int indicador;

    // Declaração das variáveis de contagem e armazenamento de indicadores
    int faixa1_count = 0, faixa2_count = 0, faixa3_count = 0;
    char faixa1_indicadores[max_linhas_length] = "";
    char faixa2_indicadores[max_linhas_length] = "";
    char faixa3_indicadores[max_linhas_length] = "";
    double soma_peso_impurezas = 0.0;

    double media_umidade = 0.0;
    //Leitura da segunda linha ate a ultima linha e coluna do arquivo 
    for (int i = 0; i < num_amostras; i++)
    {
        if (fgets(line, sizeof(line), file) != NULL)
        {
            sscanf(line, "%d %lf %lf %lf", &indicador, &peso_bruto_amostra, &impurezas, &umidade);
            double percentual_impurezas = (peso_bruto_amostra * 1000) - impurezas ;
                soma_peso_impurezas += percentual_impurezas;
            double guc = umidade;
                media_umidade += guc;

            // O indicador é convertido para uma string (indicador_str) e concatenado à string faixa1_indicadores.
            if (umidade >= 0 && umidade <= 8.5)
            {
                faixa1_count++;
                char indicador_str[10];
                sprintf(indicador_str, " %d", indicador);
                strcat(faixa1_indicadores, indicador_str);
            }
            else if (umidade >= 8.6 && umidade <= 15)
            {
                faixa2_count++;
                char indicador_str[10];
                sprintf(indicador_str, " %d", indicador);
                strcat(faixa2_indicadores, indicador_str);
            }
            else if (umidade >= 15.1 && umidade <= 25)
            {
                faixa3_count++;
                char indicador_str[10];
                sprintf(indicador_str, " %d", indicador);
                strcat(faixa3_indicadores, indicador_str);
            }
        }
        else
        {
            fprintf(stderr, "Erro ao ler a linha %d\n", i + 2);
            break;
        }
    }
    double peso_limpo_Kg = (peso_bruto_produto * 1000) - (soma_peso_impurezas / 1000);
    double peso_limpo = peso_limpo_Kg / 1000.0;
    double media_guc = media_umidade / num_amostras;

    fclose(file);
    printf("\n Origem: %d  Num. de amostras: %d  Data: %d/%d", origem, num_amostras, mes, ano);
    printf("\n Umidade: %.1lf%% \t Peso Limpo: %.2lf T \t Transgenico: %d", media_guc, peso_limpo, tipo_produto);
 
    if (faixa1_count > 0)
    {
        printf("\n Umidade: Faixa 1 \t Quant: %d ", faixa1_count);
        printf("\n Ident. das Amostras:%s ", faixa1_indicadores);
    }
    if (faixa2_count > 0)
    {
        printf("\n Umidade: Faixa 2 \t Quant: %d ", faixa2_count);
        printf("\n Ident. das Amostras:%s ", faixa2_indicadores);
    }
    if (faixa3_count > 0)
    {
        printf("\n Umidade: Faixa 3 \t Quant: %d ", faixa3_count);
        printf("\n Ident. das Amostras:%s ", faixa3_indicadores);
    }

    fclose(file);

    printf("\n");
    printf("\n");
    printf("\n Programa desenvolvido pelos alunos:");
    printf("\n Gabriel Tavares dos Santos");
    printf("\n Ivan Alves Pires");
    printf("\n Kaike Andrade Lima");
    printf("\n Mateus de Castro Leao");
    printf("\n Heitor Oliveira Pereira");

    FILE *arquivo = fopen("GraosRecebidos-2024.dat", "wb");
    if(arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Escrever os dados no arquivo
    fwrite(&origem, sizeof(origem), 1, arquivo);
    fwrite(&numero_protocolo, sizeof(numero_protocolo), 1, arquivo);
    fwrite(&mes, sizeof(mes), 1, arquivo);
    fwrite(&ano, sizeof(ano), 1, arquivo);
    fwrite(&tipo_produto, sizeof(tipo_produto), 1, arquivo);
    fwrite(&peso_limpo, sizeof(peso_limpo), 1, arquivo);
    fwrite(&peso_bruto_produto, sizeof(peso_bruto_produto), 1, arquivo);
    fwrite(&media_guc, sizeof(media_guc), 1, arquivo);

    
    fclose(arquivo);
}

int lerArquivoBinario(int *origem, int *numero_protocolo, int *mes, int *ano, int *tipo_produto, double *peso_limpo, double *media_guc, double *peso_bruto_produto) {
    //Leitura do arquivo Binario 
    FILE *arquivo = fopen("GraosRecebidos-2024.dat", "rb");
    if (arquivo == NULL) {
        fprintf(stderr, "\n Erro ao abrir o arquivo.");
        return 1;
    }

    // Leitura das variaveis do banco de dados binario
    fread(origem, sizeof(*origem), 1, arquivo);
    fread(numero_protocolo, sizeof(*numero_protocolo), 1, arquivo);
    fread(mes, sizeof(*mes), 1, arquivo);
    fread(ano, sizeof(*ano), 1, arquivo);
    fread(tipo_produto, sizeof(*tipo_produto), 1,arquivo);
    fread(peso_limpo, sizeof(*peso_limpo), 1, arquivo);
    fread(peso_bruto_produto, sizeof(*peso_bruto_produto), 1, arquivo);
    fread(media_guc, sizeof(*media_guc), 1, arquivo);

    fclose(arquivo);
    return 0;
}

int resumo_qtd_mensal(){
    // Precisa de fazer com que o sistema leia todo o banco de dados e atraves do mes e ano retorne para o usario se ele escolher a opção mensal 
    // Perguntar pro professor se precisa pedir o ano porque o usario não pode escrever dois arquivos em um mes, mas pode ser no mesmo mes em anos diferentes ?
    int origem, numero_protocolo, mes, ano, tipo_produto;
    double peso_limpo, media_guc, peso_bruto_produto;
    int resultado = lerArquivoBinario(&origem, &numero_protocolo, &mes, &ano, &tipo_produto, &peso_limpo, &media_guc, &peso_bruto_produto);
    double gu_faixa1 = 0;
    double gu_faixa2 = 0;
    double gu_faixa3 = 0;
    if (media_guc >= 0 && media_guc <= 8.5)
            {
                gu_faixa1 = media_guc;
            }
            else if (media_guc >= 8.6 && media_guc <= 15.0)
            {
                gu_faixa2 = media_guc;
            }
            else if (media_guc >= 15.1 && media_guc <= 25.0)
            {
                gu_faixa3 = media_guc;
            }
        
    printf("\n --------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n UFG-BSI-IP (COPERATIVA AGRICOLA GRAO_DO_VALE V1.0)");
    printf("\n ANO: 2024 <RESUMO QUANTITATIVO MENSAL>");
    printf("\n --------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n");
    // Retirar o gu faixa extra e se amostrar cair em alguma dessas faixas mostrar o xx na faixa 
    // O carga sempre será 1. pq so armazena 1 por mes. 
    printf("\n Origem \t Carga \t        GU Faixa 1 \t GU Faixa 2 \t  GU Faixa 3 \t     GU Extra ");
    printf("\n ----------+----------------+----------------+---------------+---------------+-----------------+---------------------------------------------");
    printf("\n    %d \t    %d \t\t    %.1lf \t   %.1lf \t  %.1lf \t\t    ", origem, numero_protocolo, gu_faixa1, gu_faixa2, gu_faixa3);
    printf("\n ----------+----------------+----------------+---------------+---------------+-----------------+---------------------------------------------");
    return 0;
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