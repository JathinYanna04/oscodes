#include<stdio.h>
#include<math.h>

struct pro{
    int at,bt,ct,wt,tat,rt;
    char pid[2];
};

int n;

int main(){
    printf("Enter the no of process:");
    scanf("%d",&n);

    struct pro pro[n];

    for(int i=0;i<n;i++){
        printf("Enetr the PID,Arrv Time,Brust Time for Process:\n");
        scanf("%s %d %d",pro[i].pid,&pro[i].at,&pro[i].bt);
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(pro[j].at>pro[j+1].at){
                struct pro temp=pro[j];
                pro[j]=pro[j+1];
                pro[j+1]=temp;
            }
        }
    }

    pro[0].ct=pro[0].at+pro[0].bt;
    pro[0].tat=pro[0].ct-pro[0].at;
    pro[0].wt=pro[0].tat-pro[0].bt;

    for(int i=1;i<n;i++){
        pro[i].ct=(int)fmax(pro[i-1].ct,pro[i].at)+pro[i].bt;
        pro[i].tat=pro[i].ct-pro[i].at;
        pro[i].wt=pro[i].tat-pro[i].bt;
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%s\t%d\t%d\t%d\t%d\t%d\n",
        pro[i].pid,pro[i].at,pro[i].bt,
        pro[i].ct,pro[i].tat,pro[i].wt);
    }

    // -------- SIMPLE GANTT (ADDED ONLY THIS) --------
    printf("\nGantt Chart:\n\n|");

    for(int i=0;i<n;i++)
        printf(" %s |", pro[i].pid);

    printf("\n");

    printf("%d", pro[0].at);

    for(int i=0;i<n;i++)
        printf("     %d", pro[i].ct);

    printf("\n");
}