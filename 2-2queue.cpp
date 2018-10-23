/*
第二周第二题
1)创建链式队列;
2)插入操作:向队尾插入值为 x 的元素;
3)删除操作:删除队首元素;
4)存取操作:读取队首元素。
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
  Node(T dat):data(dat){next=NULL;}
  Node<T>*next;
};

template<typename T>
class Queue
{
  Node<T>*head,*last;
  int len;
public:
  Queue(){head=last=NULL,len=0;}
  int push(T);
  int push_first(T);
  int pop();
  int pop_last();
  vector<T> read();
  bool empty();
  int size();
  int show();
};

template<typename T>
int Queue<T>::push(T dat)
{
  if(empty())
  {
    push_first(dat);
    return 0;
  }
  len++;
  Node<T>*p=new Node<T>(dat);
  last->next=p;
  last=p;
  return 0;
}

template<typename T>
int Queue<T>::push_first(T dat)
{
  if(!empty())
    return 1;
  len++;
  Node<T>*p=new Node<T>(dat);
  head=last=p;
  return 0;
}

template<typename T>
int Queue<T>::pop()
{
  if(empty())
  {
    cout<<"空队列无法执行出队列操作"<<endl;
    return 1;
  }
  if(len==1)
  {
    pop_last();
    return 0;
  }
  len--;
  Node<T>*p=head;
  head=head->next;
  delete p;
  return 0;
}

template<typename T>
int Queue<T>::pop_last()
{
  if(len!=1)
    return 1;
  len--;
  delete head;
  head=last=NULL;
  return 0;
}

template<typename T>
vector<T> Queue<T>::read()
{
  vector<T>v;
  if(empty())
    return v;
  v.push_back(head->data);
  return v;
}

template<typename T>
bool Queue<T>::empty()
{
  if(size()==0)
    return true;
  return false;
}

template<typename T>
int Queue<T>::size()
{
  return len;
}
template<typename T>
int Queue<T>::show()
{
  if(empty())
  {
    cout<<"当前队列为空队列"<<endl;
    return 1;
  }
  Node<T>*p=head;
  while(p!=NULL)
  {
    cout<<p->data<<" ";
    p=p->next;
  }
  cout<<endl;
  return 0;
}

int main()
{
  string cmd;
  class Queue<char>q;
  char t;
  while(cin>>cmd)
  {
    if(cmd=="push")
    {
      cin>>t;
      q.push(t);
    }
    if(cmd=="pop")
    {
      q.pop();
    }
    if(cmd=="read")
    {
      vector<char>v=q.read();
      if(v.empty())
        cout<<"空队列无法执行取栈顶操作"<<endl;
      else
        cout<<"                         "<<v[0]<<endl;
    }
    q.show();
  }
  return 0;
}
