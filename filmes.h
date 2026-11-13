#ifndef FILMES_H
#define FILMES_H
#include <stdio.h>
#include <string.h>

// ----------------------------------------------------------------------------
// MODULO 3: FILMES | Autor: Rafael Leonardo Fernandes de Lima Leal - RGM 46909371
// ----------------------------------------------------------------------------
struct Filme {
    int   idFilme;
    char  titulo[50];
    char  genero[30];
    float precoAluguel;
    int   disponivel;
};
struct Filme catalogoFilmes[50];
int totalFilmes = 0;

void salvarFilmesCSV() {
    FILE *arq = fopen("filmes.csv", "w");
    if (arq == NULL) { printf("[ERRO] Nao foi possivel salvar filmes.csv\n"); return; }
    for (int i = 0; i < totalFilmes; i++) {
        fprintf(arq, "%d;%s;%s;%.2f;%d\n",
                catalogoFilmes[i].idFilme, catalogoFilmes[i].titulo,
                catalogoFilmes[i].genero, catalogoFilmes[i].precoAluguel,
                catalogoFilmes[i].disponivel);
    }
    fclose(arq);
}

void carregarFilmesCSV() {
    FILE *arq = fopen("filmes.csv", "r");
    if (arq == NULL) return;
    totalFilmes = 0;
    while (totalFilmes < 50 && fscanf(arq, "%d;%49[^;];%29[^;];%f;%d\n",
           &catalogoFilmes[totalFilmes].idFilme,
           catalogoFilmes[totalFilmes].titulo,
           catalogoFilmes[totalFilmes].genero,
           &catalogoFilmes[totalFilmes].precoAluguel,
           &catalogoFilmes[totalFilmes].disponivel) == 5) {
        totalFilmes++;
    }
    fclose(arq);
}

int buscarFilmePorId(int id) {
    for (int i = 0; i < totalFilmes; i++)
        if (catalogoFilmes[i].idFilme == id && catalogoFilmes[i].disponivel == 1) return i;
    return -1;
}

void cadastrarFilme() {
    if (totalFilmes >= 50) { printf("\n[ALERTA] Catalogo cheio!\n"); return; }
    struct Filme novo;
    novo.idFilme = totalFilmes + 1;
    novo.disponivel = 1;
    printf("\n--- NOVO FILME (ID %d) ---\n", novo.idFilme);
    printf("Titulo: ");            scanf(" %49[^\n]", novo.titulo);
    printf("Genero: ");            scanf(" %29[^\n]", novo.genero);
    printf("Preco do aluguel (R$): "); scanf("%f", &novo.precoAluguel);
    catalogoFilmes[totalFilmes] = novo;
    totalFilmes++;
    salvarFilmesCSV();
    printf("Filme cadastrado e salvo no CSV!\n");
}

void listarOuBuscarFilmes() {
    char termo[50];
    printf("\nBuscar por titulo (ou 0 para listar todos): ");
    scanf(" %49[^\n]", termo);
    printf("\n=== CATALOGO DE FILMES ===\n");
    int achou = 0;
    for (int i = 0; i < totalFilmes; i++) {
        if (catalogoFilmes[i].disponivel == 0) continue;
        if (strcmp(termo, "0") != 0 && strstr(catalogoFilmes[i].titulo, termo) == NULL) continue;
        printf("ID %d | %s | Genero: %s | R$ %.2f\n",
               catalogoFilmes[i].idFilme, catalogoFilmes[i].titulo,
               catalogoFilmes[i].genero, catalogoFilmes[i].precoAluguel);
        achou = 1;
    }
    if (!achou) printf("Nenhum filme encontrado.\n");
}

void editarFilme() {
    int id;
    printf("\nID do filme a editar: ");
    scanf("%d", &id);
    int pos = buscarFilmePorId(id);
    if (pos == -1) { printf("Filme nao encontrado.\n"); return; }
    printf("Novo titulo: ");       scanf(" %49[^\n]", catalogoFilmes[pos].titulo);
    printf("Novo genero: ");       scanf(" %29[^\n]", catalogoFilmes[pos].genero);
    printf("Novo preco (R$): ");   scanf("%f", &catalogoFilmes[pos].precoAluguel);
    salvarFilmesCSV();
    printf("Filme atualizado e salvo!\n");
}

void removerFilme() {
    int id;
    printf("\nID do filme a remover: ");
    scanf("%d", &id);
    int pos = buscarFilmePorId(id);
    if (pos == -1) { printf("Filme nao encontrado.\n"); return; }
    catalogoFilmes[pos].disponivel = 0;
    salvarFilmesCSV();
    printf("Filme removido do catalogo e salvo!\n");
}

void moduloFilmes() {
    int op;
    do {
        printf("\n--- MODULO FILMES (CSV ATIVO) ---\n");
        printf("1. Cadastrar filme\n");
        printf("2. Listar / Buscar filmes\n");
        printf("3. Editar filme\n");
        printf("4. Remover filme\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &op) != 1) { op = 0; break; }
        switch (op) {
            case 1: cadastrarFilme();       break;
            case 2: listarOuBuscarFilmes(); break;
            case 3: editarFilme();          break;
            case 4: removerFilme();         break;
            case 0: printf("\nVoltando...\n"); break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (op != 0);
}
#endif
