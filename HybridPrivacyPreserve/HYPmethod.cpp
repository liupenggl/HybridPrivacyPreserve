#include "GraphDataStructure.h"
#include "HYPmethod.h"

using namespace std;
int partion_graph(int k, vector<struct Node>&graph,vector<struct  Node*>&graphk,vector<struct Node*>&graphr)
{//The input graph contains  graph data sorted by degree
	graphk.clear(),graphr.clear();

	int counter=0;
	bool flag=0;
	for(vector<struct Node>::iterator it=graph.begin();it<graph.end();it++)
	{
		counter=0;
		while((it+1)<graph.end()&&it->data==(it+1)->data)
		{
			counter++;
			it++;
		}
		if(counter>=k-1)
		{
			for(;counter>=0;counter--)
			{
				graphk.push_back(&(*(it-counter)));

			}
		}
		for(;counter>=0;counter--)
		{
			graphr.push_back(&(*(it-counter)));
		}

	}
	return 0;
}


int add_edge(int k,vector<struct Node *>&graphr)
{


	ofstream ofs("d:\\add_edge.txt");

	default_random_engine generator((unsigned)time(0));
	//	default_random_engine generator;
	uniform_int_distribution<int> distribution(0,graphr.size()-1);
	int source,destination;
	long counter=graphr.size()*graphr.size()*0.5;//given an arbitrary loop termination condition 
	int flag=0;//
	while (true)
	{
		if(counter<0)
		{
			cout<<"in function add_edge(),may be run more time than the threshhold"<<endl;
			flag=1;
			break;
		}
		if(k<=0)
		{
			break;
		}
		source = distribution(generator);
		destination = distribution(generator);
		if(source!=destination && find(graphr[source]->edgeNode.begin(),graphr[source]->edgeNode.end(),graphr[destination]->label)==graphr[source]->edgeNode.end())
		{
			graphr[source]->edgeNode.push_back(graphr[destination]->label);
			graphr[destination]->edgeNode.push_back(graphr[source]->label);

			graphr[source]->flagm++;
			graphr[destination]->flagm++;//record the mofification.
			ofs<<k<<": "<<graphr[destination]->label<<" , "<<graphr[source]->label<<endl;
			k--;
		}
	}
	ofs.close();
	return flag;
}

int add_edge_B(int k,vector<struct Node *>&graphr)
{

	//ofstream ofs("d:\\add_edge.txt");

	//	default_random_engine generator((unsigned)time(0));
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0,graphr.size()-1);
	int source,destination;
	int counter=graphr.size()*graphr.size()*0.5;//given an arbitrary loop termination condition 
	int flag=0;//
	while (true)
	{
		if(counter<0)
		{
			cout<<"in function add_edge(),may be run more time than the threshhold"<<endl;
			flag=1;
			break;
		}
		if(k<=0)
		{
			break;
		}

		source = distribution(generator);
		destination = source+1;

		while(destination<graphr.size())
		{
			if(find(graphr[source]->edgeNode.begin(),graphr[source]->edgeNode.end(),graphr[destination]->label)==graphr[source]->edgeNode.end())
			{
				graphr[source]->edgeNode.push_back(graphr[destination]->label);
				graphr[destination]->edgeNode.push_back(graphr[source]->label);

				graphr[source]->flagm++;
				graphr[destination]->flagm++;//record the mofification.
				//ofs<<k<<": "<<graphr[destination]->label<<" , "<<graphr[source]->label<<endl;
				k--;
				break;
			}
			destination++;
		}



	}
	//ofs.close();
	return flag;
}

bool compedge(Edge first,Edge second)
{
	return first.s<second.s;
}

