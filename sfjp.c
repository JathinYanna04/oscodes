#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<limits.h>
#include<string.h>

struct pro{
    int at,bt,ct,wt,tat,rt;
    bool flag;
    char pid[5];
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

    // -------- Gantt storage --------
    char gantt[200][5];
    int timeLog[200];
    int g = 0;

    int cmp=0,t=0;
    timeLog[0] = 0;

    while(cmp<n){
        int idx=-1;
        int minrt=INT_MAX;

        // find shortest remaining time
        for(int i=0;i<n;i++){
            if(pro[i].at<=t && pro[i].rt>0){
                if(pro[i].rt < minrt){
                    minrt = pro[i].rt;
                    idx = i;
                }
            }
        }

        if(idx==-1){
            t++;   // CPU idle
        }else{

            // -------- Gantt logging --------
            if(g==0 || strcmp(gantt[g-1], pro[idx].pid)!=0){
                strcpy(gantt[g], pro[idx].pid);
                timeLog[g+1] = t+1;
                g++;
            }else{
                timeLog[g] = t+1;
            }

            // execute 1 unit
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

    // -------- Table --------
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
        pro[i].pid,pro[i].at,pro[i].bt,
        pro[i].ct,pro[i].tat,pro[i].wt);
    }

    // -------- Gantt Chart --------
    printf("\nGantt Chart:\n\n");

    // top line
    for(int i=0;i<g;i++) printf("--------");
    printf("-\n|");

    // process boxes
    for(int i=0;i<g;i++)
        printf("  %-2s  |", gantt[i]);

    printf("\n");

    // bottom line
    for(int i=0;i<g;i++) printf("--------");
    printf("-\n");

    // timeline
    printf("%d", timeLog[0]);
    for(int i=1;i<=g;i++)
        printf("      %d", timeLog[i]);

    printf("\n");

    return 0;
}