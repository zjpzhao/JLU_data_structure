/*
1-1
1)创建单链表;
2)插入操作:分别在当前结点后、表头、表尾插入值为 x 的结点;
3)删除操作:分别删除表头结点、表尾结点和当前结点的后继结点;
4)存取操作:分别存取当前结点的值和单链表中第 k 个结点的值;
5)查找操作:查找值为 x 的元素在单链表中出现的位置(是链表中的第几个元素)。
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
  Node(T temp):data(temp){ next=NULL; }
  Node<T> *next;
};

template<typename T>
class List
{
  Node<T> *head;
  Node<T> *curr;
  Node<T> *last;
  int size;
public:
  List()
  {
    head=curr=last=NULL;
    size=0;
  }

  int push_first(T);
  int push_front(T dat);
  int push_back(T dat);
  int push_after_curr(T dat);
  int push_after(T num,T dat); //在某一个特定数后面push,返回push了几个,报错为负

  int pop_last();
  int pop_front();
  int pop_back();
  int pop_after_curr();
  int pop_all(T dat);
  int clear();

  int set_curr(int n);
  int set_curr(Node<T>* p);

  int show();
  int show_curr();
  int length();
  int change_curr(T dat);
  int change_all(T old,T dat);
  int add_curr(T);
  vector<int> search(T dat);

};

template<typename T>
int List<T>::push_first(T dat)
{
  if(size!=0)
    return 1;
  Node<T>*p=new Node<T>(dat);
  head=last=p;
  size=1;
  return 0;
}
template<typename T>
int List<T>::push_front(T dat)
{
  if(size==0)
  {
    push_first(dat);
    return 0;
  }
  size++;
  Node<T>*p=new Node<T>(dat);
  p->next=head;
  head=p;
  return 0;
}

template<typename T>
int List<T>::push_back(T dat)
{
  if(size==0)
  {
    push_first(dat);
    return 0;
  }
  size++;
  Node<T>*p=new Node<T>(dat);
  last->next=p;
  last=p;
  return 0;
}

template<typename T>
int List<T>::push_after_curr(T dat)
{
  if(curr==NULL)
  {
    cout<<"当前curr指针为空"<<endl;
    return 1;
  }
  if(curr==last)
  {
    push_back(dat);
    return 0;
  }
  size++;
  Node<T>*p=new Node<T>(dat);
  p->next=curr->next;
  curr->next=p;
  return 0;
}

template<typename T>
int List<T>::push_after(T num,T dat)
{
  Node<T>*p=head;
  int flag=0;
  while(p!=NULL)
  {
    if(p->data==num)
      if(num==dat&&flag==1)
        flag=0;
      else
      {
        set_curr(p);
        push_after_curr(dat);
        flag=1;
      }
    p=p->next;
  }
  return 0;
}

template<typename T>
int List<T>::pop_last()
{
  if(size!=1)
    return 1;
  delete head;
  head=last=curr=NULL;
  size=0;
  return 0;
}

template<typename T>
int List<T>::pop_front()
{
  if(size<=0)
    return 1;
  if(size==1)
  {
    pop_last();
    return 0;
  }
  size--;
  Node<T>*p=head;
  head=head->next;
  delete p;
  return 0;
}

template<typename T>
int List<T>::pop_back()
{
  if(size<=0)
    return 1;
  if(size==1)
  {
    pop_last();
    return 0;
  }
  size--;
  set_curr(size-1);
  curr->next=NULL;
  delete last;
  last=curr;
  return 0;
}

template<typename T>
int List<T>::pop_after_curr()
{
  if(size==0)
    return 1;
  if(curr==last)
  {
    cout<<"不能删除最后一个节点之后的节点"<<endl;
    return 1;
  }
  size--;
  Node<T>*p=curr->next;
  curr->next=curr->next->next;
  delete p;
  return 0;
}

template<typename T>
int List<T>::pop_all(T dat)
{
  if(size==0)
    return 1;
  if(size==1)
  {
    if(head->data==dat)
      pop_last();
    return 0;
  }
  Node<T>*p=head;
  while(p!=NULL&&p->data==dat)
    pop_front(),p=head;

  while(p!=NULL&&p->next!=NULL)
  {
    if(p->next->data==dat)
    {
      set_curr(p);
      pop_after_curr();
    }
    p=p->next;
  }
  return 0;
}

template<typename T>
int List<T>::clear()
{
  if(size==0)
    return 1;
  while(head!=NULL)
    pop_front();
  return 0;
}

template<typename T>
int List<T>::set_curr(int n)
{
  if(n>size-1)
    return 1;
  curr=head;
  for(int i=1;i<=n;i++)
    curr=curr->next;
  return 0;
}

template<typename T>
int List<T>::set_curr(Node<T>* p)
{
  if(p==NULL)
    return 1;
  curr=p;
  return 0;
}

template<typename T>
int List<T>::show()
{
  if(size==0)
  {
    cout<<"当前为空表"<<endl;
    head=last=curr=NULL;
    return 0;
  }
  cout<<"size:  "<<size<<"   ";
  Node<T>*p=head;
  while(p!=NULL)
  {
    cout<<"["<<p->data<<"]";
    if(p->next!=NULL)
    cout<<"->";
    p=p->next;
  }
  cout<<endl;
  return 0;
}


template<typename T>
int List<T>::show_curr()
{
  if(curr==NULL)
  {
    cout<<"当前curr指针为空"<<endl;
    return 1;
  }
  cout<<curr->data;
  return 0;
}


template<typename T>
int List<T>::change_curr(T dat)
{
  if(curr==NULL)
    return 1;
  curr->data=dat;
  return 0;
}

template<typename T>
int List<T>::change_all(T old,T dat)
{
  if(size==0)
    return 1;
  Node<T>*p=head;
  while(p!=NULL)
  {
    if(p->data==old)
      p->data=dat;
    p=p->next;
  }
  return 0;
}

template<typename T>
int List<T>::add_curr(T dat)   //在curr node 上加一个node,为了第二题的数据合并
{
  if(curr==NULL)
    return 1;
  curr->data=curr->data+dat;
  return 0;
}

template<typename T>
vector<int> List<T>::search(T dat)  //将所有找到的位置装入数组返回
{
  vector<int>v;
  if(size==0)
    return v;
  Node<T>*p=head;
  int count=0;
  while(p!=NULL)
  {
    if(p->data==dat)
      v.push_back(count);
    p=p->next;
    count++;
  }
  return v;
}

template<typename T>
int List<T>::length()
{
  return size;
}

int main()
{
  string s;
  int a,b;
  List<int> l;
  while(cin>>s)
  {
    if(s=="push")
    {
      cin>>s;
      if(s=="front")
      {
        cin>>a;
        l.push_front(a);
      }
      if(s=="back")
      {
        cin>>a;
        l.push_back(a);
      }
      if(s=="curr")
      {
        cin>>a;
        l.push_after_curr(a);
      }
      if(s=="after")
      {
        cin>>a>>b;
        l.push_after(a,b);
      }
    }
    if(s=="pop")
    {
      cin>>s;
      if(s=="front")
      {
        l.pop_front();
      }
      if(s=="back")
      {
        l.pop_back();
      }
      if(s=="curr")
      {
        l.pop_after_curr();
      }
      if(s=="all")
      {
        cin>>a;
        l.pop_all(a);
      }
    }
    if(s=="clear")
    {
      l.clear();
    }
    if(s=="show")
    {
      cin>>s;
      if(s=="curr")
      {
        l.show_curr();
        cout<<endl;
      }
      if(s=="k")
      {
        cin>>a;
        if(a>l.length()-1)
        {
          cout<<"表中没有k位置"<<endl;
          continue;
        }
        l.set_curr(a);
        l.show_curr();
      }
    }
    if(s=="change")
    {
      cin>>s;
      if(s=="curr")
      {
        cin>>a;
        l.change_curr(a);
      }
      if(s=="k")
      {
        cin>>a>>b;
        l.set_curr(a);
        l.change_curr(b);
      }
      if(s=="all")
      {
        cin>>a>>b;
        l.change_all(a,b);
      }
    }
    if(s=="search")
    {
      cin>>a;
      vector<int>v=l.search(a);
      if(v.empty())
        cout<<"并没有在链表中发现 "<<a<<endl;
      else
      {
        cout<<"在";
        for(int i=0;i<v.size();i++)
          cout<<v[i]<<" ";
        cout<<"位置发现了 "<<a<<endl;
      }
    }
    l.show();
  }
  return 0;
}
