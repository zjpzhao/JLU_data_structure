/*
​4 6
1 2 9
1 4 3
2 3 5
3 1 1
4 3 4
4 2 2
*/
#include <iostream>
using namespace std;
int main()
{
  int n,e,a,b,w;
  cin>>n>>e;
  int dist[n+1][n+1];
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
      dist[i][j]=INT_MAX/2-1;
  for(int i=1;i<=e;i++)
    cin>>a>>b>>w,dist[a][b]=w;

  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
      for(int k=1;k<=n;k++)
        if(dist[i][j]>dist[i][k]+dist[k][j])
          dist[i][j]=dist[i][k]+dist[k][j];
  for(int i=1;i<=n;i++)
  {
    for(int j=1;j<=n;j++)
      cout<<dist[i][j]<<" ";
    cout<<endl;
  }


  return 0;
}
​
