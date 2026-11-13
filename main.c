#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "clientes.h"      // Modulo 1 - Felipe Antonelli Bueno
#include "fornecedores.h"  // Modulo 2 - Rafael Gustavo de Franca Lima
#include "filmes.h"        // Modulo 3 - Rafael Leonardo Fernandes de Lima Leal
#include "locacoes.h"      // Modulo 4 - Miguel Mazorca

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    setlocale(LC_CTYPE, "Portuguese");

    carregarClientesCSV();
    carregarFornecedoresCSV();
    carregarFilmesCSV();
    carregarLocacoesCSV();

    int op;
    do {
        limparTela();
        printf("==============================================\n");
        printf("     LOCADORA DE VHS/DVD - MENU PRINCIPAL\n");
        printf("==============================================\n");
        printf("1. Clientes\n");
        printf("2. Fornecedores\n");
        printf("3. Filmes\n");
        printf("4. Locacoes e Relatorios\n");
        printf("0. Sair\n");
        printf("----------------------------------------------\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &op) != 1) { op = 0; break; }

        switch (op) {
            case 1: moduloClientes();     break;
            case 2: moduloFornecedores(); break;
            case 3: moduloFilmes();       break;
            case 4: moduloLocacoes();     break;
            case 0: printf("\nEncerrando o sistema. Dados salvos nos .csv. Ate logo!\n"); break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }
        if (op != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar(); getchar();
        }
    } while (op != 0);

    return 0;
}
