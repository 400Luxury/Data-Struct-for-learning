#include<bits/stdc++.h>
using namespace std;

#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2

#define MAX_SIZE 320

typedef int Status;

typedef struct{
    int height;
    char txid[128];    
    int prev_block;
    char prevTxID[128];
    int prevTxOutIndex;
    char scriptSig[256];
} Input;    //输入结构的定义

typedef struct{
    int height;
    char txid[128];
    int index;
    long long value;
    char script[256];
    bool is_used;
} Output;   //输出结构的定义

typedef struct{
    int height;
    char txid[128];
    int input_count;
    int output_count;
    Input *inputs[MAX_SIZE];
    Output *outputs[MAX_SIZE];
    bool is_coinbase;
    bool is_valid;
} Transaction;  //交易结构的定义

typedef struct block{
    int height;
    char hash[128];
    char prevHash[128];
    char merkleRoot[128];
    long long nonce;
    Transaction *transactions[MAX_SIZE];
    int trans_len;
    struct block *next;
    struct block *prev;
} Block, *pBlock;    //区块结构的定义

typedef struct{
    pBlock head,tail;
    int len;
} BlockChain;    //区块链表的定义

extern Input input_L[3000];
extern Output output_L[33000];
extern Transaction T[33000];

// ======================函数定义======================

void MakeInput(Input &in, char* row){
    char* token = strtok(row, ","); 
    int cnt = 0;
    while (token != NULL) {
        switch (cnt)
        {
        case 0:
            in.height = atoi(token);
            break;
        case 1:
            strcpy(in.txid,token);
            break;
        case 2:
            in.prev_block = atoi(token);
            break;
        case 3:
            strcpy(in.prevTxID,token);
            break;
        case 4:
            in.prevTxOutIndex = atoi(token);
            break;
        case 5:
            strcpy(in.scriptSig,token);
            break;
        default:
            break;
        }

        token = strtok(NULL, ",");
        cnt++;
    }
}

void MakeOutput(Output &out, char* row){
    char* token = strtok(row, ","); 
    int cnt = 0;
    while (token != NULL) {
        switch (cnt)
        {
        case 0:
            out.height = atoi(token);
            break;
        case 1:
            strcpy(out.txid,token);
            break;
        case 2:
            out.index = atoi(token);
            break;
        case 3:
            out.value = atoi(token);
            break;
        case 4:
            strcpy(out.script,token);
            break;
        default:
            break;
        }

        token = strtok(NULL, ",");
        cnt++;
    }

    out.is_used = 0;
}

void MakeTrans(Transaction &T, char* row){
    char* token = strtok(row, ","); 
    int cnt = 0;
    while (token != NULL) {
        switch (cnt)
        {
        case 0:
            T.height = atoi(token);
            break;
        case 1:
            strcpy(T.txid,token);
            break;
        case 2:
            T.is_coinbase = atoi(token);
            break;
        case 3:
            T.input_count = atoi(token);
            break;
        case 4:
            T.output_count = atoi(token);
            break;
        default:
            break;
        }

        token = strtok(NULL, ",");
        cnt++;
    }   
    T.is_valid = 1;
}

void FindInput(Transaction &T, int &start_i){
    int i=0;
    if (input_L[start_i].height > T.height) return;
    while (input_L[start_i].height < T.height) start_i++;
    for (int j = start_i; input_L[j].height == T.height; j++)
    {
        if (strcmp(T.txid,input_L[j].txid)==0)
        {
            T.inputs[i] = &input_L[j];
            i++;
        }
        
    }    
}

void FindOutput(Transaction &T, int &start_o){
    int i=0;
    if (output_L[start_o].height > T.height) return;
    while (output_L[start_o].height < T.height) start_o++;
    for (int j = start_o; output_L[j].height == T.height; j++)
    {
        if (strcmp(T.txid,output_L[j].txid)==0)
        {
            T.outputs[i] = &output_L[j];
            i++;
        }
        
    }
}

void DeleteOutput(Transaction &T){
    for (int i = 0; i < T.output_count; i++)
    {
        T.outputs[i]->is_used = 1;
    }
}

