#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>

using namespace std;

int C[125], adicional[125];
int main(int argc, char* argv[]){

    int l_input = atoi(argv[4]);

    FILE* arquivo = fopen(argv[1], "rb"); // rb para arquivos binários
    fseek(arquivo, 0, SEEK_END);
    int n = ftell(arquivo); // para salvar em n o tamanho do arquivo
    rewind(arquivo);
    char *BWT = (char*)malloc(sizeof(char)*(n));
    fread(BWT, sizeof(char), n, arquivo);
    fclose(arquivo);

    arquivo = fopen(argv[2], "rb"); // rb para arquivos binários
    int *SA = (int*)malloc(sizeof(int)*(n));
    fread(SA, sizeof(int), n, arquivo);
    fclose(arquivo);

    arquivo = fopen(argv[3], "rb"); // rb para arquivos binários
    int *LCP = (int*)malloc(sizeof(int)*(n));
    fread(LCP, sizeof(int), n, arquivo);
    fclose(arquivo);
    LCP[n] = 0;
    
    stack <int> a;
    stack <int> l;
    stack <int> h;
    a.push(0);
    l.push(l_input);
    h.push(0);
    printf("\n## Repeat DNA ##");
    printf("\nTipo 1: \n");
    for(int i = 0; i <= n; i++){
        if(LCP[i] == l_input && LCP[i-1] < l_input || LCP[i] > l_input){
            a.push(i-1);
            l.push(LCP[i]);
            h.push(i);
            if(LCP[i] > l_input){
                l_input = LCP[i];
            }
        }
        else if(LCP[i] < l_input && a.size() > 1){
            for(int k = a.top(); k < i; k++){ // nesse ponto, i == b+1
                adicional[BWT[k]]++;
                if(adicional[BWT[k]] == 1 && k > a.top()){
                    int j = SA[h.top()];
                    printf("A repeticao comeca no indice %d de T\n", j);
                    break;
                }
            }
            int aux_a = a.top();
            a.pop();
            l.pop();
            h.pop();
            if(LCP[i] >= l.top()){
                a.push(aux_a);
                l.push(LCP[i]);
                h.push(i);
                l_input = LCP[i];
            }
            else{
             
                 l_input = l.top();
            }
            i--; // para continuar analisando o intervalo [a, b] para o item anterior que pode ter LCP[i] == l_input.
            for(int k = 0; k < 125; k++){ // paraa zerar os elentos do vetor para a próxima comparação
                adicional[k] = 0;
            }
        }
    }
    printf("\nTipo 2: \n");
    for(int i = 0; i <= n; i++){
        if(LCP[i] == l_input && LCP[i-1] < l_input){
            a.push(i-1);
            l.push(LCP[i]);
        }
        else if(LCP[i] > l_input){
            if(a.size() > 1){
                a.pop();
                l.pop();
            }
            a.push(i-1);
            l.push(LCP[i]);
            l_input = LCP[i];
        }
        else if(LCP[i] < l_input && a.size() > 1){
            int tipo2 = 1;
            for(int k = a.top(); k < i; k++){ // nesse ponto, i == b+1
                adicional[BWT[k]]++;
                if(adicional[BWT[k]] > 1 && adicional[BWT[k]] != ' '){
                    tipo2 = 0;
                    break;
                }
            }
            if(tipo2 == 1){
                int j = SA[a.top()];
                printf("A repeticao comeca no indice %d de T\n", j);
            }
            a.pop();
            l.pop();
            l_input = l.top();
            for(int k = 0; k < 125; k++){
                adicional[k] = 0;
            }
        }
    }
    free(BWT);
    free(SA);
    free(LCP);
    return 0;
}
