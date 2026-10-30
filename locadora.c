#include <stdio.h>
// LOCADORA DE VHS/DVD - Projeto P2 
// MODULO CLIENTES | Autor: Felipe Antonelli Bueno - RGM 46686177
struct Cliente {
    int   idCliente;
    char  nome[50];
    char  telefone[20];
    float multasPendentes;
    int   ativo;          
};
struct Cliente listaClientes[50];
int totalClientes = 0;

void inserirCliente() {
    if (totalClientes >= 50) { printf("\nCadastro cheio!\n"); return; }
    struct Cliente novo;
    novo.idCliente = totalClientes + 1;
    novo.multasPendentes = 0;
    novo.ativo = 1;

    printf("\nNovo cliente (ID %d)\n", novo.idCliente);
    printf("Nome: ");     scanf(" %[^\n]", novo.nome);
    printf("Telefone: "); scanf(" %[^\n]", novo.telefone);

    listaClientes[totalClientes] = novo;
    totalClientes++;
    printf("Cliente cadastrado!\n");
}

void listarClientes() {
    int i;
    if (totalClientes == 0) { printf("\nNenhum cliente cadastrado.\n"); return; }
    printf("\nCLIENTES\n");
    for (i = 0; i < totalClientes; i++) {
        printf("ID %d | %s | Tel: %s | Multa: R$ %.2f | %s\n",
               listaClientes[i].idCliente, listaClientes[i].nome,
               listaClientes[i].telefone, listaClientes[i].multasPendentes,
               listaClientes[i].ativo ? "Ativo" : "Removido");
    }
}

int buscarClientePorId(int id) {
    int i;
    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].idCliente == id) return i;
    }
    return -1;
}

void editarCliente() {
    int id, pos;
    if (totalClientes == 0) { printf("\nNenhum cliente cadastrado.\n"); return; }
    printf("\nID do cliente a editar: ");
    scanf("%d", &id);
    pos = buscarClientePorId(id);
    if (pos == -1) { printf("Cliente nao encontrado.\n"); return; }
    printf("Novo nome: ");     scanf(" %[^\n]", listaClientes[pos].nome);
    printf("Novo telefone: "); scanf(" %[^\n]", listaClientes[pos].telefone);
    printf("Cliente atualizado!\n");
}

void removerCliente() {
    int id, pos, i;
    if (totalClientes == 0) { printf("\nNenhum cliente cadastrado.\n"); return; }
    printf("\nID do cliente a remover: ");
    scanf("%d", &id);
    pos = buscarClientePorId(id);
    if (pos == -1) { printf("Cliente nao encontrado.\n"); return; }
    for (i = pos; i < totalClientes - 1; i++) {
        listaClientes[i] = listaClientes[i + 1];
    }
    totalClientes--;
    printf("Cliente removido!\n");
}

void moduloClientes() {
    int opcao;
    do {
        printf("\n--- MODULO CLIENTES ---\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Listar / Buscar clientes\n");
        printf("3. Editar cliente\n");
        printf("4. Remover cliente\n");
        printf("0. Voltar\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: inserirCliente(); break;
            case 2: listarClientes(); break;
            case 3: editarCliente();  break;
            case 4: removerCliente(); break;
            case 0: printf("\nVoltando ao menu principal\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);
}


void exibirCabecalho() {
    printf("   LOCADORA DE VHS/DVD\n");
}

int main() {
    int opcao;
    do {
        exibirCabecalho();
        printf("SELECIONE A PERSPECTIVA:\n");
        printf("1. Clientes\n");
        printf("0. Encerrar o sistema\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: moduloClientes(); break;
            case 0: printf("\nEncerrando o sistema. Ate logo!\n"); break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
