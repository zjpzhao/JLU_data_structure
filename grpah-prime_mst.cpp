#include<stdio.h>
#include<string.h>
#include <iostream>
#include <bits/stdc++.h>
#define IO ios::sync_with_stdio(false);\
    cin.tie(0);\
    cout.tie(0);
#define MAX 0x3f3f3f3f
using namespace std;
int logo[1010];//用来标记0和1  表示这个点是否被选择过
int map1[1010][1010];//邻接矩阵用来存储图的信息
int dis[1010];//记录任意一点到这个点的最近距离
int n;//点个数
int prim()
{
    int i,j,now;
    int sum=0;
    /*初始化*/
    for(i=1; i<=n; i++)
    {
        dis[i]=MAX;
        logo[i]=0;
    }
    /*选定1为起始点，初始化*/
    for(i=1; i<=n; i++)
    {
        dis[i]=map1[1][i];
    }
    dis[1]=0;
    logo[1]=1;
    /*循环找最小边，循环n-1次*/
    for(i=1; i<n; i++)
    {
        now=MAX;
        int min1=MAX;
        for(j=1; j<=n; j++)
        {
            if(logo[j]==0&&dis[j]<min1)
            {
                now=j;
                min1=dis[j];
            }
        }
        if(now==MAX)
            break;//防止不成图
        logo[now]=1;
        sum+=min1;
        for(j=1; j<=n; j++)//添入新点后更新最小距离
        {
            if(logo[j]==0&&dis[j]>map1[now][j])
                dis[j]=map1[now][j];
        }
    }
    if(i<n)
        printf("?\n");
    else
        printf("%d\n",sum);
}
int main()
{
    while(scanf("%d",&n),n)//n是点数
    {
        int m=n*(n-1)/2;//m是边数
        memset(map1,0x3f3f3f3f,sizeof(map1));//map是邻接矩阵存储图的信息
        for(int i=0; i<m; i++)
        {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            if(c<map1[a][b])//防止重边
                map1[a][b]=map1[b][a]=c;
        }
        prim();
    }
}
