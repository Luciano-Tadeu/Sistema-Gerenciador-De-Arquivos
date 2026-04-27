#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

Nodo* criarNodo(Nodo* pasta_atual, bool diretorio){
    Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
    if(!novo){printf("Erro"); return NULL;}

    printf("%s: ", diretorio ? "Nome da pasta" : "Nome do arquivo");
    scanf("%99s", novo->nome);

    novo->diretorio = diretorio;
    novo->pai = pasta_atual;
    novo->filho = NULL;
    novo->irmao = NULL;

    return novo;
};
