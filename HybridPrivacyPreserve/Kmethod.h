#ifndef K_M_H
#define K_M_H
 
#include"GraphDataStructure.h"

using namespace std;
 

int degree_diff(vector<struct Node>::iterator start,vector<struct Node>::iterator end);

//int set_graph_diff(vector<struct Node>::iterator begin,vector<struct Node>::iterator end);
int degree_anonym(vector<struct Node>::iterator node,int dnum,int k);
int degree_anonymB(vector<struct Node>::iterator begin,vector<struct Node>::iterator end,int k);

int degree_anonymD(vector<struct Node>::iterator begin,vector<struct Node>::iterator end,int k);
vector<struct Node>::iterator degree_anonymE(vector<struct Node>::iterator begin,vector<struct Node>::iterator end,int k);
int count_degree_diff(vector<struct Node>&graph);
 
int diff_anonym(vector<struct Node * > &diffvector);
int node_path(int lable,vector<struct Node>&graph);
int diff_anonym_path(vector<struct Node>& graph,vector<struct Node * > &diffvector);

void diffSelect(vector<struct Node>&graph,vector<struct Node * >&diffvector);
int node_add(vector<struct Node>&graph,vector<struct Node * >&diffvector);
 
 
int label_to_node(deque<struct Node>&graph,int label);

#endif