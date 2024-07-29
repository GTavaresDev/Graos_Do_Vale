#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> 
#include "funcoes.h"

int login()
{
  int senha;
  char usuario[50];

  printf("\n Olá usuario, Bem Vindo ao sistema da Empresa Graos do Vale");
  printf("\n");
  printf("Usuario: ");
  gets(usuario);
  printf("Senha: ");
  scanf("%d", &senha);
  if (senha == 202405103 || 202405402 || 202405106 || 202400951 || 202405113)
  {
    printf("SENHA VALIDA!!");
  }
  else
  {
    printf("SENHA INVALIDA!!");
    return 1;
  }
  return 0;
}