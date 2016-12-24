#include "graph_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node
{
	int val;
	struct Node *next;
};


struct Node *InitialNode_List(int V)
{

struct Node *head = (struct Node*)malloc(sizeof(struct Node));
head->val = 0;
head->next  = NULL;

struct Node *temp = head;
    for(int i=1;i<V;i++)
        {
            struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->val = i;
            newNode->next = NULL;
            temp->next = newNode;
            temp = newNode;
        }
    return head;
}


bool emptyList(struct Node *List)
{

    if(List)
        return true;
    else
        return false;
}

struct Node* Update_UnvistedNode_List(struct Node *List,int val)   // delete node whose value matches
{
    struct Node *head = List;
    struct Node *temp=List;

    if(temp->val==val)   // If it's a head
    {
        head = head->next;
        //free(temp);
        return head;
    }
    while(temp)
        {
            if(temp->next->val==val)
              {       
            //struct Node *temp1 = temp;
            
                  temp->next = (temp->next)->next;
                  //free(temp1->next);
                  return head;
              }
              temp = temp->next;
             
        }
        return head;
}


struct Node *Update_VisitedNode_List(struct Node* List,int val)    //add node to the list
{
    
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->next =NULL;
    if(List==NULL)
        return newNode;


    struct Node *headList = List;
    newNode->next = headList;
    headList = newNode;

    return headList;
}


bool val_not_present_inList(struct Node *List,int val)
{
    if(List==NULL)
        return true;
    while(List)
    {
        if(List->val ==val)
            return false;   
          List = List->next;
    }
    return true;
}


void dijkstra_algorithm(struct Graph *graph ,struct Graph *dijsktra)
{
     int V = graph->V;
     struct Node *UnvistedNodeList =  InitialNode_List(V);
     //struct AdjListNode *CurrentNode = graph->array[0].head;
 
    int currentNodeValue_graph;
    struct Node * VisitedNodeList = NULL;

    VisitedNodeList = Update_VisitedNode_List(VisitedNodeList , 0);
    UnvistedNodeList = Update_UnvistedNode_List(UnvistedNodeList , 0);
  
     //printf("started");
     while(emptyList(UnvistedNodeList))//run till the list becomes empty
     {
        //printf("1st while loop started");
        int nextMinimumNodeWeigh = 9999;
        int nextMinimumNode, currentNodeValue;
        struct AdjListNode* Node  = NULL;

        struct Node * traverse_node = VisitedNodeList;   // for traverersing the visited node to get next minimum Node
        while(emptyList(traverse_node)) 
            {
                //printf("2nd while loop started");
                currentNodeValue = traverse_node->val;

                Node =  graph->array[currentNodeValue].head;
                while(Node)
                {
                    //printf("3rd while loop started");
                    if((nextMinimumNodeWeigh > Node->weigh) && (val_not_present_inList(VisitedNodeList,Node->val)))
                      {
                        currentNodeValue_graph = currentNodeValue;
                        nextMinimumNode = Node->val;
                        nextMinimumNodeWeigh = Node->weigh;
                        }
                    Node = Node->next;
               }
              // printf("1st while loop over");
               traverse_node  = Update_UnvistedNode_List(traverse_node,currentNodeValue);
            }
           // printf("2nd while loop started");
       

          addEdge(dijsktra , currentNodeValue_graph ,nextMinimumNode , nextMinimumNodeWeigh);
            // update the weigh of the node
          struct AdjListNode * updatedWeighList = graph->array[nextMinimumNode].head;
          while(updatedWeighList)
          {
        
            if(val_not_present_inList(VisitedNodeList,updatedWeighList->val))
            {
                updatedWeighList->weigh = updatedWeighList->weigh + nextMinimumNodeWeigh;

                /// the graph is non directive
                struct AdjListNode * updatedWeighList1 = graph->array[updatedWeighList->val].head;
                while(updatedWeighList1)
                {
                    if(updatedWeighList1->val==nextMinimumNode)
                    {
                      updatedWeighList1->weigh = updatedWeighList1->weigh + nextMinimumNodeWeigh;  
                      break;
                    }
                    updatedWeighList1 = updatedWeighList1->next;
                }

            }
            updatedWeighList = updatedWeighList->next;           
          }       

       // printf("4th while loop over");
        VisitedNodeList = Update_VisitedNode_List(VisitedNodeList,nextMinimumNode);   //update visited node list
        UnvistedNodeList = Update_UnvistedNode_List(UnvistedNodeList , nextMinimumNode);

     }

    //printf("1st while loop over");
}


int main()
{
	struct Graph *graph = NULL;
	struct Graph *Dijkstra_Graph = NULL;

	int V=5;
	/// create array
    graph = CreateGraph(V);
	addEdge(graph, 0, 1,1);
    addEdge(graph, 0, 4,2);
    addEdge(graph, 1, 2,2);
    addEdge(graph, 1, 3,3);
    addEdge(graph, 1, 4,5);
    addEdge(graph, 2, 3,1);
    addEdge(graph, 3, 4,4);

    //printf("Enter value");
    printGraph(graph);
    printf("Dijkstra Algorithm\n");
    Dijkstra_Graph = CreateGraph(V);
    


    // print the adjacency list representation of the above graph
  
    dijkstra_algorithm(graph , Dijkstra_Graph);
    printGraph(Dijkstra_Graph);

    
	return 0;
}