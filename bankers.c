#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int n,m;
int main(){
    printf("Enter no of Process:");
    scanf("%d",&n);
    printf("Enter no of resources:");
    scanf("%d",&m);
    int alloc[n][m],max[n][m],need[n][m],avail[m],total[m];
    printf("\nEnter Allocation Matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&alloc[i][j]);
        }
    }
    printf("\nEnter Max Matrix:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&max[i][j]);
        }
    }
    printf("\nEnter Total Resources: ");
    for(int i = 0; i < m; i++) {
        scanf("%d", &total[i]);
    }
    for(int j = 0; j < m; j++) {
        int sum = 0;
        for(int i = 0; i < n; i++) {
            sum += alloc[i][j];
        }
        avail[j] = total[j] - sum;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }
    printf("\nPRocess\t\tAllocation\t\tMax\t\tNeed\n");
    for(int i=0;i<n;i++){
        printf("P%d",i);
        for(int j=0;j<m;j++){
            printf("%d ",alloc[i][j]);
        }
        printf("\t\t");
        for(int j=0;j<m;j++){
            printf("%d ",max[i][j]);
        }
        printf("\t\t");
        for(int j=0;j<m;j++){
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }
    printf("\nAvailable");
    for(int j=0;j<m;j++) printf("%d ", avail[j]);
    printf("\n");
    bool finish[n];
    for(int i=0;i<n;i++){
        finish[i]=false;
    }
    int safe[n],k=0;
    while(k<n){
        int f=0;
        for(int i=0;i<n;i++){
            if(!finish[i]){
                int ok=1;
                for(int j=0;j<m;j++){
                    if(need[i][j]>avail[j]){
                        ok=0;
                        break;
                    }
                }
                if(ok){
                    printf("P%d excutes -> Available becomes: ",i);
                    for(int j=0;j<m;j++){
                        avail[j]+=alloc[i][j];
                        printf("%d ",avail[j]);
                    }
                    safe[k++]=i;
                    finish[i]=true;
                    f=1;
                }
            }
        }
        if(!f){
            printf("DeadLock Possible!!!!!!!!!");
            return 0;
        }
    }
    printf("Safe Seq");
    for(int i=0;i<n;i++){
        printf("P%d ",safe[i]);
    }
    printf("\n");
    return 0;
}