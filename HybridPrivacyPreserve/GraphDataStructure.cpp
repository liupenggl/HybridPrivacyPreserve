#include "GraphDataStructure.h"

using namespace std;

int label_to_node(vector<struct Node>&graph,int label)
{//在途graph中，寻找label的值，返回其在graph中的位置
	int value;
	for(value=0;value<int(graph.size());value++)
	{
		if(graph[value].label==label)
			return value;
	}
	return -1;//The label is not in vector graph;
}
bool compdata(const Node& first,const Node&second)
{
	return first.data>second.data;
}

int count_edge(vector<struct Node>&graph)
{
	int sum=0;
	for(vector<struct Node>::iterator it=graph.begin();it<graph.end();it++)
	{
		sum=sum+it->edgeNode.size();
	}
	return sum=sum/2;
}
int readfile_B(vector<struct Node>&graph,string filenameIn,string filenameReport,int extendnum)//filenameIn存放要读取的文件名，filenameReport，作为输出文件编号
{//extendnum indicates the vertex label big than vertice size.
	ifstream ifp;
	ofstream ofp;
	int u,v,nodeNumber=0,edgeNumber=0;
	struct Node nodeTemp;
	vector<struct Node>graphTemp;
	nodeTemp.data=0;

	char mystring[1024];
	string str;
	unsigned uFound=filenameIn.find_last_of("\\");

	if(filenameReport.empty())
	{
		filenameReport=filenameIn;
		str=filenameReport.substr(0,uFound+1)+ "Report_"+filenameReport.substr(uFound+1);
		ofp.open(str);
	}
	else
		ofp.open(filenameReport);

	ifp.open(filenameIn);
	
	if(!ifp.is_open()||!ofp.is_open())
	{
		cout<<"Error in open/output file.\n";
		cin.get();
		exit(1);
	}
	while (ifp.getline (mystring , 1024) != NULL )
	{
		str=mystring;
		if(!str.compare(0,9,"*Vertices"))//相等返回0
		{
			//printf("*Vertices:\n");
			str.erase(0,9);
			nodeNumber=atoi(str.c_str());
			break;
		}
	}
	nodeNumber=nodeNumber+extendnum;
	graph.resize(nodeNumber,nodeTemp);
	for(int i=0;i<nodeNumber;i++)
	{
		graph[i].label=i;
		graph[i].flagb=0;
		graph[i].flaga=0;
		graph[i].flagm=0;
		graph[i].diff=0;

	}//统一设置读入的点标签编号。

	while (ifp.getline (mystring , 1024) != NULL )
	{

		str=mystring;
		if(!str.compare(0,6,"*Edges"))
		{
			//printf("*Edges:\n");
			str.erase(0,6);
			break;
		}
	}

	while(ifp.getline (mystring , 1024) != NULL)	
	{


		if(strlen(mystring)<2)
			continue;
		str=mystring;
		unsigned pos;

		u=stoi(str,&pos);
		str.erase(0,pos);

		v=stoi(str,&pos);
		str.erase(0,pos);

		if(u==v)
			continue;
		if(find(graph[u].edgeNode.begin(),graph[u].edgeNode.end(),v)==graph[u].edgeNode.end())//确保新添加的边（u，v）没有出现过，目的是防止重复添加边。
		{
			graph[u].edgeNode.push_back(v);
			graph[u].data++;
			edgeNumber++;
		}
		else
		{
			ofp<<"edge add error graph"<<u<<":"<<"edge("<<u<<","<<v<<")"<<endl;
		}

		if(find(graph[v].edgeNode.begin(),graph[v].edgeNode.end(),u)==graph[v].edgeNode.end())//add the edge (v,u) too.
		{
			graph[v].edgeNode.push_back(u);
			graph[v].data++;
		}
		else
		{
			//printf("edge add error graph[%d]：edeg(%d, %d) ",v,v,u);
			//fprintf(ofp,"edge add error graph[%d]：edeg(%d, %d) ",v,v,u);
			ofp<<"edge add error graph"<<v<<":"<<"edge("<<v<<","<<u<<")"<<endl;
		}

	}
	int sum=0;
	graphTemp=graph;
	graph.resize(0);
	graph.clear();
	for(unsigned i=0;i<graphTemp.size();i++)//去除没有边的点
	{
		if(graphTemp[i].data>0)
			graph.push_back(graphTemp[i]);
		else
		{
			//fprintf(ofp,"delet data 0 node:%d,%d\n",i,graphTemp[i].data);
			ofp<<"delet data 0 node:"<<i<<","<<graphTemp[i].data<<endl;
			sum++;
		}
	}

	//fprintf(ofp,"Read %d nodes and %d edegs.\n",graph.size(),edgeNumber);
	//fprintf(ofp,"The sum of deleting nodes that have no edge is : %d",sum);
	ofp<<"Read "<<graph.size()<<"nodes and "<<edgeNumber<<"edges."<<endl;
	ofp<<"The sum of deleting nodes that have no edge is :"<<sum<<endl;

	ifp.close();
	ofp.close();

	printf("Reading nodes: %d and edges: %d \n",graph.size(),edgeNumber);

	return 0;
}
int readfile(vector<struct Node>&graph,string filenameIn,string filenameReport)//filenameIn存放要读取的文件名，filenameReport，作为输出文件编号
{//extendnum indicates the vertex label big than vertice size.
	ifstream ifp;
	ofstream ofp;
	int u,v,nodeNumber=0,edgeNumber=0;
	struct Node nodeTemp;
	vector<struct Node>graphTemp;
	nodeTemp.data=0;
	nodeTemp.label=-1;
	nodeTemp.diff=0;
	nodeTemp.flaga=0;
	nodeTemp.flagb=0;
	nodeTemp.flagm=0;
	nodeTemp.edgeNode.empty();

	char mystring[1024];
	string str;
	unsigned uFound=filenameIn.find_last_of("\\");

	if(filenameReport.empty())
	{
		filenameReport=filenameIn;
		str=filenameReport.substr(0,uFound+1)+ "Report_"+filenameReport.substr(uFound+1);
		ofp.open(str);
	}
	else
		ofp.open(filenameReport);

	ifp.open(filenameIn);
	
	if(!ifp.is_open()||!ofp.is_open())
	{
		cout<<"Error in open/output file.\n";
		cin.get();
		exit(1);
	}
	while (ifp.getline (mystring , 1024) != NULL )
	{
		str=mystring;
		if(!str.compare(0,9,"*Vertices"))//相等返回0
		{
			//printf("*Vertices:\n");
			str.erase(0,9);
			nodeNumber=atoi(str.c_str());
			break;
		}
	}

 

	while (ifp.getline (mystring , 1024) != NULL )
	{

		str=mystring;
		if(!str.compare(0,6,"*Edges"))
		{
			//printf("*Edges:\n");
			str.erase(0,6);
			break;
		}
	}

	while(ifp.getline (mystring , 1024) != NULL)	
	{


		if(strlen(mystring)<2)
			continue;
		str=mystring;
		unsigned pos;

		u=stoi(str,&pos);
		str.erase(0,pos);

		v=stoi(str,&pos);
		str.erase(0,pos);

		if(u==v)
			continue;

		if(label_to_node(graph,u)==-1)
		{
			nodeTemp.label=u;
			graph.push_back(nodeTemp);

		}
		if(label_to_node(graph,v)==-1)
		{
			nodeTemp.label=v;
			graph.push_back(nodeTemp);

		}
		int ntempU=label_to_node(graph,u);
		if(find(graph[ntempU].edgeNode.begin(),graph[ntempU].edgeNode.end(),v)==graph[ntempU].edgeNode.end())//确保新添加的边（u，v）没有出现过，目的是防止重复添加边。
		{
			graph[ntempU].edgeNode.push_back(v);
			graph[ntempU].data++;
			edgeNumber++;
		}
		else
		{
			ofp<<"edge add error graph"<<u<<":"<<"edge("<<u<<","<<v<<")"<<endl;
		}
		int ntempV=label_to_node(graph,v);
		if(find(graph[ntempV].edgeNode.begin(),graph[ntempV].edgeNode.end(),u)==graph[ntempV].edgeNode.end())//add the edge (v,u) too.
		{
			graph[ntempV].edgeNode.push_back(u);
			graph[ntempV].data++;
		}
		else
		{
			ofp<<"edge add error graph"<<v<<":"<<"edge("<<v<<","<<u<<")"<<endl;
		}

	}
	int sum=0;
	graphTemp=graph;
	graph.resize(0);
	graph.clear();
	for(unsigned i=0;i<graphTemp.size();i++)//去除没有边的点
	{
		if(graphTemp[i].data>0)
			graph.push_back(graphTemp[i]);
		else
		{
			//fprintf(ofp,"delet data 0 node:%d,%d\n",i,graphTemp[i].data);
			ofp<<"delet data 0 node:"<<i<<","<<graphTemp[i].data<<endl;
			sum++;
		}
	}
 
	ofp<<"Read "<<graph.size()<<"nodes and "<<edgeNumber<<"edges."<<endl;
	ofp<<"The sum of deleting nodes that have no edge is :"<<sum<<endl;

	ifp.close();
	ofp.close();

	cout<<"Reading nodes:"<<graph.size()<<" and edges: "<<edgeNumber<<endl;

	return 0;
}

