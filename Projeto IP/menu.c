#include <stdio.h>
#include "funcoes.h"
#include <time.h> 
// Função para exibir um menu e retornar a opção escolhida pelo usuário
int menu() {
    int opcao;
    printf("\n Ola usario, esse e o sistema da empresa Graos Do Vale");
    printf("\n Digite:");
    printf("\n 1. para DETERMINAR");
    printf("\n 2. para ARQUIVAR");
    printf("\n 3. para GERAR RELATORIOS");
    printf("\n Digite sua opcao: ");
    scanf("%d", &opcao);  
    return opcao;         
}

int gerar_relatorios(){
    double peso_bruto_produto, umidade, impurezas, percentual_impurezas, peso_impurezas, peso_limpo;
  int origem, num_amostras, tipo_produto, cargas;
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  printf("\n Digite a quantidade de cargas:  ");
  scanf("%d", &cargas);
  
  for (int i = 0; i < cargas; i++) {
  printf("\n Digite o peso do bruto bruto KG:  ");
  scanf("%lf", &peso_bruto_produto);
  printf("\n Digite o codigo de origem:  ");
  scanf("%d", &origem);
  printf("\n Digite o numero de amostras:  ");
  scanf("%d", &num_amostras);
  printf("\n Digite a porcentagem de impurezas %%:  ");
  scanf("%lf", &impurezas);
  printf("\n Digite o tipo de produto:  ");
  scanf("%d", &tipo_produto); 
  printf("\n Digite a umidade do produto:  ");
  scanf("%lf", &umidade); 
  peso_impurezas = peso_bruto_produto *  (impurezas / 100);
  percentual_impurezas = (peso_impurezas / peso_bruto_produto) * 100;
  peso_limpo = peso_bruto_produto - peso_impurezas;
  printf("\n --------------------------------------------------------------------------------------------------------------------------------------------");


  printf("\n UFG-BSI-IP (COPERATIVA AGRICOLA GRAO_DO_VALE V1.0)");
  printf("\n ANO: 2024 <nome da funcao>");
  printf("\n --------------------------------------------------------------------------------------------------------------------------------------------");
  printf("\n Origem: %d \t Num. de amostras: %d \t Data: %02d/%02d/%04d ", origem, num_amostras,  tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
  printf("\n Umidade: %.1lf%% \t Peso Limpo: %.1lf \t Transgenico: %d \t Percentual de Impurezas: %.1lf", umidade, peso_limpo, tipo_produto, percentual_impurezas);

  if (umidade == 0 || umidade <= 8.5){
    printf("\n Umidade: Faixa 1 \t Quant: %d", num_amostras);
  for (int i = 0; i < num_amostras; i++)
  {
    printf("\n Ident. da Amostra: %d", i + 1);
  }
  }
   else if (umidade >=8.6 || umidade <= 15){
    printf("\n Umidade: Faixa 2 \t Quant: %d", num_amostras);
  for (int i = 0; i < num_amostras; i++)
  {
    printf("\n Ident. da Amostra: %d", i + 1);
  }
  }
   else if (umidade >= 15.1 || umidade <= 25){
    printf("\n Umidade: Faixa 3 \t Quant: %d", num_amostras);
  for (int i = 0; i < num_amostras; i++)
  {
    printf("\n Ident. da Amostra: %d", i + 1);
  }
  }

  int mes, qtd_cargas;
  printf("\n");
  printf ("\n Mes: "); // Usar um case por extenso 
  scanf("%d", &mes);
  printf("\n Qts cargas chegaram nesse mes: ");
  scanf("%d", &qtd_cargas);
  printf("\n Origem \t Cargas \t GU Faixa 1 \t GU Faixa 2 \t GU Faixa 3 \t GU Extra ");
  printf("\n ----------+----------------+----------------+---------------+---------------+-----------------+---------------------------------------------");
  printf ("\n    %d \t\t    %d \t\t    xxxx \t   xxxx \t  xxxx \t\t   xxxx ", origem, qtd_cargas);
  printf("\n ----------+----------------+----------------+---------------+---------------+-----------------+---------------------------------------------");
  printf("\n                                                                                                                                             ");
  printf("\n        \t        \t Faixa 1                  (umid.)        Faixa 2                (umid.)      Faixa 3           (umid.) ");
  printf("\n        \t Peso   \t Peso                      Tipo          Peso                    Tipo        Peso               Tipo    ");
  printf("\n Origem \t Total  \t Limpo        Trans        Nao           Limpo      Trans        Nao         Limpo     Trans    Nao     "); // Oque é esse Não?
  printf("\n ----------+----------------+--------------+-----------+------------+------------+-----------------------------------------------------------");
  printf ("\n    %d \t\t    %d \t\t  xxxx \t\txxxx \t   xxxx \t  xxxx", origem, qtd_cargas);

  printf("\n --------------------------------------------------------------------------------------------------------------------------------------------");
  printf("\n Programa desenvolvido pelos alunos:");
  printf("\n Gabriel Tavares dos Santos");
  printf("\n Ivan Alves Pires");
  printf("\n Kaike Andrade Lima");
  printf("\n Mateus de Castro Leao");
  printf("\n Heitor Oliveira Pereira");
  return 0;
  }
}