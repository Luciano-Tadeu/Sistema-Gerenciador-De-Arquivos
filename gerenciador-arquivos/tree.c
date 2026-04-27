#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

Nodo *criarNodo(Nodo *pasta_atual, bool diretorio, char* nome)
{
    Nodo *novo = (Nodo *)malloc(sizeof(Nodo));
    if (!novo)
    {
        printf("Erro");
        return NULL;
    }

    strncpy(novo->nome, nome, 99);
    novo->nome[99] = '\0';

    novo->diretorio = diretorio;
    novo->pai = pasta_atual;
    novo->filho = NULL;
    novo->irmao = NULL;

    return novo;
};

void inserir(Nodo *pasta_atual, Nodo *arquivo)
{

    if (!pasta_atual->filho)
    {
        pasta_atual->filho = arquivo;
        return;
    }

    Nodo *aux = pasta_atual->filho;
    Nodo *prox = NULL;

  while (aux && strcmp(aux->nome, arquivo->nome) < 0) 
    {
        prox = aux;
        aux = aux->irmao;
    }
    if(aux && strcmp(aux->nome, arquivo->nome) == 0)
    {
        printf("ERRO: O nome '%s' ja existe neste diretorio.\n", arquivo->nome);
        free(arquivo);
        return;
    }
    if (!prox)
    {

        arquivo->irmao = pasta_atual->filho;
        pasta_atual->filho = arquivo;

    } else {

        arquivo->irmao = aux;
        prox->irmao = arquivo;

    }
    
}

void comando_mp(Nodo *pasta_atual, char *nome){
   Nodo* novo = criarNodo(pasta_atual, true, nome);

   if (novo)
   {
    inserir(pasta_atual, novo);
    return;
   }
   
}

void comando_ma(Nodo *pasta_atual, char *nome){
   Nodo* novo = criarNodo(pasta_atual, false, nome);

   if (novo)
   {
    inserir(pasta_atual, novo);
    return;
   }
   
}