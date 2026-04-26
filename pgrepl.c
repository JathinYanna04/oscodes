#include <stdio.h>
#define M 100

int hit(int f[], int fsize, int p){
    for(int i=0;i<fsize;i++)
        if(f[i]==p) return 1;
    return 0;
}

/* ---------- FIFO ---------- */
int fifo(int p[],int n,int fsize,int *hitc){
    int f[M],i,j=0,fault=0;
    *hitc = 0;
    for(i=0;i<fsize;i++) f[i]=-1;
    for(i=0;i<n;i++){
        if(hit(f,fsize,p[i])){
            (*hitc)++;
        }else{
            f[j%fsize]=p[i];
            j++;
            fault++;
        }
    }
    return fault;
}

/* ---------- LRU ---------- */
int lru(int p[],int n,int fsize,int *hitc){
    int f[M],t[M]={0},i,j,fault=0,time=0;
    *hitc = 0;
    for(i=0;i<fsize;i++) f[i]=-1;
    for(i=0;i<n;i++){
        for(j=0;j<fsize;j++){
            if(f[j]==p[i]){
                t[j]=++time;
                (*hitc)++;
                break;
            }
        }
        if(j==fsize){
            int l=0;
            for(j=1;j<fsize;j++)
                if(t[j]<t[l]) l=j;

            f[l]=p[i];
            t[l]=++time;
            fault++;
        }
    }
    return fault;
}

/* ---------- OPT ---------- */
int opt(int p[],int n,int fsize,int* hitc){
    int f[M],fault=0,pos;
    *hitc = 0;
    for(int i=0;i<fsize;i++){
        f[i]=-1;
    }
    for(int i=0;i<n;i++){
        if(hit(f,fsize,p[i])){
            (*hitc)++;
            continue;
        }
        pos=0;
        int far=-1;
        for(int j=0;j<fsize;j++){
            int k;
            for(k=i+1;k<n;k++){
                if(f[j]==p[k]){
                    break;
                }
            }
            if(k==n){
                pos=j;
                break;
            }
            if(k>far){
                far=k;
                pos=j;
            }
        }
        f[pos]=p[i];
        fault++;
    }
    return fault;
}

/* ---------- MAIN ---------- */
int main(){
    int p[M],n,f;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&p[i]);
    scanf("%d",&f);
    int fh,fl,fo;
    int ff,lf,of;
    ff = fifo(p,n,f,&fh);
    lf = lru(p,n,f,&fl);
    of = opt(p,n,f,&fo);
    printf("\n--- RESULTS ---\n");
    printf("\nFIFO -> Faults: %d  Hits: %d  Fault Ratio: %.2f  Hit Ratio: %.2f",
        ff, fh,
        (float)ff/n,
        (float)fh/n);
    printf("\nLRU  -> Faults: %d  Hits: %d  Fault Ratio: %.2f  Hit Ratio: %.2f",
        lf, fl,
        (float)lf/n,
        (float)fl/n);
    printf("\nOPT  -> Faults: %d  Hits: %d  Fault Ratio: %.2f  Hit Ratio: %.2f\n",of, fo,
        (float)of/n,
        (float)fo/n);
    return 0;
}