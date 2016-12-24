#include<stdio.h>
#include<stdlib.h>


struct node
{
int val;
struct node *left;
struct node *right;
} node;

struct node* insert(struct node* root ,int val)
    {
    struct node *temp,*insert_node ,*temp1;
    temp         =  (struct node*)malloc(sizeof(struct node));
    temp1        =  (struct node*)malloc(sizeof(struct node));
    insert_node  =  (struct node*)malloc(sizeof(struct node));
    insert_node->val = val;
    insert_node->left = NULL;
    insert_node->right = NULL;
    temp =root;
    if(root==NULL)
    {
        //printf("Value return");
        return insert_node;
    }
    while(temp!=NULL)
       {
        temp1 = temp;
        if(val < temp->val)
            {
            //if(temp->left!=NULL)
                temp  = temp->left;
            }
        else
            //if(temp->right!=NULL)
              //  {
              //  if(temp->right!=NULL)
                    temp = temp->right;
                //}
       }
      if(val > temp1->val)
          temp1->right = insert_node;
      else
          temp1->left = insert_node;   
return root;
}

void display_node(struct node* root)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp = root;
    if(temp==NULL)
        return;
    
        display_node(temp->left);
        printf("%d\t",temp->val);
        display_node(temp->right);
	
}

int main()
	{
	int n,val;
	printf("Enter the no of value to be inserted");
	scanf("%d",&n);
    struct node *head=NULL;
	for(int i=0;i<n;i++)
	{
        printf("enter value");
        scanf("%d",&val);
		head = insert(head,val);
	}
	display_node(head);
return 0;
}
