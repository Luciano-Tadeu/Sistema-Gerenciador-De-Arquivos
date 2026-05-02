#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Nodo
{
    char nome[100];
    bool diretorio; // define se é pasta ou arquivo: true = pasta / false = arquivo
    struct Nodo *pai;
    struct Nodo *filho;
    struct Nodo *irmao;

} Nodo;

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
    imprimir_caminho_rec(pasta);
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
            printf("comando invalido\n");
            return pasta_atual;
        }
    }
    // tratar o cd <nome>
    Nodo* aux = buscar_pasta(pasta_atual,nome);
    if(!aux){
        printf("comando invalido\n");   // não encontrou a pasta 
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

void free_tree(Nodo *nodo) {
    if (!nodo) return;
    
    Nodo *atual = nodo->filho;
    while (atual != NULL) {
        Nodo *proximo = atual->irmao;
        free_tree(atual);
        atual = proximo;
    }
    
    free(nodo);
}


void comando_rm(Nodo* pasta_atual, char *nome) {
    if (!pasta_atual || !pasta_atual->filho) {
        printf("comando invalido\n");
        return;
    }

    Nodo *atual = pasta_atual->filho;
    Nodo *anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->irmao;
    }

    if (atual == NULL) {
        printf("comando invalido\n");
        return;
    }

    if (anterior == NULL) {
        pasta_atual->filho = atual->irmao;
    } 
    else {
        anterior->irmao = atual->irmao;
    }

    free_tree(atual);
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