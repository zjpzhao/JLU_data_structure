/*

1
2 3
4 5 6 / 7 8 9
10 11 / / 12


1)创建树和森林;
2)树和森林的先根遍历的递归和迭代算法;
3)树和森林的后根遍历的递归和迭代算法;
4)树和森林的层次遍历算法。

*/
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

template<typename T>
class Node
{
public:
  T data;
  int dep,num_son,nth,num;
  Node<T>*son,*bro;
  Node(T dat,int depth,int n,int number):data(dat),dep(depth),nth(n),num(number){bro=son=NULL;num_son=0;}
};

template<typename T>
class Tree
{
  Node<T>*root;   //根节点深度是1
  int count;     //所有的节点的总数
public:
  Tree(){root=NULL,count=0;}

  int add();   //根据输入新建一棵树(第一棵树的兄弟连着第二棵树,森林都是一棵树)
  int add(T dat);    //添加第一个节点
  int add(Node<T>* father,T dat,int nth);  //插入为最后一个子节点

  int pre_i();  //迭代 iterative
  int post_i();

  int pre_r(Node<T>*); //递归 recursive
  int post_r(Node<T>*);  //遍历森林,传入的要是一个子节点指向root的虚拟节点

  int show_layer();   //按层顺序输出

  Node<T>* go(int dep,int nth);

  Node<T>* root_p();

};

template<typename T>
Node<T>* Tree<T>::root_p()
{
  return root;
}

template<typename T>
int Tree<T>::add(T dat)   //添加第一个节点
{
  count++;
  if(root==NULL&&count==1)
  {
    root=new Node<T>(dat,1,1,count);
    return 0;
  }
  Node<T>*p=root;
  int t=1;
  while(p->bro!=NULL)
    p=p->bro,t++;
  p->bro=new Node<T>(dat,1,t,count);
  return 0;
}


template<typename T>
int Tree<T>::add(Node<T> *father,T dat,int nth)   //添加的都是第二层以上的节点,第一层根节点单独有函数
{
  if(father==NULL)
    return 1;

  count++,father->num_son++;
  Node<T>*p=new Node<T>(dat,father->dep+1,nth,count);
  if(father->son==NULL)
  {
    father->son=p;
    return 0;
  }
  Node<T>*t=father->son;
  while(t->bro!=NULL)
    t=t->bro;
  t->bro=p;
  return 0;
}

template<typename T>
int Tree<T>::add()
{
  int n_depth;
  char dat;
  bool flag;
  cin>>n_depth;
  cin>>dat;
  add(dat);
  for(int i=2;i<=n_depth;i++)
  {
    cout<<i<<"+_+"<<endl;
    flag=false;
    int nth=0,nfa=1;
    while(cin>>dat)
    {
      cout<<dat<<"___"<<endl;
      if(dat=='/')
      {
        nfa++;
        continue;
      }
      if(dat=='|')
      {
        flag=true;
        break;
      }
      nth++;
      Node<T>*p=go(i-1,nfa);
      add(p,dat,nth);
    }
    if(flag)
      continue;
  }
  return 0;
}

template<typename T>
Node<T>* Tree<T>::go(int dep,int nth)
{
  queue<Node<T>*> q;
  q.push(root);
  while(!q.empty())
  {
    if(q.front()->dep==dep && q.front()->nth==nth)
      return q.front();
    Node<T>*p=q.front();
    q.pop();
    if(p->son!=NULL)
    {
      p=p->son;
      while(p!=NULL)
        q.push(p),p=p->bro;
    }
  }
  return NULL;
}

template<typename T>
int Tree<T>::pre_r(Node<T>* p)
{
  if(p==NULL)
    return 1;
  if(count==0)
    return 2;

  cout<<p->data<<" ";
  if(p->son!=NULL)
    p=p->son;
  while(p!=NULL)
    pre_r(p),p=p->bro;
  return 0;
}

template<typename T>
int Tree<T>::post_r(Node<T>* p)
{
  if(p==NULL)
    return 1;
  if(count==0)
    return 2;
  if(p->son!=NULL)
    p=p->son;
  while(p!=NULL)
    post_r(p),p=p->bro;
  cout<<p->data<<" ";
  return 0;
}

template<typename T>
int Tree<T>::pre_i()
{
  if(count==0)
    return 1;   //当前树为空,无法遍历
  vector<Node<T>*>v;
  v.push_back(root);
  while(!v.empty())
  {
    Node<T>* temp=v.back();
    cout<<temp->data<<" ";
    v.pop_back();
    if(temp->son!=NULL)
    {
      temp=temp->son;
      while(temp!=NULL)
        v.push_back(temp),temp=temp->bro;
    }
  }
  return 0;
}

template<typename T>
int Tree<T>::post_i()
{
  if(count==0)
    return 1;  //空树无法输出遍历
  int in[300];
  for(int i=0;i<=count;i++)
    in[i]=0;

  vector<Node<T>*>v;
  v.push_back(root);
  while(!v.empty())
  {
    Node<T>*p=v.back();
    if(p->son==NULL)   //如果没有子节点肯定是要输出的
    {
      cout<<p->data<<" ";
      v.pop_back();
    }
    Node<T>*t=p->son;
    in[p->num]++;

    for(int i=1;i<in[p->num];i++)
      t=t->bro;

    if(t==NULL)
      cout<<p->data<<" ";
    else
    {
      v.pop_back();
      v.push_back(p);
      v.push_back(t);
    }
  }
  return 0;
}

template<typename T>
int Tree<T>::show_layer()
{
  if(count==0)
    return 1;
  queue<Node<T>*>q;
  Node<T>*p=root;
  while(p!=NULL)
    q.push(p),p=p->bro;
  while(!q.empty())
  {
    cout<<q.front()->data<<" ";
    if(q.front()->son!=NULL)
    {
      p=q.front()->son;
      while(p!=NULL)
        q.push(p),p=p->bro;
    }
  }
  return 0;
}

int main()
{
  string s;
  int temp,ret;
  char dat;
  class Tree<char> tree;
  while(cin>>s)
  {
    if(s=="add")
    {
      tree.add();
    }
    if(s=="show")
    {
      cin>>s;
      if(s=="pre")
      {
        tree.pre_i();
        cout<<"_________"<<endl;
        tree.pre_r(tree.root_p());
      }
      if(s=="post")
      {
        tree.post_i();
        tree.post_r(tree.root_p());
      }
      if(s=="layer")
        tree.show_layer();
    }
    cout<<"+_+"<<endl;
  }
  return 0;
}
