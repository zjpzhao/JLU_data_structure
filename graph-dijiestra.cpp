/*​
6 10 2
1 2 50
1 4 10
2 3 10
2 4 15
3 5 30
4 1 20
4 5 15
5 2 20
5 3 35
6 5 3
http://p.ananas.chaoxing.com/star3/origin/3fa508f9eaddb8d6d2cfbe28ed88705b.png
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Edge
{
  Edge(int a,int b,int ww):s(a),e(b),w(ww){}
  int s,e,w;
};
inline bool cmp(const Edge &a,const Edge &b)
{
  return a.w<b.w;
}
int main()
{
  int n,a,b,w,root,e;
  cin>>n>>e>>root;
  int dist[n+1];
  vector<Edge>v;
  for(int i=1;i<=n;i++)
    dist[i]=0;
  dist[root]=1;

  for(int i=1;i<=e;i++)
    cin>>a>>b>>w,v.push_back(Edge(a,b,w));

  sort(v.begin(),v.end(),cmp); //降序排序

  cout<<"___"<<endl;
  for(int i=0;i<v.size();i++)
    cout<<v[i].s<<" "<<v[i].e<<" "<<v[i].w<<endl;
  cout<<"___"<<endl;

  while(1)
  {
    bool update=false;
    for(int i=0;i<v.size();i++)
      if( dist[v[i].s] != 0 && dist[v[i].e] == 0 )
        cout<<"节点 "<<v[i].e<<" 通过 "<<v[i].s<<" "<<v[i].e<<" 这条边更新最短路径"<<endl,dist[v[i].e]=dist[v[i].s]+v[i].w,update=true;
    if(!update)
      break;
  }
  for(int i=1;i<=n;i++)
    dist[i]-=1;
  for(int i=1;i<=n;i++)
    if(dist[i]==-1)
      cout<<"第 "<<i<<" 节点不联通"<<endl;
    else
      cout<<"第 "<<i<<" 节点最短路径长度为 "<<dist[i]<<endl;
  return 0;
}
