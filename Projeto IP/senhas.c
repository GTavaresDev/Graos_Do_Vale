#include <stdio.h>
#include <stdlib.h>

int main (){
   const char *nome_arquivo = "C:\\Users\\cidab\\DadosSenhas.txt";
   int senhas[40];
   int senha_acesso;
   

  /*printf("\n Digite o nome do arquivo: ");
    if (scanf("%39s", nome_arquivo) != 1) {
        printf("\n Erro ao ler o nome do arquivo.");
        return 0;
    }
    */
   printf(&nome_arquivo);
   FILE *primeiro_file = fopen(nome_arquivo, "r");
     if (primeiro_file) {
        printf("\n abriu o arquivo");
    } else {
      perror("\n N abriu o arquivo");
      return 0;
    }
    
    if (fscanf(primeiro_file, "%d", &senha_acesso) != 1) {
        fprintf(stderr, "\n Erro ao ler a primeira linha do arquivo");
        fclose(primeiro_file);
        return 0;
    }
    fclose(primeiro_file);
   printf("\n Senha de acesso: ");
    if (scanf("%d", &senha_acesso) != 1) {
        printf("\n Senha Incorreta.");
        return 0;
    }


   if (fscanf(primeiro_file, "%d") != senha_acesso) {
        fprintf(stderr, "\n Erro ao ler as senhas ");
        fclose(primeiro_file);
        return 0;
    }


  
 fclose(primeiro_file);
  return 0;
  
}