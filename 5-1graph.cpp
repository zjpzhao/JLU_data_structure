#include <iostream>
#include <string>
using namespace std;
struct Node
{
  int to,wei;
  Node *next;
  Node(int too,int weight):to(too),wei(weight){next=NULL;}
};

struct Graph
{
  int num_node,num_edge;
  Node* head[30];
public:
  Graph(int n):num_node(n)
  {
    num_edge=0;
    for(int i=1;i<=n;i++)
      head[i]=NULL;
  }
  int add(int s,int t,int w);
  Node* get(int s,int t);
  int del(int s,int t);
  int show();
};

int Graph::add(int s,int t,int w)
{
  if(s>num_node)
    return 1;
  Node*p=head[s];
  bool flag=false;
  while(p!=NULL)
  {
    if(p->to==t)
    {
      flag=true;
      continue;
    }
    if(p->next!=NULL)
      break;
    p=p->next;
  }
  if(flag)
    return 2;
  p->next=new Node(t,w);
  return 0;
}
Node* Graph::get(int s,int t)
{
  if(s>num_node)
    return NULL;
  Node*p=head[s];
  while(p!=NULL)
  {
    if(p->to==t)
      return p;
    p=p->next;
  }
  return NULL;
}
int Graph::del(int s,int t)
{
  if(s>num_node)
    return 1;
  Node*p=head[s];
  if(p!=NULL && p->to==t)
  {
    head[s]=p->next,delete p;
    return 0;
  }
  while(p!=NULL && p->next!=NULL && p->next->to==t)
  {
    p->next=p->next->next,delete p->next;
    break;
  }
  return 0;
}
int Graph::show()
{
  for(int i=1;i<=num_node;i++)
  {
    cout<<i<<" :";
    Node*p=head[i];
    while(p!=NULL)
    {
      cout<<"["<<p->to<<" "<<p->wei<<"]"<<" ";
      p=p->next;
    }
  }
  return 0;
}
int main()
{
  int num_node,num_edge,s,t,w;
  cin>>num_node>>num_edge;
  Graph g(num_node);
  for(int i=1;i<=num_edge;i++)
  {
    cin>>s>>t>>w;
    g.add(s,t,w);
  }
  string str;
  cin>>str;
  if(str=="add")
  {
    cin>>s>>t>>w;
    g.add(s,t,w);
  }
  if(str=="show")
  {
    g.show();
  }
  return 0;
}
