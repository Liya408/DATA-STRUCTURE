#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Node {
    char url[100];
    struct Node *prev, *next;
};
struct Node *current = NULL;
void visit(char *url) {
    struct Node *newPage = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newPage->url, url);
    newPage->prev = current;
    newPage->next = NULL;

    if (current != NULL) {
        current->next = NULL;
        current->next = newPage;
    }

    current = newPage;
    printf("Visited: %s\n", url);
}
void back() {
    if (current != NULL && current->prev != NULL) {
        current = current->prev;
        printf("Back to: %s\n", current->url);
    } else {
        printf("No previous page!\n");
    }
}
void forward() {
    if (current != NULL && current->next != NULL) {
        current = current->next;
        printf("Forward to: %s\n", current->url);
    } else {
        printf("No forward page!\n");
    }
}
void currentPage() {
    if (current != NULL) {
        printf("Current Page: %s\n", current->url);
    } else {
        printf("No page open!\n");
    }
}

int main() {
    int choice;
    char url[100];

    while (1) {
        printf("\nBrowser Navigation\n");
        printf("1.Visit new page\n");
        printf("2.Back\n");
        printf("3.Forward\n");
        printf("4.Current page\n");
        printf("5.Exit\n");
        printf("Enter choice:");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter URL: ");
                scanf("%s", url);
                visit(url);
                break;
            case 2:
                back();
                break;
            case 3:
                forward();
                break;
            case 4:
                currentPage();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
