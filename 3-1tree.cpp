/*
1)创建一棵二叉树，并对其初始化;
2)先根、中根、后根遍历二叉树;
3)在二叉树中搜索给定结点的父结点;
4)搜索二叉树中符合数据域条件的结点;

根据节点在满二叉树中的位置添加节点,所有的位置都是满二叉树中的位置
附加题中的判断二叉树是否为满二叉树已经在代码中了,建树时会顺便判断
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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
  int count;
public:
  Btree(){root=NULL,count=0;}

  bool build();  //根据模拟树形结构输入建树
  int add_p(Node<T>*father,int lrt,T dat);  //最基础的add方法,根据指针和左右儿子添加节点
  int add(int dep,int nth,T dat);   //根据满二叉树位置添加节点,第几层的第几个

  int pre_order(Node<T>*p);
  int mid_order(Node<T>*p);
  int post_order(Node<T>*p);

  int show();   //树形打印
  int show(Node<T>*p);  //显示该指针指向的数据


  vector<Node<T>*> search(T dat);   //返回所有值相等的节点的指针
  vector<Node<T>*> search(T low,T high);  //返回所有数据在范围内的节点,开区间
  int search(Node<T>*p,T dat);  //递归搜索子函数
  int search(Node<T>*p,T low,T high);

  Node<T>* go(int dep,int nth);   //返回实际该位置的节点的指针,没有为空
  Node<T>* go(int num);           //返回编号为num的节点的指针,没有为空

  Node<T>* get_root();
};

inline int ith(int n)
{
  return 1<<n;
}
template<typename T>
bool Btree<T>::build()   //返回是否是满二叉树 true---是   false---不是
{
  int dep;
  bool flag=true;  //为满二叉树
  T dat,unused;
  cout<<"输入树的最大深度和一个树中不存在的数据"<<endl;
  cin>>dep>>unused;
  for(int i=1;i<=dep;i++)
    for(int j=1;j<=(1<<(i-1));j++)
    {
      cin>>dat;
      if(dat!=unused)
        add(i,j,dat);
      else
        flag=false;   //不是满二叉树
    }
  cout<<"建树完成,共添加 "<<count<<" 个节点"<<endl;
  cout<<"该树";
  if(!flag)
    cout<<"不";
  cout<<"是满二叉树"<<endl;
  return flag;
}


template<typename T>
int Btree<T>::add_p(Node<T>*father,int lrt,T dat)  //0-l 1-r
{
  if(lrt!=0&&lrt!=1)
    return 3;  //左右节点指定错误
  if(father==NULL)   //插入根节点
  {
    if(count!=0||root!=NULL)
      return 1;
    count++;
    root=new Node<T>(NULL,dat,1,1);
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
  if(dep==1 && nth==1)
  {
    add_p(NULL,0,dat);
    return 0;
  }
  int num=pow(dep-1)+nth;

/*
  cout<<"++++++++++++++++++++++++"<<endl;
  cout<<dep<<" "<<nth<<endl;
  cout<<num<<endl;
  cout<<"++++++++++++++++++++++++"<<endl;
*/
  Node<T> *p=go(num/2);
  if(p==NULL)
    return 1;  //指定的位置没有有效父节点,空中楼阁
  //cout<<"+_+_+_"<<endl;
  add_p(p,num%2,dat);
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
vector<Node<T>*> Btree<T>::search(T low,T high)
{
  vp<T>.clear();
  search(root,low,high);
  return vp<T>;
}

template<typename T>
int Btree<T>::search(Node<T>*p,T low,T high)
{
  if(p==NULL)
    return 1;
  if(p->data>=low && p->data<=high)
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


template<typename T>
Node<T>* Btree<T>::get_root()
{
  return root;
}


inline bool cmp(const Node<char>*a,const Node<char>*b)
{
  return a->num<b->num;
}

int main()
{
  class Btree<char> tree;
  tree.build();
  string s;
  while(cin>>s)
  {
    if(s=="show")
    {
      cin>>s;
      if(s=="pre")
        tree.pre_order(tree.get_root());
      if(s=="mid")
        tree.mid_order(tree.get_root());
      if(s=="post")
        tree.post_order(tree.get_root());
      cout<<endl;
    }
    if(s=="search")
    {
      cin>>s;
      if(s=="father")
      {
        cin>>s;
        if(s=="pos")
        {
          int dep,nth;
          cin>>dep>>nth;
          if(dep==1&&nth==1)
          {
            cout<<"根节点不存在父节点"<<endl;
          }
          int num=pow(dep-1)+nth;
          num=num/2;
          Node<char>*p=tree.go(num);
          if(p==NULL)
          {
            cout<<"指定的节点不存在"<<endl;
            continue;
          }
          else
            cout<<"[ "<<p->num<<" 号 "<<p->data<<" ] "<<endl;
        }

        if(s=="val")
        {
          char val;
          cin>>val;
          vector<Node<char>*> v=tree.search(val);
          if(v.empty())
            cout<<"树中不存在为该值的节点";
          for(int i=0;i<v.size();i++)
            if(v[i]->fa==NULL)
              cout<<" [根节点符合条件但是没有父节点] ";
            else
            {
              int temp=1;
              while(pow(temp)<v[i]->fa->num)
                temp++;
              cout<<" [ 第 "<<temp<<" 行,第 "<<v[i]->fa->num-pow(temp-1)<<" 个节点,数据为 "<<v[i]->fa->data<<" ] "<<endl;
            }
          cout<<endl;
        }
      }
      if(s=="range")
      {
        char low,high;
        cin>>low>>high;
        vector<Node<char>*> v=tree.search(low,high);
        sort(v.begin(),v.end(),cmp);
        for(int i=0;i<v.size();i++)
        {
          int temp=1;
          while(pow(temp)<v[i]->num)
            temp++;
          cout<<" [ 第 "<<temp<<" 行,第 "<<v[i]->num-pow(temp-1)<<" 个节点,数据为 "<<v[i]->data<<" ] "<<endl;
        }
        cout<<endl;
      }
    }
  }

  return 0;

}
