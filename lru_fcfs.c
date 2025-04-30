#include <stdio.h>
#include <stdlib.h>

// FIFO Page Replacement Algorithm
void fifo(int pages[], int n, int frames) {
    // Array to hold frame values
    int frame_array[frames];
    
    // Initialize all frames to -1 indicating empty
    for (int i = 0; i < frames; i++) {
        frame_array[i] = -1;
    }
    
    // Variables for tracking
    int page_faults = 0;
    int next_frame = 0;  // Index to track the next frame to be replaced
    
    printf("\n----- FIFO Page Replacement Algorithm -----\n");
    printf("Reference\tFrames\t\t\tPage Fault\n");
    
    // Process each page in the reference string
    for (int i = 0; i < n; i++) {
        int current_page = pages[i];
        int page_found = 0;
        
        // Check if page is already in a frame
        for (int j = 0; j < frames; j++) {
            if (frame_array[j] == current_page) {
                page_found = 1;
                break;
            }
        }
        
        // If page not found, replace according to FIFO
        if (!page_found) {
            frame_array[next_frame] = current_page;
            next_frame = (next_frame + 1) % frames; // Circular increment
            page_faults++;
            
            printf("%d\t\t", current_page);
            for (int j = 0; j < frames; j++) {
                if (frame_array[j] == -1)
                    printf("- ");
                else
                    printf("%d ", frame_array[j]);
            }
            printf("\t\tYes\n");
        } else {
            printf("%d\t\t", current_page);
            for (int j = 0; j < frames; j++) {
                if (frame_array[j] == -1)
                    printf("- ");
                else
                    printf("%d ", frame_array[j]);
            }
            printf("\t\tNo\n");
        }
    }
    
    printf("\nTotal Page Faults (FIFO): %d\n", page_faults);
}

// LRU Page Replacement Algorithm
void lru(int pages[], int n, int frames) {
    // Array to hold frame values
    int frame_array[frames];
    
    // Array to track when each page was last used
    int time_of_use[frames];
    
    // Initialize all frames and time tracking
    for (int i = 0; i < frames; i++) {
        frame_array[i] = -1;
        time_of_use[i] = -1;
    }
    
    int page_faults = 0;
    
    printf("\n----- LRU Page Replacement Algorithm -----\n");
    printf("Reference\tFrames\t\t\tPage Fault\n");
    
    // Process each page in the reference string
    for (int i = 0; i < n; i++) {
        int current_page = pages[i];
        int page_found = 0;
        
        // Check if page is already in a frame
        for (int j = 0; j < frames; j++) {
            if (frame_array[j] == current_page) {
                page_found = 1;
                time_of_use[j] = i;  // Update time of last use
                break;
            }
        }
        
        // If page not found, replace according to LRU
        if (!page_found) {
            // Find empty frame or frame with least recently used page
            int replace_index = 0;
            
            // Look for an empty frame first
            int empty_found = 0;
            for (int j = 0; j < frames; j++) {
                if (frame_array[j] == -1) {
                    replace_index = j;
                    empty_found = 1;
                    break;
                }
            }
            
            // If no empty frame, find LRU frame
            if (!empty_found) {
                for (int j = 1; j < frames; j++) {
                    if (time_of_use[j] < time_of_use[replace_index]) {
                        replace_index = j;
                    }
                }
            }
            
            // Replace the page
            frame_array[replace_index] = current_page;
            time_of_use[replace_index] = i;
            page_faults++;
            
            printf("%d\t\t", current_page);
            for (int j = 0; j < frames; j++) {
                if (frame_array[j] == -1)
                    printf("- ");
                else
                    printf("%d ", frame_array[j]);
            }
            printf("\t\tYes\n");
        } else {
            printf("%d\t\t", current_page);
            for (int j = 0; j < frames; j++) {
                if (frame_array[j] == -1)
                    printf("- ");
                else
                    printf("%d ", frame_array[j]);
            }
            printf("\t\tNo\n");
        }
    }
    
    printf("\nTotal Page Faults (LRU): %d\n", page_faults);
}

int main() {
    int n, frames;
    
    // Get number of pages
    printf("Enter the number of pages (minimum 10): ");
    scanf("%d", &n);
    
    if (n < 10) {
        printf("Error: Number of pages should be at least 10.\n");
        return 1;
    }
    
    int pages[n];
    
    // Get the reference string
    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    
    // Get number of frames
    printf("Enter the number of frames (minimum 3): ");
    scanf("%d", &frames);
    
    if (frames < 3) {
        printf("Error: Number of frames should be at least 3.\n");
        return 1;
    }
    
    // Run both algorithms
    fifo(pages, n, frames);
    lru(pages, n, frames);
    
    return 0;
}
