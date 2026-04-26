#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
#include<math.h>
#include<stdlib.h>


void ffit(int nf,int nb,int f[],int b[]){
    bool *flag=(bool*)calloc((nb+1),sizeof(bool));
    printf("\n==============FIRST FIT==============\n");
    printf("File No.\tFile Size\tBlock No.\tBlock Size\tFragment\n");
    printf("--------------------------------------------\n");
    for(int i=1;i<=nf;i++){
        for(int j=1;j<=nb;j++){
            if(b[j]-f[i]>=0 && !flag[j]){
                printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i,f[i],j,b[j],b[j]-f[i]);
                flag[j]=true;
                break;
            }
        }
    }
    printf("=================================================\n");
}

void bestfit(int nf,int nb,int f[],int b[]){
    bool *flag=(bool*)calloc((nb+1),sizeof(bool));
    printf("\n===============Best Fit===============\n");
    printf("File No.\tFile Size\tBlock No.\tBlock Size\tFragment\n");
    printf("------------------------------------------\n");
    for(int i=1;i<=nf;i++){
        int minidx = -1;
        for(int j=1;j<=nb;j++){
            if(b[j] >= f[i] && !flag[j]){
                if(minidx == -1 || b[j] < b[minidx]){
                    minidx = j;
                }
            }
        }
        flag[minidx]=true;
        if(minidx != -1){
            flag[minidx] = true;
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i, f[i], minidx, b[minidx], b[minidx]-f[i]);
        }else{
            printf("%d\t\t%d\t\tNot Allocated\n", i, f[i]);
        }
    }
    printf("=================================================\n");
}

void worstfit(int nf,int nb,int f[],int b[]){
    bool *flag=(bool*)calloc((nb+1),sizeof(bool));
    printf("\n==================Worst Fit==================\n");
    printf("File No.\tFile Size\tBlock No.\tBlock Size\tFragment\n");
    printf("------------------------------------------\n");
    for(int i=1;i<=nf;i++){
        int maxidx = -1;
        for(int j=1;j<=nb;j++){
            if(b[j] >= f[i] && !flag[j]){
                if(maxidx == -1 || b[j] > b[maxidx]){
                    maxidx = j;
                }
            }
        }
        if(maxidx != -1){
            flag[maxidx] = true;
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i, f[i], maxidx, b[maxidx], b[maxidx]-f[i]);
        }else{
            printf("%d\t\t%d\t\tNot Allocated\n", i, f[i]);
        }
            }
    printf("=================================================\n");
}

int main(){
    int nb,nf,b[100],f[100];
    printf("Enter the no of blocks: ");
    scanf("%d",&nb);
    printf("Enter the no of frames: ");
    scanf("%d",&nf);
    printf("Enter the size of blocks \n");
    for(int i=1;i<=nb;i++){
        printf("Block %d - ",i);
        scanf("%d",&b[i]);
    }
    printf("Enter the size of files \n");
    for(int i=1;i<=nf;i++){
        printf("File %d ",i);
        scanf("%d",&f[i]);
    }
    ffit(nf,nb,f,b);
    bestfit(nf,nb,f,b);
    worstfit(nf,nb,f,b);
}