bool CheckValid(Transaction &T){
    if (T.is_coinbase) return 1;
    else
    {
        long long input_sum = 0;
        long long output_sum = 0;        
        for (int i = 0; i < T.input_count; i++)
        {
            // 每个input所使用的output能够找到。
            bool find_output = 0;
            for (int j = 0; strlen(output_L[j].txid)>1; j++)
            {
                if (strcmp(T.inputs[i]->prevTxID,output_L[j].txid)==0 && 
                            (T.inputs[i]->prevTxOutIndex == output_L[j].index))
                {
                    // 每一个output只能被使用一次。
                    if (output_L[j].is_used==0)
                    {                       
                        output_L[j].is_used = 1;
                        input_sum += output_L[j].value;
                        find_output = 1;
                        break;
                    }
                    else
                    {
                        T.is_valid = 0;
                        DeleteOutput(T);
                        return 0;
                    }
                                        
                }
            }
            
            if (find_output==0)
            {
                T.is_valid = 0;
                DeleteOutput(T);
                return 0;
            }   
        }

        for (int i = 0; i < T.output_count; i++)
        {
            output_sum += T.outputs[i]->value;
        }
        if (output_sum > input_sum)
        {
            T.is_valid = 0;
            DeleteOutput(T);
            return 0;
        }
        else return 1;            
    }
    
}

void MakeBlock(pBlock &p, char* row){
    char* token = strtok(row, ","); 
    int cnt = 0;
    p = (Block*)malloc(sizeof(Block));
    if (!p) exit(OVERFLOW);
    while (token != NULL) {
        switch (cnt)
        {
        case 0:
            p->height = atoi(token);
            break;
        case 1:
            strcpy(p->hash,token);
            break;
        case 2:
            strcpy(p->prevHash,token);
            break;
        case 3:
            strcpy(p->merkleRoot,token);
            break;
        case 4:
            p->nonce = atoi(token);
            break;
        default:
            break;
        }

        token = strtok(NULL, ",");
        cnt++;
    }
    p->next = NULL;
    p->prev = NULL;
    p->trans_len = 0;
}

void FindTrans(pBlock &p, int &start){
    int i=0;
    while (p->height == T[start].height)
    {
        if (T[start].is_valid) {
            p->transactions[i] = &T[start];
            p->trans_len ++;
        }
        i++;
        start++;
    }    
}

void InitChain(BlockChain &L){
    //构造一个空的区块链表L
    L.head = (Block*)malloc(sizeof(Block));
    if (!L.head) exit(OVERFLOW);
    L.tail = L.head;
    L.head->next = NULL;
    L.len = 0;
}

void AppendChain(BlockChain &L, pBlock s){
    //将指针s所指的区块链接在链表L的最后
    L.tail->next = s;
    s->prev = L.tail;
    while (L.tail->next)
    {
        L.tail = L.tail->next;
        L.len++;
    }
}

void SearchBlock(BlockChain L, int height){
    pBlock p;
    p = L.head->next;
    while (p && height!=p->height)
    {
        p = p->next;
    }
    if(!p) printf("Not exist!");
    else
    {
        printf("hash: %s\n", p->hash);
        printf("prevHash: %s\n", p->prev->hash);
        printf("merkleRoot: %s\n", p->merkleRoot);
        printf("nonce: %lld\n", p->nonce);
        printf("transactions: ");
        for (int i = 0; i < p->trans_len; i++)
        {
            printf("%s  ", p->transactions[i]->txid);
        }        
    } 
    return;
}

void InputPrint(Input* in){
    printf("pre_block: %d\n", in->prev_block);
    printf("prevTxID: %s\n", in->prevTxID);
    printf("prevTxOutIndex: %d\n", in->prevTxOutIndex);
    printf("scriptSig: %s\n", in->scriptSig);
    return;
}

void OutputPrint(Output* out){
    printf("index: %d\n", out->index);
    printf("value: %lld\n", out->value);
    printf("script: %s\n", out->script);
    return;
}

void SearchTrans(Transaction T[], char* id){
    bool is_exist=0;
    for (int i = 0; strlen(T[i].txid) > 1; i++)
    {
        if (strcmp(T[i].txid,id)==0) {
            if (!T[i].is_valid) printf("illegal!");
            else
            {
                printf("input_count: %d\n", T[i].input_count);
                printf("output_count: %d\n", T[i].output_count);
                printf("is_coinbase: %d\n\n", T[i].is_coinbase);
                for (int j = 0; T[i].inputs[j]; j++)
                {
                    printf("input[%d]:\n", j);
                    InputPrint(T[i].inputs[j]);
                }
                for (int j = 0; T[i].outputs[j]; j++)
                {
                    printf("output[%d]:\n", j);
                    OutputPrint(T[i].outputs[j]);
                }
            }
            is_exist = 1;
            break;
        }
    }
    if (!is_exist) printf("Not exist!");
    return;
}