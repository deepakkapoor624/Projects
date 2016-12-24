#include<stdio.h>
#include<stdlib.h>

struct AdjListNode
	{
	int val;
	int weigh;
	struct AdjListNode *next;
	};



struct AdjList
	{
	struct AdjListNode *head;
	};

struct Graph
	{
	int V;
	struct AdjList *array;
	};


struct  AdjListNode* newAdjListNode(int dest,int weigh)
	{
	struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
 	newNode->val = dest;
 	newNode->weigh = weigh;
	newNode->next = NULL;
	return newNode;
	}


struct Graph* CreateGraph(int V)
	{
	struct Graph  *newGraph = (struct Graph*)malloc(sizeof(struct Graph));
	newGraph->V = V;

	newGraph->array = (struct AdjList*)malloc(V*sizeof(struct AdjList));

	for(int i=0;i<V;i++)
		newGraph->array[i].head = NULL;
	return newGraph;
	}


struct Graph* addEdge(struct Graph *graph,int src, int dest,int weigh)
	{
		//printf("src %d dest %d\n",src,dest);
	struct AdjListNode *newNode = NULL;
	
	newNode = newAdjListNode(dest , weigh);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;


	newNode = newAdjListNode(src , weigh);
	//printf("Node value %d" , newNode->val);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
    //printf("graph value %d \n" , (graph->array[dest].head)->val);
	return graph;
	}



void printGraph(struct Graph *graph)
	{
	int V = graph->V;
	//printf("%d",V);
	for(int i=0;i<V;i++)
		{
		//printf("\nValue Vertex %d",i);
		struct AdjListNode* Node = graph->array[i].head;
		printf("AdjList Head %d",i);
		//printf("\nover\n");
		while(Node)
			{
			printf("->%d---%d",Node->val,Node->weigh);
			Node = Node->next;
			}
			printf("\n");
			
		}
		
	}

