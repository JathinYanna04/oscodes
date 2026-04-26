#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(){
    int pgsize,numpg,logadd;
    int pg_tab[100];
    printf("Enter page size: ");
    scanf("%d",&pgsize);
    printf("Enter number of pages: ");
    scanf("%d",&numpg);
    printf("Enter frame number for each page\n");
    for(int i=0;i<numpg;i++){
        printf("Page %d Frame: ",i);
        scanf("%d",&pg_tab[i]);
    }
    printf("Enter Logical Address\n");
    scanf("%d",&logadd);
    int pgno=logadd/pgsize;
    int offs=logadd%pgsize;
    if(pgno>=numpg){
        printf("Invalid Logical Address");
        return 0;
    }
    int frm_no=pg_tab[pgno];
    int phys_add=(frm_no*pgsize)+offs;
    printf("Page Number: %d\n",pgno);
    printf("Offset: %d\n",offs);
    printf("Frame Number: %d\n",frm_no);
    printf("Physical Address: %d\n",phys_add);
}