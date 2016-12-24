#include <stdio.h>	
#include <stdlib.h>
#include <math.h>
#include <string.h>	

#define SIZE 20

struct DataItem
{
	int data;
	int key;
	/* data */
};

struct DataItem* hashArray[SIZE];
struct DataItem* dummpyItem;
struct DataItem* item;

int hashCode(int key)
{
	return key %SIZE;
}


struct  DataItem *search(int key)
{
	int hashIndex = hashCode(key);
    //printf("HashIndex%d %d key is %d\n",hashIndex,(hashArray[hashIndex]->key),key);

	while(hashArray[hashIndex]->key == key)
		return hashArray[hashIndex];

	++hashIndex;

  // wrap around the table
	hashIndex %= SIZE;

	return NULL;

}

void insert(int key ,int data)
{
		struct DataItem *item =(struct DataItem*) malloc(sizeof(struct DataItem));
	    item->data = data;
	    item->key = key;
	    int hashIndex = hashCode(key);
        
	    while(hashArray[hashIndex] !=NULL && hashArray[hashIndex]->key !=-1)
	    {
	    	++hashIndex;
	    	hashIndex%= SIZE;

	    }
	    //printf("HashIndex%d\n",hashIndex);
	    hashArray[hashIndex] = item;
}


	struct DataItem* delete(struct DataItem* item)
{
		int key = item->key;

		int hashIndex = hashCode(key);
        //printf("HashIndex%d\n",hashIndex);
        while(hashArray[hashIndex] != NULL)
        {
        	if(hashArray[hashIndex]->key ==key)
        	{
        		struct DataItem *temp = hashArray[hashIndex];
        	    hashArray[hashIndex] = dummpyItem;
        	    return temp;
        	}

        	++hashIndex;
        	hashIndex%=SIZE;
        	return NULL;
        }

    }
void display()
{
	int i=0;
	for(i=0;i<SIZE;i++)
	{
		if(hashArray[i]!=NULL)
		    printf("%d, %d \n",hashArray[i]->key,hashArray[i]->data);
		else
			printf("element not found\n");
	}

}

int main()
{

	dummpyItem = (struct DataItem*)malloc(sizeof(struct  DataItem));
	dummpyItem->data = -1;
	dummpyItem->key = -1;
	//printf("Insert element in table\n");
	insert(1,20);
	insert(2,70);
	insert(4,25);
	insert(42,80);
	insert(12,44);
	insert(14,32);
	insert(17,11);
	insert(13,78);
    insert(38,97);
    //printf("Insertion Compeleted\n");

    display();
    //printf("Searching Item\n");
    item = search(38);
     	
	if(item !=NULL)
		printf("element found %d\n",item->data);
	else
		printf("Element not found\n");

	delete(item);
	item = search(37);
	if(item !=NULL)
		printf("element found %d\n",item->data);
	else
		printf("Element not found\n");

	
	/* code */
	return 0;
}

