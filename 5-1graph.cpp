#include<iostream>
#include<string>
#include<queue>
using namespace std;
class Node
{
public:
	int e,w;
	Node *next,*pre;
	Node(int to,int weight,Node*p):e(to),w(weight),pre(p){next=NULL;}
};
class Graph
{
	Node*head[100];
public:
	int tot;
	Graph()
	{
		for(int i=0;i<=99;i++)
			head[i]=NULL;
		tot=0;
	}
	int add(int s,int t,int w);
	int dist(int s,int e);
	int del(int s,int e);
	int first(int s);  //���ص�һ���ٽֽڵ�
	int show();
	int dfs(int r);
	int bfs(int r);
	int lsp();
  bool test(int from,int to);
};

int Graph::add(int s,int e,int w)
{
	if(s>99||e>99)
		return 1;
	Node*p=head[s];
	if(p==NULL)
	{
		head[s]=new Node(e,w,NULL),tot++;
		return 0;
	}
	while(p->next!=NULL)
		if(p->e==e)
			return 0;
		else
			p=p->next;
	p->next=new Node(e,w,p),tot++;
	return 0;
}

int Graph::del(int s,int e)
{
	if(s>99||e>99)
		return 1;
	Node*p=head[s];
	if(p==NULL)
		return 2;
	if(p->e==e)
	{
		head[s]=p->next;
		if(p->next!=NULL)
			p->next->pre=NULL;
		delete p,tot--;
		return 0;
	}
	p=p->next;
	while(p->next!=NULL)
		if(p->e==e)
		{
			p->pre->next=p->next;
			delete p,tot--;
			return 0;
		}
	return 2;
}

int Graph::dist(int s,int e)
{
	if(s>99||e>99)
		return INT_MAX/2-1;
	Node*p=head[s];
	if(p==NULL)
		return INT_MAX/2-1;
	while(p!=NULL)
		if(p->e==e)
			return p->w;
		else
			p=p->next;
	return INT_MAX/2-1;
}

int Graph::first(int s)
{
	if(s>99)
		return -1;
	if(head[s]==NULL)
		return -1;
	return head[s]->e;
}

int Graph::show()
{
	for(int i=1;i<=99;i++)
		for(int j=1;j<=99;j++)
			if(dist(i,j)!=INT_MAX/2-1)
				cout<<i<<" "<<j<<" "<<dist(i,j)<<endl;
	return 0;
}

bool in[100];
int Graph::dfs(int r)
{
	if(r>99)
		return 1;
	cout<<r<<" ";
	in[r]=true;
	for(int i=1;i<=99;i++)
		if(dist(r,i)!=INT_MAX/2-1 && !in[i])
			dfs(i);
	return 0;
}

int Graph::bfs(int r)
{
	if(r>99)
		return 1;
	queue<int>q;
	q.push(r);
	while(!q.empty())
	{
		cout<<q.front()<<" ";
		for(int i=1;i<=99;i++)
			if(dist(q.front(),i)!=INT_MAX/2-1 && !in[i])
				q.push(i),in[i]=true;
		q.pop();
	}
	return 0;

}
int dis[100][100];
int Graph::lsp()
{
	for(int i=1;i<100;i++)
		for(int j=1;j<100;j++)
			dis[i][j]=dist(i,j);
	for(int i=1;i<100;i++)
		for(int j=1;j<100;j++)
			for(int k=1;k<100;k++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	int ans=0;
	for(int i=1;i<100;i++)
		for(int j=1;j<100;j++)
			if(dis[i][j]!=INT_MAX/2-1 && dis[i][j]>ans)
				ans=dis[i][j];
	return ans;

}

bool Graph::test(int from,int to)
{
  if(from>99 || to>99)
		return false;
  for(int i=1;i<=99;i++)
    in[i]=false;
	queue<int>q;
	q.push(from);
	while(!q.empty())
	{
    if(q.front()==to)
      return true;
		for(int i=1;i<=99;i++)
			if(dist(q.front(),i)!=INT_MAX/2-1 && !in[i])
				q.push(i),in[i]=true;
		q.pop();
	}
	return false;
}

int main()
{
	Graph g;
	string cmd;
	int s,e,w;

	while(cin>>cmd)
	{
		if(cmd=="add")
		{
			int n;
			cin>>n;
			for(int i=1;i<=n;i++)
				cin>>s>>e>>w,g.add(s,e,w);
		}
		if(cmd=="del")
			cin>>s>>e,g.del(s,e);
		if(cmd=="first")
			cin>>s,cout<<g.first(s)<<endl;
		if(cmd=="dist")
			cin>>s>>e,cout<<g.dist(s,e)<<endl;
		if(cmd=="show")
			g.show();
		if(cmd=="dfs")
		{
			for(int i=1;i<=99;i++)
				in[i]=false;
			cin>>s,g.dfs(s);
			cout<<endl;
		}
		if(cmd=="bfs")
		{
			for(int i=1;i<=99;i++)
				in[i]=false;
			cin>>s,g.bfs(s);
			cout<<endl;
		}
		if(cmd=="lsp")
			cout<<g.lsp()<<endl;
    if(cmd=="test")
    {
      cin>>s>>e;
      if(g.test(s,e))
        cout<<"两个节点联通"<<endl;
      else
        cout<<"两个节点不联通"<<endl;
    }
		cout<<"++"<<g.tot<<"++"<<endl;
	}
	return 0;
}
