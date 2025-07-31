#include <stdio.h>
#include <stdlib.h>
#define SIZE 5


int queue[SIZE];
int front = -1, rear = -1;

// Queue Operations
void enqueue(int item) {
    if (rear == SIZE - 1)
        printf("Queue Overflow!\n");
    else {
        if (front == -1)
            front = 0;
        rear++;
        queue[rear] = item;
        printf("%d inserted.\n", item);
    }
}

void dequeue() {
    if (front == -1 || front > rear)
        printf("Queue Underflow!\n");
    else {
        printf("Deleted: %d\n", queue[front]);
        front++;
    }
}

void displayQueue() {
    if (front == -1 || front > rear)
        printf("Queue is empty.\n");
    else {
        printf("Queue: ");
        for (int i = front; i <= rear; i++)
            printf("%d ", queue[i]);
        printf("\n");
    }
}
// Main Menu
int main() {
int choice,value;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1. Enqueue\n2. Dequeue\n3. Display Queue\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to Enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                displayQueue();
                break;
            case 0:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
    }
