
#include"test.h"

using namespace std;


double cluster_c( vector<struct Node>&graph)
{
	vector<struct Node>tempGraph(graph.begin(),graph.end());
	vector<int>node_cc;
	double cc=0;
	for(unsigned i=0;i<tempGraph.size();i++)
	{
		vector<int>edge=tempGraph[i].edgeNode;
		int nodeDegree=tempGraph[i].data;
		int nodeEdegeSize=tempGraph[i].edgeNode.size();
		int neighbourCount=0;
		for(unsigned j=0;j<tempGraph[i].edgeNode.size();j++)
		{
			int findedge=tempGraph[i].edgeNode[j];
			vector<int>::iterator iter;

			for(int k=j+1;k<nodeEdegeSize;k++)
			{
				unsigned rtv=label_to_node(tempGraph,edge[k]);
				if(rtv>=tempGraph.size())
					printf("label_to_node find error");
				iter=find(tempGraph[rtv].edgeNode.begin(),tempGraph[rtv].edgeNode.end(),findedge);

				if(iter!=tempGraph[rtv].edgeNode.end())
					neighbourCount++;
			}

		}
		tempGraph[i].flaga=neighbourCount;
	}
	for(unsigned i=0;i<tempGraph.size();i++)
	{
		if(tempGraph[i].data>1)
			cc=cc+2*(double)tempGraph[i].flaga/((tempGraph[i].data)*(tempGraph[i].data-1));
		else
			cc=cc+0;
	}
	cc=cc/tempGraph.size();

	return cc;
}


int show_cost(const vector<struct Node>&graphback,const vector<struct Node>&graph, ofstream &ost)
{



	int costE=0,costN=0,cost=0;
	for(unsigned i=0;i<graphback.size();i++)
	{
		costE=costE+graph[i].edgeNode.size()-graphback[i].edgeNode.size();
	}

	for(unsigned i=graphback.size();i<graph.size();i++)
	{		
		costN=costN+1+graph[i].edgeNode.size();
	}
	ost<<setw(3)<<costE/2<<setw(6)<<costN*2<<"   cost=              "<<(costE/2+costN)<<endl ;

	return 0;
}

int test_cost_k(string sFileName,string sflag)
{
	vector<struct Node> graph,graphBack;

	vector<struct Node *>diffvector;//存放需要匿名的节点指针

	readfile(graph,sFileName);
	sort(graph.begin(),graph.end(),compdata);
	graphBack=graph;

	unsigned uFound=sFileName.find_last_of("\\");
	string str=sFileName.substr(0,uFound+1)+"Result_"+sflag+"_"+sFileName.substr(uFound+1); 
	ofstream ost(str);

	for(int k=2;k<21;k>5?k=k+4:k=k+1)
	{
		graph=graphBack;

		degree_anonymB(graph.begin(),graph.end(),k);
		diffvector.resize(0);
		diffSelect(graph,diffvector);
		if(!diff_anonym(diffvector))
		{
			ost<<setw(2)<<k<<"   ";
			show_cost(graphBack,graph,ost);

			printf("k=%d: \n",k);
		}
		else
		{
			node_add( graph, diffvector);

			ost<<setw(2)<<k<<"   ";
			show_cost(graphBack,graph,ost);

			printf("k=%d: \n",k);
		}

	}
	ost.close();
	return 0;
}

int test_cc_k(string sFileName,string sflag)
{
	vector<struct Node> graph,graphBack;
	vector<struct Node *>diffvector;//存放需要匿名的节点指针

	readfile(graph,sFileName);
	sort(graph.begin(),graph.end(),compdata);
	graphBack=graph;

	unsigned uFound=sFileName.find_last_of("\\");
	string str=sFileName.substr(0,uFound+1)+"Result_"+sflag+"_"+sFileName.substr(uFound+1); 
	ofstream ost(str);
	ost<<"orignal cc"<<cluster_c(graph)<<endl;
	for(int k=2;k<21;k>5?k=k+4:k=k+1)
	{
		graph=graphBack;

		degree_anonymB(graph.begin(),graph.end(),k);

		diffvector.resize(0);
		diffSelect(graph,diffvector);
		if(!diff_anonym(diffvector))
		{

			double cc=cluster_c(graph);
			cout<<"k="<<setw(2)<<k<<":  "<<"CC="<<cc<<endl;

			ost<<"k="<<setw(2)<<k<<":  "<<"CC= "<<cc<<endl;
	
		}
		else
		{

			double cc=cluster_c(graph);
			cout<<"k="<<setw(2)<<k<<":  "<<"CC="<<cc<<endl;

			ost<<"k="<<setw(2)<<k<<":  "<<"CC= "<<cc<<endl;
 
		}
 
	}
	ost.close();
	return 0;
}



