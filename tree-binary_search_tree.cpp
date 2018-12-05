#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;


inline int pow(int n)  //前n层有多少节点
{
  if(n<0)
    return 0;
  int t=1;
  for(int i=1;i<=n;i++)
    t*=2;
  return t-1;
}


template<typename T>
class Node
{
public:
  T data;
  Node<T>*lr[2];   //lr[0]左儿子,lr[1]右儿子
  Node<T>*fa;
  int dep,num;
  Node(Node<T>* p,T dat,int depth,int number):fa(p),data(dat),dep(depth),num(number){lr[0]=lr[1]=NULL;}
};


template<typename T>
vector<Node<T>*> vp;

template<typename T>
class Btree
{
  Node<T>*root;
  int count,dep;
public:
  Btree(){root=NULL,count=0,dep=0;}


    bool build();  //根据模拟树形结构输入建树
    bool build_seq();  //根据遍历输入

    Node<T>* add_p(Node<T>*father,int lrt,T dat);  //最基础的add方法,根据指针和左右儿子添加节点
    int add(T dat);

    int pre_order(Node<T>*p);
    int mid_order(Node<T>*p);
    int post_order(Node<T>*p);

    int show();   //树形打印
    int show(Node<T>*p);  //显示该指针指向的数据
    vector<T> path(T dat);
    T lcp(T,T);

    vector<Node<T>*> search(T dat);   //返回所有值相等的节点的指针
    vector<Node<T>*> search(T low,T high);  //返回所有数据在范围内的节点,开区间
    int search(Node<T>*p,T dat);  //递归搜索子函数
    int search(Node<T>*p,T low,T high);

    Node<T>* go(int dep,int nth);   //返回实际该位置的节点的指针,没有为空
    Node<T>* go(int num);           //返回编号为num的节点的指针,没有为空

    Node<T>* get_root();

    int set_dep(int n);
};

//12#45##6##3#7


template<typename T>
bool Btree<T>::build_seq()
{
  cout<<"输入二叉树的带终止符前序遍历"<<endl;
  int dep=0;
  string str;
  vector<Node<T>*>v;
  bool isright=false;
  cin>>str;

  count++;
  root=new Node<T>(NULL,str[0],1,1);
  v.push_back(root);

  for(int i=1;i<str.size();i++)
  {
    dep=dep>v.size()?dep:v.size();
    while(v.back()->lr[1]!=NULL)
      v.pop_back();

    if(str[i]=='#')
    {
      if(isright)
        v.pop_back(),isright=true;
      else
        isright=!isright;
      continue;
    }
    v.push_back(add_p(v.back(),isright,str[i]));
    if(isright)
      isright=!isright;
  }
  set_dep(dep);
  return pow(dep)==count;
}

template<typename T>
int Btree<T>::set_dep(int t)
{
  dep=t;
  return 0;
}

template<typename T>
int Btree<T>::add(T dat)
{
  if(count==0)
  {
    add_p(NULL,0,dat);
    return 0;
  }
  Node<T>*p=root;
  Node<T>*t=NULL;
  while(1)
  {
    if(p==NULL)
      break;
    t=p;
    if(dat<p->data)
      p=p->lr[0];
    else
      p=p->lr[1];
  }
  add_p(t,dat>t->data,dat);
  return 0;
}

template<typename T>
Node<T>* Btree<T>::add_p(Node<T>*father,int lrt,T dat)  //0-l 1-r
{
  if(lrt!=0&&lrt!=1)
    return NULL;  //左右节点指定错误
  if(father==NULL)   //插入根节点
  {
    if(count!=0||root!=NULL)
      return NULL;
    count++;
    root=new Node<T>(NULL,dat,1,1);
    return root;
  }
  if(father->lr[lrt]!=NULL)  //要添加的节点非空
    return NULL;
  count++;
  father->lr[lrt]=new Node<T>(father,dat,father->dep+1,father->num*2+lrt);
  return father->lr[lrt];
}


template<typename T>
int Btree<T>::pre_order(Node<T>*p)
{
  cout<<p->data<<" ";
  for(int i=0;i<=1;i++)
    if(p->lr[i]!=NULL)
      pre_order(p->lr[i]);
  return 0;
}

template<typename T>
int Btree<T>::post_order(Node<T>*p)
{
  for(int i=0;i<=1;i++)
    if(p->lr[i]!=NULL)
      post_order(p->lr[i]);
  cout<<p->data<<" ";
  return 0;
}

template<typename T>
int Btree<T>::mid_order(Node<T>*p)
{
  if(p->lr[0]!=NULL)
    mid_order(p->lr[0]);
  cout<<p->data<<" ";
  if(p->lr[1]!=NULL)
    mid_order(p->lr[1]);
  return 0;
}

template<typename T>
Node<T>* Btree<T>::get_root()
{
  return root;
}

template<typename T>
vector<Node<T>*> Btree<T>::search(T dat)
{
  vp<T>.clear();
  search(root,dat);
  return vp<T>;
}

template<typename T>
int Btree<T>::search(Node<T>*p,T dat)
{
  if(p==NULL)
    return 1;
  if(p->data==dat)
    vp<T>.push_back(p);
  for(int i=0;i<=1;i++)
    if(p->lr[i]!=NULL)
      search(p->lr[i],dat);
  return 0;
}

template<typename T>
vector<T> Btree<T>::path(T dat)
{
  vector<Node<int>*>temp;
  vector<T>v;
  temp=search(dat);
  Node<int>*p=temp[0];
  while(p!=NULL)
    v.push_back(p->data),p=p->fa;
  return v;
}

template<typename T>
T Btree<T>::lcp(T dat1,T dat2)
{
  vector<T>v1,v2;
  v1=path(dat1),v2=path(dat2);
  for(int i=0;i<v1.size();i++)
    cout<<v1[i]<<" ";
  cout<<endl;
  for(int i=0;i<v2.size();i++)
    cout<<v2[i]<<" ";
  cout<<endl;

  for(int i=0;i<v1.size();i++)
    for(int j=0;j<v2.size();j++)
      if(v1[i]==v2[j])
        return v1[i];
}

int main()
{
  string op;
  class Btree<int> tree;
  while(cin>>op)
  {
    if(op=="add")
    {
      int n,t;
      cin>>n;
      for(int i=1;i<=n;i++)
        cin>>t,tree.add(t);
    }
    if(op=="show")
    {
      cin>>op;
      if(op=="pre")
      {
        tree.pre_order(tree.get_root());
        cout<<endl;
      }
      if(op=="mid")
      {
        tree.mid_order(tree.get_root());
        cout<<endl;
      }
      if(op=="post")
      {
        tree.post_order(tree.get_root());
        cout<<endl;
      }
    }
    if(op=="path")
    {
      int t;
      cin>>t;
      vector<int>v=tree.path(t);
      for(int i=v.size()-1;i>0;i--)
        cout<<v[i]<<" ";
      cout<<endl;
    }
    if(op=="lca")
    {
      int t1,t2;
      cin>>t1>>t2;
      cout<<tree.lcp(t1,t2)<<endl;
    }
    cout<<"complete"<<endl;
  }
  return 0;
}
