#ifndef CLIENTES_H
#define CLIENTES_H
#include <stdio.h>
#include <string.h>

// Autor: Felipe Antonelli Bueno - RGM 46686177
struct Cliente {
    int   idCliente;
    char  nome[50];
    char  telefone[20];
    float multasPendentes;
};
struct Cliente listaClientes[50];
int totalClientes = 0;

void salvarClientesCSV() {
    FILE *arq = fopen("clientes.csv", "w");
    if (arq == NULL) { printf("Erro ao salvar os dados.\n"); return; }
    for (int i = 0; i < totalClientes; i++) {
        fprintf(arq, "%d;%s;%s;%.2f\n",
                listaClientes[i].idCliente, listaClientes[i].nome,
                listaClientes[i].telefone, listaClientes[i].multasPendentes);
    }
    fclose(arq);
}

void carregarClientesCSV() {
    FILE *arq = fopen("clientes.csv", "r");
    if (arq == NULL) return;
    totalClientes = 0;
    while (totalClientes < 50 && fscanf(arq, "%d;%49[^;];%19[^;];%f\n",
           &listaClientes[totalClientes].idCliente,
           listaClientes[totalClientes].nome,
           listaClientes[totalClientes].telefone,
           &listaClientes[totalClientes].multasPendentes) == 4) {
        totalClientes++;
    }
    fclose(arq);
}

int buscarClientePorId(int id) {
    for (int i = 0; i < totalClientes; i++)
        if (listaClientes[i].idCliente == id) return i;
    return -1;
}

void cadastrarCliente() {
    if (totalClientes >= 50) { printf("\nLimite de clientes atingido.\n"); return; }
    struct Cliente novo;
    novo.idCliente = totalClientes + 1;
    novo.multasPendentes = 0;
    printf("\n--- NOVO CLIENTE (ID %d) ---\n", novo.idCliente);
    printf("Nome: ");     scanf(" %49[^\n]", novo.nome);
    printf("Telefone: "); scanf(" %19[^\n]", novo.telefone);
    listaClientes[totalClientes] = novo;
    totalClientes++;
    salvarClientesCSV();
    printf("Cliente cadastrado com sucesso!\n");
}

void listarOuBuscarClientes() {
    char termo[50];
    printf("\nDigite parte do nome para buscar (ou 0 para listar todos): ");
    scanf(" %49[^\n]", termo);
    printf("\n===== CLIENTES =====\n");
    int achou = 0;
    for (int i = 0; i < totalClientes; i++) {
        if (strcmp(termo, "0") != 0 && strstr(listaClientes[i].nome, termo) == NULL) continue;
        printf("ID %d | %s | Tel: %s | Multa: R$ %.2f\n",
               listaClientes[i].idCliente, listaClientes[i].nome,
               listaClientes[i].telefone, listaClientes[i].multasPendentes);
        achou = 1;
    }
    if (!achou) printf("Nenhum cliente encontrado.\n");
}

void editarCliente() {
    int id;
    printf("\nID do cliente a editar: ");
    scanf("%d", &id);
    int pos = buscarClientePorId(id);
    if (pos == -1) { printf("Cliente nao encontrado.\n"); return; }
    printf("Novo nome: ");       scanf(" %49[^\n]", listaClientes[pos].nome);
    printf("Novo telefone: ");   scanf(" %19[^\n]", listaClientes[pos].telefone);
    printf("Nova multa (R$): "); scanf("%f", &listaClientes[pos].multasPendentes);
    salvarClientesCSV();
    printf("Cliente atualizado com sucesso!\n");
}

void removerCliente() {
    int id;
    printf("\nID do cliente a remover: ");
    scanf("%d", &id);
    int pos = buscarClientePorId(id);
    if (pos == -1) { printf("Cliente nao encontrado.\n"); return; }
    for (int i = pos; i < totalClientes - 1; i++)
        listaClientes[i] = listaClientes[i + 1];
    totalClientes--;
    salvarClientesCSV();
    printf("Cliente removido com sucesso!\n");
}

void moduloClientes() {
    int op;
    do {
        printf("\n===== CLIENTES =====\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Listar / Buscar clientes\n");
        printf("3. Editar cliente\n");
        printf("4. Remover cliente\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &op) != 1) { op = 0; break; }
        switch (op) {
            case 1: cadastrarCliente();       break;
            case 2: listarOuBuscarClientes(); break;
            case 3: editarCliente();          break;
            case 4: removerCliente();         break;
            case 0: printf("\nVoltando...\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (op != 0);
}
#endif
