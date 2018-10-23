/*
第二周 第三题 括号匹配
利用循环链表存储表达式,利用栈判断括号是否匹配

不得不吐槽正常括号匹配根本不用存储表达式,这居然还用循环链表存...老师设计题目真是煞费苦心
1、实现循环链表类。
2、创建循环链表s，通过用户逐个字符输入，完成s的初始化。
3、编写程序实现函数Check，并输出检查结果。
4、为增强程序的可读性，对程序中较难理解的语句要有准确、清晰的注释。
5、由教师随机给出测试数据，程序能够反馈括号是否匹配，如果不匹配，指出第一个不匹配所在位置。
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
  int push_back(T dat);
  int show();
  int check(int);
};

template<typename T>
int List<T>::push_first(T dat)
{
  if(size!=0)
    return 1;
  Node<T>*p=new Node<T>(dat);
  head=last=p;
  head->next=head;
  size=1;
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
  last->next=head;
  return 0;
}

template<typename T>
int List<T>::show()
{
  if(size==0)
    return 1;
  Node<T>*p=head;
  while(1)
  {
    cout<<p->data<<" ";
    p=p->next;
    if(p==head)
      break;
  }
  cout<<endl;
  return 0;
}

#define MAX_SIZE 200  //定义最大栈长度

template<typename T>
class Stack
{
  T data[MAX_SIZE];
  int last;
public:
  Stack(){last=-1;}
  int push(T);
  int pop();
  vector<T> top();
  int size();
  bool empty();
  bool full();
  int show();
  T bottom();
};
template<typename T>
int Stack<T>::push(T dat)
{
  if(full())
  {
    cout<<"当前栈已满,pop或者增加栈容量重试"<<endl;
    return 1;
  }
  last++;
  data[last]=dat;
  return 0;
}
template<typename T>
int Stack<T>::pop()
{
  if(empty())
  {
    cout<<"空栈无法执行退栈操作"<<endl;
    return 1;
  }
  last--;
  return 0;
}
template<typename T>
vector<T> Stack<T>::top()
{
  vector<T>v;
  if(empty())
    return v;
  v.push_back(data[last]);
  return v;
}
template<typename T>
int Stack<T>::size()
{
  return last+1;
}
template<typename T>
bool Stack<T>::empty()
{
  if(last==-1)
    return true;
  return false;
}
template<typename T>
bool Stack<T>::full()
{
  if(last==MAX_SIZE)
    return true;
  return false;
}
template<typename T>
int Stack<T>::show()
{
  if(empty())
  {
    cout<<"当前为空栈"<<endl;
    return 0;
  }
  for(int i=0;i<=last;i++)
    cout<<data[i]<<" ";
  cout<<endl;
  return 0;
}

inline bool is_bracket(char c)
{
  if(c=='('||c==')'||c=='['||c==']'||c=='{'||c=='}')
    return true;
  return false;
}

template<typename T>
T Stack<T>::bottom()
{
  return data[0];
}

template<typename T>
int List<T>::check(int n)
{
  class Stack<char>s;
  class Stack<int>pos;

  Node<char>*p=new Node<char>('a');
  p->next=head;
  int count=-1;

  for(int i=1;i<=n;i++)  //读取list里面的每一个字符
  {
    p=p->next;
    count++;
    if(is_bracket(p->data))
    {
      if(s.empty())
      {
        if(p->data==')'||p->data==']'||p->data=='}')
            return count;
        s.push(p->data),pos.push(count);
        continue;
      }
      vector<char>v=s.top();
      char l=v[0],r=p->data;
      if( (l=='('&&r==')') || (l=='['&&r==']') || (l=='{'&&r=='}'))
      {
        s.pop(),pos.pop();
        continue;
      }
      if(p->data==')'||p->data==']'||p->data=='}')
          return pos.top()[0];
      s.push(p->data),pos.push(count);
    }
  }
  if(s.empty())
    return -1;
  else
      return pos.bottom();
}

int main()
{
  class List<char> l;
  string str;
  cin>>str;
  for(int i=0;i<str.size();i++)
    l.push_back(str[i]);
  int t=l.check(str.size());
  if(t==-1)
    cout<<"括号正确匹配"<<endl;
  else
    cout<<"括号在第 "<<t<<" 个位置失配"<<endl;
  return 0;
}
