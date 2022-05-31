#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>

using namespace std;

int open(char *arq, int n, int *ARQ){
    FILE* f = fopen(arq, "rb"); // rb para arquivos binários
    int ret = fread(ARQ, sizeof(int), n, f);
    if(ret != n){
        printf("Error reading file\n");
    }
    fclose(f);
    return *ARQ;
}

char repeat(int j, int l, char *T, int n, char *omega){
    int y = 0;
    for(int i = j; i < j+l; i++){
        omega[y] = T[i];
        y++;
    }
    omega[y] = '\0';
    return *omega;
}

char print(int k, char *file_type, char *arg, char *t){
    strcpy(file_type, arg);
    strcat(file_type, t);
    return *file_type;
}

int add[125];
int main(int argc, char* argv[]){

    int l_input = atoi(argv[5]);
    int op = atoi(argv[6]);
    int op_p = atoi(argv[7]);

    FILE* f = fopen(argv[1], "r"); 
    fseek(f, 0, SEEK_END);
    int n = ftell(f); // para salvar em n o tamanho do arquivo
    rewind(f);
    char *T = (char*)malloc(sizeof(char)*(n+1));
    T[n]='\0';
    int ret = fread(T, sizeof(char), n, f);
    if(ret != n){
        printf("Error reading file\n");
    }
    fclose(f);

    f = fopen(argv[2], "rb"); // rb para arquivos binários
    char *BWT = (char*)malloc(sizeof(char)*(n));
    ret = fread(BWT, sizeof(char), n, f);
    if(ret != n){
        printf("Error reading file\n");
    }
    fclose(f);
    int *SA = (int*)malloc(sizeof(int)*(n+1));
    open(argv[3], n, SA);

    int *LCP = (int*)malloc(sizeof(int)*(n+1));
    open(argv[4], n, LCP);
    LCP[n] = 0;
    
    stack <int> a;
    stack <int> l;
    stack <int> h;
    a.push(0);
    l.push(l_input);
    h.push(0);

    int k = strlen(argv[1]);        
    char *file_type = (char*)malloc(sizeof(char)*(k+7));

    if(op == 1 || op == 0){
        char *type1 = (char*)".type1";
        *file_type = print(k, file_type, argv[1], type1);
        f = fopen(file_type, "wb");
        
        for(int i = 0; i <= n; i++){
            if((LCP[i] == l_input && LCP[i-1] < l_input) || LCP[i] > l_input){
                a.push(i-1);
                l.push(LCP[i]);
                h.push(i);
                if(LCP[i] > l_input){
                    l_input = LCP[i];
                }
            }
            else if(LCP[i] < l_input && a.size() > 1){
                for(int k = a.top(); k < i; k++){ // i == b+1
                    add[BWT[k]]++;
                    if(add[BWT[k]] == 1 && k > a.top()){
                        if(op_p == 1){

                            char *omega = (char*)malloc(sizeof(char)*(l_input+1));
                            *omega = repeat(SA[h.top()], l_input, T, n, omega);
                            fprintf(f, "%s\n", omega);
                        }   
                        else if(op_p == 2){
                            fprintf(f, "%d, %d\n", SA[h.top()], l_input);
                        }
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
                i--; 
                for(int k = 0; k < 125; k++){ 
                    add[k] = 0;
                }
            }
        }
    }

    if(op == 2 || op == 0){

        char *type2 = (char*)".type2";
        *file_type = print(k, file_type, argv[1], type2);
        f = fopen(file_type, "wb");

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
                for(int k = a.top(); k < i; k++){ //i == b+1
                    add[BWT[k]]++;
                    if(add[BWT[k]] > 1 && add[BWT[k]] != ' '){
                        tipo2 = 0;
                        break;
                    }
                }
                if(tipo2 == 1){
                    if(op_p == 1){
                        char *omega = (char*)malloc(sizeof(char)*(l_input+1));
                        *omega = repeat(SA[a.top()], l_input, T, n, omega);
                        fprintf(f, "%s\n", omega);
                    }   
                    else if(op_p == 2){
                        fprintf(f, "%d, %d\n", SA[a.top()], l_input);
                    }      
                }
                a.pop();
                l.pop();
                l_input = l.top();
                for(int k = 0; k < 125; k++){
                    add[k] = 0;
                }
            }
        }
    }
    printf("\n");
    free(BWT);
    free(SA);
    free(LCP);
    return 0;
}