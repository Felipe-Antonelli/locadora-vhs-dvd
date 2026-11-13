#ifndef FORNECEDORES_H
#define FORNECEDORES_H
#include <stdio.h>
#include <string.h>

// ----------------------------------------------------------------------------
// MODULO 2: FORNECEDORES | Autor: Rafael Gustavo de Franca Lima - RGM 48242365
// ----------------------------------------------------------------------------
struct Fornecedor {
    int   idFornecedor;
    char  nome[50];
    char  contato[30];
    float valorDivida;
    int   ativo;
};
struct Fornecedor listaFornecedores[50];
int totalFornecedores = 0;

void salvarFornecedoresCSV() {
    FILE *arq = fopen("fornecedores.csv", "w");
    if (arq == NULL) { printf("[ERRO] Nao foi possivel salvar fornecedores.csv\n"); return; }
    for (int i = 0; i < totalFornecedores; i++) {
        fprintf(arq, "%d;%s;%s;%.2f;%d\n",
                listaFornecedores[i].idFornecedor, listaFornecedores[i].nome,
                listaFornecedores[i].contato, listaFornecedores[i].valorDivida,
                listaFornecedores[i].ativo);
    }
    fclose(arq);
}

void carregarFornecedoresCSV() {
    FILE *arq = fopen("fornecedores.csv", "r");
    if (arq == NULL) return;
    totalFornecedores = 0;
    while (totalFornecedores < 50 && fscanf(arq, "%d;%49[^;];%29[^;];%f;%d\n",
           &listaFornecedores[totalFornecedores].idFornecedor,
           listaFornecedores[totalFornecedores].nome,
           listaFornecedores[totalFornecedores].contato,
           &listaFornecedores[totalFornecedores].valorDivida,
           &listaFornecedores[totalFornecedores].ativo) == 5) {
        totalFornecedores++;
    }
    fclose(arq);
}

int buscarFornecedorPorId(int id) {
    for (int i = 0; i < totalFornecedores; i++)
        if (listaFornecedores[i].idFornecedor == id && listaFornecedores[i].ativo == 1) return i;
    return -1;
}

void cadastrarFornecedor() {
    if (totalFornecedores >= 50) { printf("\n[ALERTA] Limite atingido!\n"); return; }
    struct Fornecedor novo;
    novo.idFornecedor = totalFornecedores + 1;
    novo.valorDivida = 0;
    novo.ativo = 1;
    printf("\n--- NOVO FORNECEDOR (ID %d) ---\n", novo.idFornecedor);
    printf("Nome da distribuidora: "); scanf(" %49[^\n]", novo.nome);
    printf("Contato: ");               scanf(" %29[^\n]", novo.contato);
    printf("Valor da divida (R$): ");  scanf("%f", &novo.valorDivida);
    listaFornecedores[totalFornecedores] = novo;
    totalFornecedores++;
    salvarFornecedoresCSV();
    printf("Fornecedor cadastrado e salvo no CSV!\n");
}

void listarOuBuscarFornecedores() {
    char termo[50];
    printf("\nDigite parte do nome (ou 0 para listar todos): ");
    scanf(" %49[^\n]", termo);
    printf("\n=== FORNECEDORES ===\n");
    int achou = 0;
    for (int i = 0; i < totalFornecedores; i++) {
        if (listaFornecedores[i].ativo == 0) continue;
        if (strcmp(termo, "0") != 0 && strstr(listaFornecedores[i].nome, termo) == NULL) continue;
        printf("ID %d | %s | Contato: %s | Divida: R$ %.2f\n",
               listaFornecedores[i].idFornecedor, listaFornecedores[i].nome,
               listaFornecedores[i].contato, listaFornecedores[i].valorDivida);
        achou = 1;
    }
    if (!achou) printf("Nenhum fornecedor encontrado.\n");
}

void editarFornecedor() {
    int id;
    printf("\nID do fornecedor a editar: ");
    scanf("%d", &id);
    int pos = buscarFornecedorPorId(id);
    if (pos == -1) { printf("Fornecedor nao encontrado.\n"); return; }
    printf("Novo nome: ");             scanf(" %49[^\n]", listaFornecedores[pos].nome);
    printf("Novo contato: ");          scanf(" %29[^\n]", listaFornecedores[pos].contato);
    printf("Nova divida (R$): ");      scanf("%f", &listaFornecedores[pos].valorDivida);
    salvarFornecedoresCSV();
    printf("Fornecedor atualizado e salvo!\n");
}

void removerFornecedor() {
    int id;
    printf("\nID do fornecedor a remover: ");
    scanf("%d", &id);
    int pos = buscarFornecedorPorId(id);
    if (pos == -1) { printf("Fornecedor nao encontrado.\n"); return; }
    listaFornecedores[pos].ativo = 0;
    salvarFornecedoresCSV();
    printf("Fornecedor removido e salvo!\n");
}

void moduloFornecedores() {
    int op;
    do {
        printf("\n--- MODULO FORNECEDORES (CSV ATIVO) ---\n");
        printf("1. Cadastrar fornecedor\n");
        printf("2. Listar / Buscar fornecedores\n");
        printf("3. Editar fornecedor\n");
        printf("4. Remover fornecedor\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &op) != 1) { op = 0; break; }
        switch (op) {
            case 1: cadastrarFornecedor();       break;
            case 2: listarOuBuscarFornecedores(); break;
            case 3: editarFornecedor();          break;
            case 4: removerFornecedor();         break;
            case 0: printf("\nVoltando...\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (op != 0);
}
#endif
