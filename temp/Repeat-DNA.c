#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct estrutura{
	char *rotacao;
	int SA;
}p_rot;
typedef struct pilha{
    int a;
    int l;
    int h;
}p_pilha;

int ordena(const void *a, const void *b){
    struct estrutura* aa = (struct estrutura*)a;
    struct estrutura* bb = (struct estrutura*)b;
    if(strcmp(aa->rotacao, bb->rotacao) > 0){ return 1;}
    if(strcmp(aa->rotacao, bb->rotacao) < 0){ return -1;}
}

int C[125], adicional[125];
int main(){
    char T[200];
    scanf("%s", T);
    int n = strlen(T), aux = 0, soma = 0;
    T[n] = '#';
    n++;
    p_rot rot[n];
    char BWT[n], Saida[n];
    int LF[n], LCP[n+1], ISA[n];
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

    for(int i = 0; i < n; i++){
        ISA[rot[i].SA] = i;
    }
    LCP[0] = 0;
    int l = 0;
    for(int i = 0; i < n; i++){
        int j = ISA[i];
        if(j > 0){
            int k = rot[j-1].SA;
            while(T[k+l] == T[i+l] && T[k+l] != '$'){
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
    LCP[n] = 0;
    p_pilha p[n];
    int z = 1;
    scanf("%d", &l);
    p[0].a = 0;
    p[0].l = l;
    p[0].h = 0;
    printf("Tipo 1: \n");
    for(int i = 0; i <= n; i++){
        if(LCP[i] == l && LCP[i-1] < l || LCP[i] > l){
            p[z].a = i-1;
            p[z].l = LCP[i];
            p[z].h = i;
            z++;
            if(LCP[i] > l){
                l = LCP[i];
            }
        }
        else if(LCP[i] < l && z > 1){
            z--;
            for(int k = p[z].a; k < i; k++){ // nesse ponto, i == b+1
                adicional[BWT[k]]++;
                if(adicional[BWT[k]] == 1 && k > p[z].a){
                    char omega[200];
                    int y = 0;
                    for(int j = rot[p[z].h].SA; j < rot[p[z].h].SA+l; j++){
                        omega[y] = T[j];
                        y++;
                    }
                    omega[y] = '\0';
                    printf("%s\n", omega);
                    break;
                }
            }
            if(LCP[i] >= p[z-1].l){
                p[z].l = LCP[i];
                p[z].h = i;
                l = LCP[i];
                z++;
            }
            else{
                l = p[z-1].l;
            }
            i--; // para continuar analisando o intervalo [a, b] para o item anterior que pode ter LCP[i] == l.
            for(int k = 0; k < 125; k++){ // paraa zerar os elentos do vetor para a próxima comparação
                adicional[k] = 0;
            }
        }
    }
    printf("\nTipo 2: \n");
    for(int i = 0; i <= n; i++){
        if(LCP[i] == l && LCP[i-1] < l){
            p[z].a = i-1;
            p[z].l = LCP[i];
            z++;
        }
        else if(LCP[i] > l){
            if(z > 1){
                z--; // já que as variáveis do elemento anterior não correspondem com a condição de LCP[b+1] < l
            }
            p[z].a = i-1;
            p[z].l = LCP[i];
            l = LCP[i];
            z++;
        }
        else if(LCP[i] < l && z > 1){
            z--;
            int tipo2 = 1;
            for(int k = p[z].a; k < i; k++){ // nesse ponto, i == b+1
                adicional[BWT[k]]++;
                if(adicional[BWT[k]] > 1 && adicional[BWT[k]] != '$'){
                    tipo2 = 0;
                    break;
                }
            }
            if(tipo2 == 1){
                char omega[n], y = 0;
                for(int j = rot[p[z].a].SA; j < rot[p[z].a].SA+l; j++){
                    omega[y] = T[j];
                    y++;
                }
                omega[y] = '\0';
                printf("%s\n", omega);
            }
            l = p[z-1].l;
            for(int k = 0; k < 125; k++){
                adicional[k] = 0;
            }
        }
    }
}
