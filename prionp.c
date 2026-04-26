#include<stdio.h>
#include<math.h>
#include<limits.h>
#include<stdbool.h>

int n;
struct pro{
    int at,bt,pr,ct,tat,wt,rt;
    char pid[2];
    bool flag;
};

int main(){
    printf("Enter the no of process\n");
    scanf("%d",&n);
    struct pro pro[n];
    for(int i=0;i<n;i++){
        printf("Enter the PID-AT-BT-PRIORITY\n");
        scanf("%s %d %d %d",pro[i].pid,&pro[i].at,&pro[i].bt,&pro[i].pr);
        pro[i].flag=false;
    }
    int cmp=0,t=0;
    while(cmp<n){
        int idx=-1;
        int mpr=INT_MAX;
        for(int i=0;i<n;i++){
            if((pro[i].at<=t)&& !(pro[i].flag)){
                if(pro[i].pr<mpr){
                    mpr=pro[i].pr;
                    idx=i;
                }
            }
        }
        if(idx==-1){
            t++;
        }else{
           t+=pro[idx].bt;
           pro[idx].ct=t;
           pro[idx].tat=pro[idx].ct-pro[idx].at;
           pro[idx].wt=pro[idx].tat-pro[idx].bt;
           pro[idx].flag=true;
           cmp++;
        }
    }
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",pro[i].pid,pro[i].at,pro[i].bt,pro[i].ct,pro[i].tat,pro[i].wt);
    }
}
