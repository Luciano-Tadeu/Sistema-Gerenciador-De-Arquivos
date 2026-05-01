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
}

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




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






// linhas acrescentadas por Gabriel 
/*
===========================
2. IMPRIMIR CAMINHO (AUXILIAR RECURSIVA)
===========================
Entrada: Nodo* pasta
Saída: imprime partes do caminho (sem o "->" final)
Exemplo:
-temp-teste2
Regra:
- Percorrer via ponteiro pai
- Ordem: raiz -> ... -> atual
*/
void imprimir_caminho_rec(Nodo *pasta){

    if(!pasta || !pasta->pai){
        return;
    }
    imprimir_caminho_rec(pasta->pai);
    printf("-%s",pasta->nome);

}

/*
===========================
1. IMPRIMIR CAMINHO (INTERFACE)
===========================
Entrada: Nodo* pasta atual
Saída: imprime o caminho no formato:
       -temp-teste2->
Regra:
- Se for raiz: imprime apenas "->"
- Não altera a estrutura
*/
void imprimir_caminho(Nodo *pasta){
    if(!pasta->pai){
        printf("->");
        return;
    }
    imprimir_caminho_rec( pasta);
    printf("->");

}





/*
===========================
3. BUSCAR PASTA
===========================
Entrada:
- Nodo* pasta_atual
- char* nome

Saída:
- retorna ponteiro para a pasta encontrada
- retorna NULL se não existir

Regra:
- Procurar apenas nós com diretorio == true
- Percorrer lista: filho -> irmao
*/
Nodo* buscar_pasta(Nodo *pasta_atual, char *nome){
    
    if(!pasta_atual || !pasta_atual->filho)
        return NULL;

    Nodo* aux= pasta_atual->filho;
    while(aux){
        if(aux->diretorio && strcmp(aux->nome,nome) == 0)
            return aux;
        aux = aux->irmao;
    }
    return NULL;

}


/*
===========================
4. COMANDO CD
===========================
Entrada:
- Nodo* pasta_atual
- char* nome

Saída:
- retorna nova pasta atual
- se erro → retorna a mesma pasta

Regras:
- "cd .." → volta para pai (se existir)
- "cd nome" → entra na subpasta
- erro → print "comando invalido"
*/
Nodo* comando_cd(Nodo *pasta_atual, char *nome){
    
    // tratar o cd ..
    if(strcmp(nome,"..")==0){
        if(pasta_atual->pai){
            return pasta_atual->pai;
        }else{
            printf("\ncomando invalido");
            return pasta_atual;
        }
    }
    // tratar o cd <nome>
    Nodo* aux = buscar_pasta(pasta_atual,nome);
    if(!aux){
        printf("\n comando invalido");   // não encontrou a pasta 
        return pasta_atual;
    }

    return aux;
}


/*
===========================
5. COMANDO LS
===========================
Entrada:
- Nodo* pasta_atual

Saída:
- imprime conteúdo da pasta:
  arquivos → nome
  pastas   → nome-

Regra:
- Percorrer lista filho -> irmao
- Ordem já está garantida na inserção
*/
void comando_ls(Nodo *pasta_atual){
    // TODO:
    if(!pasta_atual || !pasta_atual->filho){
        return;
    }
    Nodo* aux = pasta_atual->filho;
    while(aux){
        if(aux->diretorio){
            printf("%s-\n",aux->nome);
        }else{
            printf("%s\n",aux->nome);
        }
        aux = aux->irmao;
    }

}
