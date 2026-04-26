#include <stdio.h>
#define M 100

int find(int f[], int n, int p){
    for(int i=0;i<n;i++) if(f[i]==p) return 1;
    return 0;
}

int fifo(int p[],int n,int f){
    if(!f) return n;
    int fr[M],i,j=0,c=0;
    for(i=0;i<f;i++) fr[i]=-1;
    for(i=0;i<n;i++)
        if(!find(fr,f,p[i]))
            fr[j++%f]=p[i],c++;
    return c;
}

int lru(int p[],int n,int f){
    if(!f) return n;
    int fr[M],t[M]={0},i,j,c=0,tm=0;
    for(i=0;i<f;i++) fr[i]=-1;
    for(i=0;i<n;i++){
        for(j=0;j<f;j++)
            if(fr[j]==p[i]){ t[j]=++tm; break; }
        if(j==f){
            int l=0;
            for(j=1;j<f;j++) if(t[j]<t[l]) l=j;
            fr[l]=p[i]; t[l]=++tm; c++;
        }
    }
    return c;
}

int opt(int p[],int n,int f){
    if(!f) return n;
    int fr[M],i,j,k,c=0,pos;
    for(i=0;i<f;i++) fr[i]=-1;
    for(i=0;i<n;i++){
        if(find(fr,f,p[i])) continue;
        pos=0; int far=-1;
        for(j=0;j<f;j++){
            for(k=i+1;k<n;k++) if(fr[j]==p[k]) break;
            if(k==n){ pos=j; break; }
            if(k>far) far=k,pos=j;
        }
        fr[pos]=p[i]; c++;
    }
    return c;
}

int main(){
    int p[M],n,f,i;
    scanf("%d",&n);
    for(i=0;i<n;i++) scanf("%d",&p[i]);
    scanf("%d",&f);

    printf("FIFO:%d\nLRU:%d\nOPT:%d",
        fifo(p,n,f), lru(p,n,f), opt(p,n,f));
}