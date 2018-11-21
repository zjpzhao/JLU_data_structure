/*
实现快速排序算法
理论分析并实验测试算法在最好、最坏及平均情况下的时间复杂性。

1.当分区选取的基准元素为待排序元素中的最大或最小值时，为最坏的情况，时间复杂度和直接插入排序的一样，移动次数达到最大值
Cmax = 1+2+...+(n-1) = n*(n-1)/2 = O(n2) 此时最好时间复杂为O(n2)

2.当分区选取的基准元素为待排序元素中的"中值"，为最好的情况，时间复杂度为O(nlog2n)。
每个区间都要移动元素,移动的个数是整个数组长度的 1/2^n 所以是log级别的复杂度

*/
#include <iostream>
#include <time.h>
#include <chrono>



using namespace std;
int times;
void qsort(int a[],int low,int high)
{
  if(low>=high)
    return;
  int left=low,right=high,mid=a[low];
  while(left<right)
  {
    while(left<right && a[right]>=mid)
      right--,times++;
    a[left]=a[right];
    while(left<right && a[left]<=mid)
      left++,times++;
    a[right]=a[left];
  }
  a[left]=mid;
  qsort(a,low,left-1);
  qsort(a,right+1,high);
  return;
}


int main()
{

  int n,a[900000];
  int tot_times;
  cin>>n;
  freopen("/Users/davidparker/desktop/sort.out","w",stdout);

  for(int k=1;k<=10;k++)
  {
    times=0;
    cout<<"##################################"<<endl;


    for(int i=1;i<=n;i++)
      cout<<(a[i]=( rand()%1000000+10 ) )<<" ";
    cout<<endl;

    cout<<"____________________"<<endl;

    clock_t start=clock();
    qsort(a,0,n-1);
    cout<<"+_+"<<(clock()-double(start))/CLOCKS_PER_SEC<<endl;


    for(int i=1;i<=n;i++)
      cout<<a[i]<<" ";
    cout<<endl;

    tot_times+=times;
    cout<<"共进行  "<<times<<"  次比较"<<endl;


  }

  cout<<endl<<endl<<"平均进行  "<<tot_times/10<<"  次比较"<<endl;
  return 0;
}
