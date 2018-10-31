#include <iostream>
using namespace std;
double freq[300];
int check_freq()
{
  char t;
  int tot=0;
  for(int i=0;i<300;i++)
    freq[i]=0;
  while(t=getchar())
    freq[t]++,tot++;
  for(int i=1;i<300;i++)
    freq[i]/=tot;
  return tot;
}
class Node
{
public:
  char data;
  Node*lrp[2];
  Node(char dat):data(dat){lrp[0]=lrp[1]=NULL;}
};

class Tree
{
  Node *root;
  double cost;
public:
  Tree(char dat){root=new Node(dat),cost=freq[dat];}
  int merge(Tree*);
  double get_cost();
};
inline bool cmp(Tree* a,Tree *b)
{
  return a.cost>b.cost;
}
int main()
{
  vactor<Tree*>
  check_freq();
  for(int i=0;i<300;i++)
    if(freq[i]!=0)
      v.push_back(Tree(char(i)));
  while(v.size()>1)
  {
    sort(v.begin(),v.end(),cmp);
    v[v.size()-2].merge(v.back());
    v.pop_back();
    v.back()->get_cost();
  }
  return 0;
}
