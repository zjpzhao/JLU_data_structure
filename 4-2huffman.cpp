#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
double freq[300];
string* code[300];
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
  int encode(Node *,string path);
  Node* get_root();
};

Node* Tree::get_root()
{
  return root;
}

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

vector<string> v;
int Tree::encode(Node* p,string path)
{
  cout<<"______"<<endl;
  cout<<p->data<<endl;
  cout<<path<<endl;
  cout<<"______"<<endl;
  if(p==NULL)
    return 1;
  if(p->data!=NULL)
    code[p->data]=new string(path);
  for(int i=0;i<=1;i++)
    if(p->lrp[i]!=NULL)
    {
      path.push_back(48+i);
      encode(p->lrp[i],path);
      path.pop_back();
    }
  path.pop_back();
  return 0;
}

inline bool cmp(Tree* a,Tree *b)
{
  return a->cost > b->cost;
}

inline int compress()
{
  freopen("/Users/davidparker/desktop/text.in","r",stdin);
  freopen("/Users/davidparker/desktop/compressed.out","w",stdout);
  char t;
  while((t=getchar())!=EOF)
  {
    cout<<*code[t];
  }
  fclose(stdin);
  fclose(stdout);
}

inline int decompress(Tree* tree)
{
  freopen("/Users/davidparker/desktop/compressed.out","r",stdin);
  freopen("/Users/davidparker/desktop/decompressed.out","w",stdout);
  char t;
  Node*p=tree->get_root();
  while((t=getchar())!=EOF)
  {
    //cout<<"++"<<t<<"--"<<endl;
    p=p->lrp[t-'0'];
    if(p->data!=NULL)
      cout<<p->data,p=tree->get_root();
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
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
  Tree* tree=v[0];
  string s;
  tree->encode(tree->get_root(),"");

  compress();
  decompress(tree);
  return 0;
}
