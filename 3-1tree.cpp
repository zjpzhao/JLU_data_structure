/*
1)创建一棵二叉树，并对其初始化;
2)先根、中根、后根遍历二叉树;
3)在二叉树中搜索给定结点的父结点;
4)搜索二叉树中符合数据域条件的结点;

根据节点在满二叉树中的位置添加节点,所有的位置都是满二叉树中的位置
*/
#include <iostream>
#include <string>
#include <vector>
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
  Node<T>*lr[2];
  Node<T>*fa;
  int dep,num;
  Node(Node<T>* p,T dat,int depth,int number):fa(p),data(dat),dep(depth),num(number){lr[0]=lr[1]=fa=NULL;}
};

template<typename T>
vector<Node<T>*> vp;


template<typename T>
class Btree
{
  Node<T>*root;
  int count;
public:
  Btree(){root=NULL,count=0;}

  int build();  //根据模拟树形结构输入建树
  int add(Node<T>*father,int lrt,T dat);  //最基础的add方法,根据指针和左右儿子添加节点
  int add(int dep,int nth,T dat);   //根据满二叉树位置添加节点,第几层的第几个

  int del(Node<T>*father);  //最基础的del方法,删除所有给定节点的子节点并修改其父节点指针
  int del(int dep,int nth);  //删除指定满二叉树位置的节点
  int del(T dat);   //删除所有相等的元素
  int del_child(Node<T>*);

  int pre_order(Node<T>*p);
  int mid_order(Node<T>*p);
  int post_order(Node<T>*p);

  int show();   //树形打印
  int show(Node<T>*p);  //显示该指针指向的数据


  vector<Node<T>*> search(T dat);   //返回所有值相等的节点的指针
  vector<Node<T>*> search(T low,T high);  //返回所有数据在范围内的节点
  int search(Node<T>*p,T dat);  //递归搜索子函数
  int search(Node<T>*p,T low,T high);

  Node<T>* go(int dep,int nth);   //返回实际该位置的节点的指针,没有为空
  Node<T>* go(int num);           //返回编号为num的节点的指针
};

template<typename T>
bool Btree<T>::build()   //返回是否是满二叉树 true---是   false---不是
{
  int dep,unused;
  bool flag=true;
  T dat;
  cout<<"输入树的最大深度和一个树中不存在的数"<<endl;
  cin>>dep>>unused;
  for(int i=1;i<=dep;i++)
    for(int j=1;j<=(1<<(i-1));i++)
    {
      cin>>dat;
      if(dat!=unused)
        add(i,j,dat);
      else
        flag=false;
    }
  return flag;
}


template<typename T>
int Btree<T>::add(Node<T>*father,int lrt,T dat)  //0-l 1-r
{
  if(lrt!=0&&lrt!=1)
    return 3;  //左右节点指定错误
  if(father==NULL)   //插入根节点
  {
    if(count!=0||root!=NULL)
      return 1;
    count++;
    Node<T>*p=new Node<T>(NULL,dat,1,1);
    root=p;
    return 0;
  }
  if(father->lr[lrt]!=NULL)  //要添加的节点非空
    return 2;
  count++;
  father->lr[lrt]=new Node<T>(father,dat,father->dep+1,father->num*2+lrt);
  return 0;
}

template<typename T>
int Btree<T>::add(int dep,int nth,T dat)
{
  int num=pow(dep-1)+nth;
  Node<T> *p=go(num/2);
  if(p==NULL)
    return 1;  //指定的位置没有有效父节点,空中楼阁
  add(p,num%2,dat);
  return 0;
}

template<typename T>
int Btree<T>::del_child(Node<T> *p)   //删除给定节点的所有子节点
{
  if(p==NULL)
    return 1;

  p->father->lr[p->num%2]=NULL;
  for(int i=0;i<=1;i++)
    if(p->lr[i]!=NULL)
      del(p->lr[i]);
  for(int i=0;i<=1;i++)
    if(p->lr[i]!=NULL)
      delete p->lr[i],p->lr[i]=NULL,count--;
  return 0;
}

template<typename T>
int Btree<T>::del(Node<T> *p)
{
  if(p==NULL)
    return 1;
  del_child(p);
  if(count==1)
  {
    count--,root=NULL;
    delete p;
  }
  p->father->lr[p->num%2]=NULL;
  delete p,count--;
  return 0;
}

template<typename T>
int Btree<T>::del(T dat)
{
  vector<Node<T>*>v=search(dat);
  for(int i=0;i<v.size();i++)
    del(v[i]);
  return 0;
}

template<typename T>
int Btree<T>::del(int dep,int nth)
{
  Node<T>*p=go(dep,nth);
  if(p==NULL)
    return 1;   //所指定的位置不存在
  del(p);
  return 0;
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
int Btree<T>::show()
{

}

template<typename T>
int Btree<T>::show(Node<T>*p)
{
  if(p==NULL)
    return 1;
  cout<<p->data<<endl;
  return 0;
}

template<typename T>
vector<Node<T>*> Btree<T>::search(T dat)
{
  vp<T>->clear();
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
vector<Node<T>*> Btree<T>::search(T low,T high)
{
  vp<T>->clear();
  search(root,low,high);
  return vp<T>;
}

template<typename T>
int Btree<T>::search(Node<T>*p,T low,T high)
{
  if(p==NULL)
    return 1;
  if(p->data>low && p->data<high)
    vp<T>.push_back(p);
  for(int i=0;i<=1;i++)
    if(p->lr[i]!=NULL)
      search(p->lr[i],low,high);
  return 0;
}

template<typename T>
Node<T>* Btree<T>::go(int num)
{
  if(num<1)
    return NULL;
  if(num==1)
    return root;
  Node<T>*p=go(num/2);
  return p->lr[num%2];
}

template<typename T>
Node<T>* Btree<T>::go(int dep,int nth)
{
  int num=pow(dep-1)+nth;
  return go(num);
}

int main()
{
  cout<<pow(3)<<endl;

}
