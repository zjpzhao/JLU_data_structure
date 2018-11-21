#include <iostream>
#include <time.h>
using namespace std;
int times;
void select_sort(int a[],int n)
{
	int i,j,min;
    for(int i=0;i<n-1;i++)
	{
        min=i;
        for(int j=i+1;j<n;j++)
        {
            if(a[j]<a[min])
                min=j;
            times++;
        }
        if(min!=i)
            swap(a[i],a[min]);
    }
}

int main()
{
  int n,num[900000];
  int tot_times;
  cin>>n;
  freopen("/Users/davidparker/desktop/sort.out","w",stdout);

  for(int k=1;k<=1;k++)
  {
    cout<<"##################################"<<endl;
    times=0;
    for(int i=1;i<=n;i++)
      num[i]=rand()%1000000+10;
    for(int i=1;i<=n;i++)
      cout<<num[i]<<" ";
    cout<<endl;
    cout<<"____________________"<<endl;

    cout<<"+_+"<<clock()<<endl;

    select_sort(num,n);
    cout<<"+_+"<<clock()<<endl;


    for(int i=1;i<=n;i++)
      cout<<num[i]<<" ";
    cout<<endl;
    tot_times+=times;
    cout<<"共进行  "<<times<<"  次比较"<<endl;
  }

  cout<<endl<<endl<<"平均进行  "<<tot_times/10<<"  次比较"<<endl;

  fclose(stdin);
  return 0;

}
