#ifndef LOCACOES_H
#define LOCACOES_H
#include <stdio.h>
#include <string.h>
#include "clientes.h"
#include "filmes.h"

// Autor: Miguel Mazorca - RGM 49858998
struct Locacao {
    int   idLocacao;
    int   idClienteLocador;
    int   idFilmeAlugado;
    int   diasAluguel;
    float valorTotal;
};
struct Locacao historicoLocacoes[100];
int totalLocacoes = 0;

void salvarLocacoesCSV() {
    FILE *arq = fopen("locacoes.csv", "w");
    if (arq == NULL) { printf("Erro ao salvar os dados.\n"); return; }
    for (int i = 0; i < totalLocacoes; i++) {
        fprintf(arq, "%d;%d;%d;%d;%.2f\n",
                historicoLocacoes[i].idLocacao, historicoLocacoes[i].idClienteLocador,
                historicoLocacoes[i].idFilmeAlugado, historicoLocacoes[i].diasAluguel,
                historicoLocacoes[i].valorTotal);
    }
    fclose(arq);
}

void carregarLocacoesCSV() {
    FILE *arq = fopen("locacoes.csv", "r");
    if (arq == NULL) return;
    totalLocacoes = 0;
    while (totalLocacoes < 100 && fscanf(arq, "%d;%d;%d;%d;%f\n",
           &historicoLocacoes[totalLocacoes].idLocacao,
           &historicoLocacoes[totalLocacoes].idClienteLocador,
           &historicoLocacoes[totalLocacoes].idFilmeAlugado,
           &historicoLocacoes[totalLocacoes].diasAluguel,
           &historicoLocacoes[totalLocacoes].valorTotal) == 5) {
        totalLocacoes++;
    }
    fclose(arq);
}

void registrarLocacao() {
    if (totalLocacoes >= 100) { printf("\nLimite de locacoes atingido.\n"); return; }
    int idc, idf, dias;
    printf("\nID do cliente: "); scanf("%d", &idc);
    int posC = buscarClientePorId(idc);
    if (posC == -1) { printf("Cliente inexistente! Cadastre o cliente antes.\n"); return; }
    printf("ID do filme: ");   scanf("%d", &idf);
    int posF = buscarFilmePorId(idf);
    if (posF == -1) { printf("Filme inexistente! Cadastre o filme antes.\n"); return; }
    printf("Dias de aluguel: "); scanf("%d", &dias);

    struct Locacao nova;
    nova.idLocacao = totalLocacoes + 1;
    nova.idClienteLocador = idc;
    nova.idFilmeAlugado = idf;
    nova.diasAluguel = dias;
    nova.valorTotal = catalogoFilmes[posF].precoAluguel * dias;
    historicoLocacoes[totalLocacoes] = nova;
    totalLocacoes++;
    salvarLocacoesCSV();
    printf("Locacao registrada: %s alugou \"%s\" por %d dias = R$ %.2f\n",
           listaClientes[posC].nome, catalogoFilmes[posF].titulo, dias, nova.valorTotal);
}

void listarLocacoes() {
    printf("\n===== HISTORICO DE LOCACOES =====\n");
    if (totalLocacoes == 0) { printf("Nenhuma locacao registrada.\n"); return; }
    for (int i = 0; i < totalLocacoes; i++) {
        int posC = buscarClientePorId(historicoLocacoes[i].idClienteLocador);
        int posF = buscarFilmePorId(historicoLocacoes[i].idFilmeAlugado);
        char nomeCliente[50];
        char tituloFilme[50];
        if (posC != -1) strcpy(nomeCliente, listaClientes[posC].nome);
        else            strcpy(nomeCliente, "(removido)");
        if (posF != -1) strcpy(tituloFilme, catalogoFilmes[posF].titulo);
        else            strcpy(tituloFilme, "(removido)");
        printf("Loc %d | Cliente: %s | Filme: %s | %d dias | R$ %.2f\n",
               historicoLocacoes[i].idLocacao, nomeCliente, tituloFilme,
               historicoLocacoes[i].diasAluguel, historicoLocacoes[i].valorTotal);
    }
}

void devolverLocacao() {
    int id;
    printf("\nID da locacao a devolver/cancelar: ");
    scanf("%d", &id);
    int pos = -1;
    for (int i = 0; i < totalLocacoes; i++)
        if (historicoLocacoes[i].idLocacao == id) { pos = i; break; }
    if (pos == -1) { printf("Locacao nao encontrada.\n"); return; }
    for (int i = pos; i < totalLocacoes - 1; i++)
        historicoLocacoes[i] = historicoLocacoes[i + 1];
    totalLocacoes--;
    salvarLocacoesCSV();
    printf("Locacao devolvida e removida do historico!\n");
}

