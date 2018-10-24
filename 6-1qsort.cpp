/*
实现快速排序算法
理论分析并实验测试算法在最好、最坏及平均情况下的时间复杂性。

1.当分区选取的基准元素为待排序元素中的最大或最小值时，为最坏的情况，时间复杂度和直接插入排序的一样，移动次数达到最大值
Cmax = 1+2+...+(n-1) = n*(n-1)/2 = O(n2) 此时最好时间复杂为O(n2)

2.当分区选取的基准元素为待排序元素中的"中值"，为最好的情况，时间复杂度为O(nlog2n)。
每个区间都要移动元素,移动的个数是整个数组长度的 1/2^n 所以是log级别的复杂度

*/
#include <iostream>
using namespace std;
void qsort(int a[],int low,int high)
{
  if(low>=high)
    return;
  int left=low,right=high,mid=a[low];
  while(left<right)
  {
    while(left<right && a[right]>=mid)
      right--;
    a[left]=a[right];
    while(left<right && a[left]<=mid)
      left++;
    a[right]=a[left];
  }
  a[left]=mid;
  qsort(a,low,left-1);
  qsort(a,right+1,high);
  return;
}
int main()
{
  int n;
  cin>>n;
  int a[100000];
  for(int i=0;i<n;i++)
    cin>>a[i];
  qsort(a,0,n-1);
  for(int i=0;i<n;i++)
    cout<<a[i]<<" ";
  cout<<endl;
  return 0;
}
