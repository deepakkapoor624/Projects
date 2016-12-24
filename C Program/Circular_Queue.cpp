#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
	int data;
	struct node *front;
}node;
main()
{
	int max_size;
	printf("enter the size of queue\n");
	scanf("%d\n",&max_size);
	struct node *head=(node*)malloc(sizeof(node));
	head->front=NULL;
	head->data=10;
		struct node *temp=(node*)malloc(sizeof(node));
		temp->data=0;
		temp->front=NULL;
		head->front=temp;
	
	for(int i=1;i<max_size;i++)
	{
		struct node *temp1=(node*)malloc(sizeof(node));
		temp1->data=i;
		temp1->front=NULL;
		temp->front=temp1;
		temp=temp1;
	}
	while(head->front!=NULL)
	{
		printf("%d\n",head->data);
		head=head->front;
	}	
}