void relatorioFilmeMaisAlugado() {
    if (totalLocacoes == 0) { printf("\nSem locacoes para analisar.\n"); return; }
    int melhorPos = -1, maiorCont = 0;
    for (int i = 0; i < totalFilmes; i++) {
        int cont = 0;
        for (int j = 0; j < totalLocacoes; j++)
            if (historicoLocacoes[j].idFilmeAlugado == catalogoFilmes[i].idFilme) cont++;
        if (cont > maiorCont) { maiorCont = cont; melhorPos = i; }
    }
    printf("\n===== FILME MAIS ALUGADO =====\n");
    if (melhorPos != -1)
        printf("\"%s\" com %d locacoes.\n", catalogoFilmes[melhorPos].titulo, maiorCont);
    else
        printf("Nenhum filme foi alugado ainda.\n");
}

void relatorioClienteVIP() {
    if (totalLocacoes == 0) { printf("\nSem locacoes para analisar.\n"); return; }
    int vipPos = -1, maiorCont = 0;
    for (int i = 0; i < totalClientes; i++) {
        int cont = 0;
        for (int j = 0; j < totalLocacoes; j++)
            if (historicoLocacoes[j].idClienteLocador == listaClientes[i].idCliente) cont++;
        if (cont > maiorCont) { maiorCont = cont; vipPos = i; }
    }
    printf("\n===== CLIENTE VIP (MAIS ALUGOU) =====\n");
    if (vipPos != -1)
        printf("%s com %d locacoes.\n", listaClientes[vipPos].nome, maiorCont);
    else
        printf("Nenhum cliente alugou ainda.\n");
}

void relatorioLocacoesPorCliente() {
    int id;
    printf("\nID do cliente: "); scanf("%d", &id);
    int posC = buscarClientePorId(id);
    if (posC == -1) { printf("Cliente nao encontrado.\n"); return; }
    printf("\n===== LOCACOES DE %s =====\n", listaClientes[posC].nome);
    float total = 0; int qtd = 0;
    for (int j = 0; j < totalLocacoes; j++) {
        if (historicoLocacoes[j].idClienteLocador != id) continue;
        int posF = buscarFilmePorId(historicoLocacoes[j].idFilmeAlugado);
        char tituloFilme[50];
        if (posF != -1) strcpy(tituloFilme, catalogoFilmes[posF].titulo);
        else            strcpy(tituloFilme, "(removido)");
        printf("- %s | %d dias | R$ %.2f\n",
               tituloFilme, historicoLocacoes[j].diasAluguel, historicoLocacoes[j].valorTotal);
        total += historicoLocacoes[j].valorTotal; qtd++;
    }
    if (qtd == 0) printf("Esse cliente nao tem locacoes.\n");
    else          printf("Total: %d locacoes, R$ %.2f gastos.\n", qtd, total);
}

#define PRAT_LINHAS 3
#define PRAT_COLUNAS 5
void mapaDaEstante() {
    int grade[PRAT_LINHAS][PRAT_COLUNAS];
    int k = 0;
    for (int i = 0; i < PRAT_LINHAS; i++) {
        for (int j = 0; j < PRAT_COLUNAS; j++) {
            if (k < totalFilmes) grade[i][j] = catalogoFilmes[k].idFilme;
            else                 grade[i][j] = 0;
            k++;
        }
    }
    printf("\n===== MAPA DA ESTANTE (codigo do filme por posicao) =====\n");
    int ocupadas = 0;
    for (int i = 0; i < PRAT_LINHAS; i++) {
        printf("Prateleira %c: ", 'A' + i);
        for (int j = 0; j < PRAT_COLUNAS; j++) {
            if (grade[i][j] == 0) printf("[ -- ] ");
            else { printf("[ #%2d ] ", grade[i][j]); ocupadas++; }
        }
        printf("\n");
    }
    printf("Posicoes ocupadas: %d de %d\n", ocupadas, PRAT_LINHAS * PRAT_COLUNAS);
}

void moduloLocacoes() {
    int op;
    do {
        printf("\n===== LOCACOES E RELATORIOS =====\n");
        printf("1. Registrar locacao\n");
        printf("2. Listar locacoes\n");
        printf("3. Devolver / Cancelar locacao\n");
        printf("4. Relatorio: filme mais alugado\n");
        printf("5. Relatorio: cliente VIP\n");
        printf("6. Relatorio: locacoes por cliente\n");
        printf("7. Mapa da estante\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        if (scanf("%d", &op) != 1) { op = 0; break; }
        switch (op) {
            case 1: registrarLocacao();            break;
            case 2: listarLocacoes();              break;
            case 3: devolverLocacao();             break;
            case 4: relatorioFilmeMaisAlugado();   break;
            case 5: relatorioClienteVIP();         break;
            case 6: relatorioLocacoesPorCliente(); break;
            case 7: mapaDaEstante();               break;
            case 0: printf("\nVoltando...\n");     break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (op != 0);
}
#endif
