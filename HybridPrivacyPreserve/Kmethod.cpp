#include"GraphDataStructure.h"
#include "Kmethod.h"

using namespace std;



int degree_diff(vector<struct Node>::iterator start,vector<struct Node>::iterator end)
{
	int i,value=0;
	i=end-start;
	while(i>=0)
	{
		value=value+start->data-(end-i)->data;
		i--;
	}
	return value;
}


int degree_anonymB(vector<struct Node>::iterator begin,vector<struct Node>::iterator end,int k)   
{//���� ���Ȳ�ͬ��̰���㷨
	vector<struct Node>::iterator nodep=begin;
	int temp,i=0;
	int flag=0,x;
	while (end-nodep>=2*k) //���д���2k
	{
		i=0;temp=0;flag=0;
		temp = (nodep + i)->data - (nodep + i+1)->data;//���һ��Ķ�����

		for (; i < 2*k-1; i++) 
		{
			x=(nodep + i)->data - (nodep + i+1)->data;
			if(x>temp)
			{
				temp=x;
				flag=i;
			}
		}//choose the max differency within 2*k

		if(end-nodep-flag-1<k)//��֤���һ�����k��
		{
			flag=flag-(k-(end-nodep-flag-1));//��flagָ������k-1λ
		}
		if(flag<k-1)//���ֵ������ǰk��
		{
			flag=k-1;
		}

		(nodep + flag+1)->flaga = 1;
		nodep = nodep + 1 + flag;
	}
	int r_value=0;
	nodep=begin;//��ͷ��ʼ����diff��ֵ��flaga��ֵ��
	for(int i=0,j=0,k=0;i<end-begin;i++)
	{
		if((nodep+i)->flaga==1)
		{
			j=i;
			k++;
		}
		(nodep+i)->diff=(nodep+j)->data-(nodep+i)->data;
		r_value=(nodep+i)->diff+r_value;
		(nodep+i)->flaga=k;	
	}
	return r_value/2;
}
int degree_anonymD(vector<struct Node>::iterator begin,vector<struct Node>::iterator end,int k)
{
	vector<struct Node>::iterator nodep=begin;
	int i=0;
	int add=i+k;
	int cmerge,cnew;


	if((end-nodep)==2*k)//������Ԫ��Ϊ 2kʱ����Ϊ2��
	{
		(nodep+k)->flaga=1;
	}
	else//������Ԫ��Ϊ >=2k+1ʱ��̰���㷨����
	{
		while((end-nodep)>=2*k+1)//�����±�add+k<<N-1,ʹ�䲻ҪԽ��,Ҫ������Ԫ��>=2k+1
		{
			cmerge=(nodep+i)->data-(nodep+add)->data+degree_diff(nodep+add+1,nodep+add+k);
			cnew=degree_diff(nodep+add,nodep+add+k-1);

			if(cmerge<=cnew)
			{

				if(add<i+2*k-1&&(end-(nodep+add))>k+1)//add�ѼӴ��� <=k-2��,���ұ�֤ add�����Ԫ�أ���ʣ�µ�Ԫ��>k+1
				{
					add++;//ָ��ָ����һԪ��
				}
				else
				{
					(nodep+add)->flaga=1;
					//����	
					nodep=nodep+add;
					i=0;
					add=i+k;//��Ҫ���Ǹ���
				}
			}
			else
			{
				(nodep+add)->flaga=1;
				//����	
				nodep=nodep+add;
				i=0;
				add=i+k;//��Ҫ���Ǹ���
			}

			if(end-nodep==2*k)//�����º�Ԫ�ظ����պ�Ϊ 2k ,���Ϊ����
			{
				(nodep+i+k)->flaga=1;
			}
		}
	}

	nodep=begin;//��ͷ��ʼ����diff��ֵ��flaga��ֵ��
	int r_value=0;
	for(int i=0,j=0,k=0;i<end-begin;i++)//ֵ��ѧϰ��������
	{
		//printf("flaga:%d ",(nodep+i)->flaga);
		if((nodep+i)->flaga==1)
		{
			j=i;
			k++;
		}
		(nodep+i)->diff=(nodep+j)->data-(nodep+i)->data;
		r_value=(nodep+i)->diff+r_value;
		(nodep+i)->flaga=k;	
	}
	return r_value/2;
}

