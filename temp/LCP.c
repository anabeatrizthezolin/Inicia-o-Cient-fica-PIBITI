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

int main(){
    char T[200];
    scanf("%s", T);
    int n = strlen(T), aux = 0, soma = 0;
    T[n] = '#';
    n++;
    p_rot rot[n];
    int LCP[n], ISA[n];

    for(int i = 0; i < n; i++){
        rot[i].rotacao = &T[i];
        rot[i].SA = i;
    }
    qsort(rot, n, sizeof(struct estrutura), ordena);
    for(int i = 0; i < n; i++){
        ISA[rot[i].SA] = i;
    }
    LCP[0] = 0;
    int l = 0;
    for(int i = 0; i < n; i++){
        int j = ISA[i];
        if(j > 0){
            int k = rot[j-1].SA;
            while(T[k+l] == T[i+l]){
                l++;
            }
            LCP[j] = l;
            if(l-1 >= 0){
                l = l-1;
            }
            else{
                l = 0;
            }
        }
    }
    for(int i = 0; i < n; i++){
        printf("%d ", LCP[i]);
    }
}
