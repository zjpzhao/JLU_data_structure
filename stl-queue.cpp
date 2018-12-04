#include <iostream>
#include <queue>
using namespace std;

// int operator + (int a, int b) { return a - b; }

int main()
{
  queue<int>q;
  q.push(3);
  q.push(4);
  q.pop();
  q.front();
  q.back();
  q.empty();
  q.size();


  priority_queue<int,vector<int>,less<int> >pq;  // greater<int>  第一个参数数据类型，第二个储存模板，第三个比较函数
  pq.push(1);
  pq.push(3);
  pq.push(2);
  cout<<pq.top()<<endl;


  return 0;
}