vector<struct Node>::iterator degree_anonymE(vector<struct Node>::iterator begin,vector<struct Node>::iterator end,int k)
{//���÷��η��Ķ������㷨��divide-and-conquer algorithm.
	if(end-begin>2*k)
	{
		int j=0,temp=(begin)->data-(begin+1)->data;
		for(int i=1;i<end-begin;i++)
		{
			if(temp<(begin+i-1)->data-(begin+i)->data)
			{
				temp=(begin+i)->data-(begin+i-1)->data;
				j=i;
			}

		}
		if(j<k)
		{
			j=k;
		}
		degree_anonymE(begin,begin+j,k);
		degree_anonymE(begin+j,end,k);
	}
	else
	{
		begin->flaga=1;//�Է��������б�ǡ�		
	}

	return begin;
}

int count_degree_diff(vector<struct Node>&graph)
{//������η����graph���ݵķ����ǣ���diff���㣬����ֵΪ �������������
	int r_value=0;
	for(unsigned i=0,j=0,k=0;i<graph.size();i++)
	{
		if(graph[i].flaga==1)
		{
			j=i;
			k++;
		}
		graph[i].diff=graph[j].data-graph[i].data;
		r_value=graph[i].diff+r_value;
		graph[i].flaga=k;	
	}
	return r_value/2;
	
}


void diffSelect(vector<struct Node>&graph,vector<struct Node * >&diffvector)
{
	for(unsigned i=0;i<graph.size();i++)
		if(graph[i].diff!=0)
		{
			diffvector.push_back(&graph[i]);
		}
}

int diff_anonym(vector<struct Node * > &diffvector)
{

	for(int i=0;i<int(diffvector.size())-1;i++)//�ͺ�һ���Ƚϣ�����Ҫ���һ��Ԫ��
	{
		int flag=0;
		vector<int>::iterator iter;

		for(int j=i+1;j<(signed)diffvector.size();j++)
		{
			iter=find(diffvector[j]->edgeNode.begin(),diffvector[j]->edgeNode.end(),diffvector[i]->label);
			if(iter==diffvector[j]->edgeNode.end())
			{
				diffvector[i]->edgeNode.push_back(diffvector[j]->label);
				diffvector[j]->edgeNode.push_back(diffvector[i]->label);

				diffvector[i]->diff--;
				diffvector[i]->data++;
				diffvector[j]->diff--;
				diffvector[j]->data++;
				if(diffvector[j]->diff==0)
					diffvector.erase(diffvector.begin()+j);
				if(diffvector[i]->diff==0)
					diffvector.erase(diffvector.begin()+i);

				flag=1;
				break;
			}
		}
		if(flag==1)
			i--;//�ִӵ�ǰԪ�ؿ�ʼ��
	}
	if(diffvector.size()==0)
		return 0;//���������
	else
		return 1;
}

int node_path(int label,vector<struct Node>&graph)
{//������ɺ����е���label�ľ��룬�����diff�С�labelΪ��ı�ǩ��graphΪ�洢��ͼ���ݡ�
	struct Node * node;
	unsigned v;

	deque<struct Node *>deq;
	for(unsigned i=0;i<graph.size();i++)
	{
		if(graph[i].data!=0)
		{
		 	graph[i].flaga=0;
			graph[i].diff=0;
		}
	}
	v=label_to_node(graph,label);
	graph[v].flaga=2;


	deq.push_back(&graph[v]);

	while(!deq.empty())
	{
		node=deq.front();
		deq.pop_front();

		for(unsigned i=0;i<node->edgeNode.size();i++)
		{
			v=label_to_node(graph,node->edgeNode[i]);
			if(graph[v].flaga==0)
			{
				graph[v].flaga=1;
				graph[v].diff=node->diff+1;
 				deq.push_back(&graph[v]);
			}
		}
		node->flaga=2;
	}
	return 0;
}	

