#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
double freq[300];
int check_freq()
{
  freopen("/Users/davidparker/desktop/text.in","r",stdin);
  char t;
  int tot=0;
  for(int i=0;i<300;i++)
    freq[i]=0;
  while((t=getchar())!=EOF)
    freq[t]++,tot++,cout<<t<<" ";

  for(int i=1;i<300;i++)
    freq[i]/=tot;
  fclose(stdin);
  return tot;
}

class Node
{
public:
  int dep;
  char data;
  Node*lrp[2];
  Node(char dat):data(dat){lrp[0]=lrp[1]=NULL;}
};

class Tree
{
public:
  Node *root;
  double cost;
  Tree(char dat){root=new Node(dat),cost=freq[dat];}
  int merge(Tree*);
  double get_cost();
  int show_pre(Node*);
};

int Tree::merge(Tree*b)
{
  Node*p=new Node(0);
  p->lrp[0]=root;
  p->lrp[1]=b->root;
  root=p;
  return 0;
}

double Tree::get_cost()
{
  queue<Node*>q;
  cost=0,root->dep=0;
  q.push(root);
  while(!q.empty())
  {
    if(q.front()->lrp[0] == NULL && q.front()->lrp[1] == NULL)
      cost+=freq[q.front()->data]*q.front()->dep;
    else
    {
      if(q.front()->lrp[0] != NULL)
        q.front()->lrp[0]->dep=q.front()->dep+1,q.push(q.front()->lrp[0]);
      if(q.front()->lrp[1] != NULL)
        q.front()->lrp[1]->dep=q.front()->dep+1,q.push(q.front()->lrp[1]);
    }
    q.pop();
  }
  return 0;

}

int Tree::show_pre(Node*p)
{
  if(p==NULL)
    return 1;
  cout<<"["<<p->data<<","<<p->dep<<"]"<<endl;
  for(int i=0;i<=1;i++)
    show_pre(p->lrp[i]);
  return 0;
}

inline bool cmp(Tree* a,Tree *b)
{
  return a->cost > b->cost;
}


int main()
{
  vector<Tree*>v;
  check_freq();
  for(int i=0;i<300;i++)
    if(freq[i]!=0)
      v.push_back(new Tree(char(i)));
  while(v.size()>1)
  {
    sort(v.begin(),v.end(),cmp);

    for(int i=0;i<v.size();i++)
      cout<<v[i]->root->data<<" ";
    cout<<"++"<<endl;

    v[v.size()-2]->merge(v.back());
    delete v.back();
    v.pop_back();
    v.back()->get_cost();
  }
  v[0]->show_pre(v[0]->root);
  return 0;
}
