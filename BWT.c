#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct estrutura{
	char *rotacao;
	int SA;
}p_rot;

int ordena(const void *a, const void *b){
    struct estrutura* aa = (struct estrutura*)a;
    struct estrutura* bb = (struct estrutura*)b;
    if(strcmp(aa->rotacao, bb->rotacao) > 0){ return 1;}
    if(strcmp(aa->rotacao, bb->rotacao) < 0){ return -1;}
}

int C[125], cont[125];
int main(){
    char T[200];
    scanf("%s", T);
    int n = strlen(T), aux = 0, soma = 0;
    T[n] = '#';
    n++;
		p_rot rot[n];
		char BWT[n], Saida[n];
		int LF[n];

    for(int i = 0; i < n; i++){
        rot[i].rotacao = &T[i];
        rot[i].SA = i;
    }
    qsort(rot, n, sizeof(struct estrutura), ordena);
    for(int i = 0; i < n; i++){
        if(rot[i].SA == 0){
            BWT[i] = '#';
        }
        else{
            BWT[i] = T[rot[i].SA-1];
        }
        C[BWT[i]]++;
    }
    BWT[n] = '\0';

    for(int i = 35; i < 125; i++){
        if(C[i] > 0){
	    cont[i] = aux;
            soma += C[i];
        }
    }
    for(int i = 0; i < n; i++){
        LF[i] = cont[BWT[i]];
        cont[BWT[i]]++;
    }
    Saida[n-1] = '#';
    int j = 0;
    for(int i = n-2; i >= 0; i--){
        Saida[i] = BWT[j];
        j = LF[j];
    }
    Saida[n] = '\0';

    printf("\n%s \n%s \n", BWT, Saida);
}
