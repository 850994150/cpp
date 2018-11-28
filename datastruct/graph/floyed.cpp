#include <iostream>
using namespace std; int main()
{
    int n,m,i,j,k,l,r;
    cout<<"输入结点数和边数\n";
    cin>>n>>m;

    int**s=new int*[n];//确定的是行数
    for(int i=0;i<n;i++)
    {
        s[i]=new int[n];//确定的是列数
    }
    //初始化，将自己与自己的距离置为0，任意两点距离置为99999
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
        {  if(i==j)  s[i][j]=0;
            s[i][j]=99999;
        }
    }

    //Input:
    cout<<"输入结点和两个结点的权值\n";
    for(k=0;k<m;k++)
    {
        cin>>i>>j;
        cin>>s[i][j];
    }

    for (k=0; k<n; k++)
        for (i=0; i<n; i++)
            for (j=0; j<n; j++)
                if (s[i][k] + s[k][j] < s[i][j])
                    s[i][j] = s[i][k] + s[k][j];
    cout<<"输入起始和终止结点"<<endl;
    cin>>l>>r;
    cout<<s[l][r]<<endl;
    return 0;
}
// sample
/*
   10 16
   0 1
   4
   0 2
   1
   1 4
   9
   1 5
   8
   2 4
   6
   2 3
   1
   2 6
   8
   3 5
   4
   3 6
   7
   6 8
   5
   4 7
   5
   4 8
   6
   5 7
   8
   5 8
   6
   7 9
   7
   8 9
   3
   */
