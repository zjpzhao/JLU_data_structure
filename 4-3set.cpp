#include <iostream>
using namespace std;
int father[300];
int fa(int t)
{
  if(father[t]==t)
    return t;
  return father[t]=fa(father[t]);
}

int main()
{
  for(int i=0;i<=256;i++)
    father[i]=i;
  char t1,t2;
  while(cin>>t1)
  {
    if(t1=='|')
      break;
    while(cin>>t2)
    {
      if(t2=='|')
        break;
      father[fa(t1)]=fa(t2);
    }
  }
  cout<<"集合创建完毕"<<endl;
  string s;
  while(cin>>s)
  {
    if(s=="union")
    {
      cin>>t1>>t2;
      father[fa(t1)]=fa(t2);
    }
    if(s=="search")
    {
      cin>>t1>>t2;
      if(fa(t1)==fa(t2))
        cout<<"true"<<endl;
      else
        cout<<"false"<<endl;
    }
    if(s=="quit")
      break;
    if(s=="show")
    {
      for(int i='a';i<='n';i++)
        cout<<father[i]<<" ";
      cout<<endl;
    }
  }
  return 0;
}
