#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_SIZE 100

int comparisons = 0;

int linear_search(const int arr[], const int n, const int key) {
    comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

int binary_search(const int arr[], int left, int right, const int key) {
    comparisons = 0;
    while (left <= right) {
        comparisons++;
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            return mid;
        }
        else if (arr[mid] < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

int jump_search(const int arr[], const int n, const int key) {
    comparisons = 0;
    int step = sqrt(n);
    int prev = 0;

    while(arr[step < n ? step : n - 1] < key){
        comparisons++;
        if(step > n - 1){
            return -1;
        }
        prev = step;
        step += sqrt(n);
    }

    while (arr[prev] < key) {
        comparisons++;
        prev++;
        if (prev == step || prev >= n) {
            return -1;
        }
    }
    comparisons++;
    return (arr[prev] == key) ? prev : -1;
}

int interpolation_search(const int arr[], const int n, const int key) {
    comparisons = 0;
    
    int low = 0, high = n - 1;

    while(low <= high && key >= arr[low] && key <= arr[high]){
        comparisons++;

        const int pos = low + (double)(high - low) / (arr[high] - arr[low]) * (key - arr[low]);

        if(arr[pos] == key) return pos;
        if(arr[pos] > key) high = pos - 1;
        else low = pos + 1;
    }

    return -1;
}

int exponential_search(const int arr[], const int n, const int key) {
    comparisons = 0;
    
    if(arr[0] == key){
        comparisons++;
        return 0;
    }

    int i = 1;
    while(i < n && arr[i] <= key){
        comparisons++;
        i *= 2;
    }

    const auto right = i > n - 1 ? n - 1 : i;
    const auto left = i / 2;
    
    // return binary_search(arr, low, high, key);
    int result = binary_search(arr, left, right, key);
    comparisons *= 2;
    return result;
}

void print_result(int result) {
    if (result == -1) printf("Not found\n");
    else printf("Found at index %d\n", result);
}

int main() {
    srand(0);
    int arr[MAX_SIZE];
    arr[0] = rand() % 5;
    for (int i = 1; i < MAX_SIZE; i++) {
        arr[i] = arr[i - 1] + 1 + rand() % 5;
    }

    int key = arr[rand() % MAX_SIZE];
    printf("Search key: %d\n\n", key);

    int result = linear_search(arr, MAX_SIZE, key);
    printf("Linear Search: ");
    print_result(result);
    printf("Comparisons: %d\n\n", comparisons);

    result = binary_search(arr, 0, MAX_SIZE - 1, key);
    printf("Binary Search: ");
    print_result(result);
    printf("Comparisons: %d\n\n", comparisons);

    result = jump_search(arr, MAX_SIZE, key);
    printf("Jump Search: ");
    print_result(result);
    printf("Comparisons: %d\n\n", comparisons);

    result = interpolation_search(arr, MAX_SIZE, key);
    printf("Interpolation Search: ");
    print_result(result);
    printf("Comparisons: %d\n\n", comparisons);

    result = exponential_search(arr, MAX_SIZE, key);
    printf("Exponential Search: ");
    print_result(result);
    printf("Comparisons: %d\n\n", comparisons);


    return 0;
}
