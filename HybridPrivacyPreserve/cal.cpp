#include"cal.h"
#include"GraphDataStructure.h"
using namespace std;
double combine(int n, int m)
{//combination of choosing m from n.
	double cnm = 1.0;
	if(m>n)
	{
		cout<<"in combine(): m>n error"<<endl;
	}
	if (m * 2 > n) 
		m = n - m;

	for (int i = 1; i <= m; n--, i++)
	{
		cnm /= i;
		cnm *= n;
	}
	return cnm;
}
double binomial(int k,int n,double p)
{
	//cout << com(n, k) << endl;
	if(p<0||p>1.0)
	{
		cout<<"int binomail():probability p error!"<<endl;
		return 1;
	}
	if(n==0)
	{//for scenario of two events but one not happen. 
		return 1;
	}
	if(k>n||k<0||n<0)
	{
		cout<<"int binomail():probability k or n error!"<<endl;
		return 0;
	}
	return combine(n, k)*pow(p, k)*pow(1-p, n-k);

}

int test_binomial(int n,double p)
{
	double sum=0;
	ofstream ost;
	ost.open("d:\\binomial.txt");

	cout<<"binomail("<<n<<","<<p<<")"<<endl;
	ost<<"binomail("<<n<<","<<p<<")"<<endl;
	for(int i=0;i<=n;i++)
	{
		sum=sum+binomial(i,n,p);
		cout<<"k="<<setw(3)<<i<<" :  "<<setw(12)<<binomial(i,n,p)<<"  sum:"<<sum<<endl;
		ost<<"k="<<setw(3)<<i<<" :  "<<setw(12)<<binomial(i,n,p)<<"  sum:"<<sum<<endl;
	}
	for(int i=0;i<=n;i++)
	{
		cout << i << ": "<< string(unsigned(binomial(i,n,p)*100),'*') <<endl;
		ost << i << ": "<< string(unsigned(binomial(i,n,p)*100),'*') <<endl;
	}
	return 0;
}
double binomial_con(int k,int n1,int n2,double p1,double p2)
{//calculate function distribution,(X+Y), of two binomail distributions b(n1,p1) and b(n2,p2)
	double sum=0;

	for(int j=0;j<=n1;j++)
	{
		if(k-j>=0 && k-j<=n2)
		{
			sum=sum+binomial(j,n1,p1)*binomial(k-j,n2,p2);
			//cout<<sum<<endl;
		}
	}
	return sum;
}
double binomial_con_s(int x,int n1,int n2,double p1,double p2,int di)
{//calculate function distribution,(X+Y), of two binomail distributions b(n1,p1) and b(n2,p2)
	double sum=0;

	for(int t=0;t<=n1;t++)
	{
		if(x-di+t>=0 && x-di+t<=n2)
		{	 
			//sum=sum+binomial(j,n1,p1)*binomial(x+di-j,n2,p2);
			sum=sum+binomial(t,n1,p1)*binomial(x-di+t,n2,p2);
		}
	}
	return sum;
}
double prior(int x,int di,double p1,double p2,int n)
{
	double sum=0,y,z;

	for(int t=0;t<=x;t++)
	{
		y=binomial(t,di,p1);
		z=binomial(x-t,n-1-di,p2);
		//sum=sum+binomial(t,di,p1)*binomial(x-t,n-1-di,p2);
		sum=sum+z*y;
	}
	return sum;
}
void temp()
{

	int n1=10,n2=6;
	double p1=0.25,p2=0.5;
	int t=n1+n2;
	double sum=0;
	for(int i=0;i<=n1+n2;i++)
	{
		for(int j=0;j<=n1;j++)
		{
			if(i-j>=0 && i-j<=n2)
			{
				sum=sum+binomial(j,n1,p1)*binomial(i-j,n2,p2);
				cout<<sum<<endl;
			}
		}
	}
	return;
}
double test()
{

	double sum=0;
	int n1=10,n2=200;
	double p1=0.95,p2=0.01;

	ofstream ost("d:\\text.txt");
	if(!ost)
	{
		cout << "Unable to open outfile";
		exit(1); // terminate with error
	}
	//cout<<"binomail("<<n<<","<<p<<")"<<endl;
	for(;n1>=0;n1--)
	{
		sum=0;

		ost<<"binomial_con(k,n1,n2,p1,p2) "<<" n1="<<n1<<" n2="<<n2<<" p1="<<p1<<" p2="<<p2<<endl;
		int k=0;
		for(int k=0;k<=n1+n2;k++)
		{
			double bi=binomial_con(k,n1,n2,p1,p2);
			sum=sum+bi ;

			if (bi>1e-010)
			{
				//cout<<"k="<<setw(3)<<k<<" :  "<<setw(12)<<binomial_con(k,n1,n2,p1,p2)<<"  sum:"<<sum<<endl;
				ost<<"k="<<setw(3)<<k<<" :  "<<setw(12)<<bi <<"  sum:"<<sum<<endl;  
			}
		}
		for(int k=0;k<=n1+n2;k++)
		{   
			double bi=binomial_con(k,n1,n2,p1,p2);

			if (unsigned(bi *500)!=0)
			{
				//cout<<setw(2)<< k << ": "<< string(unsigned(bi *500),'*') <<endl;
				ost<<setw(2)<< k << ": "<< string(unsigned(bi *500),'*') <<endl;
			}
		}
	}
	ost.close();

	return 0.0;
}
 
