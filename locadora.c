#include <stdio.h>
#include <string.h>

// ============================================================================
// PARTE 1: MODELAGEM DE DADOS (ESCOPO GLOBAL - 1 STRUCT POR INTEGRANTE)
// ============================================================================

// 1.Felipe: Clientes da locadora
struct Cliente {
    int   idCliente;
    char  nome[50];
    char  telefone[20];
    float multasPendentes;
    int   ativo;           
};
struct Cliente listaClientes[50];
int totalClientes = 0;

// 2.Rafael Gustavo: Fornecedores (distribuidoras)
struct Fornecedor {
    int   idFornecedor;
    char  nome[50];
    char  contato[30];
    float valorDivida;
    int   ativo;
};
struct Fornecedor listaFornecedores[50];
int totalFornecedores = 0;

// 3.Rafael Leonardo: Catalogo de Filmes
struct Filme {
    int   idFilme;
    char  titulo[50];
    char  genero[30];
    float precoAluguel;
    int   disponivel;        
};
struct Filme catalogoFilmes[50];
int totalFilmes = 0;

// 4.Miguel: Locacoes e Relatorios
struct Locacao {
    int   idLocacao;
    int   idClienteLocador;
    int   idFilmeAlugado;
    int   diasAluguel;
    float valorTotal;
};
struct Locacao historicoLocacoes[50];
int totalLocacoes = 0;

// ============================================================================
// PARTE 2: FUNCOES DE INTERFACE E MODULOS DE CADA INTEGRANTE
// ============================================================================

void exibirCabecalho() {
    printf("   LOCADORA DE VHS/DVD\n");
}

// ----------------------------------------------------------------------------
// MODULO 1: CLIENTES | Autor: Felipe Antonelli Bueno - RGM 46686177
// ----------------------------------------------------------------------------
void moduloClientes() {
    int opcao;
    do {
        printf("\nMODULO CLIENTES\n");
        printf("1. Cadastrar cliente\n");
        printf("2. Listar / Buscar clientes\n");
        printf("3. Editar cliente\n");
        printf("4. Remover cliente\n");
        printf("0. Voltar\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: printf("\n[Em construcao] Cadastro de cliente\n"); break;
            case 2: printf("\n[Em construcao] Listagem de clientes\n"); break;
            case 3: printf("\n[Em construcao] Edicao de cliente\n"); break;
            case 4: printf("\n[Em construcao] Remocao de cliente\n"); break;
            case 0: printf("\nVoltando ao menu principal\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);
}

// ----------------------------------------------------------------------------
// MODULO 2: FORNECEDORES | Autor: Rafael Gustavo de Franca Lima - RGM 48242365
// ----------------------------------------------------------------------------
void moduloFornecedores() {
    int opcao;
    do {
        printf("\nMODULO FORNECEDORES\n");
        printf("1. Cadastrar fornecedor\n");
        printf("2. Listar / Buscar fornecedores\n");
        printf("3. Editar fornecedor\n");
        printf("4. Remover fornecedor\n");
        printf("0. Voltar\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: printf("\n[Em construcao] Cadastro de fornecedor\n"); break;
            case 2: printf("\n[Em construcao] Listagem de fornecedores\n"); break;
            case 3: printf("\n[Em construcao] Edicao de fornecedor\n"); break;
            case 4: printf("\n[Em construcao] Remocao de fornecedor\n"); break;
            case 0: printf("\nVoltando ao menu principal\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);
}

// ----------------------------------------------------------------------------
// MODULO 3: FILMES | Autor: Rafael Leonardo Fernandes de Lima Leal - RGM 46909371
// ----------------------------------------------------------------------------
void moduloFilmes() {
    int opcao;
    do {
        printf("\nMODULO FILMES / CATALOGO\n");
        printf("1. Cadastrar filme\n");
        printf("2. Listar / Buscar filmes\n");
        printf("3. Editar preco ou disponibilidade\n");
        printf("4. Remover filme\n");
        printf("0. Voltar\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: printf("\n[Em construcao] Cadastro de filme\n"); break;
            case 2: printf("\n[Em construcao] Listagem de filmes\n"); break;
            case 3: printf("\n[Em construcao] Edicao de filme\n"); break;
            case 4: printf("\n[Em construcao] Remocao de filme\n"); break;
            case 0: printf("\nVoltando ao menu principal\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);
}

// ----------------------------------------------------------------------------
// MODULO 4: LOCACOES E RELATORIOS | Autor: Miguel Mazorca - RGM 49858998
// ----------------------------------------------------------------------------
void moduloLocacoesRelatorios() {
    int opcao;
    do {
        printf("\nMODULO LOCACOES E RELATORIOS\n");
        printf("1. Registrar locacao (cruza cliente + filme)\n");
        printf("2. Listar historico de locacoes\n");
        printf("3. Devolver / cancelar locacao\n");
        printf("4. Filme mais alugado\n");
        printf("5. Cliente que mais alugou\n");
        printf("6. Locacoes por cliente\n");
        printf("0. Voltar\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: printf("\n[Em construcao] Registro de locacao\n"); break;
            case 2: printf("\n[Em construcao] Historico de locacoes\n"); break;
            case 3: printf("\n[Em construcao] Devolucao de locacao\n"); break;
            case 4: printf("\n[Em construcao] Ranking de filme mais alugado\n"); break;
            case 5: printf("\n[Em construcao] Cliente que mais alugou\n"); break;
            case 6: printf("\n[Em construcao] Locacoes por cliente\n"); break;
            case 0: printf("\nVoltando ao menu principal\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);
}

// ============================================================================
// PARTE 3: FUNCAO PRINCIPAL (MAIN) - DESPACHANTE DE MENUS
// ============================================================================
int main() {
    int opcao;
    do {
        exibirCabecalho();
        printf("SELECIONE A PERSPECTIVA:\n");
        printf("1. Clientes\n");
        printf("2. Fornecedores\n");
        printf("3. Filmes\n");
        printf("4. Locacoes e Relatorios\n");
        printf("0. Encerrar o sistema\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: moduloClientes();           break;
            case 2: moduloFornecedores();       break;
            case 3: moduloFilmes();             break;
            case 4: moduloLocacoesRelatorios(); break;
            case 0: printf("\nEncerrando o sistema. Ate logo!\n"); break;
            default: printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
