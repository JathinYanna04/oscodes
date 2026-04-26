#include<stdio.h>
#include<math.h>
#include<limits.h>
#include<stdbool.h>
#include<string.h>

int n;

struct pro{
    int at,bt,pr,ct,tat,wt;
    char pid[5];
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

    // Gantt storage
    char gantt[100][5];
    int timeLog[100];
    int g=0;

    int cmp=0,t=0;
    timeLog[0]=0;

    while(cmp<n){
        int idx=-1;
        int mpr=INT_MAX;

        // pick highest priority (lowest number)
        for(int i=0;i<n;i++){
            if(pro[i].at<=t && !pro[i].flag){
                if(pro[i].pr < mpr){
                    mpr = pro[i].pr;
                    idx = i;
                }
            }
        }

        if(idx==-1){
            t++;   // CPU idle
        }else{
            // Gantt logging
            strcpy(gantt[g], pro[idx].pid);
            timeLog[g+1] = t + pro[idx].bt;
            g++;

            t += pro[idx].bt;

            pro[idx].ct=t;
            pro[idx].tat=pro[idx].ct-pro[idx].at;
            pro[idx].wt=pro[idx].tat-pro[idx].bt;
            pro[idx].flag=true;
            cmp++;
        }
    }

    // Table
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
        pro[i].pid,pro[i].at,pro[i].bt,pro[i].pr,
        pro[i].ct,pro[i].tat,pro[i].wt);
    }

    // -------- BEAUTIFUL GANTT --------
    printf("\nGantt Chart:\n\n");

    // top border
    for(int i=0;i<g;i++) printf("---------");
    printf("-\n|");

    // boxes
    for(int i=0;i<g;i++)
        printf("  %-3s |", gantt[i]);

    printf("\n");

    // bottom border
    for(int i=0;i<g;i++) printf("---------");
    printf("-\n");

    // timeline
    printf("%-3d", timeLog[0]);
    for(int i=1;i<=g;i++)
        printf("      %-3d", timeLog[i]);

    printf("\n");

    return 0;
}