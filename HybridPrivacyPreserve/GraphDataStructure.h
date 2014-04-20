#ifndef GDS_H
#define GDS_H

#include<vector>
#include<list>
#include<algorithm>
#include<stdio.h>
#include<iostream>
#include<deque>
#include<time.h>
#include<iomanip>
#include<fstream>
#include<string>
#include<random>
#include<time.h>
using namespace std;

struct Node{
	int label;//��¼�ڵ�ı�ǩ���Ժ�����ȷ���ڵ㡣
	int data;//��¼�ڵ�Ķȡ�
	vector<int> edgeNode;//��¼�ڵ����ڱ߹�ϵ��
	int flaga;// ������
	int flagb;//��
	int flagm;
	int diff;
};
typedef struct Edge{//edge<s,d>
	int s;//the label of vertex 
	int e;
}Edge;
int readfile_B(vector<struct Node>&graph,string filenameIn,string filenameReport="",int extendnum=200000);

int readfile(vector<struct Node>&graph,string filenameIn,string filenameReport="" );
int count_edge(vector<struct Node>&graph);

bool compdata(const Node& first,const Node&second);

int label_to_node(vector<struct Node>&graph,int label);

#endif