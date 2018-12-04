#include <iostream>
#include <vector>
using namespace std;
int main()
{
  vector<int>a;
  vector<int>b(10);
  vector<char>c(5,6);
  vector<char>d(c);

  vector<int>v;
  v.reserve(10);   //预留空间，节省时间，size不变
  cout<<v.size()<<endl;

  v.push_back(9);
  v.push_back(1);
  v.push_back(2);

  //v.pop_back();

  vector<int>::iterator itr=v.begin();
  v.insert(itr+1,1,5);    //在迭代器之后插入n个元素，迭代器可以用做加法移动


  for(int i=0;i<v.size();i++)
    cout<<v[i]<<" ";
  cout<<endl;

  v.erase(itr);

  for(int i=0;i<v.size();i++)
    cout<<v[i]<<" ";
  cout<<endl;
  v.erase(itr,itr+2);   //删除从第一个迭代器开始，到第二个迭代器之前的所有元素，注意野指针

  for(int i=0;i<v.size();i++)
    cout<<v[i]<<" ";
  cout<<endl;

  v.empty();
  v.size();
  v.clear();
  v.front();
  v.back();

  v.begin();
  v.end();
/*
  v.max_size();
  v.capacity();


*/
  return 0;

}
