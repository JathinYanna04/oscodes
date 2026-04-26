#include<stdio.h>
#include<limits.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>

int n;

struct pro{
    int at,bt,ct,tat,wt,rt,pr;
    char pid[5];
};

int main(){
    printf("Enter the no of process");
    scanf("%d",&n);

    struct pro pro[n];

    for(int i=0;i<n;i++){
        printf("Enter PID,AT,BT,Priority\n");
        scanf("%s %d %d %d",pro[i].pid,&pro[i].at,&pro[i].bt,&pro[i].pr);
        pro[i].rt=pro[i].bt;
    }

    // -------- Gantt storage --------
    char gantt[200][5];
    int timeLog[200];
    int g=0;

    int cmp=0,t=0;
    timeLog[0]=0;

    while(cmp<n){
        int idx=-1;
        int mpr=INT_MAX;

        // pick highest priority (lowest number)
        for(int i=0;i<n;i++){
            if(pro[i].at<=t && pro[i].rt>0){
                if(pro[i].pr < mpr){
                    mpr = pro[i].pr;
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
    printf("PID\tPR\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\n",
        pro[i].pid,pro[i].pr,pro[i].at,pro[i].bt,
        pro[i].ct,pro[i].tat,pro[i].wt);
    }

    // -------- BEAUTIFUL GANTT --------
    printf("\nGantt Chart:\n\n");

    // top border
    for(int i=0;i<g;i++) printf("-----------");
    printf("-\n|");

    // boxes
    for(int i=0;i<g;i++)
        printf("  %-5s  |", gantt[i]);

    printf("\n");

    // bottom border
    for(int i=0;i<g;i++) printf("-----------");
    printf("-\n");

    // timeline
    printf("%-3d", timeLog[0]);
    for(int i=1;i<=g;i++)
        printf("        %-3d", timeLog[i]);

    printf("\n");

    return 0;
}