int test_cost_rdm(string sFileName,string sflag)//直接计算graph.size()*(1-1.0/k)*2
{
	vector<struct Node> graph,graphBack;
	vector<struct Node*>graphp;
	readfile(graph,sFileName);
 
	graphBack=graph;

	unsigned uFound=sFileName.find_last_of("\\");
	string str=sFileName.substr(0,uFound+1)+"Result_"+sflag+"_"+sFileName.substr(uFound+1); 
	ofstream ost(str);


	for(int k=2;k<21;k>5?k=k+4:k=k+1)
	{
		graph=graphBack;
		graphp.resize(0);
		for(vector<Node>::iterator it=graph.begin();it!=graph.end();it++)
		{
			graphp.push_back(&(*it));		
		}
		int m=int(graphp.size()*(1-1.0/k));
		del_edge(m,graphp);
		add_edge_B(m,graphp);
		int sum=0;
		for(vector<struct Node>::iterator it=graph.begin();it<graph.end();it++)
		{
			sum=sum+it->flagm;
		}

		ost<<"k="<<setw(2)<<k<<":  "<<"graph.size="<<m<<"  "<<"sum=                  "<<sum/2<<endl;
		cout<<"k="<<setw(2)<<k<<":  "<<"graph.size="<<m<<"  "<<"sum=                  "<<sum/2<<endl;

	}
	ost.close();

	return 0;
}
int test_cc_rdm(string sFileName,string sflag)
{
	vector<struct Node> graph,graphBack;
	vector<struct Node*>graphp;
	readfile(graph,sFileName);
 
	graphBack=graph;

	unsigned uFound=sFileName.find_last_of("\\");
	string str=sFileName.substr(0,uFound+1)+"Result_"+sflag+"_"+sFileName.substr(uFound+1); 
	ofstream ost(str);

	for(int k=2;k<21;k>5?k=k+4:k=k+1)
	{
		graph=graphBack;
		for(vector<Node>::iterator it=graph.begin();it!=graph.end();it++)
		{
			graphp.push_back(&(*it));		
		}
		int m=int(graph.size()*(1-1.0/k));
		del_edge(m,graphp);
		add_edge_B(m,graphp);

		double cc=cluster_c(graph);
		cout<<"k="<<setw(2)<<k<<":  "<<"CC="<<cc<<endl;

		ost<<"k="<<setw(2)<<k<<":  "<<"CC= "<<cc<<endl;
	}
	ost.close();

	return 0;
}

int test_cost_hyp(string sFileName,string sflag)
{
	vector<struct Node> graph,graphBack;
	vector<struct Node*>graphk,graphr,graphra,graphrb;

	unsigned uFound=sFileName.find_last_of("\\");
	string str=sFileName.substr(0,uFound+1)+"Result_"+sflag+"_"+sFileName.substr(uFound+1); 
	ofstream ost(str);

	str=sFileName.substr(0,uFound+1)+"Report_Read_"+sFileName.substr(uFound+1); 
	readfile(graph,sFileName,str);

 	sort(graph.begin(),graph.end(),compdata);
	graphBack=graph;

	for(int k=2;k<21;k>5?k=k+4:k=k+1)
	{
		int r=1;
		for(;r<10;r=r+2)
		{
			graph=graphBack;
			partion_graph(k,graph,graphk,graphr);
			int m=int(graphr.size()*r*0.10);
			del_edge(m,graphr);
			add_edge_B(m,graphr);

			partion_graphr(graphr,graphra,graphrb);
			random_graphrb(graphrb);

			int sum=0;
			for(vector<struct Node>::iterator it=graph.begin();it<graph.end();it++)
			{
				sum=sum+it->flagm;
			};

			ost<<"k="<<setw(2)<<k<<":  "<<"r="<<setw(2)<<r<<":  "<<"graphr="<<graphr.size()<<"  "<<"sum="<<sum<<endl;
			//int sum2=0;
			//for(vector<struct Node*>::iterator it=graphr.begin();it<graphr.end();it++)
			//{
			//	sum2=sum2+(*it)->flagm;
			//}

			//ost<<"k="<<k<<":  "<<"r="<<m<<":  "<<"sum2="<<sum2/2<<endl;

		}
		ost<<endl;
	}
	ost.close();

	return 0;
}


