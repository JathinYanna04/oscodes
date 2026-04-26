#include <stdio.h>

void equal(int n, int frames) {
    printf("\nEqual Allocation\n");
    int f = frames / n;
    for (int i = 0; i < n; i++) {
        printf("Process %d -> %d frames\n", i, f);
    }
}

void proportional(int n, int frames, int pages[]) {
    printf("\nProportional Allocation\n");
    int total = 0;
    for (int i = 0; i < n; i++)
        total += pages[i];
    for (int i = 0; i < n; i++) {
        int f = (pages[i] * frames) / total;
        printf("Process %d -> %d frames\n", i, f);
    }
}

void minimum(int n, int frames) {
    printf("\nMinimum Allocation\n");
    int min_frames = 2; 
    if (frames < n * min_frames) {
        printf("Not enough frames for minimum allocation\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        printf("Process %d -> %d frames\n", i, min_frames);
    }
}

int main() {
    int n, frames;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter number of pages for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        scanf("%d", &pages[i]);
    }
    printf("Enter total number of frames: ");
    scanf("%d", &frames);
    equal(n, frames);
    proportional(n, frames, pages);
    minimum(n, frames);
    return 0;
}