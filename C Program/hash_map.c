

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct DataItem
{
		char data[50];
		char key[50];
};
 
struct DataItem* temp;
struct DataItem* dumpy;

struct DataItem* hashArray;

void insert(char key[], char value[] ,int p)
{
	struct DataItem *temp =(struct DataItem*)malloc(sizeof(struct DataItem));
	strcpy(hashArray[p].key,key);
	strcpy(hashArray[p].data ,value);
	
}


void display(int n)
{
	for(int i=0;i<n;i++)
	{
		printf("%s %s\n",hashArray[i].key,hashArray[i].data);
	}

}

int main()
{
	int n;
	int f=0;
	char name[50];
	char key[50];
	char data[50];
	scanf("%d",&n);
	hashArray = realloc(hashArray,n* sizeof *hashArray);
	for(int i =0;i<n;i++)
	{
		scanf("%s %s",key,data);	
		insert(key,data,i);
	}
	
		while(scanf("%s",name) != EOF)
		{
		for(int k=0;k<n;k++)
		{
			//printf("Compare %s %s",name,hashArray[k].key);
			if(strcmp(name,hashArray[k].key)==0)
			{
				f=1;
				printf("%s=%s\n",hashArray[k].key,hashArray[k].data);
				break;
			}
		}		
			if(f!=1)
			{
				printf("Not found\n");
			}
		f=0;
	}

}