int test_cc_hyp(string sFileName,string sflag)
{
	vector<struct Node> graph,graphBack;
	vector<struct Node*>graphk,graphr,graphra,graphrb;

	unsigned uFound=sFileName.find_last_of("\\");
	string str=sFileName.substr(0,uFound+1)+"Result_"+sflag+"_"+sFileName.substr(uFound+1); 
	ofstream ost(str);

	str=sFileName.substr(0,uFound+1)+"Report_Read_"+sFileName.substr(uFound+1); 
	readfile(graph,sFileName,str);

 	sort(graph.begin(),graph.end(),compdata);
	graphBack=graph;


 
	for(int k=2;k<21;k>5?k=k+4:k=k+1)
	{
		int r=1;
		for(;r<10;r++)
		{
			graph=graphBack;
			partion_graph(k,graph,graphk,graphr);
			int m=int(graphr.size()*r*0.10);
			del_edge(m,graphr);
			add_edge_B(m,graphr);

			partion_graphr(graphr,graphra,graphrb);
			random_graphrb(graphrb);
			double cc=cluster_c(graph);
			cout<<"k="<<setw(2)<<k<<":  "<<"r="<<setw(2)<<r<<":  "<<"graphrm="<<setw(2)<<m<<"  "<<"CC="<<cc<<endl;
			ost<<"k="<<setw(2)<<k<<":  "<<"r="<<setw(2)<<r<<":  "<<"graphrm="<<setw(2)<<m<<"  "<<"CC="<<cc<<endl;

		}
		ost<<endl;
	}
	ost.close();
	return 0;
}

int count_edge(vector<Node *>&graph)
{

	int sum=0;
	for(vector<Node *>::iterator it=graph.begin();it!=graph.end();it++)
	{
		sum=sum+(*it)->edgeNode.size();
	}
	return sum;
}

int cal_binomial(string sFileName,string sflag)
{
	vector<struct Node> graph,graphBack;
	vector<struct Node*>graphk,graphr,graphra,graphrb;

	unsigned uFound=sFileName.find_last_of("\\");
	string str=sFileName.substr(0,uFound+1)+"Result_"+sflag+"_"+sFileName.substr(uFound+1); 
	ofstream ost(str);

	str=sFileName.substr(0,uFound+1)+"Report_Read_"+sFileName.substr(uFound+1); 
	readfile(graph,sFileName,str);

 	sort(graph.begin(),graph.end(),compdata);
	graphBack=graph;
	 
	//for(int k=2;k<21;k>5?k=k+4:k=k+1)
	int k=5;
	{
		int r=1;
		for(;r<10;r++)
		{
			graph=graphBack;
			partion_graph(k,graph,graphk,graphr);
			int m=int(graphr.size()*r*0.10);
			unsigned di=0,n1=0,n2=0,nEdge=count_edge(graphr),N=graphr.size()*(graphr.size()-1); 

			double p1=double(m)/nEdge;
			double p2=(double)m/(N-nEdge);
			double result=0;
			for(vector<Node *>::iterator it = graphr.begin();it!=graphr.end();it++)
			{
				n1=(*it)->edgeNode.size()<m?(*it)->edgeNode.size():m;//n1取顶点的度和删除的点数间的小者
				n2=(graphr.size()-1-(*it)->edgeNode.size())<m?(graphr.size()-1-(*it)->edgeNode.size()):m;//取能够添加的边数，集合的总顶点数减1，再减已有边数

				double bi=binomial_con_s((*it)->edgeNode.size(),n1,n2,p1,p2,(*it)->edgeNode.size());
				//ost<<"di="<<(*it)->edgeNode.size()<<":    "<<"bi="<<bi<<endl;
				//cout<<"di="<<(*it)->edgeNode.size()<<":    "<<"bi="<<bi<<endl;
				result=1-bi+result;
			}
			ost<<"r="<<r<<"          "<<result/graphr.size()<<endl;
		}
 
	}
	ost.close();
	return 0;
}
				 