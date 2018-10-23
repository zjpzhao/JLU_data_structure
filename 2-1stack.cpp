/*
第二周 第一题
1)创建顺序栈;
2)插入操作:向栈顶压入值为 x 的元素;
3)删除操作:弹出栈顶元素;
4)存取操作:读取栈顶元素。
*/
#include <iostream>
#include <vector>
#include <string>
#define MAX_SIZE 200  //定义最大栈长度
using namespace std;

template<typename T>
class Stack
{
  T data[MAX_SIZE];
  int last;
public:
  Stack(){last=-1;}
  int push(T);
  int pop();
  vector<T> read();
  int size();
  bool empty();
  bool full();
  int show();
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
vector<T> Stack<T>::read()
{
  vector<T>v;
  if(empty())
  {
    cout<<"空栈无法执行取栈顶操作"<<endl;
    return v;
  }
  cout<<data[last];
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

int main()
{
  class Stack<char> s;
  string cmd;
  while(cin>>cmd)
  {
    if(cmd=="push")
    {
      char dat;
      cin>>dat;
      s.push(dat);
    }
    if(cmd=="pop")
    {
      s.pop();
    }
    if(cmd=="read")
    {
      cout<<"                 ";
      s.read();
      cout<<endl;
    }
    s.show();
  }
  return 0;
}
