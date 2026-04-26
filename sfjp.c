#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<limits.h>
struct pro{
    int at,bt,ct,wt,tat,rt;
    bool flag;
    char pid[2];
};
int n;

int main(){
    printf("Enter the no of process\n");
    scanf("%d",&n);
    struct pro pro[n];
    for(int i=0;i<n;i++){
        printf("Enter PID,AT,BT for the process\n");
        scanf("%s %d %d",pro[i].pid,&pro[i].at,&pro[i].bt);
        pro[i].rt=pro[i].bt;
    }
    int cmp=0,t=0;
    while(cmp<n){
        int idx=-1;
        int minrt=INT_MAX;
        for(int i=0;i<n;i++){
            if((pro[i].at<=t)&&(pro[i].rt>0)){
                if(pro[i].rt<minrt){
                    minrt=pro[i].rt;
                    idx=i;
                }
            }
        }
        if(idx==-1){
            t++;
        }else{
            pro[idx].rt--;
            t++;
            if(pro[idx].rt==0){
                pro[idx].ct=t;
                pro[idx].tat=pro[idx].ct-pro[idx].at;
                pro[idx].wt=pro[idx].tat-pro[idx].bt;
                cmp++;
            }
        }
    }
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",pro[i].pid,pro[i].at,pro[i].bt,pro[i].ct,pro[i].tat,pro[i].wt);
    }
}