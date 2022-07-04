#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>
#include <zlib.h>
#include "external/kseq/kseq.h"

KSEQ_INIT(gzFile, gzread);

using namespace std;

/////// sequence struct ///////
typedef struct sequence{
	int n;
	char *T;
	struct sequence *prox;
} s_seq;

/////// open files SA and LCP ///////
int open(char *arq, int n, int *ARQ){
    FILE* f = fopen(arq, "rb"); // rb to binary files
    int ret = fread(ARQ, sizeof(int), n, f);
    if(ret != n){
        printf("Error reading file %s\n", arq);
    }
    fclose(f);
    return *ARQ;
}

/////// save repeats in .type1 and .type2 files ///////
char repeat(int j, int l, char *T, int n, char *omega){
    int y = 0;
    for(int i = j; i < j+l; i++){
        omega[y] = T[i];
        y++;
    }
    omega[y] = '\0';
    return *omega;
}

///////  ///////
char print(int k, char *file_type, char *arg, char *t){
    strcpy(file_type, arg);
    strcat(file_type, t);
    return *file_type;
}

/////// read fasta and fastq files ///////
long int read_fast(s_seq *seq_sq, char *arg){
    gzFile fp;
    kseq_t *seq;
    s_seq *sq = (s_seq*)malloc(sizeof(s_seq));

    fp = gzopen(arg, "r");
    seq = kseq_init(fp);
    int n;
    long int sum = 0;
    while ((n = kseq_read(seq)) >= 0){
        sum += n;
        sq->T = seq->seq.s;
        sq->n = sum;
    }
    fp = gzopen(arg, "r");
    seq = kseq_init(fp);
    return sum; // total concatenation size
}

char seq_fast(char *T, long int n, s_seq *seq_sq){
    s_seq *aux = (s_seq*)malloc(sizeof(s_seq));
    aux = seq_sq;printf("entrou\n\n");
    while(aux->prox == NULL){
        printf("-%s\n", aux->T);
        strcat(T, aux->T);
    }
    return *T;
}

int add[125];
int main(int argc, char *argv[]){

    /////// repeat size ///////
    int l_input = atoi(argv[5]);

    /////// input options ///////
    int op = atoi(argv[6]);
    int op_p = atoi(argv[7]);
    int op_file = atoi(argv[8]);
    
    long int n;

    s_seq *seq_sq = NULL;
    char *T;

    /////// read txt files ///////
    if(op_file == 0){
        FILE* f = fopen(argv[1], "r"); 
        fseek(f, 0, SEEK_END);
        n = ftell(f); 
        rewind(f);
        T = (char*)malloc(sizeof(char)*(n+1));
        int ret = fread(T, sizeof(char), n, f);
        T[n]='\0';
        if(ret != n){
            printf("Error reading file %s\n", argv[1]);
        }
        fclose(f);  
    }
    /////// read fasta and fastq files ///////
    else if(op_file == 1){
        n = read_fast(seq_sq, argv[1]);
        T = (char*)malloc(sizeof(char)*(n+1));
        //*T = seq_fast(T, n, seq_sq);
    }

    FILE *fi = fopen(argv[2], "rb"); // rb to binary files
    char *BWT = (char*)malloc(sizeof(char)*(n+1));
    int retn = fread(BWT, sizeof(char), n, fi);
    if(retn != n){ // não pega o arquivo inteirooo
        printf("Error reading file %s\n", argv[2]);
    }
    fclose(fi);
    printf("%s\n", BWT);

    int *SA = (int*)malloc(sizeof(int)*(n+1));
    open(argv[3], n, SA);
    int *LCP = (int*)malloc(sizeof(int)*(n+1));
    open(argv[4], n, LCP);
    LCP[n] = 0;
    for(int i = 0; i < n; i++){
        printf("%d ", LCP[i]);
    }
    printf("\n");
    for(int i = 0; i < n; i++){
        printf("%d ", SA[i]);
    }
    printf("\n");
    /////// data stack /////// 
    stack <int> a;
    stack <int> l;
    stack <int> h;
    a.push(0);
    l.push(l_input);
    h.push(0);

    int k = strlen(argv[1]);

    /////// repeat file type ///////
    char *file_type = (char*)malloc(sizeof(char)*(k+7));

    /////// if repeat ir type 1 or both ///////
    if(op == 1 || op == 0){
        char *type1 = (char*)".type1";
        *file_type = print(k, file_type, argv[1], type1);
        fi = fopen(file_type, "wb");
        
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
                            int q = (i - 1) - a.top() + 1; //q = b - a + 1
                            char *omega = (char*)malloc(sizeof(char)*(l_input+1));
                            *omega = repeat(SA[h.top()], l_input, T, n, omega);
                            fprintf(fi, "%d %s\n", q, omega);
                        }   
                        else if(op_p == 2){
                            fprintf(fi, "%d, %d\n", SA[h.top()], l_input);
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
    
    /////// if repeat ir type 2 or both ///////
    if(op == 2 || op == 0){

        char *type2 = (char*)".type2";
        *file_type = print(k, file_type, argv[1], type2);
        fi = fopen(file_type, "wb");

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
                        int q = (i - 1) - a.top() + 1; //q = b - a + 1
                        char *omega = (char*)malloc(sizeof(char)*(l_input+1));
                        *omega = repeat(SA[a.top()], l_input, T, n, omega);
                        fprintf(fi, "%d %s\n", q, omega);
                    }   
                    else if(op_p == 2){
                        fprintf(fi, "%d, %d\n", SA[a.top()], l_input);
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