double graphtest()
{
	vector<struct Node> graph;
	readfile(graph,"d:\\data\\polbooks.txt");
	sort(graph.begin(),graph.end(),compdata);
	int k=50,n1=graph[0].edgeNode.size(),n2=graph.size()-1-graph[0].edgeNode.size(),m=count_edge(graph),N=graph.size()*(graph.size()-1);
	double sum=0; 
	double p1=double(m-k)/m, p2=(double)k/((graph.size()*(graph.size()-1)-m));

	ofstream ost("d:\\text.txt");
	ost<<"binomial_con(k,n1,n2,p1,p2) "<<" n1="<<n1<<" n2="<<n2<<" p1="<<p1<<" p2="<<p2<<endl;

	for(int k=0;k<=n1+n2;k++)
	{
		double bi=binomial_con(k,n1,n2,p1,p2);
		sum=sum+bi ;

		if (bi>1e-010)
		{
			//cout<<"k="<<setw(3)<<k<<" :  "<<setw(12)<<binomial_con(k,n1,n2,p1,p2)<<"  sum:"<<sum<<endl;
			ost<<"k="<<setw(3)<<k<<" :  "<<setw(12)<<bi <<"  sum:"<<sum<<endl;  
		}
	}
	for(int k=0;k<=n1+n2;k++)
	{   
		double bi=binomial_con(k,n1,n2,p1,p2);

		if (unsigned(bi *500)!=0)
		{
			//cout<<setw(2)<< k << ": "<< string(unsigned(bi *500),'*') <<endl;
			ost<<setw(2)<< k << ": "<< string(unsigned(bi *500),'*') <<endl;
		}
	}

	ost.close();
	return 0.0;
}

double graphtest2()
{
	vector<struct Node> graph;
	readfile(graph,"d:\\data\\polbooks.txt");
	sort(graph.begin(),graph.end(),compdata);
	unsigned k=400,n=graph.size();
	unsigned n1=0,n2=0,m=0,N=0;
	n1=graph[0].edgeNode.size()<k?graph[0].edgeNode.size():k;//minimum of di and k
	n2=(n-1-graph[0].edgeNode.size())<k?(n-1-graph[0].edgeNode.size()):k;//minimum of n-1-di and k
	m=count_edge(graph);
	N=graph.size()*(graph.size()-1)/2;
	double sum=0; 
	double p1=double(k)/m, p2=(double)k/(N-m);

	ofstream ost("d:\\text.txt");
	ost<<"binomial_con(k,n1,n2,p1,p2) "<<" n1="<<n1<<" n2="<<n2<<" p1="<<p1<<" p2="<<p2<<endl;
	int di=graph[0].edgeNode.size();
	for(unsigned x=di-k>0?di-k:0 ; x<=di+n2;x++)
	{
		double bi=binomial_con_s(x,n1,n2,p1,p2,graph[0].edgeNode.size());
		sum=sum+bi ;

		//if (bi>1e-010)
		{
			//cout<<"k="<<setw(3)<<k<<" :  "<<setw(12)<<binomial_con(k,n1,n2,p1,p2)<<"  sum:"<<sum<<endl;
			ost<<"x="<<setw(3)<<x<<" :  "<<setw(12)<<bi <<"  sum:"<<sum<<endl;  
		}
	}
	for(unsigned x=di-k>0?di-k:0 ; x<=di+n2;x++)
	{   
		double bi=binomial_con_s(x,n1,n2,p1,p2,graph[0].edgeNode.size());

		if (unsigned(bi *500)!=0)
		{
			//cout<<setw(2)<< k << ": "<< string(unsigned(bi *500),'*') <<endl;
			ost<<setw(2)<< x << ": "<< string(unsigned(bi *500),'*') <<endl;
		}
	}

	ost.close();
	return 0.0;
}