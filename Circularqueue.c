#include<stdio.h>
int queue[100];
int MAX;
int front=-1,rear=-1;
void enqueue(int value){
	if((front==0 && rear==MAX-1)||(rear+1)%MAX==front){
		printf("Queue is full\n");
		return;
	}
	if(front==-1)

	  front=rear=0;
	else

          rear=(rear+1)%MAX;
	  queue[rear]=value;
	  printf("%d enqueued \n",value);
}
void dequeue(){
	if(front==-1){

		printf("Queue is Empty \n");
		return;
	}
	printf("%d dequeued\n",queue[front]);
	if(front==rear)
		front=rear=-1;
	else
		front=(front+1)%MAX;

}

void display(){
	if (front==-1){

		printf("Queue is Empty\n");

		return ;
	}
	int i=front;
	printf("queue:   ");
	while(1){
		printf("%d ",queue[i]);
		if(i==rear)break;
		i=(i+1)%MAX;
	}
	printf("\n");
}
int main(){
	int choice,value;
	printf("Enter the size of the circular queue: ");
	scanf("%d",&MAX);
	if(MAX<=0||MAX>100){
		printf("Invalid Size! \n");
		return 1;
	}
	while(1){
		printf("\n1. Enqueue \n2.Dequeue  \n3.Exit\n Enter choice: ");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("Enter the value to Enqueue: ");
				scanf("%d", &value);
				enqueue(value);
				display();
				break;
			case 2:
				dequeue();
				display();
				break;
			case 3:
			        printf("Exit");
				return 0;
			default:
				printf("Invalid choice: ");

			}

		}
	}


	 


	
