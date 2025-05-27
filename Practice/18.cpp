#include <stdio.h>
#include <algorithm>

using namespace std;

#define MAX_SIZE 100
#define ROOT 1

int heap[MAX_SIZE];
int heapSize = 0;

int parent(int i) { return i / 2; }
int left(int i) { return 2 * i; }
int right(int i) { return 2 * i + 1; }

void insert(int value) {
    heap[++heapSize] = value;
    int i = heapSize;
    while(i > 1 && heap[i] > heap[parent(i)]){
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

void heapify(int i) { // bubble down approach
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l <= heapSize && heap[l] > heap[largest]) largest = l;
    if (r <= heapSize && heap[r] > heap[largest]) largest = r;

    if(largest == i) return;

    swap(heap[largest], heap[i]);
    heapify(largest);
}

int deleteMax() {
    if(heapSize == 0) return - 1;

    int ret = heap[ROOT];
    heap[ROOT] = heap[heapSize--];

    heapify(ROOT);

    return ret;
}

void printHeapByLevel() {
    int level = 0;
    int count = 0;
    int nextLevelCount = 1;

    printf("Heap by Level:\n");
    for (int i = 1; i <= heapSize; i++) {
        if (count == 0) {
            printf("Level %d: ", level);
        }

        printf("%d ", heap[i]);
        count++;

        if (count == nextLevelCount) {
            printf("\n");
            level++;
            count = 0;
            nextLevelCount *= 2;
        }
    }

    if (count != 0) {
        printf("\n");
    }
}

void buildHeap() { // print intermediate results
    printf("Start building heap (heapify from bottom-up):\n");
    for(int i = heapSize / 2; i >= 1; i--){
        printf("\nHeapify at index %d (value = %d):\n", i, heap[i]);
        heapify(i);
        printHeapByLevel();
    }
    printf("\n Finished building heap.\n");
}

void printHeap() { // print in array form
    printf("Heap: ");
    for (int i = 1; i <= heapSize; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int main() {
    insert(10);
    insert(30);
    insert(20);
    insert(5);
    insert(40);

    printHeapByLevel();

    printf("Deleted max: %d\n", deleteMax());
    printf("Deleted max: %d\n", deleteMax());
    printf("Deleted max: %d\n", deleteMax());
    printf("Deleted max: %d\n", deleteMax());
    printHeapByLevel();

    heap[1] = 15;
    heap[2] = 8;
    heap[3] = 10;
    heap[4] = 2;
    heap[5] = 25;
    heapSize = 5;

    printf("\nBefore buildHeap:\n");
    printHeapByLevel();

    buildHeap();

    printf("After buildHeap:\n");
    printHeapByLevel();

    return 0;
}
