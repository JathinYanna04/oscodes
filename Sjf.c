#include<stdio.h>
#include<math.h>
#include<stdbool.h>

int n;

struct pro{
    int at,bt,ct,wt,tat,rt;
    char pid[2];
    bool flag;
};

int main(){
    printf("Enter no of process:\n");
    scanf("%d",&n);

    struct pro pro[n];

    for(int i=0;i<n;i++){
        printf("Enter PID,AT,BT for process\n");
        scanf("%s %d %d",pro[i].pid,&pro[i].at,&pro[i].bt);
        pro[i].flag=false;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if (pro[j].at > pro[j+1].at){
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
        int idx=i;
        for(int j=i;j<n;j++){
            if((pro[i-1].ct>=pro[j].at)&&(pro[j].bt<pro[idx].bt)){
                idx=j;
            }
        }
        struct pro temp2=pro[i];
        pro[i]=pro[idx];
        pro[idx]=temp2;
    }

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

    // -------- BEAUTIFUL GANTT WITH IDLE --------
    printf("\nGantt Chart:\n\n");

    int currentTime = pro[0].at;

    // top line
    for(int i=0;i<n;i++) printf("--------");
    printf("-\n|");

    // boxes
    for(int i=0;i<n;i++){
        if(currentTime < pro[i].at){
            printf(" IDLE |");
            currentTime = pro[i].at;
        }
        printf("  %-2s  |", pro[i].pid);
        currentTime = pro[i].ct;
    }

    printf("\n");

    // bottom line
    for(int i=0;i<n;i++) printf("--------");
    printf("-\n");

    // timeline
    currentTime = pro[0].at;
    printf("%-2d", currentTime);

    for(int i=0;i<n;i++){
        if(currentTime < pro[i].at){
            printf("      %-2d", pro[i].at);
            currentTime = pro[i].at;
        }
        printf("      %-2d", pro[i].ct);
        currentTime = pro[i].ct;
    }

    printf("\n");

    return 0;
}