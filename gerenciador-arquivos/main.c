#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tree.h"

typedef struct{
    char digitado[100];
    char com[100];
    char arg[100];
} COMANDO;


void lerComando(COMANDO* c){
    fgets(c->digitado, sizeof(c->digitado), stdin);
    c->digitado[strcspn(c->digitado, "\n\r")] = '\0';
    sscanf(c->digitado, "%[^ ] %[^ ]", c->com, c->arg);
}



int main(void){

    COMANDO* c = (COMANDO*)malloc(sizeof(COMANDO));
    Nodo *pasta_atual, *raiz = criarNodo(NULL, true, "");
    pasta_atual = raiz;

    do
    {
        imprimir_caminho(pasta_atual);
        lerComando(c);
        if(strcmp(c->com, "ls") == 0) comando_ls(pasta_atual);
        else if(strcmp(c->com, "ma") == 0) comando_ma(pasta_atual, c->arg);
        else if(strcmp(c->com, "mp") == 0) comando_mp(pasta_atual, c->arg);
        else if(strcmp(c->com, "cd") == 0) pasta_atual = comando_cd(pasta_atual, c->arg);
        else if(strcmp(c->com, "rm") == 0) comando_rm(pasta_atual, c->arg);
        else if(strcmp(c->com, "ex") == 0) printf("sistema encerrado\n");
        else printf("comando invalido\n");
    } while (strcmp(c->com, "ex") != 0);
    

    free_tree(raiz);
    free(c);
    return 0;
}