int label_in_graphr(int label,vector<struct Node*>&graphr)
{//translate label to position
	for (unsigned i= 0; i < graphr.size(); i++)
	{
		if((graphr[i]->label)==label)
			return i;
	}
	return graphr.size();
}
int del_edge(unsigned k,vector<struct Node *>&graphr)
{
	vector<Edge>ve;//store all edges in graphr;
	vector<int>delnum,labeltemp;

	Edge ed;

	for(vector<struct Node*>::iterator it=graphr.begin();it<graphr.end();it++)
	{
		for(vector<int>::iterator itj=(*it)->edgeNode.begin();itj<(*it)->edgeNode.end();itj++)
		{
			ed.s=(*it)->label;
			ed.e=*itj;
			ve.push_back(ed);
		}
		labeltemp.push_back((*it)->label);
	};

	sort(labeltemp.begin(),labeltemp.end());
	unsigned i=0;
	while(i<ve.size())
	{
		if(find(labeltemp.begin(),labeltemp.end(),ve[i].e)==labeltemp.end())
			ve.erase(ve.begin()+i);
		else
			i++;
	}

	sort(ve.begin(),ve.end(),compedge);
	vector<Edge>ves;//each edge in ve only contain once;
	for (vector<Edge>::iterator it=ve.begin();it<ve.end();it++)
	{
		if(it->s<it->e)
			ves.push_back(*it);
	}

	//default_random_engine generator((unsigned)time(0));
	default_random_engine generator ;



	if (k<ves.size())
	{
		unsigned i=0;
		uniform_int_distribution<int> distribution(0,ves.size()-1);
		while (i<k)
		{
			int temp=distribution(generator);
			if(find(delnum.begin(),delnum.end(),temp)==delnum.end())
			{
				delnum.push_back(temp);
				i++;
			}
		}
	}
	else
	{
		cout<<"calculate delnum error:delnum.size()="<<delnum.size(	)<<endl;

	}
	for (unsigned i = 0; i < delnum.size(); i++)
	{
		int temp;
		temp=label_in_graphr(ves[delnum[i]].s,graphr);
		if(temp==graphr.size())
			cout<<"must error in deledge,label_in_graphr"<<endl;
		for (unsigned j = 0; j < graphr[temp]->edgeNode.size(); j++)
		{
			if(ves[delnum[i]].e==graphr[temp]->edgeNode[j])
			{
				graphr[temp]->edgeNode.erase(graphr[temp]->edgeNode.begin()+j);
				graphr[temp]->flagm++;
				break;
			}
		}

		temp=label_in_graphr(ves[delnum[i]].e,graphr);
		for (unsigned j = 0; j < graphr[temp]->edgeNode.size(); j++)
		{
			if(ves[delnum[i]].s==graphr[temp]->edgeNode[j])
			{
				graphr[temp]->edgeNode.erase(graphr[temp]->edgeNode.begin()+j);
				graphr[temp]->flagm++;
				break;
			}
		}
	}

	return 0;
}

int partion_graphr(vector<struct  Node*>&graphr, vector<struct  Node*>&graphra, vector<struct  Node*>&graphrb)
{
	graphra.clear(),graphrb.clear();

	for(unsigned i=0;i<graphr.size();i++)
	{
		if(graphr[i]->flagm==0)//selelect unchange vertices
			graphrb.push_back(graphr[i]);
		else
		{
			graphra.push_back(graphr[i]);
		}
	}
	return 0;
}

int random_graphrb(vector<struct Node*>&graphrb)
{
	if(graphrb.empty ()||graphrb.size()==1)
	{
		cout<<"in random_graphrb(vector<struct Node*>&graphrb may be error, graphrb is empty "<<endl;
		return 1;
	}

	vector<struct Node*>::iterator it=graphrb.begin();
	if(graphrb.size()%2==1)
	{
		vector<int>::iterator f;
		f=find((*it)->edgeNode.begin(),(*it)->edgeNode.end(),(*(it+1))->label);

		if(f!=(*it)->edgeNode.end())
		{
			(*it)->edgeNode.erase(f);
			(*(it+1))->edgeNode.erase(find((*(it+1))->edgeNode.begin(),(*(it+1))->edgeNode.end(),(*it)->label));
			(*(it+1))->flagm ++;
			(*(it))->flagm++;
		}
		else//there is no edge between it and it+1;
		{
			(*it)->edgeNode.push_back((*(it+1))->label);
			(*(it+1))->edgeNode.push_back((*(it))->label);
			(*(it+1))->flagm ++;
			(*(it))->flagm++;
		}
		it++;
	}
	for(;it<graphrb.end();it=it+2)
	{
		vector<int>::iterator f;
		f=find((*it)->edgeNode.begin(),(*it)->edgeNode.end(),(*(it+1))->label);

		if(f!=(*it)->edgeNode.end())
		{
			(*it)->edgeNode.erase(f);
			(*(it+1))->edgeNode.erase(find((*(it+1))->edgeNode.begin(),(*(it+1))->edgeNode.end(),(*it)->label));
			(*(it+1))->flagm ++;
			(*(it))->flagm++;
		}
		else//there is no edge between it and it+1;
		{
			(*it)->edgeNode.push_back((*(it+1))->label);
			(*(it+1))->edgeNode.push_back((*(it))->label);
			(*(it+1))->flagm ++;
			(*(it))->flagm++;
		}
	}
	return 0;
}
