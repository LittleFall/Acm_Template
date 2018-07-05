//rand.cpp 随机数据生成
#include<bits/stdc++.h>
using namespace std;
#define random(a,b) ((a)+rand()*rand()%((b)-(a)+1))
stringstream ss;
int main( int argc, char *argv[] )
{ 
    int seed=time(NULL);
    if(argc)//如果有参数
    {ss.clear();ss<<argv[1];ss>>seed; }
    srand(seed); 

    //以下写你自己的数据生成代码 
    int cnt = 1;
    while(cnt--)
    {
    }
    return 0;
}
