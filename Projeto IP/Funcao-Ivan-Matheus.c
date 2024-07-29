#include <stdio.h>

#define MAX_AMOSTRAS 100

 
typedef struct {
    float media_guc;
    float peso_limpo;
    int tipo_produto; // 1 para transgênico, 0 para não transgênico
} Registro;

int lerArquivoBinario(Registro registros[], int *num_registros) {
    // Implementação da função de leitura aqui
    // Exemplo: abrir arquivo, ler registros, etc.
    // Retorne 0 se bem-sucedido, outro valor se houver erro
    return 0; // Simulando retorno de sucesso para exemplo
}

// Função para gerar o resumo geral
int resumo_geral() {
    Registro registros[MAX_AMOSTRAS]; // Array para armazenar os registros lidos do arquivo
    int num_registros = 0;
    
    // Lê os registros do arquivo binário
    if (lerArquivoBinario(registros, &num_registros) != 0) {
        printf("\n Erro ao ler registros do arquivo.");
        return 0;
    }

    // Declaração de variáveis para cálculos de resumo
    float total_peso_limpo_faixa1 = 0.0, total_peso_limpo_faixa2 = 0.0, total_peso_limpo_faixa3 = 0.0;
    int count_transgenicos_faixa1 = 0, count_transgenicos_faixa2 = 0, count_transgenicos_faixa3 = 0;
    int count_nao_transgenicos_faixa1 = 0, count_nao_transgenicos_faixa2 = 0, count_nao_transgenicos_faixa3 = 0;

    // laço para processar os registros e calcular o resumo
    for (int i = 0; i < num_registros; i++) {
        Registro reg = registros[i];

        if (reg.media_guc >= 0 && reg.media_guc <= 8.5) {
            total_peso_limpo_faixa1 += reg.peso_limpo;
            if (reg.tipo_produto == 1) {
                count_transgenicos_faixa1++;
            } else {
                count_nao_transgenicos_faixa1++;
            }
        } else if (reg.media_guc > 8.5 && reg.media_guc <= 15.0) {
            total_peso_limpo_faixa2 += reg.peso_limpo;
            if (reg.tipo_produto == 1) {
                count_transgenicos_faixa2++;
            } else {
                count_nao_transgenicos_faixa2++;
            }
        } else if (reg.media_guc > 15.0 && reg.media_guc <= 25.0) {
            total_peso_limpo_faixa3 += reg.peso_limpo;
            if (reg.tipo_produto == 1) {
                count_transgenicos_faixa3++;
            } else {
                count_nao_transgenicos_faixa3++;
            }
        }
    }

    // Impressão do resumo geral
    printf("\n Origem \t Total \t Peso Limpo \t Transgênico \t Não Transgênico");
    printf("\n -------+-------+------------+-------------+------------------");
    printf("\n Faixa 1 \t \t %.2f \t %d \t\t %d", total_peso_limpo_faixa1, count_transgenicos_faixa1, count_nao_transgenicos_faixa1);
    printf("\n Faixa 2 \t \t %.2f \t %d \t\t %d", total_peso_limpo_faixa2, count_transgenicos_faixa2, count_nao_transgenicos_faixa2);
    printf("\n Faixa 3 \t \t %.2f \t %d \t\t %d", total_peso_limpo_faixa3, count_transgenicos_faixa3, count_nao_transgenicos_faixa3);
    printf("\n ------------------------------------------------------------------");

    return 1;
}

int main() {

    resumo_geral();

    return 0;
}