/*
* 1
** 2
*** 5
**** 6 7
*** 8
** 3
** 4
1)创建树和森林;
2)树和森林的先根遍历的递归和迭代算法;
3)树和森林的后根遍历的递归和迭代算法;
4)树和森林的层次遍历算法。

*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template<typename T>
class Node
{
public:
  T data;
  int num,dep,num_son;
  Node<T>*son,*bro;
  Node(T dat,int number,int depth):data(dat),num(number),dep(depth){son=bro=NULL;num_son=0}
};

template<typename T>
class Tree
{
  Node<T>*root;   //根节点是1号节点,深度是1
  int count;
public:
  Tree(){root=NULL,count=0;}

  int build();   //根据缩进表示建树或森林(第一棵树的兄弟连着第二棵树,森林都是一棵树)

  int add_son(int father,T dat);  //插入为最后一个子节点
  int add_bro(int bro,T dat);   //插入为指针指向的节点右边的兄弟
  int add_first(T dat);
  Node<T>* get_p(int num);    //根据唯一编号遍历找到节点的指针
  //int add(Node<T>*father,T dat,int n);  //插入为第n个子节点

  int pre_i();  //迭代 iterative
  int post_i();

  int pre_r(Node<T>*); //递归 recursive
  int post_r(Node<T>*);  //遍历森林,传入的要是一个子节点指向root的虚拟节点

  int show_layer();

};

template<typename T>
int Tree<T>::add_first(T dat)
{
  if(count!=0 || root!=NULL)
    return 1;   //当前森林非空
  count++;
  root=new Node<T>(dat,count,1);
  return 0;
}

template<typename T>
int Tree<T>::add_bro(Node<T>*p,T dat)
{
  if(p==NULL)
    return 1;   //不能在空节点之后添加
  count++;
  Node<T>*t=Node(dat,count,p->dep);
  t->bro=p->bro;
  p->bro=t;
  return 0;
}

template<typename T>
int Tree<T>::add_son(int father,T dat,int n)
{
  if(father>count || father<0)
    return 1;   //指定的父节点不存在
  if(father==0)
  {
    add_first(dat);
    return 0;
  }
  Node<T>*p=get_p(father);
  if(p==NULL)
    return 2;   //未找到标号num的节点
  if(n>p->num_son+1)
    return 3;   //指定的子节点位置不和之前连续,空中楼阁
  count++;
  p->num_son++;
  Node<T>*t=Node(dat,count,p->dep+1);
  if(p->son==NULL)
  {
    p->son=t;
    return 0;
  }
  if(n==1)
  {
    t->bro=p->son;
    p->son=t;
    return 0;
  }
  for(int i=1;i<n;i++)
    p=p->bro;
  t->bro=p->bro;
  p->bro=t;
  return 0;
}

template<typename T>
Node<T>* Tree<T>::get_p(int num)
{
  if(num<=0 || num>count)
    return NULL;  //num不在合法范围
  vector<Node<T>*>v;
  v.push_back(root);
  while(!v.empty())
  {
    Node<T>*temp=v.back();
    if(temp->num==num)
      return temp;
    else
    {
      v.pop_back();
      if(temp->son!=NULL)
      {
        temp=temp->son;
        while(temp!=NULL)
          v.push_back(temp),temp=temp->bro;
      }
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
  whlie(p!=NULL)
    pre_i(p),p=p->bro;
  return 0;
}

template<typename T>
int Tree<T>::pre_r(Node<T>* p)
{
  if(p==NULL)
    return 1;
  if(count==0)
    return 2;
  if(p->son!=NULL)
    p=p->son;
  whlie(p!=NULL)
    pre_i(p),p=p->bro;
  cout<<p->data<<" ";
  return 0;
}

template<typename T>
int Tree<T>::pre_i(Node<T>* p)
{
  if(count==0)
    return 1;   //当前树为空,无法遍历
  vector<Node<T>*>v;
  v.push_back(p);
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
int Tree<T>::post_i(Node<T>*p)
{
  if(count==0)
    return 1;  //空树无法输出遍历
  vctor<Node<T>*>v;
  v.push_back(p);
  while(!v.empty())
}

int main()
{
  string s;
  int temp,ret;
  char dat;
  class Tree<char>tree;
  while(cin>>s)
  {
    if(s=="add")
    {
      cin>>s;
      if(s=="son")
      {
        cin>>temp>>dat;   //给编号为temp的节点插入数据为dat的最后一个子节点
        ret=tree.add_son(temp,dat);

      }
      if(s=="bro")
      {
        cin>>temp>>dat;
        ret=tree.add_bro(temp,dat);   //在编号为temp的节点右面插入一个兄弟节点

      }
    }

  }

}
