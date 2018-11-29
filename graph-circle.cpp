#include <iostream>
#include <queue>
using namespace std;
bool g[200][200];
int n,e;
bool bfs(int root)
{
	queue<int>q;
	bool in[200];
	for(int i=1;i<=n;i++)
	in[i]=false;
	q.push(root),in[root]=true;
	while(!q.empty())
	{
		for(int i=1;i<=n;i++)
			if(g[q.front()][i])
			{
				if(i==root)
					return true;
				if(!in[i])
					q.push(i),in[i]=true;
			}
		q.pop();
	}
	return false;
}
int main()
{

	int a,b;
	cin>>n>>e;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			g[i][j]=false;
	for(int i=1;i<=e;i++)
		cin>>a>>b,g[a][b]=true;
	for(int i=1;i<=n;i++)
	{
		if(bfs(i))
		{
			cout<<"存在回路"<<endl;
			return 0;
		}
	}
	cout<<"不存在回路"<<endl;
	return 0;
}