int diff_anonym_path(vector<struct Node>& graph,vector<struct Node * > &diffvector)
{
	vector<struct Node>tempnode,graphBack=graph;
	int i=0;
	for(i=0;i<int(diffvector.size())-1;i++)//�ͺ�һ���Ƚϣ�����Ҫ���һ��Ԫ��
	{
		int flag=0;
		vector<int>::iterator iter;

		tempnode.resize(0);
		for(unsigned j=i+1;j<diffvector.size();j++)
		{
			iter=find(diffvector[j]->edgeNode.begin(),diffvector[j]->edgeNode.end(),diffvector[i]->label);
			if(iter==diffvector[j]->edgeNode.end())
			{
				tempnode.push_back (*(diffvector[j]));	
			}
		}
		if(tempnode.size()!=0)
		{
			node_path(diffvector[i]->label,graphBack);
			int selectLabel=tempnode[0].label;
			int selecttemp=1000;//�㹻�����������1
			for(unsigned t=0;t<tempnode.size();t++)
			{
				if (tempnode[t].diff<selecttemp && tempnode[t].diff!=0)
				{
					selectLabel=tempnode[t].label ;
				}
			}
			int v;
			v=label_to_node(graph,selectLabel);
			diffvector[i]->edgeNode.push_back(graph[v].label);
			graph[v].edgeNode.push_back(diffvector[i]->label);

			diffvector[i]->diff--;
			diffvector[i]->data++;
			graph[v].diff--;
			graph[v].data++;
			if(graph[v].diff==0)
			{
				for(unsigned i=0;i<diffvector.size();i++)
				{
					if(diffvector[i]->label==selectLabel)
					{
						diffvector.erase(diffvector.begin()+i);
						break;
					}
				}

			}

			if(diffvector[i]->diff==0)
				diffvector.erase(diffvector.begin()+i);
			flag=1;
		}
		if(flag==1)
			i--;//�ִӵ�ǰԪ�ؿ�ʼ��
	}

	if(diffvector.size()==0)
		return 0;//���������
	else
		return 1;
}

int node_add(vector<struct Node>&graph,vector<struct Node * >&diffvector)
{
	int nodeAddNum=diffvector[0]->diff;
	for(unsigned i=0;i<diffvector.size();i++)//ѡ�����diff
	{
		if(nodeAddNum<diffvector[i]->diff)
			nodeAddNum=diffvector[i]->diff;
	}

	vector<struct Node>graphTemp;//����diffvector�����ָ��ָ��ԭgraph�����ܶ�ԭ���ݽ��в���
	struct Node temp;
	for(int i=0;i<nodeAddNum;i++)
	{
		temp.label=graph.size()+i+100000;//��ֹ����ص���������
		temp.data=0;
		temp.diff=0;
		graphTemp.push_back(temp);
	}
	while(!diffvector.empty())
	{
		for(int i=0;i<diffvector[0]->diff;i++)
		{
			graphTemp[i].edgeNode.push_back(diffvector[0]->label);
			graphTemp[i].data++;//����������Ķ�

			diffvector[0]->edgeNode.push_back(graphTemp[i].label);	
			diffvector[0]->data++;

		}
		diffvector[0]->diff=0;
		diffvector.erase(diffvector.begin());
	}
	graph.insert(graph.end(),graphTemp.begin(),graphTemp.end());
	return 0;
}


int label_to_node(deque<struct Node>&graph,int label)
{
	unsigned value;
	for(value=0;value<graph.size();value++)
	{
		if(graph[value].label==label)
			return value;
	}
	return value;
}


