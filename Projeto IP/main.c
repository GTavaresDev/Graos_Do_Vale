#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "funcoes.h"

int main()
{
    int senha;

    do
    {
        printf("\n");
        printf("\n Ola usuario, Bem Vindo ao sistema da Empresa Graos do Vale");
        printf("\n");
        printf("\n Por favor digite sua senha de acesso ");
        printf("\n Senha: ");
        scanf("%d", &senha);
        printf("\n");
        switch (senha)
        {
        case 202405103:
            system("cls");  
            menu();
            break;
        case 202405402:
            system("cls");
            menu();
            break;
        case 202405106:
            system("cls");
            menu();
            break;
        case 202400951:
            system("cls");
            menu();
            break;
        case 202405113:
            system("cls");
            menu();
            break;
        default:
            printf("SENHA INVALIDA!!");  
            break;
        }
        
    } while (senha != 0);
   
    return 1;
}