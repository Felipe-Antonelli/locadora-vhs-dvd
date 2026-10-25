#include <stdio.h>

// struct do cliente
struct Cliente {
    int  id;
    char nome[50];
    char cpf[15];
    char cidade[30];
    char telefone[20];
    int  bloqueado;   // 1 = devendo, 0 = ok
};

struct Cliente clientes[100];
int totalClientes = 0;


// ---- clientes ----

void exibirMenuClientes() {
    printf("\n===== MENU CLIENTES =====\n");
    printf("1. Inserir cliente\n");
    printf("2. Listar clientes\n");
    printf("3. Atualizar cliente\n");
    printf("4. Remover cliente\n");
    printf("0. Voltar\n");
    printf("Escolha uma opcao: ");
}

void inserirCliente() {
    if (totalClientes >= 100) {
        printf("\nCadastro cheio!\n");
        return;
    }
    struct Cliente novo;
    novo.id = totalClientes + 1;
    novo.bloqueado = 0;

    printf("\n--- Novo cliente (ID %d) ---\n", novo.id);
    printf("Nome: ");     scanf(" %[^\n]", novo.nome);
    printf("CPF: ");      scanf(" %[^\n]", novo.cpf);
    printf("Cidade: ");   scanf(" %[^\n]", novo.cidade);
    printf("Telefone: "); scanf(" %[^\n]", novo.telefone);

    clientes[totalClientes] = novo;
    totalClientes++;
    printf("Cliente cadastrado com sucesso!\n");
}

void listarClientes() {
    int i;
    if (totalClientes == 0) {
        printf("\nNenhum cliente cadastrado ainda.\n");
        return;
    }
    printf("\n--- LISTA DE CLIENTES ---\n");
    for (i = 0; i < totalClientes; i++) {
        printf("ID %d | %s | CPF: %s | %s | Tel: %s | %s\n",
               clientes[i].id, clientes[i].nome, clientes[i].cpf,
               clientes[i].cidade, clientes[i].telefone,
               clientes[i].bloqueado ? "BLOQUEADO" : "Liberado");
    }
}

// procura o cliente pelo id e devolve a posicao (ou -1)
int buscarPorId(int id) {
    int i;
    for (i = 0; i < totalClientes; i++) {
        if (clientes[i].id == id) return i;
    }
    return -1;
}

void atualizarCliente() {
    int id, pos;
    if (totalClientes == 0) { printf("\nNenhum cliente cadastrado.\n"); return; }

    printf("\nDigite o ID do cliente a atualizar: ");
    scanf("%d", &id);
    pos = buscarPorId(id);
    if (pos == -1) { printf("Cliente nao encontrado.\n"); return; }

    printf("Atualizando: %s\n", clientes[pos].nome);
    printf("Novo nome: ");     scanf(" %[^\n]", clientes[pos].nome);
    printf("Nova cidade: ");   scanf(" %[^\n]", clientes[pos].cidade);
    printf("Novo telefone: "); scanf(" %[^\n]", clientes[pos].telefone);
    printf("Cliente atualizado!\n");
}

void removerCliente() {
    int id, pos, i;
    if (totalClientes == 0) { printf("\nNenhum cliente cadastrado.\n"); return; }

    printf("\nDigite o ID do cliente a remover: ");
    scanf("%d", &id);
    pos = buscarPorId(id);
    if (pos == -1) { printf("Cliente nao encontrado.\n"); return; }

    // puxa os de depois uma posicao pra tras
    for (i = pos; i < totalClientes - 1; i++) {
        clientes[i] = clientes[i + 1];
    }
    totalClientes--;
    printf("Cliente removido!\n");
}

void menuClientes() {
    int opcao;
    do {
        exibirMenuClientes();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: inserirCliente();   break;
            case 2: listarClientes();   break;
            case 3: atualizarCliente(); break;
            case 4: removerCliente();   break;
            case 0: printf("\nVoltando ao menu principal...\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);
}


// os outros modulos ainda vamos fazer

void menuFilmes() {
    printf("\n===== MENU FILMES =====\n");
    printf("(ainda em construcao)\n");
}

void menuLocacoes() {
    printf("\n===== MENU LOCACOES =====\n");
    printf("(ainda em construcao)\n");
}

void menuRelatorios() {
    printf("\n===== MENU RELATORIOS =====\n");
    printf("(ainda em construcao)\n");
}


// ---- menu principal ----

void exibirMenuPrincipal() {
    printf("\n==============================\n");
    printf("   LOCADORA DE VHS/DVD\n");
    printf("==============================\n");
    printf("Bem-vindo! Selecione uma opcao:\n");
    printf("1. Clientes\n");
    printf("2. Filmes\n");
    printf("3. Locacoes\n");
    printf("4. Relatorios\n");
    printf("0. Sair\n");
    printf("Opcao: ");
}

int main() {
    int opcao;
    do {
        exibirMenuPrincipal();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: menuClientes();   break;
            case 2: menuFilmes();     break;
            case 3: menuLocacoes();   break;
            case 4: menuRelatorios(); break;
            case 0: printf("\nEncerrando o sistema. Ate logo!\n"); break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
