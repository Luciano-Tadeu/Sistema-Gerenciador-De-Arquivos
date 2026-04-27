#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

    do
    {
        //Inserir função que printa o caminho
        lerComando(c);
        if(strcmp(c->com, "ls") == 0) printf("ls\n"); //Inserir funções no local do printf.
        else if(strcmp(c->com, "ma") == 0) printf("ma\n");
        else if(strcmp(c->com, "mp") == 0) printf("mp\n");
        else if(strcmp(c->com, "cd") == 0) printf("cd\n");
        else if(strcmp(c->com, "rm") == 0) printf("rm\n");
        else if(strcmp(c->com, "ex") == 0) printf("sistema encerrado\n"); //Puxar função para libertar a memória.
        else printf("comando invalido\n");
    } while (strcmp(c->com, "ex") != 0);
    

    free(c);
    return 0;
}
