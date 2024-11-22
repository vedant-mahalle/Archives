#include <stdio.h>
#include <stdlib.h>

void displayPageTable(int pageTable[], int n) {
    printf("\nPage Table:\n");
    printf("Logical Page\tPhysical Frame\n");
    for (int i = 0; i < n; i++) {
        if (pageTable[i] != -1)
            printf("%d\t\t%d\n", i, pageTable[i]);
        else
            printf("%d\t\tNot Allocated\n", i);
    }
}

int main() {
    int numPages, numFrames;

    // Input number of pages and frames
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    int pageTable[numPages];
    int frameStatus[numFrames];

    // Initialize page table and frame status
    for (int i = 0; i < numPages; i++)
        pageTable[i] = -1; // Page not allocated initially
    for (int i = 0; i < numFrames; i++)
        frameStatus[i] = 0; // Frame is free initially

    // Assign pages to frames
    for (int i = 0; i < numPages; i++) {
        int frame;
        printf("Enter the frame number to map page %d (or -1 to skip): ", i);
        scanf("%d", &frame);

        if (frame >= 0 && frame < numFrames && frameStatus[frame] == 0) {
            pageTable[i] = frame;
            frameStatus[frame] = 1; // Mark frame as occupied
        } else if (frame >= 0 && frame < numFrames) {
            printf("Frame %d is already occupied!\n", frame);
        } else if (frame != -1) {
            printf("Invalid frame number!\n");
        }
    }

    // Display the final page table
    displayPageTable(pageTable, numPages);

    return 0;
}
