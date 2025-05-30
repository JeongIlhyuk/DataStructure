#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100

int ternary_search_peak(int arr[], int size) {
    int left = 0, right = size - 1;
    while (right - left > 2) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        if (arr[mid1] < arr[mid2]) left = mid1 + 1;
        else right = mid2 - 1;
    }

    int max_idx = left;
    for (int i = left + 1; i <= right; i++) {
        if (arr[i] > arr[max_idx]) max_idx = i;
    }
    return max_idx;
}

int main() {
    int arr[MAX_SIZE];
    // srand(time(NULL));
    srand(0);

    // Generate unimodal array with random peak position
    int peak = rand() % (MAX_SIZE - 2) + 1;
    for (int i = 0; i <= peak; i++) arr[i] = i;
    for (int i = peak + 1; i < MAX_SIZE; i++) arr[i] = arr[i - 1] - 1;

    int max_idx = ternary_search_peak(arr, MAX_SIZE);

    printf("Ternary Search (on unimodal array):\n");
    printf("Peak was generated at index %d with value %d\n", peak, arr[peak]);
    printf("Ternary search found peak at index %d with value %d\n", max_idx, arr[max_idx]);

    return 0;
}
