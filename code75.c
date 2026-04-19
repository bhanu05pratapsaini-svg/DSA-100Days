#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;    
    int value;  
    struct Node* next;
};

int hash(int key, int size) {
    return abs(key) % size;
}

void insert(struct Node* table[], int size, int key, int value) {
    int idx = hash(key, size);

    struct Node* temp = table[idx];
    while (temp != NULL) {
        if (temp->key == key)
            return; 
        temp = temp->next;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = table[idx];
    table[idx] = newNode;
}

int search(struct Node* table[], int size, int key) {
    int idx = hash(key, size);

    struct Node* temp = table[idx];
    while (temp != NULL) {
        if (temp->key == key)
            return temp->value;
        temp = temp->next;
    }

    return -1;
}

int longestZeroSumSubarray(int arr[], int n) {
    int size = 1000; // hash table size
    struct Node* table[1000] = {NULL};

    int sum = 0, maxLen = 0;

    for (int i = 0; i < n; i++) {
        sum += arr[i];

        if (sum == 0) {
            maxLen = i + 1;
        }

        int prevIndex = search(table, size, sum);

        if (prevIndex != -1) {
            int len = i - prevIndex;
            if (len > maxLen)
                maxLen = len;
        } else {
            insert(table, size, sum, i);
        }
    }

    return maxLen;
}

int main() {
    int arr[] = {15, -2, 2, -8, 1, 7, 10, 23};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", longestZeroSumSubarray(arr, n));

    return 0;
}