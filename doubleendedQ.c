#include <stdio.h>

int deque[100];   
int MAX;          
int front = -1, rear = -1;

void insertFront(int value) {
    if ((front == 0 && rear == MAX - 1) || (front == rear + 1)) {
        printf("Deque is Full\n");
        return;
    }
    if (front == -1) {
        front = rear = 0;
    } else if (front == 0) {
        front = MAX - 1;
    } else {
        front--;
    }
    deque[front] = value;
    printf("%d inserted at front\n", value);
}

void insertRear(int value) {
    if ((front == 0 && rear == MAX - 1) || (front == rear + 1)) {
        printf("Deque is Full\n");
        return;
    }
    if (front == -1) {
        front = rear = 0;
    } else if (rear == MAX - 1) {
        rear = 0;
    } else {
        rear++;
    }
    deque[rear] = value;
    printf("%d inserted at rear\n", value);
}

void deleteFront() {
    if (front == -1) {
        printf("Deque is Empty\n");
        return;
    }
    printf("%d deleted from front\n", deque[front]);
    if (front == rear) {
        front = rear = -1;
    } else if (front == MAX - 1) {
        front = 0;
    } else {
        front++;
    }
}

void deleteRear() {
    if (front == -1) {
        printf("Deque is Empty\n");
        return;
    }
    printf("%d deleted from rear\n", deque[rear]);
    if (front == rear) {
        front = rear = -1;
    } else if (rear == 0) {
        rear = MAX - 1;
    } else {
        rear--;
    }
}

void display() {
    if (front == -1) {
        printf("Deque is Empty\n");
        return;
    }
    int i = front;
    printf("Deque: ");
    while (1) {
        printf("%d ", deque[i]);
        if (i == rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    int choice, value;

    printf("Enter the size of the DEQUEUE (MAX up to 100): ");
    scanf("%d", &MAX);

    if (MAX <= 0 || MAX > 100) {
        printf("Invalid size!\n");
        return 1;
    }

    while (1) {
        printf("\n1. Insert Front\n2. Insert Rear\n3. Delete Front\n4. Delete Rear\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert at front: ");
                scanf("%d", &value);
                insertFront(value);
                display();
                break;
            case 2:
                printf("Enter value to insert at rear: ");
                scanf("%d", &value);
                insertRear(value);
                display(); 
                break;
            case 3:
                deleteFront();
                display(); 
                break;
            case 4:
                deleteRear();
                display(); 
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}
