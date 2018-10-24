/*
1-2
利用第一题的单链表解决多项式想加问题
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
    cout<<"pointer curr remain unset"<<endl;
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
    cout<<"unable to pop after the last node"<<endl;
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
    cout<<"curr pointer remain unset"<<endl;
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




class term   //多项式中的一项
{
public:
  int ratio,power;
  term(int a,int b):ratio(a),power(b){}
  term(){ratio=power=0;}
  bool operator ==(const term &b)   //如果两项指数相等则认为相等,用于链表查找
  {
    if(power==b.power)
      return true;
    return false;
  }
  class term operator + (const term &b)
  {
    ratio+=b.ratio;
    return *this;
  }


};
inline ostream& operator<< (ostream &os, const term &t)
{
  os << t.ratio<<" "<<t.power ;
  return os;
}
int main()
{
  List<term>l;
  int len,a,b;
  cout<<"请输入第一个多项式的长度"<<endl;
  cin>>len;
  cout<<"请两个一组输入第一个多项式的系数和指数,请输入已经合并过的多项式表达式"<<endl;
  for(int i=1;i<=len;i++)
  {
    cin>>a>>b;
    l.push_back(term(a,b));
  }

  cout<<"请输入第二个多项式的长度"<<endl;
  cin>>len;
  cout<<"请两个一组输入第二个多项式的系数和指数,请输入已经合并过的多项式表达式"<<endl;
  for(int i=1;i<=len;i++)
  {
    cin>>a>>b;
    class term temp(a,b);
    vector<int>v=l.search(temp);
    if(v.empty())
      l.push_back(temp);
    else
      l.set_curr(v[0]),l.add_curr(temp);
  }
  for(int i=100;i>=0;i--)
  {
    class term temp(0,i);
    vector<int>v=l.search(temp);
    if(!v.empty())
      l.set_curr(v[0]),l.show_curr(),cout<<" ";
  }
  cout<<endl;
  return 0;
}
