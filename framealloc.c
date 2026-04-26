#include <stdio.h>

int main() {
    int numProcesses, totalFrames, i;
    long long processSize[50], totalSize = 0;

    // Read number of processes and total frames
    scanf("%d %d", &numProcesses, &totalFrames);

    // Basic validation (avoid invalid cases)
    if (numProcesses <= 0 || totalFrames < 0) return 0;

    // Read process sizes and calculate total size
    for (i = 0; i < numProcesses; i++) {
        scanf("%lld", &processSize[i]);
        totalSize += processSize[i];
    }

    // -------- Minimum Allocation --------
    // Each process gets at least 1 frame
    printf("\nMinimum:\n");
    if (totalFrames < numProcesses)
        printf("Not possible\n");  // Not enough frames
    else
        for (i = 0; i < numProcesses; i++)
            printf("P%d=1\n", i+1);

    // -------- Equal Allocation --------
    printf("\nEqual:\n");

    if (totalFrames == 0) {
        // No frames available → all get 0
        for (i = 0; i < numProcesses; i++)
            printf("P%d=0\n", i+1);
    } else {
        // Divide frames equally
        int base = totalFrames / numProcesses;
        int rem = totalFrames % numProcesses;

        // Distribute base frames + extra remainder frames
        for (i = 0; i < numProcesses; i++)
            printf("P%d=%d\n", i+1, base + (i < rem));
    }

    // -------- Proportional Allocation --------
    printf("\nProportional:\n");

    if (totalFrames == 0 || totalSize == 0) {
        // No frames or no sizes → all get 0
        for (i = 0; i < numProcesses; i++)
            printf("P%d=0\n", i+1);
    } else {
        int alloc[50] = {0}, used = 0;
        long long remFrac[50];

        // Step 1: Base proportional allocation
        for (i = 0; i < numProcesses; i++) {
            // Allocate based on size ratio
            alloc[i] = (processSize[i] * totalFrames) / totalSize;

            // Store remainder for fairness
            remFrac[i] = (processSize[i] * totalFrames) % totalSize;

            used += alloc[i]; // track used frames
        }

        // Step 2: Distribute leftover frames
        int extra = totalFrames - used;

        // Give extra frames to highest remainder processes
        while (extra--) {
            int max = 0;
            for (i = 1; i < numProcesses; i++)
                if (remFrac[i] > remFrac[max]) max = i;

            alloc[max]++;
            remFrac[max] = -1; // avoid re-selection
        }

        // Print final allocation
        for (i = 0; i < numProcesses; i++)
            printf("P%d=%d\n", i+1, alloc[i]);
    }

    return 0;
}