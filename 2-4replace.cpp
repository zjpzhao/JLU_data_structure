/*
第二周 第四题

1. 若S2是S1的子串，用串S3代替串S1中的所有S2,子串(S2在S1中可能 出现 1 次或多次);
2. 若 S2 不是 S1 的字串，用 S3 的逆序列替换 S1 的最后 n 位字符
n 是 S3 中的字符数量。
*/
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main()
{
  string s1,s2,s3;
  cin>>s1>>s2>>s3;
  size_t pos=0;
  bool flag=false;
  while(1)
  {
    pos=s1.find(s2);
    if(pos == string::npos)
      break;
    s1.replace(pos,s2.size(),s3);
    flag=true;
  }
  if(!flag)
  {
    reverse(s3.begin(),s3.end());
    s1.replace(s1.size()-s3.size(),s3.size(),s3);
  }
  cout<<s1<<endl;
  return 0;
}
