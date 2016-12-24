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
		struct AdjListNode* Node = graph->array[i].head;
		printf("\n AdjList Head %d",i);
		while(Node)
			{
			printf("->%d",Node->val);
			Node = Node->next;
			}
			
		}
		
	}


int main()
	{
	int V=5;
	struct Graph *graph =CreateGraph(V);
	addEdge(graph,0,1,1);
	addEdge(graph,0,4,2);
	addEdge(graph,1,2,3);
	addEdge(graph,1,3,3);
	addEdge(graph,1,4,2);
	addEdge(graph,2,3,4);
    addEdge(graph,3,4,5);

	printGraph(graph);
	return 0;
	}


