#include <iostream>
using namespace std;
inline void swap(int *a,int *b)
{
  *a+=*b,*b=*a-*b,*a=*a-*b;
}
void adj(int num[],int fa,int end)
{
  int son=fa*2;
  while(son<=end)
  {
    if(son+1<=end && num[son+1]>num[son])
      son++;
    if(num[fa]<num[son])
    {
      swap(num+fa,num+son);
      fa=son,son=fa*2;
    }
    else
      return;
  }
}

void heap_sort(int num[],int n)
{
  for(int i=n/2;i>=1;i--)
    adj(num,i,n);
  for(int i=n;i>=2;i--)
  {
    swap(num+1,num+i);
    adj(num,1,i-1);
  }
}
int main()
{
  int n,num[100];
  cin>>n;
  for(int i=1;i<=n;i++)
    cin>>num[i];
  heap_sort(num,n);

  for(int i=1;i<=n;i++)
    cout<<num[i]<<" ";
  cout<<endl;

  return 0;

}
