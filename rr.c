#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
#include<math.h>

int n;
struct pro{
    int at,bt,ct,tat,wt,rt;
    char pid[2];
    bool flag;
};

int main(){
    printf("Enter the no of process:");
    scanf("%d",&n);
    struct pro pro[n];
    for(int i=0;i<n;i++){
        printf("Enter PID,AT,BT for the process\n");
        scanf("%s %d %d",pro[i].pid,&pro[i].at,&pro[i].bt);
        pro[i].rt=pro[i].bt;
        pro[i].flag=false;
    }
    char gantt[500][3];
    int time[500];
    int g = 0;
    int tq;
    printf("Enter Time-Qunta");
    scanf("%d",&tq);
    int q[100],fr=0,rr=-1;
    int t=0,cmp=0;
    while(cmp<n){
        for(int i=0;i<n;i++){
            if(pro[i].at<=t && !pro[i].flag && pro[i].rt>0){
                q[rr++]=i;
                pro[i].flag=true;
            }
        }
        if(fr>rr){
            t++;
            continue;
        }
        int idx=q[fr++];
        if(g==0 || strcmp(gantt[g-1], pro[idx].pid) != 0){
            strcpy(gantt[g], pro[idx].pid);
            time[g] = t;
            g++;
        }
        int ex=(int)fmin(pro[idx].rt,tq);
        pro[idx].rt-=ex;
        t+=ex;
        time[g] = t;
        for(int i=0;i<n;i++){
            if(pro[i].at<=t && !pro[i].flag && pro[i].rt>0){
                q[rr++]=i;
                pro[i].flag=true;
            }
        }
        if(pro[idx].rt>0){
            q[++rr]=idx;
        }else{
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
    printf("\nGantt Chart\n");

    for(int i=0;i<g;i++) printf("---------");
    printf("-\n|");

    for(int i=0;i<g;i++)
        printf(" %-3s |", gantt[i]);

    printf("\n");

    for(int i=0;i<g;i++) printf("---------");
    printf("-\n");

    for(int i=0;i<=g;i++)
        printf("%-4d ", time[i]);

    printf("\n");

    return 0;

}