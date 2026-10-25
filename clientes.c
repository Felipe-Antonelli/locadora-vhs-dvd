#include <stdio.h>


/* A ficha do cliente (fora do main, no escopo global) */
struct Cliente {
    int  id;
    char nome[50];
    char cpf[15];
    char cidade[30];
    char telefone[20];
    int  bloqueado;        /* 1 = devendo/bloqueado, 0 = liberado */
};

/* O "banco de dados" na memoria: um vetor de fichas */
struct Cliente clientes[100];
int totalClientes = 0;          /* quantos clientes ja foram cadastrados */

/* Menu: funcao void que so mostra as opcoes */
void exibirMenuClientes() {
    printf("\n===== MENU CLIENTES =====\n");
    printf("1. Inserir cliente\n");
    printf("2. Listar clientes\n");
    printf("3. Atualizar cliente\n");
    printf("4. Remover cliente\n");
    printf("0. Voltar\n");
    printf("Escolha uma opcao: ");
}

/* 1. INSERIR (Create)  */
void inserirCliente() {
    if (totalClientes >= 100) {
        printf("\nCadastro cheio! Nao e possivel inserir mais clientes.\n");
        return;
    }

    struct Cliente novo;
    novo.id = totalClientes + 1;          /* id automatico */
    novo.bloqueado = 0;                   /* cliente novo comeca liberado */

    printf("\n--- Novo cliente (ID %d) ---\n", novo.id);

    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);          /* le o nome inteiro, com espacos */

    printf("CPF: ");
    scanf(" %[^\n]", novo.cpf);

    printf("Cidade: ");
    scanf(" %[^\n]", novo.cidade);

    printf("Telefone: ");
    scanf(" %[^\n]", novo.telefone);

    clientes[totalClientes] = novo;       /* guarda a ficha no vetor */
    totalClientes++;                      /* avanca o contador */

    printf("Cliente cadastrado com sucesso!\n");
}

/*  2. LISTAR (Read)  */
void listarClientes() {
    int i;

    if (totalClientes == 0) {
        printf("\nNenhum cliente cadastrado ainda.\n");
        return;
    }

    printf("\n--- LISTA DE CLIENTES ---\n");
    for (i = 0; i < totalClientes; i++) {
        printf("ID %d | %s | CPF: %s | %s | Tel: %s | %s\n",
               clientes[i].id,
               clientes[i].nome,
               clientes[i].cpf,
               clientes[i].cidade,
               clientes[i].telefone,
               clientes[i].bloqueado ? "BLOQUEADO" : "Liberado");
    }
}

/* \ Funcao de apoio: procura um cliente pelo id 
   devolve a POSICAO no vetor, ou -1 se nao achar */
int buscarPorId(int id) {
    int i;
    for (i = 0; i < totalClientes; i++) {
        if (clientes[i].id == id) {
            return i;
        }
    }
    return -1;
}

/* 3. ATUALIZAR (Update)  */
void atualizarCliente() {
    int id, pos;

    if (totalClientes == 0) {
        printf("\nNenhum cliente cadastrado ainda.\n");
        return;
    }

    printf("\nDigite o ID do cliente a atualizar: ");
    scanf("%d", &id);

    pos = buscarPorId(id);
    if (pos == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    printf("Atualizando o cliente: %s\n", clientes[pos].nome);

    printf("Novo nome: ");
    scanf(" %[^\n]", clientes[pos].nome);

    printf("Nova cidade: ");
    scanf(" %[^\n]", clientes[pos].cidade);

    printf("Novo telefone: ");
    scanf(" %[^\n]", clientes[pos].telefone);

    printf("Cliente atualizado com sucesso!\n");
}

/*  4. REMOVER (Delete) */
void removerCliente() {
    int id, pos, i;

    if (totalClientes == 0) {
        printf("\nNenhum cliente cadastrado ainda.\n");
        return;
    }

    printf("\nDigite o ID do cliente a remover: ");
    scanf("%d", &id);

    pos = buscarPorId(id);
    if (pos == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    /* "empurra" todos os de depois uma posicao para tras */
    for (i = pos; i < totalClientes - 1; i++) {
        clientes[i] = clientes[i + 1];
    }
    totalClientes--;

    printf("Cliente removido com sucesso!\n");
}

/*  MAIN: so o menu interativo */
int main() {
    int opcao;

    do {
        exibirMenuClientes();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: inserirCliente();   break;
            case 2: listarClientes();   break;
            case 3: atualizarCliente(); break;
            case 4: removerCliente();   break;
            case 0: printf("\nSaindo do modulo de clientes...\n"); break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
