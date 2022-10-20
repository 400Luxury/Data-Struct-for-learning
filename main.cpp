#include"blockchain.h"
#include<bits/stdc++.h>
using namespace std;

Input input_L[3000];
Output output_L[33000];
Transaction T[33000];

int main(){
    char row[1000];
    int valid_num = 0, trans_num = 0;

    FILE *fi = fopen("./Data/inputs.csv","r");
    if (fi!=NULL)
    {
        fseek(fi,58L,SEEK_SET);
        int i=0;
        while (fgets(row, 1000, fi) != NULL) {
            MakeInput(input_L[i],row);
            i++;
        }    
    }
    fclose(fi);

    FILE *fo = fopen("./Data/outputs.csv","r");
    if (fo!=NULL)
    {
        fseek(fo,32L,SEEK_SET);
        int i=0;
        while (fgets(row, 1000, fo) != NULL) {
            MakeOutput(output_L[i],row);
            i++;
        }    
    }
    fclose(fo);

    FILE *ft = fopen("./Data/transactions.csv","r");
    if (ft!=NULL)
    {
        fseek(ft,50L,SEEK_SET);
        int start_i,start_o = 0;
        while (fgets(row, 1000, ft) != NULL) {
            MakeTrans(T[trans_num],row);
            FindInput(T[trans_num],start_i);
            FindOutput(T[trans_num],start_o);
            bool v = CheckValid(T[trans_num]);
            if(!v) printf("Transaction %s on Block %d is illegal!\n", T[trans_num].txid, T[trans_num].height);
            valid_num += v;
            trans_num++;
        }
    }
    fclose(ft);

    BlockChain L;
    InitChain(L);
    FILE *fb = fopen("./Data/blocks.csv","r");
    if (fb!=NULL)
    {
        fseek(fb,39L,SEEK_SET);
        int start=0;
        while (fgets(row, 1000, fb) != NULL) {
            Block* p;          
            MakeBlock(p,row);
            FindTrans(p,start);
            AppendChain(L,p);
        }     
    }
    fclose(fb);
    
    
    printf("The length of the blockchain is %d.\n", L.len);
    printf("The total number of blocks is %d.\n", L.len-1);
    printf("The total number of legal transactions is %d.\n", valid_num);
    printf("The total number of illegal transactions is %d.\n", trans_num - valid_num);
    printf("\nPlease enter the height of the block you want to searsh for: \n");
    int height;
    scanf("%d", &height);
    SearchBlock(L, height);
    printf("\n\nPlease enter the txID of the transaction you want to searsh for: \n");
    char id[128];
    scanf("%s", &id);
    SearchTrans(T, id);

    return 0;
}