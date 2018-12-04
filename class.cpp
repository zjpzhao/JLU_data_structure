#include <iostream>
using namespace std;
class c
{
public:
  c(int t):val(t){}
  int val;
  class c& operator +(class c a)
  {
    val+=a.val;
    return *this;
  }

};
bool operator <(const class c &a,const class c &b)
{
  return a.val<b.val;
}
int main()
{
  class c a(10);
  class c b(20);
  cout<<(a<b)<<endl;
  cout<<(a+b).val<<endl;
  return 0;
}
