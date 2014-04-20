#ifndef HYP_M
#define HYP_M
 

int partion_graph(int k, vector<struct Node>&graph,vector<struct  Node*>&graphk,vector<struct Node*>&graphr);

int label_to_node(vector<struct Node>&graph,int label);
int add_edge(int k,vector<struct Node *>&graphr);
int add_edge_B(int k,vector<struct Node *>&graphr);

bool compedge(Edge first,Edge second);
int label_in_graphr(int label,vector<struct Node*>&graphr);
int del_edge(unsigned k,vector<struct Node *>&graphr);
int partion_graphr(vector<struct  Node*>&graphr, vector<struct  Node*>&graphra, vector<struct  Node*>&graphrb);
int random_graphrb(vector<struct Node*>&graphrb);
 

#endif 