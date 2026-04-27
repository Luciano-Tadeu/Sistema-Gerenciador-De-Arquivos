#include <stdbool.h>

typedef struct nodo
{
    char nome[100];
    bool diretorio; // define se é pasta ou arquivo: true = pasta / false = arquivo
    struct Nodo *pai;
    struct Nodo *filho;
    struct Nodo *irmao;

} Nodo;

Nodo* criarNodo(Nodo *p, bool diretorio, char *nome); // passa o nó e se é pasta ou arquivos
void inserir(Nodo *pasta_atual, Nodo* arquivo);
void comando_mp(Nodo* pasta_atual, char* nome);
void comando_ma(Nodo* pasta_atual, char* nome);

